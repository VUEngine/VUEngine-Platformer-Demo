
//{{BLOCK(Lava)

//======================================================================
//
//	Lava, 384x128@2,
//	+ 20 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 48x16
//	Total size: 320 + 1536 = 1856
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int LavaTiles[80] __attribute__((aligned(4)))=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,
	0xAAAAAAAA,0xAAAAAABA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAEAAAAAA,0xAAAAAAAA,0xAAAAAAAA,
	0xAAAAAEAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xBAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,
	0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAEA,0xAAAAAAAA,0xAAAAAAEA,0xAAAAAAAA,0xAAAAAAAA,
	0xAAAAAAAA,0xAAAAAAAA,0xAAABAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xBAAAAAAA,0xAAAAAAAA,
	0xAABAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xEAAAAAAA,
	0xAAAAAAAA,0xAAAAAAAA,0xAAAAEAAA,0xAAAAAAAA,0xEAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,
	0xAAAAAAEA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAEAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,

	0xAAAABAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAABAA,0xAAAAAAAA,
	0xAAAAAAAA,0xAAAAAAAA,0xAEAAAAAA,0xAAABAAAA,0xAAAAAAAA,0xEAAAABAA,0xAAAAAAAA,0xAAAAAAAA,
};

const unsigned short LavaMap[] __attribute__((aligned(4)))=
{
	0x0001,0x0002,0x0001,0x0001,0x0001,0x0001,0x0003,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0004,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0005,0x0001,0x0006,0x0001,
	0x0001,0x0002,0x0001,0x0001,0x0007,0x0001,0x0001,0x0001,
	0x0008,0x0001,0x0001,0x0001,0x0001,0x0001,0x1008,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x1005,0x0001,
	0x0001,0x0001,0x0001,0x0009,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x000A,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x000B,0x0001,0x2006,0x0001,0x0001,0x0001,0x0001,
	0x000C,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x000A,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x000D,0x0001,0x2006,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x000E,0x0001,0x0001,0x0001,0x0001,0x0001,0x100B,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x100C,0x0001,
	0x0001,0x0001,0x0001,0x100B,0x0001,0x000F,0x0001,0x0001,

	0x000E,0x0001,0x0001,0x0001,0x0001,0x0001,0x100B,0x0001,
	0x0010,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0011,0x0001,0x300B,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x1009,0x0001,0x0001,0x0001,0x0012,0x0001,
	0x0001,0x0001,0x0001,0x0004,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x300B,0x0001,0x3008,0x0001,0x0001,0x0001,
	0x0001,0x3010,0x1009,0x0001,0x0001,0x0001,0x0012,0x0001,
	0x0005,0x0001,0x0001,0x0001,0x0001,0x1008,0x0001,0x0001,

	0x0001,0x0001,0x0001,0x0001,0x0001,0x3010,0x2004,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x000B,0x0001,0x0001,0x0001,0x0001,0x0011,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x3010,0x2004,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x000B,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x000F,0x0001,0x0001,0x0001,
	0x0009,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0001,0x0001,0x0001,0x0007,0x0001,0x0001,
	0x0001,0x0006,0x0001,0x0001,0x000F,0x0001,0x0001,0x0001,
	0x0009,0x0001,0x0001,0x0008,0x0001,0x0011,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x1004,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x300C,0x0001,0x0001,0x200E,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x3004,
	0x0001,0x0001,0x1004,0x0001,0x0001,0x0001,0x0001,0x300C,

	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x200E,
	0x0001,0x300A,0x0001,0x0001,0x0001,0x1011,0x0001,0x3004,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x300F,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x1006,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x300F,0x0001,0x0001,0x0001,0x0001,

	0x2007,0x0001,0x0001,0x3002,0x0001,0x0001,0x1006,0x0001,
	0x0001,0x2007,0x0001,0x0001,0x0001,0x2004,0x0001,0x0001,
	0x0001,0x2009,0x0001,0x0001,0x0001,0x0001,0x0001,0x1008,
	0x100D,0x0001,0x0001,0x0001,0x0001,0x0001,0x1006,0x0001,
	0x0001,0x2007,0x100A,0x0001,0x0001,0x2004,0x0001,0x2011,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x1008,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x2002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x2010,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x2003,0x0001,0x0001,
	0x0001,0x0001,0x2002,0x0001,0x0001,0x300A,0x0001,0x0001,
	0x100E,0x0001,0x2003,0x0001,0x0001,0x0001,0x0001,0x300B,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x2009,0x0001,
	0x0001,0x0001,0x2003,0x0001,0x0001,0x0001,0x0001,0x300B,

	0x0001,0x100B,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x1003,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0009,0x0001,0x0001,0x100A,0x0001,0x0001,0x0013,
	0x0001,0x0001,0x0001,0x0006,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x2003,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x100A,0x0001,0x0001,0x2007,
	0x0001,0x0001,0x0001,0x0006,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0001,0x0001,0x0004,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x300F,0x0001,
	0x0001,0x0001,0x0001,0x3004,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x200D,0x0001,0x0001,0x0001,0x0001,0x0001,0x2003,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x1009,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x1009,0x0001,
	0x0001,0x0001,0x3002,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x200C,
	0x0001,0x100E,0x0001,0x0001,0x0001,0x3009,0x0001,0x0001,
	0x0001,0x0001,0x300E,0x0001,0x000D,0x0001,0x0001,0x200A,
	0x0001,0x0001,0x0001,0x0001,0x2010,0x0001,0x2003,0x0001,
	0x0001,0x300D,0x2003,0x0001,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x100D,0x0001,0x0001,0x3006,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x100B,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0003,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x2011,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x2008,0x0001,0x0001,0x0001,0x0001,
	0x000B,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x2008,0x0001,0x0001,0x0001,0x0001,0x0001,0x300C,0x0001,

	0x0001,0x0001,0x100D,0x0001,0x0001,0x3006,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x100B,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0003,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x2011,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x2008,0x0001,0x0001,0x0001,0x0001,
	0x000B,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x2008,0x0001,0x0001,0x0001,0x0001,0x0001,0x300C,0x0001,

	0x0001,0x0001,0x100D,0x0001,0x0001,0x3006,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x100B,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0003,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x2011,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x2008,0x0001,0x0001,0x0001,0x0001,
	0x000B,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x2008,0x0001,0x0001,0x0001,0x0001,0x0001,0x300C,0x0001,

	0x0001,0x0001,0x100D,0x0001,0x0001,0x3006,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x100B,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0003,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x2011,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x2008,0x0001,0x0001,0x0001,0x0001,
	0x000B,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x2008,0x0001,0x0001,0x0001,0x0001,0x0001,0x300C,0x0001,

	0x0001,0x0001,0x100D,0x0001,0x0001,0x3006,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x100B,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0003,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x2011,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x2008,0x0001,0x0001,0x0001,0x0001,
	0x000B,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x2008,0x0001,0x0001,0x0001,0x0001,0x0001,0x300C,0x0001,
};

//}}BLOCK(Lava)
