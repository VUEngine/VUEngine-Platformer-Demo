//---------------------------------------------------------------------------------------------------------
//
//	BackgroundMoundCastleFlag
//  • 8×16 pixels
//  • 2 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 1×2 map, not compressed
//  Size: 36 + 4 = 40
//
//---------------------------------------------------------------------------------------------------------

const uint32 BackgroundMoundCastleFlagTiles[9] __attribute__((aligned(4))) =
{
    0x00000000,0x00050000,0x06A90159,0x05A51AA9,0x00000050,0x05550000,0x06A91AA9,0x005501A9,
    0x00000000,
};

const uint16 BackgroundMoundCastleFlagMap[2] __attribute__((aligned(4))) =
{
    0x0000,0x0001,
};
