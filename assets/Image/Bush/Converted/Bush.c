//---------------------------------------------------------------------------------------------------------
//
//  Bush
//  • 24×16 pixels
//  • 6 tiles, unreduced, not compressed
//  • 3×2 map, not compressed
//  • 2 animation frames, 3×1, spritesheet
//  Size: 100 + 12 = 112
//
//---------------------------------------------------------------------------------------------------------

const uint32 BushTiles[25] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x55000000,0xEAD07F40,0xAAA4AAB4,0x7FF41550,0xAAABEAAD,0xAAAAAAAB,
    0xAAAAAAAA,0x00000000,0x00170001,0x07EA017E,0x7AAA1EAA,0x00000000,0x00000000,0xFF505500,
    0xAAA4AAF4,0x15500000,0xEAAD7FF4,0xAAAAAAAB,0xAAAAAAAA,0x00000000,0x00170001,0x07EA017E,
    0x7AAA1EAA,
};

const uint16 BushMap[6] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,
};

const uint32 BushTilesFrameOffsets[2] __attribute__((aligned(4))) =
{
    0x00000001,0x0000000D,
};
