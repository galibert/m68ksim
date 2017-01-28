#include "blocks.h"

struct microcode_t {
  u16 val, mask;
  u32 code[16];
};

struct nanocode_t {
  u16 val, mask;
  u32 code[4][3];
};

const struct microcode_t microcode_entry[34] = {
  { 0x000, 0x3f0, { 0x12160, 0x10800, 0x052d0, 0x07cc0, 0x0800c, 0x0800c, 0x08480, 0x118e0, 0x08880, 0x10080, 0x10080, 0x08880, 0x01480, 0x10100, 0x10100, 0x0d300 } },
  { 0x020, 0x3f0, { 0x00004, 0x01580, 0x07060, 0x04a4a, 0x0000c, 0x161a1, 0x0000c, 0x01d00, 0x06940, 0x046a0, 0x00480, 0x10c02, 0x07d80, 0x008e0, 0x05ea0, 0x12702 } },
  { 0x040, 0x3f0, { 0x13a00, 0x00996, 0x05280, 0x161a1, 0x00004, 0x07c20, 0x12ea0, 0x08c20, 0x0af00, 0x1149a, 0x08ca1, 0x00cba, 0x098a0, 0x11497, 0x08021, 0x069c0 } },
  { 0x060, 0x3f0, { 0x00460, 0x09421, 0x169c0, 0x036a0, 0x10004, 0x169c0, 0x00004, 0x01040, 0x008e6, 0x11ca1, 0x000f2, 0x090c0, 0x010a6, 0x11437, 0x001f2, 0x091c0 } },
  { 0x080, 0x3f0, { 0x15201, 0x11041, 0x08004, 0x0987a, 0x00c40, 0x02c60, 0x03400, 0x161a1, 0x0f060, 0x03000, 0x00921, 0x00004, 0x00160, 0x00004, 0x022a0, 0x12e21 } },
  { 0x0a0, 0x3f0, { 0x00460, 0x00004, 0x0f0e0, 0x036a0, 0x05a00, 0x08cba, 0x05a00, 0x11560, 0x0ac60, 0x03180, 0x0ac60, 0x11ce1, 0x00960, 0x08cba, 0x00960, 0x115e0 } },
  { 0x0c0, 0x3f0, { 0x15201, 0x01156, 0x03ea0, 0x0db80, 0x00004, 0x17c20, 0x008e0, 0x11941, 0x00c40, 0x01c12, 0x04a16, 0x05a20, 0x000e0, 0x011e0, 0x04a1a, 0x069c0 } },
  { 0x0e0, 0x3f0, { 0x00422, 0x01580, 0x00004, 0x05a80, 0x0a280, 0x08dc0, 0x00004, 0x000b2, 0x06940, 0x046a0, 0x10008, 0x0d680, 0x07d80, 0x008e0, 0x12a00, 0x0fca0 } },
  { 0x100, 0x3f0, { 0x11941, 0x10502, 0x08540, 0x03f20, 0x14f01, 0x12582, 0x0e9c0, 0x02e80, 0x15701, 0x12502, 0x0e120, 0x00120, 0x14b21, 0x10582, 0x09540, 0x02e00 } },
  { 0x120, 0x3f0, { 0x01500, 0x15721, 0x0a621, 0x12a80, 0x00180, 0x17421, 0x0b280, 0x12a00, 0x05b60, 0x14721, 0x0bd00, 0x0e8e0, 0x057c0, 0x161a1, 0x0aaa1, 0x00000 } },
  { 0x110, 0x3f0, { 0x02216, 0x0e53a, 0x16880, 0x069c0, 0x08486, 0x0e5bb, 0x0f800, 0x05a20, 0x05251, 0x0b7e0, 0x0dec0, 0x04700, 0x07c30, 0x00000, 0x15ec0, 0x00000 } },
  { 0x130, 0x3f0, { 0x07100, 0x0b600, 0x01120, 0x11941, 0x04300, 0x0b680, 0x011a0, 0x133a1, 0x00cba, 0x0b700, 0x001a0, 0x13a81, 0x00000, 0x00000, 0x00000, 0x00000 } },
  { 0x150, 0x3f0, { 0x161a1, 0x03a20, 0x03a20, 0x0222e, 0x0b580, 0x0b2a0, 0x13aa0, 0x00004, 0x161a1, 0x06c00, 0x160e1, 0x160e1, 0x13a01, 0x0e9c0, 0x05b20, 0x13100 } },
  { 0x170, 0x3f0, { 0x10004, 0x00004, 0x009c0, 0x009c0, 0x009c0, 0x018aa, 0x01016, 0x05280, 0x13100, 0x03720, 0x08880, 0x0800c, 0x13081, 0x137a0, 0x13fa1, 0x03080 } },
  { 0x1c0, 0x3f0, { 0x07c40, 0x15721, 0x11500, 0x15721, 0x04680, 0x16061, 0x10180, 0x16161, 0x00000, 0x16161, 0x16da0, 0x143a1, 0x07880, 0x13b01, 0x17d20, 0x126a1 } },
  { 0x1e0, 0x3f0, { 0x01500, 0x17c20, 0x10900, 0x07460, 0x00180, 0x13200, 0x10980, 0x074e0, 0x05b60, 0x11dc0, 0x15f40, 0x02900, 0x057c0, 0x16860, 0x15fc0, 0x02880 } },
  { 0x1d0, 0x3f0, { 0x078a0, 0x15701, 0x15340, 0x15701, 0x00000, 0x13e21, 0x153c0, 0x13621, 0x00000, 0x126a1, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000 } },
  { 0x1f0, 0x3f0, { 0x07100, 0x16960, 0x152a0, 0x05640, 0x04300, 0x11c80, 0x15e40, 0x056c0, 0x00cba, 0x17180, 0x13ba0, 0x07560, 0x00000, 0x156e0, 0x0c7a1, 0x075e0 } },
  { 0x210, 0x3f0, { 0x04a00, 0x00816, 0x00004, 0x01c0e, 0x04200, 0x161a1, 0x04aca, 0x07060, 0x04b01, 0x13080, 0x0db00, 0x0000c, 0x0cb80, 0x0000c, 0x0187a, 0x0987a } },
  { 0x230, 0x3f0, { 0x15e01, 0x009c0, 0x15e01, 0x00004, 0x04e80, 0x01d60, 0x1a300, 0x0653a, 0x00004, 0x009c0, 0x00004, 0x161a1, 0x0cf81, 0x10004, 0x0f920, 0x0c321 } },
  { 0x250, 0x3f0, { 0x00060, 0x114a1, 0x06d06, 0x00004, 0x04200, 0x17c20, 0x14e20, 0x07080, 0x10004, 0x05320, 0x05b20, 0x00004, 0x04ba0, 0x00004, 0x04ba0, 0x04ba0 } },
  { 0x270, 0x3f0, { 0x14e20, 0x0d620, 0x0fc21, 0x14e20, 0x14e40, 0x17c20, 0x05e80, 0x0653a, 0x00004, 0x14721, 0x00004, 0x004e1, 0x14fa0, 0x00004, 0x05fa0, 0x05f60 } },
  { 0x290, 0x3f0, { 0x04a40, 0x05216, 0x06420, 0x04620, 0x04ac0, 0x052e0, 0x057b0, 0x05e40, 0x02800, 0x169c1, 0x0e520, 0x161a1, 0x02980, 0x169a1, 0x0f1a0, 0x17da1 } },
  { 0x2b0, 0x3f0, { 0x046a0, 0x04e20, 0x00d02, 0x17c20, 0x008e0, 0x06180, 0x00d82, 0x12380, 0x169c1, 0x10008, 0x0e120, 0x16940, 0x12ba1, 0x17c20, 0x0dbe0, 0x15740 } },
  { 0x2d0, 0x3f0, { 0x05216, 0x114e1, 0x04206, 0x05a06, 0x052e0, 0x114e1, 0x06dc6, 0x05a86, 0x11941, 0x16940, 0x15b60, 0x0fc21, 0x14b21, 0x15740, 0x157c0, 0x0c321 } },
  { 0x2f0, 0x3f0, { 0x0653a, 0x114a1, 0x16900, 0x169c1, 0x0e5ba, 0x114a1, 0x156a0, 0x169a1, 0x17921, 0x0df80, 0x08c81, 0x15fe0, 0x15781, 0x0c780, 0x0e921, 0x16000 } },
  { 0x300, 0x3f0, { 0x13380, 0x06c00, 0x05e40, 0x17c20, 0x069c0, 0x11920, 0x00004, 0x06400, 0x008a6, 0x07c20, 0x07c20, 0x14ec0, 0x0e981, 0x0e920, 0x12a00, 0x16d00 } },
  { 0x320, 0x3f0, { 0x06c00, 0x02c60, 0x00cba, 0x00cba, 0x069c0, 0x17480, 0x01d80, 0x00004, 0x161a1, 0x0f500, 0x0ac61, 0x17580, 0x161a0, 0x0428a, 0x0ac61, 0x0e120 } },
  { 0x340, 0x3f0, { 0x009c0, 0x17021, 0x00004, 0x060a0, 0x0fc20, 0x170a1, 0x00004, 0x07060, 0x0fc20, 0x10004, 0x0f920, 0x08004, 0x00004, 0x0e9c0, 0x0f9a0, 0x0e520 } },
  { 0x360, 0x3f0, { 0x09de0, 0x00004, 0x00004, 0x161a1, 0x00000, 0x00000, 0x00000, 0x0b300, 0x0f521, 0x0004a, 0x10004, 0x0e5a0, 0x0eda0, 0x0f5a1, 0x0fc20, 0x00004 } },
  { 0x380, 0x3f0, { 0x119a7, 0x17841, 0x17841, 0x05a06, 0x11967, 0x178c1, 0x178c1, 0x05a86, 0x16940, 0x0fc20, 0x16940, 0x17921, 0x17d80, 0x08004, 0x17d80, 0x17121 } },
  { 0x3a0, 0x3f0, { 0x17c00, 0x16481, 0x07c81, 0x07060, 0x15380, 0x16021, 0x05f20, 0x07170, 0x0653a, 0x0f540, 0x08c81, 0x08c80, 0x0e5ba, 0x0f5c0, 0x0e921, 0x0e921 } },
  { 0x3c0, 0x3f0, { 0x053a0, 0x11920, 0x0e420, 0x161a1, 0x0041e, 0x0f000, 0x08140, 0x16081, 0x05ba0, 0x17400, 0x09440, 0x16c21, 0x00000, 0x00000, 0x00000, 0x00000 } },
  { 0x3e0, 0x3f0, { 0x14f40, 0x00000, 0x12402, 0x14e01, 0x14fc0, 0x00000, 0x12482, 0x11ce1, 0x04660, 0x0424a, 0x12602, 0x115a1, 0x0c6e0, 0x042ca, 0x12682, 0x11521 } },
};

const struct nanocode_t nanocode_entry[84] = {
  { 0x000, 0x3fc, { { 0x0, 0x00010000, 0x00000000 }, { 0x0, 0x00010000, 0x00000000 }, { 0x0, 0x00010000, 0x00000000 }, { 0x8, 0x25000398, 0x10000000 } } },
  { 0x020, 0x3fc, { { 0x8, 0x532200e5, 0x08418425 }, { 0x0, 0x008c400a, 0x01000002 }, { 0x0, 0x20062f89, 0x4c018084 }, { 0xc, 0x08280211, 0x00018044 } } },
  { 0x004, 0x3fc, { { 0x9, 0x26020058, 0x12218084 }, { 0x9, 0x24024018, 0x10140180 }, { 0x0, 0xa1010028, 0x02218004 }, { 0x8, 0xa0020088, 0x10000083 } } },
  { 0x024, 0x3fc, { { 0x0, 0x08010000, 0x62000680 }, { 0x8, 0xa0020008, 0x10000000 }, { 0x9, 0x240a4018, 0x10140180 }, { 0x0, 0x00010000, 0x00210014 } } },
  { 0x008, 0x3f8, { { 0x0, 0x80028000, 0x00218084 }, { 0x1, 0x8b00c022, 0x60100682 }, { 0x1, 0x8980c022, 0x60100682 }, { 0x0, 0xa0020008, 0x00218084 } } },
  { 0x028, 0x3f8, { { 0x0, 0x008c400a, 0x01218046 }, { 0x0, 0x004c8001, 0x49000000 }, { 0x9, 0x240a4018, 0x12218004 }, { 0x1, 0xa04c0009, 0x00400000 } } },
  { 0x040, 0x3fc, { { 0x8, 0xa0010008, 0x10120048 }, { 0x0, 0x01110060, 0x00038044 }, { 0x0, 0x00010062, 0x00020048 }, { 0x8, 0xb6022059, 0x98000000 } } },
  { 0x060, 0x3fc, { { 0x0, 0x00010000, 0x0082002c }, { 0x1, 0x80800002, 0x00104800 }, { 0x5, 0x0b000060, 0x441200ae }, { 0xc, 0x08280211, 0x00858044 } } },
  { 0x044, 0x3fc, { { 0x0, 0x08212081, 0x00000345 }, { 0x8, 0x20020088, 0x10000001 }, { 0x9, 0x24024018, 0x58098004 }, { 0x0, 0xc102a024, 0x085000c8 } } },
  { 0x064, 0x3fc, { { 0x8, 0xa0020088, 0x10000083 }, { 0x5, 0x0b000060, 0x441200ca }, { 0x8, 0x360200d9, 0x90000083 }, { 0x8, 0x40028004, 0x10400392 } } },
  { 0x048, 0x3f8, { { 0x0, 0x80068000, 0x00280080 }, { 0x8, 0xa0020019, 0x10418044 }, { 0x0, 0xc101a024, 0x0a140080 }, { 0x0, 0x0300c560, 0x00000082 } } },
  { 0x068, 0x3f8, { { 0x4, 0x088c0002, 0x44100000 }, { 0x1, 0x80010380, 0x00280308 }, { 0x8, 0x20020009, 0x5808038a }, { 0x0, 0xa008c008, 0x02000000 } } },
  { 0x080, 0x3fc, { { 0x8, 0xb0220058, 0x10498010 }, { 0x8, 0xc0028004, 0x1028038a }, { 0x0, 0x830100e0, 0x02024b45 }, { 0x0, 0x81068521, 0x40000800 } } },
  { 0x0a0, 0x3fc, { { 0x0, 0x00010000, 0x00820028 }, { 0x0, 0x10212081, 0x00420345 }, { 0x4, 0x88228481, 0x0001c804 }, { 0xc, 0x08280211, 0x00018044 } } },
  { 0x084, 0x3f4, { { 0x0, 0x08212001, 0x00080308 }, { 0x8, 0x20020088, 0x10000001 }, { 0x0, 0x41028024, 0x02000080 }, { 0x8, 0xc0028005, 0x50100048 } } },
  { 0x0a4, 0x3f4, { { 0x0, 0x0421c009, 0x08298144 }, { 0x0, 0x80028501, 0x40000800 }, { 0x0, 0x0421c009, 0x48098144 }, { 0x0, 0x9022a001, 0x00200080 } } },
  { 0x088, 0x3fc, { { 0x4, 0x960685d1, 0x8401c805 }, { 0x4, 0x2c042019, 0x4c018004 }, { 0x0, 0x00010000, 0x00030048 }, { 0x8, 0x20020089, 0xb8400083 } } },
  { 0x0a8, 0x3fc, { { 0x5, 0x888c0200, 0x44004800 }, { 0x0, 0x24046019, 0x08018004 }, { 0x5, 0x888c0002, 0x44104800 }, { 0x1, 0xcb01c000, 0x60000600 } } },
  { 0x0c0, 0x3fc, { { 0x8, 0xa0020008, 0x10498018 }, { 0x0, 0x01110060, 0x00038044 }, { 0x0, 0x08210001, 0x0081010c }, { 0x0, 0x81068021, 0x40000800 } } },
  { 0x0e0, 0x3fc, { { 0xc, 0x000e8050, 0x84418030 }, { 0x0, 0x200c400a, 0x01000002 }, { 0x8, 0x40028084, 0x10000083 }, { 0x8, 0x20060388, 0x10000000 } } },
  { 0x0c4, 0x3fc, { { 0x0, 0x00010081, 0x88420345 }, { 0x0, 0x80028000, 0x00000082 }, { 0x8, 0x20020088, 0x10000001 }, { 0x8, 0xc0028004, 0x10000000 } } },
  { 0x0e4, 0x3fc, { { 0x0, 0x00068000, 0x00000000 }, { 0x0, 0x88228001, 0x00000800 }, { 0x0, 0x00010080, 0x000000d7 }, { 0x8, 0x20020009, 0x58098086 } } },
  { 0x0c8, 0x3f8, { { 0x0, 0x00010000, 0x00400310 }, { 0x0, 0x00010000, 0x00030048 }, { 0x0, 0x06210023, 0x00850008 }, { 0x0, 0x03000060, 0x0041808a } } },
  { 0x0e8, 0x3f8, { { 0x0, 0x200c400a, 0x01218046 }, { 0x0, 0x080ca001, 0x49000000 }, { 0x8, 0xc4228005, 0x98200082 }, { 0x0, 0x84448410, 0x0003c804 } } },
  { 0x100, 0x3f0, { { 0x1, 0x8001c00b, 0x40000048 }, { 0x1, 0xa04ce009, 0x08400000 }, { 0x0, 0xc622a007, 0x08000800 }, { 0x0, 0x280ec008, 0x60140600 } } },
  { 0x120, 0x3f0, { { 0x0, 0x008c450a, 0x01000082 }, { 0x8, 0xcc02a015, 0x58018044 }, { 0x0, 0xa0082008, 0x0a218084 }, { 0x0, 0x80028601, 0x00200082 } } },
  { 0x110, 0x3f0, { { 0x0, 0x00010000, 0x00000000 }, { 0x0, 0xa102c52a, 0x00000080 }, { 0x0, 0x84228001, 0x00200080 }, { 0x0, 0x03000060, 0x004080ae } } },
  { 0x130, 0x3f0, { { 0x0, 0x008c450a, 0x01000082 }, { 0x1, 0x10016000, 0x8a218004 }, { 0x0, 0x200e2008, 0x0a000080 }, { 0x8, 0xc0028005, 0x58010048 } } },
  { 0x150, 0x3fc, { { 0x8, 0xc0028004, 0x10000000 }, { 0x0, 0x00068000, 0x40180048 }, { 0x0, 0x00068008, 0x40080048 }, { 0x8, 0x40028004, 0x10038044 } } },
  { 0x170, 0x3fc, { { 0x8, 0xb0024088, 0x905000cb }, { 0x0, 0x08210081, 0x000004af }, { 0x0, 0x20112002, 0x000200ae }, { 0x0, 0x28312003, 0x000000ae } } },
  { 0x154, 0x3fc, { { 0x1, 0x46018054, 0x00280080 }, { 0x0, 0x80028000, 0x00100180 }, { 0x8, 0xb0024008, 0x90500048 }, { 0x0, 0x00010080, 0x000204af } } },
  { 0x174, 0x3fc, { { 0x0, 0x26312003, 0x000000ae }, { 0x0, 0x0302c060, 0x0003800e }, { 0x0, 0x00010001, 0x40010008 }, { 0x0, 0x00010022, 0x00820048 } } },
  { 0x158, 0x3fc, { { 0x8, 0xd0428005, 0x90200000 }, { 0x0, 0x00068601, 0x00200000 }, { 0x1, 0x04004210, 0x40190144 }, { 0x1, 0x04004218, 0x40090144 } } },
  { 0x178, 0x3fc, { { 0x1, 0xa444e019, 0x08200002 }, { 0x0, 0x20040008, 0x00218004 }, { 0x0, 0xc0028004, 0x00000080 }, { 0x9, 0x34006018, 0x9a038084 } } },
  { 0x158, 0x3f8, { { 0x8, 0xd0428005, 0x90200000 }, { 0x0, 0x00068601, 0x00200000 }, { 0x1, 0x04004210, 0x40190144 }, { 0x1, 0x04004218, 0x40090144 } } },
  { 0x178, 0x3f8, { { 0x1, 0xa444e019, 0x08200002 }, { 0x0, 0x20040008, 0x00218004 }, { 0x0, 0xc0028004, 0x00000080 }, { 0x9, 0x34006018, 0x9a038084 } } },
  { 0x1c0, 0x3e0, { { 0x8, 0x20060388, 0x10000000 }, { 0x1, 0x8441c01b, 0x48000048 }, { 0x1, 0x888c2002, 0x48100082 }, { 0x1, 0x8441c01b, 0x08200048 } } },
  { 0x1e0, 0x3e0, { { 0x0, 0x200c450a, 0x01000082 }, { 0x8, 0xc0028605, 0x10200082 }, { 0x0, 0x84228001, 0x00200080 }, { 0x0, 0x00010000, 0x00210014 } } },
  { 0x210, 0x3fc, { { 0x0, 0x06210001, 0x00018044 }, { 0x0, 0x08210001, 0x00058444 }, { 0x0, 0x00010086, 0x080204cb }, { 0x0, 0x20112002, 0x00020048 } } },
  { 0x230, 0x3fc, { { 0x1, 0xac00c01b, 0x40000600 }, { 0x0, 0x53014067, 0x80000082 }, { 0x1, 0x8441c011, 0x4801804c }, { 0x8, 0x360220d9, 0x98000083 } } },
  { 0x214, 0x3fc, { { 0xc, 0x000e8000, 0x00418010 }, { 0x8, 0xc0028004, 0x10200344 }, { 0x0, 0x00010051, 0x00018044 }, { 0x4, 0x30066f89, 0x8c018004 } } },
  { 0x234, 0x3fc, { { 0x4, 0x10014303, 0x84058004 }, { 0x0, 0x20062a88, 0x08000000 }, { 0x1, 0x06010050, 0x00000002 }, { 0x0, 0x8302c560, 0x00000080 } } },
  { 0x218, 0x3fc, { { 0x8, 0x240a4019, 0x10018004 }, { 0x1, 0xa004e008, 0x08000082 }, { 0x0, 0x81028020, 0x00140100 }, { 0x8, 0x30026008, 0x98000080 } } },
  { 0x238, 0x3fc, { { 0x8, 0x20020089, 0xb0400001 }, { 0x0, 0x28310003, 0x000000ae }, { 0x8, 0x20020088, 0x10000083 }, { 0x8, 0xd0428405, 0x90018044 } } },
  { 0x21c, 0x3fc, { { 0x0, 0xa9080028, 0x62140600 }, { 0x8, 0x30026008, 0x9a038084 }, { 0x0, 0x2106c528, 0x00000002 }, { 0x0, 0x89268521, 0x00000800 } } },
  { 0x23c, 0x3fc, { { 0x0, 0x80028001, 0x48018844 }, { 0x8, 0xb0024088, 0x900380a7 }, { 0x0, 0x8826a001, 0x0001c824 }, { 0x9, 0xa0000009, 0x58018844 } } },
  { 0x250, 0x3fc, { { 0x0, 0x10210001, 0x00410004 }, { 0x8, 0xa4220009, 0x10438044 }, { 0x0, 0x00010022, 0x00820048 }, { 0x8, 0x20020088, 0xb8400001 } } },
  { 0x270, 0x3fc, { { 0x1, 0x2604e058, 0x08000002 }, { 0x4, 0xc822a007, 0x08000800 }, { 0x1, 0x83020061, 0x44000800 }, { 0x1, 0x2c042018, 0x48000002 } } },
  { 0x254, 0x3fc, { { 0x0, 0x00010011, 0x00418018 }, { 0x0, 0xa0020008, 0x00000002 }, { 0x1, 0x2604e019, 0x08200002 }, { 0x0, 0x40110002, 0x88440400 } } },
  { 0x274, 0x3fc, { { 0x9, 0x24024018, 0x10000000 }, { 0x0, 0x90428001, 0x80200002 }, { 0x8, 0x240a4018, 0x10000002 }, { 0x0, 0x0302c560, 0x00000080 } } },
  { 0x258, 0x3fc, { { 0x8, 0xc0028084, 0x100380a7 }, { 0x0, 0x00010001, 0x88400082 }, { 0x0, 0x28310003, 0x0000002c }, { 0x8, 0x30222089, 0x10400001 } } },
  { 0x278, 0x3fc, { { 0x0, 0x4b2120e7, 0x080180a7 }, { 0x8, 0xc4428015, 0x58000000 }, { 0x8, 0x20020089, 0xb0400083 }, { 0x0, 0x00860002, 0x00800000 } } },
  { 0x25c, 0x3fc, { { 0x0, 0x20112003, 0x804200ae }, { 0x8, 0x30220089, 0x10400001 }, { 0x0, 0x28312003, 0x0000002c }, { 0x0, 0x26312003, 0x0000002c } } },
  { 0x27c, 0x3fc, { { 0x8, 0xb0024009, 0x90000000 }, { 0x0, 0x16012081, 0x88200083 }, { 0x0, 0x00010680, 0x00000000 }, { 0x0, 0x00800300, 0x00000000 } } },
  { 0x290, 0x3f8, { { 0x0, 0x00010051, 0x00018044 }, { 0xc, 0x000e8000, 0x00418010 }, { 0x0, 0x00010080, 0x00000001 }, { 0x0, 0x04410011, 0x00200000 } } },
  { 0x2b0, 0x3f8, { { 0x0, 0x088c2002, 0x48100000 }, { 0x0, 0x2004e008, 0x08000002 }, { 0x0, 0x088c2002, 0x48800000 }, { 0x0, 0x83020002, 0x00100002 } } },
  { 0x298, 0x3f8, { { 0x0, 0x00010000, 0x00410014 }, { 0x1, 0x8300c061, 0x401000ca }, { 0x0, 0x80028000, 0x02001080 }, { 0x8, 0xc0028005, 0xb0218044 } } },
  { 0x2b8, 0x3f8, { { 0x1, 0x8300c060, 0x002100ca }, { 0x8, 0xc0028005, 0x90200082 }, { 0x0, 0x8822a001, 0x00098824 }, { 0x1, 0x8300c013, 0x48118046 } } },
  { 0x2d0, 0x3f8, { { 0xc, 0x000e8000, 0x00418018 }, { 0x8, 0xa0020008, 0x10000000 }, { 0x0, 0x00010022, 0x00820048 }, { 0xc, 0x000e8000, 0x00418050 } } },
  { 0x2f0, 0x3f8, { { 0x0, 0x81028521, 0x80200080 }, { 0x1, 0xa101c629, 0x00200000 }, { 0x1, 0x888c2002, 0x48100000 }, { 0x1, 0x9340c461, 0x801000ca } } },
  { 0x2d8, 0x3f8, { { 0x1, 0x9041c40b, 0x80000048 }, { 0x1, 0x8080c013, 0x48118046 }, { 0x1, 0x888cc002, 0x40100002 }, { 0x9, 0xa0020009, 0x5a018844 } } },
  { 0x2f8, 0x3f8, { { 0x1, 0xa00ee009, 0x480180c6 }, { 0x0, 0xa822e009, 0x08080800 }, { 0x0, 0xa008e009, 0x4a018844 }, { 0x0, 0x90228801, 0x00200080 } } },
  { 0x300, 0x3fc, { { 0x0, 0x80028f01, 0x80200080 }, { 0x0, 0x0806a601, 0x48000000 }, { 0x0, 0x4421a107, 0x082000e0 }, { 0x0, 0x93024003, 0x80100002 } } },
  { 0x320, 0x3fc, { { 0x0, 0x00028601, 0x00400000 }, { 0x0, 0x00010100, 0x00000060 }, { 0x0, 0x204cc509, 0x00200002 }, { 0x0, 0x2000c508, 0x00000002 } } },
  { 0x304, 0x3fc, { { 0x0, 0x03000060, 0x004180d2 }, { 0x0, 0x80028011, 0x00200000 }, { 0x8, 0x20020088, 0x10038025 }, { 0x0, 0x00010409, 0x08000008 } } },
  { 0x324, 0x3fc, { { 0x0, 0x03000461, 0x00018086 }, { 0x0, 0x800a8601, 0x00200082 }, { 0x8, 0x40068015, 0x10210014 }, { 0x8, 0x40068104, 0x10000061 } } },
  { 0x308, 0x3fc, { { 0x8, 0x204c0408, 0x10000000 }, { 0x8, 0x300a4009, 0x90000002 }, { 0x8, 0x300a4009, 0x90000000 }, { 0x0, 0x8c02a011, 0x48018004 } } },
  { 0x328, 0x3fc, { { 0x8, 0xa0020008, 0x10000000 }, { 0x0, 0x83020053, 0x0011c844 }, { 0x9, 0xa0020008, 0x1003c824 }, { 0x1, 0x8111c002, 0x00a180c4 } } },
  { 0x30c, 0x3fc, { { 0x0, 0xc6228005, 0x00000800 }, { 0x1, 0x888c2002, 0x48104800 }, { 0x0, 0x9042a001, 0x88200002 }, { 0x1, 0x8111c013, 0x00a38084 } } },
  { 0x32c, 0x3fc, { { 0x8, 0xb6022059, 0x98000000 }, { 0x0, 0x00010000, 0x00000000 }, { 0x9, 0x26020009, 0x12204800 }, { 0x0, 0x80028011, 0x0043c424 } } },
  { 0x340, 0x3fc, { { 0x0, 0x00010401, 0x88000082 }, { 0x1, 0x8931e00b, 0x00058044 }, { 0x0, 0x1602a084, 0x008380a7 }, { 0x0, 0x0300c461, 0x00100008 } } },
  { 0x360, 0x3fc, { { 0x4, 0xc822ae85, 0x0801c804 }, { 0x0, 0x00010080, 0x000380a7 }, { 0x0, 0x08212081, 0x000180a7 }, { 0x8, 0xc0028004, 0x10000000 } } },
  { 0x344, 0x3fc, { { 0x9, 0xa0000008, 0x1221c844 }, { 0x1, 0x8001c409, 0x00040008 }, { 0x0, 0x00028081, 0xa84380c7 }, { 0x0, 0x20062f89, 0x4c018004 } } },
  { 0x364, 0x3fc, { { 0x0, 0x00010000, 0x00000000 }, { 0x0, 0x00010000, 0x00000000 }, { 0x0, 0x00010000, 0x00000000 }, { 0x8, 0xc3020064, 0x10000080 } } },
  { 0x348, 0x3fc, { { 0x9, 0xa00200d9, 0x10000801 }, { 0x8, 0xb0024088, 0x90000083 }, { 0x0, 0x80068000, 0x0003c824 }, { 0x9, 0x30024088, 0x92004801 } } },
  { 0x368, 0x3fc, { { 0x9, 0xa00a0008, 0x12002080 }, { 0x0, 0x10210001, 0x00410004 }, { 0x8, 0xc0028084, 0x90200083 }, { 0x0, 0x88228001, 0x02001800 } } },
  { 0x34c, 0x3fc, { { 0x0, 0x00010080, 0x00000083 }, { 0x0, 0x88268001, 0x00004c2c }, { 0x0, 0x80028000, 0x02002080 }, { 0x0, 0x90228001, 0x02201080 } } },
  { 0x36c, 0x3fc, { { 0x0, 0x88228001, 0x02002800 }, { 0x0, 0x80028008, 0x0a005000 }, { 0x9, 0xa00a0008, 0x52002800 }, { 0x0, 0x40112082, 0x000384a7 } } },
  { 0x380, 0x3f8, { { 0x8, 0xc0018004, 0x10010004 }, { 0x1, 0x88a0e201, 0x00018004 }, { 0x1, 0x88a0e00b, 0x08018004 }, { 0xc, 0x000e8000, 0x488181c6 } } },
  { 0x3a0, 0x3f8, { { 0x0, 0x80028601, 0x00200000 }, { 0x1, 0x8001c380, 0x00000000 }, { 0x8, 0x40028605, 0x10210005 }, { 0x4, 0x30066f09, 0x8c018004 } } },
  { 0x388, 0x3f8, { { 0x1, 0x8080c002, 0x00a18046 }, { 0x9, 0xa0020088, 0x12004801 }, { 0x1, 0x888cc002, 0x40a18046 }, { 0x1, 0xa00ee008, 0x082180c6 } } },
  { 0x3a8, 0x3f8, { { 0x0, 0x91428521, 0x80200080 }, { 0x0, 0xa002e008, 0x0821c444 }, { 0x0, 0x80028000, 0x0003c824 }, { 0x0, 0xa008e008, 0x0a218844 } } },
  { 0x3c0, 0x3f0, { { 0x0, 0x00010006, 0x08800082 }, { 0x0, 0x84428011, 0x00200000 }, { 0x0, 0x80048401, 0x0001c804 }, { 0x8, 0xc0028004, 0x10218044 } } },
  { 0x3e0, 0x3f0, { { 0x0, 0x90228001, 0x00200080 }, { 0x0, 0x00010000, 0x00000000 }, { 0x1, 0xa04c0009, 0x00400000 }, { 0x1, 0xac00c01b, 0x40000600 } } },
};

void rom(cstate &s)
{
  if(s.romarray_precharge) {
    s.r_micro = 0x1ffff;
    s.r_nano1 = 0xf;
    s.r_nano2 = 0xffffffff;
    s.r_nano3 = 0xffffffff;
  }

  for(int i=0; i<34; i++)
    if((s.marom & microcode_entry[i].mask) == microcode_entry[i].val)
      s.r_micro &= ~microcode_entry[i].code[s.marom & 15];

  for(int i=0; i<84; i++)
    if((s.marom & nanocode_entry[i].mask) == nanocode_entry[i].val) {
      s.r_nano1 &= ~nanocode_entry[i].code[s.marom & 3][0];
      s.r_nano2 &= ~nanocode_entry[i].code[s.marom & 3][1];
      s.r_nano3 &= ~nanocode_entry[i].code[s.marom & 3][2];
    }

  if(s.romarray_clear) {
    s.l_micro = s.l_micro & 0x07ffe;
    s.l_nano1 = 0;
    s.l_nano2 = 0x7d00003d;
    s.l_nano3 = 0xe0028281;
  } else if(s.eu_w) {
    s.l_micro = s.r_micro ^ 0x07f80;
    s.l_nano1 = s.r_nano1;
    s.l_nano2 = s.r_nano2 ^ 0x7d01003d;
    s.l_nano3 = s.r_nano3 ^ 0xe0028281;
  }
}
