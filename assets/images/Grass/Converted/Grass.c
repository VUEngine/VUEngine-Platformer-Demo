//---------------------------------------------------------------------------------------------------------
//
//  Grass
//  • 16×32 pixels
//  • 8 tiles, unreduced, not compressed
//  • 2×4 map, not compressed
//  • 2 animation frames, 2×2, spritesheet
//  Size: 132 + 16 = 148
//
//---------------------------------------------------------------------------------------------------------

const uint32 GrassTiles[33] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0x7D001400,0xA400E900,0x00000000,0x00000000,0x00010000,
    0x00060007,0x9000A400,0x95509000,0xBA909FF4,0xA900AA40,0x001A001E,0x7F6A157A,0x06AA1AEA,
    0x01AA06AA,0x00000000,0x00000000,0x14000000,0xE9007D00,0x00000000,0x00000000,0x00000000,
    0x00070001,0xA400A400,0x90009000,0xBFF49550,0xA900AA50,0x141E0006,0x1B6A7D7A,0x06AA1AEA,
    0x01AA06AA,
};

const uint16 GrassMap[8] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
};

const uint32 GrassTilesFrameOffsets[2] __attribute__((aligned(4))) =
{
    0x00000001,0x00000011,
};
