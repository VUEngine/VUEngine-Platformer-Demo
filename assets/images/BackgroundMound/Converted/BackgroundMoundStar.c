//---------------------------------------------------------------------------------------------------------
//
//	BackgroundMoundStar
//  • 8×24 pixels
//  • 3 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 1×3 map, not compressed
//  Size: 52 + 6 = 58
//
//---------------------------------------------------------------------------------------------------------

const uint32 BackgroundMoundStarTiles[13] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x01900040,0x00000040,0x00000000,0x00400000,0x06A40080,0x00400080,
    0x00000000,0x00800040,0x1AA90080,0x00800080,0x00000040,
};

const uint16 BackgroundMoundStarMap[3] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,
};
