//---------------------------------------------------------------------------------------------------------
//
//  Torch
//  • 8×72 pixels
//  • 9 tiles, unreduced, not compressed
//  • 1×9 map, not compressed
//  • 3 animation frames, 1×3, spritesheet
//  Size: 148 + 18 = 166
//
//---------------------------------------------------------------------------------------------------------

const uint32 TorchTiles[37] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0x28000800,0xAA802A00,0xAFE0ABA0,0x1B902FE0,0x2AA02560,
    0xFFFC1550,0x0540FFFC,0x0A800A80,0x00000200,0x00000000,0x00000000,0x00000000,0x08800080,
    0x0AA00280,0x2FE02BE0,0x1B902FE0,0x2AA02560,0xFFFC1550,0x0540FFFC,0x0A800A80,0x00000200,
    0x00000000,0x00000000,0x00000000,0x08000020,0x2A800880,0x2FE02FA0,0x1B902FE0,0x2AA02560,
    0xFFFC1550,0x0540FFFC,0x0A800A80,0x00000200,0x00000000,
};

const uint16 TorchMap[9] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
    0x0008,
};

const uint32 TorchTilesFrameOffsets[3] __attribute__((aligned(4))) =
{
    0x00000001,0x0000000D,0x00000019,
};
