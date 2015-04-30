
//{{BLOCK(Fence)

//======================================================================
//
//	Fence, 24x16@2, 
//	+ 5 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 3x2 
//	Total size: 80 + 12 = 92
//
//	Time-stamp: 2015-04-30, 19:17:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int FenceTiles[20] __attribute__((aligned(4)))=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x07D00140,0xEAA45EB4,0x9AA49AA4,0x1AA45AA4,
	0x00000000,0xFFFF5555,0xAAAAAAAA,0x00005555,0xEAA45AA4,0x9AA49AA4,0x1AA45AA4,0x1AA41AA4,
	0xFFFF5555,0xAAAAAAAA,0x00005555,0x00000000,
};

const unsigned short FenceMap[6] __attribute__((aligned(4)))=
{
	0x0001,0x0002,0x2001,0x0003,0x0004,0x2003,
};

//}}BLOCK(Fence)
