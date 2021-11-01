//======================================================================
//
//	FlowerA, 16x16@2, 
//	+ 4 tiles not compressed
//	+ regular map (flat), not compressed, 2x2 
//	Total size: 64 + 8 = 72
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 FlowerATiles[16] __attribute__((aligned(4)))=
{
	0xAF000000,0x5F60FFC0,0x5F60FFE0,0xAA005580,
	0x000F0000,0x009F003F,0x009F00BF,0x000A0025,0xAA000000,0xFFE0AF80,0xFFE0AFA0,0xAA00AF80,
	0x000A0000,0x00BF002F,0x00BF00AF,0x000A002F,
};

const uint16 FlowerAMap[4] __attribute__((aligned(4)))=
{
	0x0000,0x0001,0x0002,0x0003,
};
