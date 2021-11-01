//======================================================================
//
//	TorchOff, 8x16@2, 
//	+ 2 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 1x2 
//	Total size: 32 + 4 = 36
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 TorchOffTiles[8] __attribute__((aligned(4)))=
{
	0x00000000,0x10100000,0x2AA02560,0xFFFC1550,
	0x0540FFFC,0x0A800A80,0x00000200,0x00000000,
};

const uint16 TorchOffMap[2] __attribute__((aligned(4)))=
{
	0x0000,0x0001,
};
