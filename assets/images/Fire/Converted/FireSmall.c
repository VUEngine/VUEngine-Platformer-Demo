//---------------------------------------------------------------------------------------------------------
//
//  FireSmall
//  • 8×24 pixels
//  • 3 tiles, unreduced, not compressed
//  • 1×3 map, not compressed
//  • 3 animation frames, 1×1, spritesheet
//  Size: 52 + 6 = 58
//
//---------------------------------------------------------------------------------------------------------

const uint32 FireSmallTiles[13] __attribute__((aligned(4))) =
{
    0x00000000,0x28000800,0xAA802A00,0xAFE0ABA0,0x2BA02FE0,0x08800080,0x0AA00280,0x2FE02BE0,
    0x2BA02FE0,0x08000020,0x2A800880,0x2FE02FA0,0x2BA02FE0,
};

const uint16 FireSmallMap[3] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,
};

const uint32 FireSmallTilesFrameOffsets[3] __attribute__((aligned(4))) =
{
    0x00000001,0x00000005,0x00000009,
};
