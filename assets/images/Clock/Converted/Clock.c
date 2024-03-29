//---------------------------------------------------------------------------------------------------------
//
//  Clock
//  • 16×64 pixels
//  • 16 tiles, unreduced, not compressed
//  • 2×8 map, not compressed
//  • 4 animation frames, 2×2, spritesheet
//  Size: 260 + 32 = 292
//
//---------------------------------------------------------------------------------------------------------

const uint32 ClockTiles[65] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0xF9005400,0x6B90AE40,0x6AE46AE4,0x00000000,0x007F0015,0x076B01DA,
    0x1DAB1DAB,0xAAE46AE4,0xAE40AB90,0x5400F900,0x00000000,0x1DAA1DBF,0x01DA076A,0x0015007F,
    0x00000000,0x00000000,0xF9005400,0xAB90AE40,0xAAE4AAE4,0x00000000,0x007F0015,0x076A01DA,
    0x1DAA1DAA,0xAAE46AE4,0xAE40AB90,0x5400F900,0x00000000,0x1DAA1DFF,0x01DA076A,0x0015007F,
    0x00000000,0x00000000,0xF9005400,0xAB90AE40,0xAAE4AAE4,0x00000000,0x007F0015,0x076A01DA,
    0x1DAA1DAA,0x6AE46AE4,0x6E406B90,0x5400F900,0x00000000,0x1DAB1DBF,0x01DB076B,0x0015007F,
    0x00000000,0x00000000,0xF9005400,0xAB90AE40,0xAAE4AAE4,0x00000000,0x007F0015,0x076A01DA,
    0x1DAA1DAA,0xAAE4FDE4,0xAE40AB90,0x5400F900,0x00000000,0x1DAA1DBF,0x01DA076A,0x0015007F,
    0x00000000,
};

const uint16 ClockMap[16] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
    0x0008,0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x000F,
};

const uint32 ClockTilesFrameOffsets[4] __attribute__((aligned(4))) =
{
    0x00000001,0x00000011,0x00000021,0x00000031,
};
