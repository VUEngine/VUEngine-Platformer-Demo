//---------------------------------------------------------------------------------------------------------
//
//  CoinBackSilhouette
//  • 16×64 pixels
//  • 16 tiles, unreduced, not compressed
//  • 2×8 map, not compressed
//  • 4 animation frames, 2×2, spritesheet
//  Size: 260 + 32 = 292
//
//---------------------------------------------------------------------------------------------------------

const uint32 CoinBackSilhouetteTiles[65] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0xA5005000,0x02400A40,0x90904090,0x00000000,0x00160001,0x00600068,
    0x01810180,0x02404090,0xA5000A40,0x00005000,0x00000000,0x00600180,0x00160068,0x00000001,
    0x00000000,0x00000000,0x90004000,0x24002400,0x99004900,0x00000000,0x00060001,0x00180018,
    0x00610060,0x24004900,0x90002400,0x00004000,0x00000000,0x00180060,0x00060018,0x00000001,
    0x00000000,0x00000000,0x90004000,0x90009000,0x90009000,0x00000000,0x00010000,0x00010001,
    0x00010001,0x90009000,0x90009000,0x00004000,0x00000000,0x00010001,0x00010001,0x00000000,
    0x00000000,0x00000000,0xA4005000,0x09000900,0x92404240,0x00000000,0x00010000,0x00060006,
    0x00190018,0x09004240,0xA4000900,0x00005000,0x00000000,0x00060018,0x00010006,0x00000000,
    0x00000000,
};

const uint16 CoinBackSilhouetteMap[16] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
    0x0008,0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x000F,
};

const uint32 CoinBackSilhouetteTilesFrameOffsets[4] __attribute__((aligned(4))) =
{
    0x00000001,0x00000011,0x00000021,0x00000031,
};
