using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using LegacyBin.Core.Data;
using LegacyBin.Core.Export;
using LegacyBin.Core.Schema;

namespace LegacyBin
{
    /// <summary>
    /// Schema-based view of datafile/localfile: every table with named, typed and resolved fields.
    /// The schema comes from an unpacked client executable or a saved TableDefs folder.
    /// </summary>
    public sealed class SchemaBrowserForm : Form
    {
        Schema schema;
        List<DecodedTable> tables = new List<DecodedTable>();
        RecordDecoder decoder;
        DecodedTable current;
        List<Record> rows = new List<Record>();
        List<string> columns = new List<string>();
        int cachedRow = -1;
        Dictionary<string, string> cachedValues;

        readonly ToolStripStatusLabel status = new ToolStripStatusLabel { Spring = true, TextAlign = ContentAlignment.MiddleLeft };
        readonly TextBox tableFilter = new TextBox { Dock = DockStyle.Top };
        readonly ListBox tableList = new ListBox { Dock = DockStyle.Fill, IntegralHeight = false };
        readonly TextBox rowFilter = new TextBox { Dock = DockStyle.Top };
        readonly DataGridView grid = new DataGridView
        {
            Dock = DockStyle.Fill, VirtualMode = true, ReadOnly = true, AllowUserToAddRows = false,
            AllowUserToDeleteRows = false, RowHeadersWidth = 70, SelectionMode = DataGridViewSelectionMode.CellSelect,
        };
        readonly ToolStripButton btnSchemaExe = new ToolStripButton("Schema from Client.exe…");
        readonly ToolStripButton btnSchemaDir = new ToolStripButton("Schema folder…");
        readonly ToolStripButton btnSaveSchema = new ToolStripButton("Save schema…") { Enabled = false };
        readonly ToolStripButton btnOpen = new ToolStripButton("Open .bin files…") { Enabled = false };
        readonly ToolStripButton btnExport = new ToolStripButton("Export XML…") { Enabled = false };

        public SchemaBrowserForm()
        {
            Text = "LegacyBin – Schema browser";
            Size = new Size(1400, 850);
            StartPosition = FormStartPosition.CenterParent;

            var tools = new ToolStrip();
            tools.Items.AddRange(new ToolStripItem[] { btnSchemaExe, btnSchemaDir, btnSaveSchema, new ToolStripSeparator(), btnOpen, btnExport });
            var strip = new StatusStrip();
            strip.Items.Add(status);
            status.Text = "Step 1: load a schema (unpacked Client.exe / Client64.exe, or a TableDefs folder). Step 2: open datafile + localfile.";

            var split = new SplitContainer { Dock = DockStyle.Fill, SplitterDistance = 300 };
            tableFilter.TextChanged += (s, e) => FillTableList();
            split.Panel1.Controls.Add(tableList);
            split.Panel1.Controls.Add(tableFilter);
            split.Panel2.Controls.Add(grid);
            split.Panel2.Controls.Add(rowFilter);
            SetCue(tableFilter, "filter tables");
            SetCue(rowFilter, "filter rows (any field contains, Enter)");

            Controls.Add(split);
            Controls.Add(tools);
            Controls.Add(strip);

            btnSchemaExe.Click += async (s, e) => await LoadSchemaFromExe();
            btnSchemaDir.Click += (s, e) => LoadSchemaFolder();
            btnSaveSchema.Click += (s, e) => SaveSchema();
            btnOpen.Click += async (s, e) => await OpenBins();
            btnExport.Click += async (s, e) => await ExportXml();
            tableList.SelectedIndexChanged += (s, e) => ShowTable(tableList.SelectedItem as TableItem);
            rowFilter.KeyDown += (s, e) => { if (e.KeyCode == Keys.Enter) { e.SuppressKeyPress = true; ApplyRowFilter(); } };
            grid.CellValueNeeded += Grid_CellValueNeeded;
            grid.RowHeaderMouseDoubleClick += (s, e) => ShowRecord(e.RowIndex);
            UiTheme.Apply(this);
        }

        static void SetCue(TextBox box, string cue)
        {
            const int EM_SETCUEBANNER = 0x1501;
            box.HandleCreated += (s, e) => NativeMethods.SendMessage(box.Handle, EM_SETCUEBANNER, (IntPtr)1, cue);
        }

        static class NativeMethods
        {
            [System.Runtime.InteropServices.DllImport("user32.dll", CharSet = System.Runtime.InteropServices.CharSet.Unicode)]
            public static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wParam, string lParam);
        }

        sealed class TableItem
        {
            public DecodedTable Table;
            public override string ToString() =>
                $"{Table.Name}  [{(Table.Body?.Records.Count ?? 0)}]{(Table.Problem != null ? "  ⚠" : "")}";
        }

        async Task Busy(string what, Func<Task> work)
        {
            UseWaitCursor = true;
            foreach (ToolStripItem i in new ToolStripItem[] { btnSchemaExe, btnSchemaDir, btnOpen, btnExport, btnSaveSchema }) i.Enabled = false;
            status.Text = what + "…";
            try { await work(); }
            catch (Exception ex) { MessageBox.Show(this, ex.Message, what, MessageBoxButtons.OK, MessageBoxIcon.Error); status.Text = what + " failed: " + ex.Message; }
            finally
            {
                UseWaitCursor = false;
                btnSchemaExe.Enabled = btnSchemaDir.Enabled = true;
                btnSaveSchema.Enabled = btnOpen.Enabled = schema != null;
                btnExport.Enabled = tables.Count > 0;
            }
        }

        async Task LoadSchemaFromExe()
        {
            using (var dlg = new OpenFileDialog { Title = "Unpacked client executable", Filter = "Executable (*.exe)|*.exe|All files|*.*" })
            {
                if (dlg.ShowDialog(this) != DialogResult.OK) return;
                await Busy("Reading schema", async () =>
                {
                    schema = await Task.Run(() => SchemaDumper.Dump(dlg.FileName));
                    OnSchemaLoaded();
                });
            }
        }

        void LoadSchemaFolder()
        {
            using (var dlg = new FolderBrowserDialog { Description = "TableDefs folder (one JSON per table)" })
            {
                if (dlg.ShowDialog(this) != DialogResult.OK) return;
                try { schema = SchemaJson.Load(dlg.SelectedPath); OnSchemaLoaded(); }
                catch (Exception ex) { MessageBox.Show(this, ex.Message, "Schema", MessageBoxButtons.OK, MessageBoxIcon.Error); }
                btnSaveSchema.Enabled = btnOpen.Enabled = schema != null;
            }
        }

        void OnSchemaLoaded()
        {
            status.Text = $"Schema: {schema.Source}, {(schema.Is64 ? "64" : "32")}-bit, {schema.Tables.Count} tables. Now open the .bin files.";
            if (tables.Count > 0) Rebind();
        }

        void SaveSchema()
        {
            using (var dlg = new FolderBrowserDialog { Description = "Folder for the TableDefs JSON files" })
            {
                if (dlg.ShowDialog(this) != DialogResult.OK) return;
                SchemaJson.Save(schema, dlg.SelectedPath);
                status.Text = $"Saved {schema.Tables.Count} definitions to {dlg.SelectedPath}";
            }
        }

        List<Datafile> files = new List<Datafile>();

        async Task OpenBins()
        {
            using (var dlg = new OpenFileDialog
            {
                Title = "datafile and localfile (select both so text references resolve)",
                Filter = "Datafiles (*.bin)|*.bin|All files|*.*",
                Multiselect = true,
            })
            {
                if (dlg.ShowDialog(this) != DialogResult.OK) return;
                await Busy("Reading tables", async () =>
                {
                    files = await Task.Run(() => dlg.FileNames.Select(Datafile.Load).ToList());
                    await Task.Run(Rebind);
                    FillTableList();
                });
            }
        }

        void Rebind()
        {
            var bound = new List<DecodedTable>();
            foreach (var df in files) bound.AddRange(RecordDecoder.Bind(schema, df));
            tables = bound.OrderBy(t => t.Name, StringComparer.Ordinal).ToList();
            decoder = new RecordDecoder(schema, files.FirstOrDefault()?.Is64 ?? schema.Is64, tables);
            int bad = tables.Count(t => t.Problem != null);
            string width = files.Any(f => f.Is64 != schema.Is64) ? "  WARNING: schema width does not match the file width." : "";
            BeginInvoke((Action)(() =>
            {
                status.Text = $"{tables.Count} tables, {tables.Sum(t => (long)(t.Body?.Records.Count ?? 0)):N0} records, {bad} without a matching definition.{width}";
                FillTableList();
            }));
        }

        void FillTableList()
        {
            string f = tableFilter.Text.Trim();
            tableList.BeginUpdate();
            tableList.Items.Clear();
            foreach (var t in tables)
                if (f.Length == 0 || t.Name.IndexOf(f, StringComparison.OrdinalIgnoreCase) >= 0)
                    tableList.Items.Add(new TableItem { Table = t });
            tableList.EndUpdate();
        }

        void ShowTable(TableItem item)
        {
            current = item?.Table;
            grid.Rows.Clear();
            grid.Columns.Clear();
            cachedRow = -1;
            if (current?.Body == null) return;
            if (current.Problem != null)
            {
                columns = new List<string> { "raw" };
                status.Text = $"{current.Name}: {current.Problem}";
            }
            else
            {
                columns = new List<string> { "<element>" };
                columns.AddRange(RecordDecoder.Columns(current.Def));
                status.Text = $"{current.Name}: type {current.Raw.Type}, version {current.Raw.Version}, {current.Body.Records.Count:N0} records{(current.Body.Compressed ? ", compressed" : "")}";
            }
            foreach (var c in columns)
                grid.Columns.Add(new DataGridViewTextBoxColumn { Name = c, HeaderText = c, SortMode = DataGridViewColumnSortMode.NotSortable, FillWeight = 1 });
            rows = current.Body.Records;
            grid.RowCount = rows.Count;
        }

        Dictionary<string, string> Values(int row)
        {
            if (row == cachedRow) return cachedValues;
            var r = rows[row];
            var d = new Dictionary<string, string>();
            if (current.Problem != null) d["raw"] = BitConverter.ToString(r.Fixed).Replace("-", "");
            else
            {
                d["<element>"] = RecordDecoder.SubTypeName(current.Def, r) ?? RecordDecoder.ElementName(current.Def, r);
                foreach (var f in decoder.Decode(current, r)) d[f.Name] = f.Value;
            }
            cachedRow = row; cachedValues = d;
            return d;
        }

        void Grid_CellValueNeeded(object sender, DataGridViewCellValueEventArgs e)
        {
            if (current == null || e.RowIndex >= rows.Count) return;
            e.Value = Values(e.RowIndex).TryGetValue(columns[e.ColumnIndex], out var v) ? v : "";
        }

        void ApplyRowFilter()
        {
            if (current?.Body == null) return;
            string f = rowFilter.Text.Trim();
            cachedRow = -1;
            rows = f.Length == 0
                ? current.Body.Records
                : current.Body.Records.Where(r =>
                {
                    if (current.Problem != null) return false;
                    return decoder.Decode(current, r).Any(v => v.Value.IndexOf(f, StringComparison.OrdinalIgnoreCase) >= 0);
                }).ToList();
            grid.RowCount = 0;
            grid.RowCount = rows.Count;
            status.Text = $"{current.Name}: {rows.Count:N0} of {current.Body.Records.Count:N0} records match \"{f}\"";
        }

        void ShowRecord(int row)
        {
            if (row < 0 || row >= rows.Count || current?.Problem != null) return;
            var text = string.Join(Environment.NewLine, decoder.Decode(current, rows[row]).Select(f => $"{f.Name} ({f.Type}) = {f.Value}"));
            using (var f = new Form { Text = $"{current.Name} – record {row}", Size = new Size(700, 800), StartPosition = FormStartPosition.CenterParent })
            {
                f.Controls.Add(new TextBox { Multiline = true, ReadOnly = true, ScrollBars = ScrollBars.Both, Dock = DockStyle.Fill, Text = text, Font = new Font("Consolas", 9f), WordWrap = false });
                f.ShowDialog(this);
            }
        }

        async Task ExportXml()
        {
            using (var dlg = new FolderBrowserDialog { Description = "Output folder (one XML per table)" })
            {
                if (dlg.ShowDialog(this) != DialogResult.OK) return;
                await Busy("Exporting XML", async () =>
                {
                    var progress = new Progress<string>(m => status.Text = m);
                    var st = await Task.Run(() => XmlTableExporter.Export(tables, decoder, dlg.SelectedPath, progress));
                    status.Text = $"Exported {st.Tables} tables ({st.DecodedTables} decoded, {st.RawTables} raw), {st.Records:N0} records to {dlg.SelectedPath}";
                });
            }
        }
    }
}
