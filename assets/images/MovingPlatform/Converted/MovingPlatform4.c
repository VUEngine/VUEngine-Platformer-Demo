//---------------------------------------------------------------------------------------------------------
//
//	MovingPlatform4
//  • 32×8 pixels
//  • 3 tiles, reduced by non-unique tiles, not compressed
//  • 4×1 map, not compressed
//  Size: 52 + 8 = 60
//
//---------------------------------------------------------------------------------------------------------

const uint32 MovingPlatform4Tiles[13] __attribute__((aligned(4))) =
{
    0x00000000,0xFFF45550,0xA969AAAD,0xAAA9A969,0x5550AAA4,0xFFFF5555,0xAAAAAAAA,0xAAAAAAAA,
    0x5555AAAA,0x1FFF0555,0x696A7AAA,0x6AAA696A,0x05551AAA,
};

const uint16 MovingPlatform4Map[4] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0001,0x0002,
};
