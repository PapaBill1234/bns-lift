# IDA batch script for tools/hr_export.py. Do not run it by hand.
# Env: HR_FUNCS (rva, module, name, size per line), HR_OUT (output folder).
import os, traceback
import ida_auto, ida_funcs, ida_hexrays, ida_lines, ida_nalt, ida_pro

out = os.environ["HR_OUT"]
rows = [l.rstrip("\n").split("\t") for l in open(os.environ["HR_FUNCS"])]
ida_auto.auto_wait()
base = ida_nalt.get_imagebase()
ok_hr = ida_hexrays.init_hexrays_plugin()
files, lines, index = {}, {}, []
try:
    for rva, mod, name, size in rows:
        ea = base + int(rva, 16)
        if mod not in files:
            files[mod] = open(os.path.join(out, mod + ".c"), "w")
            lines[mod] = 0
        f = files[mod]
        status = "ok"
        try:
            if not ida_funcs.get_func(ea):
                ida_funcs.add_func(ea)
            text = str(ida_hexrays.decompile(ea)) if ok_hr else None
            if not text:
                raise RuntimeError("no hexrays")
        except Exception as e:
            status = "fail: " + str(e).replace("\t", " ").replace("\n", " ")[:80]
            text = "// decompile failed: " + status
        body = f"// 0x{rva} {name}\n{text}\n\n"
        first = lines[mod] + 1
        f.write(body)
        lines[mod] += body.count("\n")
        index.append(f"{mod}\t0x{rva}\t{name}\t{first}\t{lines[mod]}\t{status}")
finally:
    for f in files.values():
        f.close()
    with open(os.path.join(out, "index.tsv"), "w") as f:
        f.write("\n".join(index) + "\n")
ida_pro.qexit(0)
