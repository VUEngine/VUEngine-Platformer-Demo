
//{{BLOCK(PlateBG)

//======================================================================
//
//	PlateBG, 512x512@2, 
//	+ 14 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 64x64 
//	Total size: 224 + 8192 = 8416
//
//	Time-stamp: 2015-04-30, 16:27:16
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int PlateBGTiles[56] __attribute__((aligned(4)))=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x55555555,0x55555555,0x55555555,0x55555555,
	0x15551555,0x15551555,0x15551555,0x15551555,0x55500000,0x54145554,0x55545614,0x55545554,
	0x55550000,0x55555555,0x55555555,0x55555555,0x05550000,0x14151555,0x15551615,0x15551555,
	0x15551555,0x14151555,0x15551615,0x00000555,0x55545554,0x54145554,0x55545614,0x00005550,
	0x05500000,0x14141554,0x15541614,0x15541554,0x15541554,0x15541554,0x15541554,0x15541554,
	0x15541554,0x14141554,0x15541614,0x00000550,0x55500000,0x54145554,0x55545614,0x00005550,
	0x55550000,0x55555555,0x55555555,0x00005555,0x05550000,0x14151555,0x15551615,0x00000555,
};

const unsigned short PlateBGMap[4096] __attribute__((aligned(4)))=
{
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,
	0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,
	0x2002,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x0003,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,0x0005,0x2002,
	0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,

	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,
	0x2002,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0007,0x3004,0x3004,0x3004,0x3004,

	0x0003,0x0005,0x0008,0x0007,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,
	0x0006,0x0007,0x3004,0x3004,0x3004,0x3004,0x3004,0x0006,
	0x2002,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0007,0x0006,0x0007,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x0006,0x2002,
	0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x2002,0x0002,0x0009,0x0003,0x0004,0x0004,0x0005,0x0003,
	0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,0x0005,0x0003,
	0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,0x0004,0x0005,
	0x2002,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,0x0004,0x0005,
	0x0003,0x0005,0x0003,0x0004,0x0004,0x0004,0x0005,0x0007,
	0x3004,0x3004,0x0006,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x2002,0x0002,0x000A,0x0007,0x3004,0x3004,0x0006,0x0007,
	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x0007,0x3004,0x3004,0x3004,0x0006,
	0x0007,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,
	0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,0x0003,
	0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0007,0x0006,0x0003,0x0004,0x0004,0x0004,0x0005,0x0003,
	0x0004,0x0004,0x0005,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,0x0003,0x0004,
	0x0004,0x0004,0x0005,0x0007,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0002,
	0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0002,0x0007,
	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0005,0x0003,0x0004,0x0004,
	0x0004,0x0004,0x0005,0x0007,0x3004,0x3004,0x3004,0x0006,
	0x0007,0x0006,0x0007,0x3004,0x3004,0x3004,0x0006,0x0007,
	0x3004,0x0006,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0003,0x0004,

	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,0x0003,
	0x0004,0x0004,0x0005,0x0007,0x3004,0x3004,0x0006,0x0007,
	0x3004,0x3004,0x0006,0x0007,0x3004,0x0006,0x2002,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0005,0x0003,0x0005,0x0003,0x0004,0x0004,0x0004,
	0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2002,0x0001,

	0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,0x0006,0x0007,
	0x3004,0x3004,0x0006,0x000B,0x000C,0x000D,0x0003,0x0004,
	0x0005,0x0003,0x0005,0x000B,0x000C,0x000D,0x0007,0x3004,
	0x3004,0x3004,0x0006,0x2002,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x0007,0x3004,0x3004,0x3004,
	0x3004,0x0006,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0007,0x3004,

	0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0005,0x2002,0x0001,
	0x0002,0x2002,0x0002,0x0003,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0005,0x0007,0x0006,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x0003,0x0004,0x0004,0x0005,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0003,0x0004,0x0004,

	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0007,0x3004,
	0x0006,0x0007,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0005,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0007,0x0006,0x2002,0x0001,0x0001,0x0002,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0007,0x3004,0x3004,

	0x0003,0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0003,0x0004,
	0x0004,0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0003,0x0005,0x2002,0x0001,0x0001,0x0002,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x2002,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0007,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0007,0x0006,0x0007,0x3004,0x3004,
	0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x0006,0x2002,0x0002,0x0007,0x3004,0x3004,0x0006,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0003,0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0007,0x3004,
	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,0x0004,0x0005,
	0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0005,0x0007,0x0006,0x0003,0x0004,0x0005,0x0003,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0007,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0003,0x0004,
	0x0005,0x0003,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0003,0x0005,0x2002,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x000C,0x000C,0x000D,0x0007,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x3004,0x3004,0x0006,0x2002,0x0001,
	0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x0007,0x3004,0x0006,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x000B,0x000C,

	0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0005,0x0007,0x3004,
	0x0006,0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0007,0x3004,0x3004,0x3004,0x0006,
	0x0007,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x0006,0x2002,0x0002,0x0003,0x0004,0x0005,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0003,

	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0003,0x0004,
	0x0005,0x0007,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0005,0x000B,0x000C,0x000C,0x000C,0x000C,
	0x000C,0x000D,0x0007,0x0006,0x2002,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x2002,

	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0002,0x0003,0x0005,0x0007,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,0x0005,0x0003,
	0x0004,0x0004,0x0004,0x0005,0x0007,0x3004,0x0006,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x2002,

	0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,
	0x0006,0x0007,0x0006,0x000B,0x000C,0x000C,0x000D,0x000B,
	0x000C,0x000C,0x000D,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0007,

	0x0005,0x0003,0x0004,0x0004,0x0005,0x0003,0x0004,0x0005,
	0x0003,0x0004,0x0004,0x0004,0x0005,0x0003,0x0005,0x0003,
	0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x0007,
	0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x0006,0x0000,0x0000,0x0003,0x0004,0x0004,0x0004,

	0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x0003,
	0x0004,0x0004,0x0004,0x0004,0x0005,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,

	0x0002,0x0007,0x3004,0x3004,0x0006,0x0007,0x3004,0x0006,
	0x0007,0x3004,0x3004,0x3004,0x0006,0x2002,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0007,0x3004,0x3004,0x0006,0x0007,
	0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x0006,0x0007,
	0x3004,0x3004,0x3004,0x3004,0x0006,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,

	0x0002,0x0003,0x0005,0x0003,0x0005,0x0003,0x0005,0x000B,
	0x000C,0x000D,0x000B,0x000C,0x000D,0x0007,0x0006,0x0007,
	0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,0x0003,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,

	0x0002,0x2002,0x0002,0x2002,0x0002,0x2002,0x0002,0x0003,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0005,0x0003,0x0005,0x0003,0x0004,0x0004,0x0005,
	0x0003,0x0005,0x0008,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,

	0x0002,0x2002,0x0002,0x2002,0x0002,0x2002,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x2002,0x0002,0x0009,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,

	0x0006,0x0007,0x0006,0x0007,0x0006,0x0007,0x0006,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x2002,0x0002,0x0009,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0007,0x3004,0x3004,0x3004,

	0x0004,0x0005,0x0003,0x0004,0x0004,0x0004,0x0005,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0007,0x0006,0x2002,0x0001,0x0001,0x0002,
	0x0007,0x0006,0x000A,0x0007,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x0006,0x0007,0x3004,0x0006,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0003,

	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0003,0x0005,0x2002,0x0001,0x0001,0x0002,
	0x0003,0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,
	0x0004,0x0005,0x0003,0x0004,0x0004,0x0005,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2002,

	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2002,

	0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,0x0006,0x2002,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x0007,0x3004,0x3004,0x0006,0x0007,0x3004,
	0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,
	0x0006,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0007,

	0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,0x0005,0x0007,
	0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x0006,0x2002,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x0007,0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,
	0x3004,0x0006,0x0003,0x0004,0x0004,0x0004,0x0005,0x0003,
	0x0005,0x0003,0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,
	0x0004,0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,

	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x0003,
	0x0004,0x0005,0x0003,0x0004,0x0004,0x0005,0x0003,0x0005,
	0x0003,0x0005,0x0007,0x0006,0x0007,0x3004,0x3004,0x0006,
	0x000B,0x000D,0x0003,0x0004,0x0005,0x0003,0x0004,0x0004,
	0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,
	0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,

	0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x0006,0x0007,
	0x3004,0x0006,0x2002,0x0001,0x0001,0x0002,0x2002,0x0002,
	0x2002,0x0002,0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0005,0x2002,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,
	0x0002,0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0007,0x3004,0x3004,0x3004,0x3004,0x3004,

	0x0004,0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,
	0x0004,0x0005,0x2002,0x0001,0x0001,0x0002,0x2002,0x0002,
	0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0007,0x3004,0x0006,0x0007,0x3004,0x3004,
	0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,0x0006,0x0007,
	0x0006,0x0007,0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,
	0x3004,0x3004,0x0006,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0003,

	0x0001,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x0007,0x0006,
	0x0007,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0003,0x0005,0x0003,0x0004,0x0004,0x0004,
	0x0005,0x0003,0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,
	0x0004,0x0005,0x0003,0x0005,0x0003,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2002,

	0x0001,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x0007,0x3004,0x3004,0x0006,0x0008,0x0003,
	0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2002,

	0x3004,0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,
	0x3004,0x0006,0x000B,0x000C,0x000C,0x000D,0x0009,0x2002,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0007,

	0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,0x0005,0x0003,
	0x0004,0x0004,0x0005,0x000B,0x000C,0x000D,0x000A,0x0007,
	0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0007,0x0006,0x0007,0x3004,0x3004,0x3004,
	0x0006,0x0007,0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,
	0x3004,0x0006,0x0007,0x0006,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0003,

	0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x0003,0x0005,0x0003,0x0004,0x0004,
	0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0003,0x0004,0x0004,0x0005,0x0003,0x0004,
	0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,
	0x0004,0x0004,0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2002,

	0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0007,0x3004,0x0006,0x0007,
	0x3004,0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0007,

	0x0003,0x0004,0x0005,0x2002,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,0x0005,
	0x0003,0x0004,0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0007,0x3004,0x0006,0x0007,0x3004,0x3004,0x0006,0x0007,
	0x3004,0x3004,0x0006,0x0007,0x0006,0x0007,0x3004,0x3004,
	0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0005,0x0003,
	0x0004,0x0005,0x0007,0x3004,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x0006,0x0007,0x3004,0x3004,0x0006,0x0007,0x3004,
	0x3004,0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0001,0x0002,0x2002,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0002,0x0003,0x0004,0x0004,0x0005,0x0003,0x0004,
	0x0005,0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0005,0x0007,0x3004,0x3004,0x0006,
	0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x3004,0x0006,0x0007,0x3004,0x0006,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0007,
	0x3004,0x0006,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,0x0005,
	0x0007,0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x0006,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0003,0x0004,0x0004,0x0004,0x0005,0x0007,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x0006,0x000B,
	0x000C,0x000D,0x2002,0x0001,0x0001,0x0002,0x0007,0x3004,
	0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x0003,0x0005,0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x2002,0x0001,0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,
	0x0003,0x0005,0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0005,0x2002,0x0001,0x0001,0x0002,0x0003,0x0004,
	0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,
	0x0007,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0007,0x3004,0x3004,0x0006,0x2002,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,
	0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0007,0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x0006,
	0x0003,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0003,0x0004,0x0004,0x0005,0x0007,0x3004,
	0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0007,0x3004,0x3004,0x0006,
	0x0007,0x0006,0x0007,0x3004,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x0006,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0004,0x0005,0x0003,0x0004,0x0004,0x0004,0x0004,0x0005,
	0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x0003,0x0004,
	0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0002,0x0003,0x0005,0x0003,0x0004,
	0x0005,0x0003,0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,
	0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0002,
	0x2002,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0002,0x0007,0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x0006,0x2002,0x0002,0x2002,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,0x3004,0x0006,
	0x0007,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,
	0x0002,0x0003,0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,
	0x0005,0x000B,0x000C,0x000D,0x0007,0x0006,0x0007,0x3004,
	0x0006,0x0007,0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x000B,0x000C,0x000D,0x0003,0x0004,0x0005,0x0003,0x0004,
	0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0007,0x3004,0x3004,0x0006,0x0007,0x3004,
	0x0006,0x0007,0x0006,0x2002,0x0001,0x0002,0x2002,0x0001,
	0x0002,0x0003,0x0004,0x0004,0x0005,0x0003,0x0004,0x0005,
	0x0003,0x0004,0x0004,0x0004,0x0005,0x2002,0x0001,0x0001,
	0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0004,0x0004,0x0005,0x2002,0x0001,0x0002,0x2002,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x0003,0x0005,0x0003,0x0004,0x0005,0x0003,
	0x0004,0x0004,0x0005,0x0007,0x3004,0x0006,0x2002,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,
	0x0007,0x3004,0x3004,0x3004,0x0006,0x0007,0x3004,0x3004,
	0x0006,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0003,0x0004,0x0004,0x0004,0x0004,

	0x0001,0x0001,0x0002,0x0007,0x3004,0x0006,0x2002,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,0x2002,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,
	0x0003,0x0004,0x0004,0x0005,0x000B,0x000C,0x000D,0x0003,
	0x0004,0x0004,0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,0x2002,0x0001,
	0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0002,0x2002,0x0002,0x2002,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x2002,0x0001,
	0x0002,0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,0x0007,
	0x3004,0x3004,0x3004,0x0006,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x0007,0x3004,
	0x3004,0x0006,0x0007,0x3004,0x3004,0x3004,0x3004,0x3004,
	0x3004,0x0006,0x0007,0x0006,0x0007,0x3004,0x0006,0x2002,
	0x0001,0x0001,0x0002,0x0007,0x3004,0x0006,0x0007,0x3004,
	0x0006,0x0007,0x3004,0x3004,0x0006,0x2002,0x0001,0x0002,
	0x2002,0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x0003,
	0x0004,0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0007,0x3004,0x0006,0x0003,0x0005,
	0x0003,0x0004,0x0004,0x0004,0x0005,0x0003,0x0004,0x0004,
	0x0005,0x0008,0x0003,0x0004,0x0005,0x000B,0x000D,0x0007,
	0x3004,0x3004,0x0006,0x0003,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0005,0x0003,0x0005,0x0007,0x3004,0x0006,
	0x0007,0x3004,0x3004,0x0006,0x0007,0x3004,0x0006,0x2002,
	0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0003,0x0004,0x0005,0x2002,0x0002,
	0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0002,0x0009,0x2002,0x0001,0x0002,0x0003,0x0004,0x0005,
	0x0003,0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x0003,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,0x0005,0x2002,
	0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x2002,0x0001,0x0002,0x2002,0x0002,
	0x2002,0x0001,0x0001,0x0001,0x0002,0x2002,0x0001,0x0001,
	0x0002,0x000A,0x0007,0x3004,0x0006,0x0007,0x3004,0x0006,
	0x2002,0x0001,0x0002,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0007,0x0006,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x2002,
	0x0001,0x0001,0x0002,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0007,0x3004,0x0006,0x0007,0x0006,
	0x0007,0x3004,0x3004,0x3004,0x0006,0x2002,0x0001,0x0001,
	0x0002,0x0003,0x0004,0x0004,0x0004,0x0004,0x0004,0x0005,
	0x0007,0x3004,0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0003,0x0005,0x2002,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0007,
	0x3004,0x3004,0x0006,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0003,0x0004,0x0004,0x0004,0x0004,
	0x0004,0x0004,0x0004,0x0004,0x0005,0x0007,0x3004,0x3004,
	0x0006,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,
	0x0003,0x0004,0x0005,0x2002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x2002,0x0002,0x0007,0x3004,0x3004,
	0x3004,0x3004,0x3004,0x3004,0x3004,0x3004,0x0006,0x0003,
	0x0004,0x0004,0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x2002,0x0001,0x0001,0x0001,0x0001,
};

//}}BLOCK(PlateBG)
