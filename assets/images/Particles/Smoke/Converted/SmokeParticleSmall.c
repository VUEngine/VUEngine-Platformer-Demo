//======================================================================
//
//	SmokeParticleSmall, 8x32@2, 
//	+ 4 tiles not compressed
//	+ regular map (flat), not compressed, 1x4 
//	Total size: 64 + 8 = 72
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 SmokeParticleSmallTiles[16] __attribute__((aligned(4)))=
{
	0x0FC00000,0xBFFF2FFC,0xAFFEBFFF,0x0AA02AE8,
	0x0BC00000,0x2FFC2FF0,0x2BF82FFC,0x00000AA0,0x00000000,0x0BF003C0,0x02800BF0,0x00000000,
	0x00000000,0x03C00000,0x00000280,0x00000000,
};

const uint16 SmokeParticleSmallMap[4] __attribute__((aligned(4)))=
{
	0x0000,0x0001,0x0002,0x0003,
};
