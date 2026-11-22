// LobbyLocale.obj (LobbyDaemon PDB, 2019 + PDB).
#include "LobbyLocale.h"
#include <wchar.h>
#include <wctype.h>

// LIFT: Character tables have no PDB names (0x161450, 0x1615d0, 0x161b80, 0x161bd0).
static const LobbyLocale::ThaiCharType ThaiCharTypes[0x60] =
{
    LobbyLocale::TYPE_NONE, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_FV3, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_FV3, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS,
    LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_CONS, LobbyLocale::TYPE_PUNCT,
    LobbyLocale::TYPE_FV1, LobbyLocale::TYPE_AV2, LobbyLocale::TYPE_FV1, LobbyLocale::TYPE_FV4,
    LobbyLocale::TYPE_AV1, LobbyLocale::TYPE_AV3, LobbyLocale::TYPE_AV2, LobbyLocale::TYPE_AV3,
    LobbyLocale::TYPE_BV1, LobbyLocale::TYPE_BV2, LobbyLocale::TYPE_BD, LobbyLocale::TYPE_NONE,
    LobbyLocale::TYPE_NONE, LobbyLocale::TYPE_NONE, LobbyLocale::TYPE_NONE, LobbyLocale::TYPE_PUNCT,
    LobbyLocale::TYPE_LV, LobbyLocale::TYPE_LV, LobbyLocale::TYPE_LV, LobbyLocale::TYPE_LV,
    LobbyLocale::TYPE_LV, LobbyLocale::TYPE_FV2, LobbyLocale::TYPE_PUNCT, LobbyLocale::TYPE_AD2,
    LobbyLocale::TYPE_TONE, LobbyLocale::TYPE_TONE, LobbyLocale::TYPE_TONE, LobbyLocale::TYPE_TONE,
    LobbyLocale::TYPE_AD1, LobbyLocale::TYPE_AV2, LobbyLocale::TYPE_AV3, LobbyLocale::TYPE_PUNCT,
    LobbyLocale::TYPE_DIGIT, LobbyLocale::TYPE_DIGIT, LobbyLocale::TYPE_DIGIT, LobbyLocale::TYPE_DIGIT,
    LobbyLocale::TYPE_DIGIT, LobbyLocale::TYPE_DIGIT, LobbyLocale::TYPE_DIGIT, LobbyLocale::TYPE_DIGIT,
    LobbyLocale::TYPE_DIGIT, LobbyLocale::TYPE_DIGIT, LobbyLocale::TYPE_PUNCT, LobbyLocale::TYPE_PUNCT,
    LobbyLocale::TYPE_NONE, LobbyLocale::TYPE_NONE, LobbyLocale::TYPE_NONE, LobbyLocale::TYPE_NONE,
};

static const int ThaiCharLevels[LobbyLocale::TYPE_COUNT] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -1, -1, 1, 1, 1, 2, 3, 1, 2,
};

static const LobbyLocale::ThaiCharOp ThaiCharOps[LobbyLocale::TYPE_COUNT][LobbyLocale::TYPE_COUNT] =
{
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::CP, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::CP, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
    {LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::AC, LobbyLocale::CP, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::CP, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ, LobbyLocale::RJ},
};

// One bit per character from U+4E00. A set bit marks an accepted kanji.
static const unsigned long long JapaneseKanji[0x5200 / 64] =
{
    0x9b46244243f36f8bULL, 0x400a0004e3e0e82cULL, 0x04497977db365f65ULL, 0x08c56038c3f0ecd7ULL,
    0x355180003403e602ULL, 0x986982007eabe0c8ULL, 0x8060e8032942a948ULL, 0x4568c03aad93441cULL,
    0x02403f7a8656aa60ULL, 0x2174102014618388ULL, 0x40bc300007022021ULL, 0x0a2060a84462a624ULL,
    0x9c84040285740217ULL, 0x11e27f2414157bfbULL, 0x20ff1f7502efb665ULL, 0x676326c338403a70ULL,
    0x0fc946b020924dd9ULL, 0xa03f86384850bc98ULL, 0x52323e0988162388ULL, 0xc72c00dde3a422aaULL,
    0x8f0a840b26e1a166ULL, 0x89bbc241559e27ebULL, 0x0849636185400014ULL, 0x05cfff3e8ad07f0cULL,
    0x7b407a41a803ff1aULL, 0x38eb050080024745ULL, 0x710c99340005d851ULL, 0x2404636601000397ULL,
    0x430ac000005180d0ULL, 0x5800000830c89071ULL, 0x00415f80f7000e99ULL, 0x62800018941000b0ULL,
    0x0156820009d00240ULL, 0x05101d1008015004ULL, 0x10504025001084c1ULL, 0xa60d40094d8a410fULL,
    0x098121c0914cab19ULL, 0x800006520003c485ULL, 0x0009041d00080b04ULL, 0x16900009905c4849ULL,
    0x2433841222200c65ULL, 0x42250a0447960c03ULL, 0x4f08490090880028ULL, 0x3e87d830d3aa14a2ULL,
    0x41867ea41f618604ULL, 0x211857a505b3c390ULL, 0x4a0411282a48241eULL, 0x88400d60161b0a40ULL,
    0x106082219502020aULL, 0x8000144404000243ULL, 0x700000000c040000ULL, 0x0c00024a00c11a06ULL,
    0x4045140400401a00ULL, 0x052b0a78bdb30029ULL, 0x8379407cbfa0bba9ULL, 0xc5694bf6e81d12fcULL,
    0xff022115044aeff6ULL, 0x0242d033402bed63ULL, 0x59ca1b0200131000ULL, 0x2c41a703020000a0ULL,
    0x000002048ff24880ULL, 0x0048920010055800ULL, 0x3480500420011894ULL, 0x68be49ea684c3200ULL,
    0x21c9a8202e42184cULL, 0xff7c001e80b050b9ULL, 0x01e028c114e0849aULL, 0xdddb130fac49870eULL,
    0x51a2a2e089fbbe1aULL, 0x928b3e4632ca5502ULL, 0x32186703438f1dbfULL, 0xa923081133c03028ULL,
    0x04028fe33a65c000ULL, 0x00a1bf3d86252c4eULL, 0x317c06c98cd43a1aULL, 0x0edb018b950a00e0ULL,
    0xf01011828c20e34bULL, 0x40fbc9aca7287d94ULL, 0x44445a9006534484ULL, 0xf5d4004800013fc8ULL,
    0x891dc442ec577701ULL, 0xd242410949286b83ULL, 0x3a22180059fe061dULL, 0xc0eaf0033b9fb7e4ULL,
    0xe400898082021386ULL, 0x0cc44b8010a1b200ULL, 0x48341faf8944d309ULL, 0x0450420a0c458259ULL,
    0x4450314010c8a040ULL, 0x0540828001004004ULL, 0x1a056a30442c0108ULL, 0x645690cf051420a6ULL,
    0xcbf09c1831000021ULL, 0x01b5104c63e2a120ULL, 0x3281b8b29a83538cULL, 0x0c0233e70a84987aULL,
    0x9070a1a19018d4ccULL, 0x0451c3d4e0048a1eULL, 0x5310484421c2439aULL, 0xf3bd024136400292ULL,
    0xa5d27dc0e8f0ab09ULL, 0xd0afa43fd24bc242ULL, 0x03d8824734a11aa0ULL, 0xc83ad294651bc452ULL,
    0x33140e0640c8001cULL, 0xc0d00088b21b614fULL, 0x166ba1c5a898a02aULL, 0x0604c08b85b42e50ULL,
    0xa251056e1e04f933ULL, 0x73b8ec0776380400ULL, 0xc816408118324406ULL, 0xaa04298063097c8aULL,
    0x27604e0eca9c1c24ULL, 0x8104004683000990ULL, 0x0908540d10816011ULL, 0x0c000500cc0a000eULL,
    0x6784008ba0440430ULL, 0x8b18865e8a195288ULL, 0x9cbe8c1041602e59ULL, 0x00089800891c6861ULL,
    0x41900018089a8100ULL, 0x640d0505e4a14007ULL, 0xff0a48060e4d310eULL, 0x000b852e2aa81632ULL,
    0x696c0e20ca841800ULL, 0x0390565816000032ULL, 0x112480001a285120ULL, 0x0eaa5d52432618e1ULL,
    0x4500fa7bae280fa0ULL, 0xc044c88089406408ULL, 0x24c48424b1419005ULL, 0xc1949000603a1a34ULL,
    0xc106180d003a8246ULL, 0x1511e05099100022ULL, 0x020a041a00824057ULL, 0x444ad8138930004fULL,
    0x400510c0ed228a02ULL, 0x3101880801021000ULL, 0x0708f00002044600ULL, 0x22020000a2008900ULL,
    0x1040004216100200ULL, 0x200052f402605200ULL, 0x4202110082308510ULL, 0x9a2070e180b54308ULL,
    0xfc65350008012040ULL, 0x62140286ab0419c1ULL, 0x0244908500440087ULL, 0x338032070a85405cULL,
    0xc0d0ce20b8c00400ULL, 0x0d2505080080c030ULL, 0x080c020000400a90ULL, 0x4102642140006505ULL,
    0x847c002400000268ULL, 0x40498619de200002ULL, 0x2001008440000808ULL, 0x01c742cd10108400ULL,
    0x1d8f1968d52a7038ULL, 0x81d92ef53e12be50ULL, 0x732e08282412cec4ULL, 0xd41d020c4b3424acULL,
    0x0811009780002a02ULL, 0x7d451786114411c4ULL, 0x87914000064949d9ULL, 0x491444bad8c4254cULL,
    0x15800271c8001b92ULL, 0xc200096a0c000081ULL, 0xba49302140024800ULL, 0x1008e2ac1c802080ULL,
    0x841400e100341004ULL, 0x1014980020000020ULL, 0x5420868804aa70c2ULL, 0x2010918004130c62ULL,
    0x54001c4002064082ULL, 0x84802125e4e90383ULL, 0xe60944c02000e433ULL, 0x080112da81260a03ULL,
    0xf886400197906901ULL, 0xa6510a0e0081e24dULL, 0x8441c60081ec011aULL, 0x8741a46fb62cadb8ULL,
    0x026811614b028d54ULL, 0x043350a02057bb60ULL, 0x01122402b7b4a8c0ULL, 0x00c8227120009ad3ULL,
    0xe1800c8a809e2081ULL, 0x402810318151b009ULL, 0x620e69b689a52a0eULL, 0x4d548085d1444425ULL,
    0x862dd8071fb12c75ULL, 0x226e414e4841d87cULL, 0xed37f80c9e088200ULL, 0x0814931375268c80ULL,
    0x6ea6484ec8040e32ULL, 0xba0126c066702c4aULL, 0x00000000185dd30cULL, 0x0000000000000000ULL,
    0x0540000000000000ULL, 0x03a54f8181337020ULL, 0x2344c318641055ecULL, 0x1a090a4300341462ULL,
    0xa848010213a5187bULL, 0xe2dd8106c5440440ULL, 0x0416b6262d481af0ULL, 0x311280326e405058ULL,
    0x420a82080c0007e4ULL, 0x87134860803b4840ULL, 0xe52903193428850dULL, 0x5c1825a9870a2345ULL,
    0x03e85e00d9c577a6ULL, 0x41c6cd54a7000081ULL, 0x2b0ab860a2042800ULL, 0x0e1a08eada9e0020ULL,
    0x0376890811c0427cULL, 0x18a8000001058621ULL, 0x20220d05c44846a0ULL, 0x28978a0191485422ULL,
    0x3122160500087898ULL, 0x06a2fa4e08804240ULL, 0x9b04200292110814ULL, 0x9010500006432e52ULL,
    0x2020304285ba0041ULL, 0x4080270805a04f0bULL, 0x0600df501a930591ULL, 0x4e8006303021a202ULL,
    0x8001a00404c80cc4ULL, 0x0a020880d4316000ULL, 0x00418e1800281c00ULL, 0x4b00f210ca106ad0ULL,
    0x889002201506274dULL, 0x8150454982a85a00ULL, 0x2c08880480002004ULL, 0x4ac48001000508d1ULL,
    0x0a42008e0062e020ULL, 0xe0a5090e6a8c3055ULL, 0x80b3481442c42906ULL, 0x731c0102b330803eULL,
    0x09400c20600d1494ULL, 0xc094a451c040301aULL, 0xa40c96c205c88dcaULL, 0x011000c834040001ULL,
    0x1c5a2428a9c9550dULL, 0x100f7a4d48370142ULL, 0x9205317b452a32b4ULL, 0x458a68d75c44b894ULL,
    0x420819432ed15097ULL, 0x209798409d40d202ULL, 0x00000000064d5409ULL, 0x0000000000000000ULL,
    0x8480000000000000ULL, 0x17001c0604215542ULL, 0xb9ddff8761107624ULL, 0x3c00245d5c0a659fULL,
    0x000000000059adb0ULL, 0x009b28d000000000ULL, 0x4408010802000422ULL, 0x90288d0aac409804ULL,
    0x00310400e0018700ULL, 0x1054001982211794ULL, 0x40039c02021a2cb2ULL, 0x7900080c88043d60ULL,
    0xcb088640ba3c1628ULL, 0x0000001e90807274ULL, 0x9c87e188d8000000ULL, 0x2791ae6404124034ULL,
    0x5366408fe6fbe86bULL, 0xb5e4e32b537feea6ULL, 0x012285480002869fULL, 0x20a0211608004402ULL,
    0x0005200002040004ULL, 0x01ac162c01547e00ULL, 0x05308c1410852a84ULL, 0x906000cab943fbc3ULL,
    0x8090120040326000ULL, 0x400200544c810b30ULL, 0x028020001d6a0029ULL, 0x150c261000048000ULL,
    0x0c24d94d07018040ULL, 0x5020500118502810ULL, 0x0201708004d01000ULL, 0x0000013221c30108ULL,
    0x0560080207190088ULL, 0xf0a104054c0e0012ULL, 0x0000000000000002ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0080000000000000ULL, 0x5a0421bd035a8e8dULL, 0x0000002611703488ULL,
    0x8804c50210000000ULL, 0x25ed147cf801b815ULL, 0x1bd705891bb0ed60ULL, 0x0ac50d0c1a627af3ULL,
    0x63050490524ae5d1ULL, 0x16122b5752440354ULL, 0x001829491101a872ULL, 0x886c600010080948ULL,
    0x39903012058f916eULL, 0x001b88804930f840ULL, 0x0042850000000000ULL, 0x7014ea0498000058ULL,
    0x60005113611d1628ULL, 0x0000000000a71a24ULL, 0x1018712003c00000ULL, 0x89066004a9270172ULL,
    0x40810900020cc022ULL, 0x00000e348ca0202dULL, 0x1101210000000000ULL, 0x0892ec4cc11a8011ULL,
    0x1806c7ac85000040ULL, 0x001080000512e03eULL, 0x02106d0180ce4008ULL, 0x0027011e08568641ULL,
    0x4e05e032083d3750ULL, 0x01400081048401c0ULL, 0x0000000000000000ULL, 0x00591aa000000000ULL,
    0xc8001d48882443c8ULL, 0x0404901372030152ULL, 0x0d148a1004008280ULL, 0x2704a04002088056ULL,
    0x000000004c000000ULL, 0xa320000000000000ULL, 0xdf002660a0ae1902ULL, 0x3ad081217b15f010ULL,
    0x4800100300284180ULL, 0x00c414cf8014cc00ULL, 0x0000000130202000ULL, 0x0000000000000000ULL,
};

static const bool FrenchChars[192] =
{
    1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
    1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
};

static const bool GermanChars[64] =
{
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
};

static const bool BrazilianPortugueseChars[96] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0,
};

// LIFT: 0x57ab0. The original reads kanji bytes from the shared table byte_140161BD0 (first 0x5200 bytes). The lift uses a bit table.
static __forceinline bool IsJapaneseKanji(wchar_t c)
{
    unsigned int index = c - 0x4e00;
    return index <= 0x51fe && (JapaneseKanji[index / 64] & (1ULL << (index % 64))) != 0;
}

// LIFT: 0x58120. Use the PDB names for the inlined Thai table operations.
// BUG: 0x58159 has a wrong range check.
// LIFT: Safety guard (0x58159). The lift reads the table only inside its bounds. See "Safety differences" in the handoff.
__forceinline LobbyLocale::ThaiCharType LobbyLocale::GetThaiCharType(wchar_t c)
{
    unsigned int index = c - 0x0e00;
    return index < 0x60 ? ThaiCharTypes[index] : TYPE_NONE;
}

#pragma comment(linker, "/INCLUDE:?IsAllowedChar@LobbyLocale@@QEAA_N_W_NPEB_W@Z")  // LIFT: Keep 0x57ab0 until its caller is lifted.
bool LobbyLocale::IsAllowedChar(wchar_t c, bool enableNumericForName, wchar_t const* forbiddenCharactersForName)
{
    if ((c >= L'a' && c <= L'z') || static_cast<unsigned short>(c - L'A') <= 25 ||
        (enableNumericForName && static_cast<unsigned short>(c - L'0') <= 9))
        return true;
    if (forbiddenCharactersForName != nullptr)
    {
        int len = static_cast<int>(wcslen(forbiddenCharactersForName));
        for (int i = 0; i < len; ++i)
            if (c == forbiddenCharactersForName[i])
                return false;
    }
    switch (_language)
    {
    case LANGUAGE_default:
    case LANGUAGE_korean:
        return static_cast<unsigned short>(c - 0xac00) <= 0x2baf;
    case LANGUAGE_japanese:
        if ((c >= 0x3041 && c <= 0x3093) || static_cast<unsigned short>(c - 0x30a1) <= 0x55)
            return true;
        return IsJapaneseKanji(c);
    case LANGUAGE_chineses:
    case LANGUAGE_chineset:
        return static_cast<unsigned short>(c - 0x4e00) <= 0x51ff;
    case LANGUAGE_russian:
        return static_cast<unsigned short>(c - 0x0400) <= 0xff;
    case LANGUAGE_french:
        return c >= 0xc0 && static_cast<unsigned int>(c - 0xc0) < 0xc0 && FrenchChars[c - 0xc0];
    case LANGUAGE_german:
        return c >= 0xc0 && static_cast<unsigned int>(c - 0xc0) < 0x40 && GermanChars[c - 0xc0];
    case LANGUAGE_thai:
        return static_cast<unsigned short>(c - 0x0e01) <= 0x39 ||
               static_cast<unsigned short>(c - 0x0e3f) <= 0x1c;
    case LANGUAGE_vietnamese:
        return IsVietnamese(c);
    case LANGUAGE_bportuguese:
        return c >= 0xa0 && static_cast<unsigned int>(c - 0xa0) < 0x60 && BrazilianPortugueseChars[c - 0xa0];
    default:
        return false;
    }
}

// 0x57d20
__declspec(noinline)  // LIFT: The original calls this function out of line at 0x57eb0.
int LobbyLocale::GetLanguageTypeOfChar(wchar_t c)
{
    if (static_cast<unsigned short>(c - 0xac00) <= 0x2baf)
        return LANGUAGE_korean;
    if ((c >= L'a' && c <= L'z') || static_cast<unsigned short>(c - L'A') <= 25)
        return LANGUAGE_english;
    if (IsVietnamese(c))
        return LANGUAGE_vietnamese;
    if ((c >= 0x3041 && c <= 0x3093) || static_cast<unsigned short>(c - 0x30a1) <= 0x55)
        return LANGUAGE_japanese;
    if (static_cast<unsigned short>(c - 0x4e00) <= 0x51ff)
        return LANGUAGE_chineses;
    if (static_cast<unsigned short>(c - 0x0400) <= 0xff)
        return LANGUAGE_russian;
    if (c >= 0xc0)
    {
        unsigned int index = c - 0xc0;
        if (index < 0xc0 && FrenchChars[index])
            return LANGUAGE_french;
        if (index < 0x40 && GermanChars[index])
            return LANGUAGE_german;
    }
    if (static_cast<unsigned short>(c - 0x0e01) <= 0x39 ||
        static_cast<unsigned short>(c - 0x0e3f) <= 0x1c)
        return LANGUAGE_thai;
    unsigned short index = static_cast<unsigned short>(c - 0xa0);
    if (index < 0x60 && BrazilianPortugueseChars[index])
        return LANGUAGE_bportuguese;
    return LANGUAGE_default;
}

#pragma comment(linker, "/INCLUDE:?IsMonolingualString@LobbyLocale@@SA_NPEB_WHAEBULobbyLocaleSet@@@Z")  // LIFT: Keep 0x57eb0 until its caller is lifted.
bool LobbyLocale::IsMonolingualString(wchar_t const* str, int strLen, LobbyLocaleSet const& lcset)
{
    if (str == nullptr || strLen <= 0)
        return false;
    int i = 0;
    wchar_t const* nextChar = str;
    for (; i < strLen; ++i, ++nextChar)
    {
        wchar_t c = *nextChar;
        if (c == 0)
            return false;
        if ((c < L'0' || c > L'9') && c != L' ')
            break;
    }
    if (i == strLen)
        return false;
    int language = GetLanguageTypeOfChar(*nextChar);
    ++i;
    ++nextChar;
    if (language == LANGUAGE_default)
        return false;
    for (; i < strLen; ++i, ++nextChar)
    {
        wchar_t c = *nextChar;
        if (c == 0)
            return false;
        if ((c < L'0' || c > L'9') && c != L' ')
        {
            int next = GetLanguageTypeOfChar(c);
            if (!lcset.languages[LANGUAGE_vietnamese])
            {
                if (next != language)
                    return false;
            }
            else
            {
                if (language != LANGUAGE_vietnamese && language != LANGUAGE_english)
                    return false;
                if (next != LANGUAGE_vietnamese && next != LANGUAGE_english)
                    return false;
            }
        }
    }
    return true;
}

#pragma comment(linker, "/INCLUDE:?IsSentenceCase@LobbyLocale@@SA_NPEB_WH@Z")  // LIFT: Keep 0x57fc0 until its caller is lifted.
bool LobbyLocale::IsSentenceCase(wchar_t const* str, int strLen)
{
    if (str == nullptr || strLen <= 0)
        return false;
    wchar_t c = *str;
    if (static_cast<unsigned short>(c - 0xac00) <= 0x2baf ||
        static_cast<unsigned short>(c - 0x0e01) <= 0x39 ||
        static_cast<unsigned short>(c - 0x0e3f) <= 0x1c)
        return true;
    if (iswupper(c) == 0)
        return false;
    bool upper = false;
    for (int i = 1; i < strLen; ++i)
    {
        c = *++str;
        if (c == 0)
            return false;
        if (c == L' ')
            upper = true;
        else if ((c < L'0' || c > L'9') && !IsWupperNotApplied(c))
        {
            int valid;
            if (upper)
            {
                upper = false;
                valid = iswupper(c);
            }
            else
                valid = iswlower(c);
            if (valid == 0)
                return false;
        }
    }
    return true;
}

// 0x580e0
__declspec(noinline)  // LIFT: The original calls this function out of line at 0x57fc0.
bool LobbyLocale::IsWupperNotApplied(wchar_t c)
{
    return static_cast<unsigned short>(c - 0xac00) <= 0x2baf ||
           static_cast<unsigned short>(c - 0x0e01) <= 0x39 ||
           static_cast<unsigned short>(c - 0x0e3f) <= 0x1c;
}

// 0x58120
__declspec(noinline)  // LIFT: The original calls this function out of line at 0x584a0.
int LobbyLocale::GetNextThaiCell(wchar_t const* str, int strLen, ThaiCell* cell)
{
    // LIFT: Safety guard (0x58120). The original tests only strLen. The lift also tests str for null.
    if (strLen <= 0 || str == nullptr)
        return 0;
    if (cell != nullptr)
    {
        cell->base = 0;
        cell->hilo = 0;
        cell->top = 0;
    }
    int count = 0;
    ThaiCharType type = GetThaiCharType(*str);
    do
    {
        if (cell != nullptr)
        {
            switch (ThaiCharLevels[type])
            {
            case 0: cell->base = str[count]; break;
            case -1:
            case 1: cell->hilo = str[count]; break;
            case 2: cell->top = str[count]; break;
            case 3:
                if (cell->hilo != 0)
                    cell->top = str[count];
                else
                    cell->hilo = str[count];
                break;
            }
        }
        ++count;
        if (count >= strLen)
            break;
        ThaiCharType previous = type;
        type = GetThaiCharType(str[count]);
        if (ThaiCharOps[previous][type] != CP)
            break;
    } while (true);
    return count;
}

// 0x58260
__declspec(noinline)  // LIFT: The original calls this function out of line at 0x584a0.
LobbyLocale::VietVowelType LobbyLocale::GetVietVowelType(wchar_t ch)
{
    switch (ch)
    {
    case L'A': return VIETVOWEL_TYPE_CAPITAL_LETTER_A;
    case L'E': return VIETVOWEL_TYPE_CAPITAL_LETTER_E;
    case L'I': return VIETVOWEL_TYPE_CAPITAL_LETTER_I;
    case L'O': return VIETVOWEL_TYPE_CAPITAL_LETTER_O;
    case L'U': return VIETVOWEL_TYPE_CAPITAL_LETTER_U;
    case L'Y': return VIETVOWEL_TYPE_CAPITAL_LETTER_Y;
    case L'a': return VIETVOWEL_TYPE_SMALL_LETTER_A;
    case L'e': return VIETVOWEL_TYPE_SMALL_LETTER_E;
    case L'i': return VIETVOWEL_TYPE_SMALL_LETTER_I;
    case L'o': return VIETVOWEL_TYPE_SMALL_LETTER_O;
    case L'u': return VIETVOWEL_TYPE_SMALL_LETTER_U;
    case L'y': return VIETVOWEL_TYPE_SMALL_LETTER_Y;
    case 0x00c2: return VIETVOWEL_TYPE_CAPITAL_LETTER_A_CIRCUMFLEX;
    case 0x00ca: return VIETVOWEL_TYPE_CAPITAL_LETTER_E_CIRCUMFLEX;
    case 0x00d4: return VIETVOWEL_TYPE_CAPITAL_LETTER_O_CIRCUMFLEX;
    case 0x00e2: return VIETVOWEL_TYPE_SMALL_LETTER_A_CIRCUMFLEX;
    case 0x00ea: return VIETVOWEL_TYPE_SMALL_LETTER_E_CIRCUMFLEX;
    case 0x00f4: return VIETVOWEL_TYPE_SMALL_LETTER_O_CIRCUMFLEX;
    case 0x0102: return VIETVOWEL_TYPE_CAPITAL_LETTER_A_BREVE;
    case 0x0103: return VIETVOWEL_TYPE_SMALL_LETTER_A_BREVE;
    case 0x01a0: return VIETVOWEL_TYPE_CAPITAL_LETTER_O_HORN;
    case 0x01a1: return VIETVOWEL_TYPE_SMALL_LETTER_O_HORN;
    case 0x01af: return VIETVOWEL_TYPE_CAPITAL_LETTER_U_HORN;
    case 0x01b0: return VIETVOWEL_TYPE_SMALL_LETTER_U_HORN;
    default: return VIETVOWEL_TYPE_NONE;
    }
}

// 0x58460
__declspec(noinline)  // LIFT: The original calls this function out of line at 0x584a0.
LobbyLocale::VietToneMarkType LobbyLocale::GetVietToneMarkType(wchar_t ch)
{
    switch (ch)
    {
    case 0x0300: return VIETTONEMARK_TYPE_GRAVEACCENT;
    case 0x0301: return VIETTONEMARK_TYPE_ACUTEACCENT;
    case 0x0303: return VIETTONEMARK_TYPE_TILDE;
    case 0x0309: return VIETTONEMARK_TYPE_HOOKABOVE;
    case 0x0323: return VIETTONEMARK_TYPE_DOTBELOW;
    default: return VIETTONEMARK_TYPE_NONE;
    }
}

// LIFT: The PDB names this helper (GetNextVietCell) but gives it no RVA. The original inlines it at 0x58562.
__forceinline int LobbyLocale::GetNextVietCell(wchar_t const* str, int strLen, VietCell* cell)
{
    if (str == nullptr || strLen < 1)
        return 0;
    cell->base = str[0];
    if (GetVietVowelType(str[0]) == VIETVOWEL_TYPE_NONE || strLen < 2 ||
        GetVietToneMarkType(str[1]) == VIETTONEMARK_TYPE_NONE)
        return 1;
    cell->top = str[1];
    return 2;
}

#pragma comment(linker, "/INCLUDE:?GetStringLengthWithCellCombination@LobbyLocale@@SAHPEB_WH@Z")  // LIFT: Keep 0x584a0 until its caller is lifted.
int LobbyLocale::GetStringLengthWithCellCombination(wchar_t const* str, int strLen)
{
    // LIFT: Safety guard (0x584a0). The original reads str[0] before any null test. The lift returns 0 for a null str.
    if (str == nullptr)
        return 0;
    int length = 0;
    ThaiCell cell;
    int count = 0;
    for (int i = 0; i < strLen; i += count)
    {
        int width = 1;
        count = 1;
        wchar_t c = str[i];
        if ((c >= 0x0e01 && c <= 0x0e3a) || (c >= 0x0e3f && c <= 0x0e5b))
        {
            cell.Reset();
            // LIFT: 0x5851a tests str + i before the call (inlined ThaiCell::Reset and the null test of the call site).
            if (str + i == nullptr)
                return length;
            count = GetNextThaiCell(str + i, strLen - i, &cell);
            if (cell.hilo == 0x0e33)
                width = 2;
        }
        else if (IsVietnamese(c))
        {
            // LIFT: 0x58562 inlines the PDB function LobbyLocale::GetNextVietCell.
            VietCell vietCell;
            count = GetNextVietCell(str + i, strLen - i, &vietCell);
        }
        if (count <= 0)
            return length;
        length += width;
    }
    return length;
}

// 0x585d0
__declspec(noinline)  // LIFT: The original calls this function out of line at 0x57d20 and 0x584a0.
bool IsVietnamese(wchar_t ch)
{
    switch (ch)
    {
    case L'A': case L'B': case L'C': case L'D': case L'E': case L'F':
    case L'G': case L'H': case L'I': case L'J': case L'K': case L'L':
    case L'M': case L'N': case L'O': case L'P': case L'Q': case L'R':
    case L'S': case L'T': case L'U': case L'V': case L'W': case L'X':
    case L'Y': case L'Z': case L'a': case L'b': case L'c': case L'd':
    case L'e': case L'f': case L'g': case L'h': case L'i': case L'j':
    case L'k': case L'l': case L'm': case L'n': case L'o': case L'p':
    case L'q': case L'r': case L's': case L't': case L'u': case L'v':
    case L'w': case L'x': case L'y': case L'z': case 0x00c0: case 0x00c1:
    case 0x00c2: case 0x00c3: case 0x00c8: case 0x00c9: case 0x00ca: case 0x00cc:
    case 0x00cd: case 0x00d2: case 0x00d3: case 0x00d4: case 0x00d5: case 0x00d9:
    case 0x00da: case 0x00dd: case 0x00e0: case 0x00e1: case 0x00e2: case 0x00e3:
    case 0x00e8: case 0x00e9: case 0x00ea: case 0x00ec: case 0x00ed: case 0x00f2:
    case 0x00f3: case 0x00f4: case 0x00f5: case 0x00f9: case 0x00fa: case 0x00fd:
    case 0x0102: case 0x0103: case 0x0110: case 0x0111: case 0x0128: case 0x0129:
    case 0x0168: case 0x0169: case 0x01a0: case 0x01a1: case 0x01af: case 0x01b0:
    // BUG: 0x585d0 has 0xaea7, not 0x1ea7. Keep the original set.
    case 0x0300: case 0x0301: case 0x0303: case 0x0309: case 0x0323: case 0xaea7:
    case 0x1ea0: case 0x1ea1: case 0x1ea2: case 0x1ea3: case 0x1ea4: case 0x1ea5:
    case 0x1ea6: case 0x1ea8: case 0x1ea9: case 0x1eaa: case 0x1eab: case 0x1eac:
    case 0x1ead: case 0x1eae: case 0x1eaf: case 0x1eb0: case 0x1eb1: case 0x1eb2:
    case 0x1eb3: case 0x1eb4: case 0x1eb5: case 0x1eb6: case 0x1eb7: case 0x1eb8:
    case 0x1eb9: case 0x1eba: case 0x1ebb: case 0x1ebc: case 0x1ebd: case 0x1ebe:
    case 0x1ebf: case 0x1ec0: case 0x1ec1: case 0x1ec2: case 0x1ec3: case 0x1ec4:
    case 0x1ec5: case 0x1ec6: case 0x1ec7: case 0x1ec8: case 0x1ec9: case 0x1eca:
    case 0x1ecb: case 0x1ecc: case 0x1ecd: case 0x1ece: case 0x1ecf: case 0x1ed0:
    case 0x1ed1: case 0x1ed2: case 0x1ed3: case 0x1ed4: case 0x1ed5: case 0x1ed6:
    case 0x1ed7: case 0x1ed8: case 0x1ed9: case 0x1eda: case 0x1edb: case 0x1edc:
    case 0x1edd: case 0x1ede: case 0x1edf: case 0x1ee0: case 0x1ee1: case 0x1ee2:
    case 0x1ee3: case 0x1ee4: case 0x1ee5: case 0x1ee6: case 0x1ee7: case 0x1ee8:
    case 0x1ee9: case 0x1eea: case 0x1eeb: case 0x1eec: case 0x1eed: case 0x1eee:
    case 0x1eef: case 0x1ef0: case 0x1ef1: case 0x1ef2: case 0x1ef3: case 0x1ef4:
    case 0x1ef5: case 0x1ef6: case 0x1ef7: case 0x1ef8: case 0x1ef9:
        return true;
    default:
        return false;
    }
}
