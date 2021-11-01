//======================================================================
//
//	OneWayPlatform4, 32x16@2, 
//	+ 4 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 4x2 
//	Total size: 64 + 16 = 80
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const uint32 OneWayPlatform4Tiles[16] __attribute__((aligned(4)))=
{
	0x00000000,0x55400000,0xAAB4FFD0,0xD5E4FFE4,
	0x00000000,0x15500000,0xEAAF7FF5,0xB57ABFFA,0xD5E4DDE4,0xAA90FFE4,0x00005540,0x00000000,
	0xB57AB77A,0x6AA5BFFA,0x00001550,0x00000000,
};

const uint16 OneWayPlatform4Map[8] __attribute__((aligned(4)))=
{
	0x0000,0x0001,0x2001,0x2000,0x0002,0x0003,0x2003,0x2002,
};
