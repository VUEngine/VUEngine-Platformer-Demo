//---------------------------------------------------------------------------------------------------------
//
//  WaterfallTop
//  • 32×24 pixels
//  • 12 tiles, unreduced, not compressed
//  • 4×3 map, not compressed
//  • 3 animation frames, 4×1, spritesheet
//  Size: 196 + 24 = 220
//
//---------------------------------------------------------------------------------------------------------

const uint32 WaterfallTopTiles[49] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x7ED05550,0x555069D0,0x50005500,0xFF3CF000,0x5555FFFF,0xA9ABFEFF,
    0x55555995,0x0F3F0003,0x5555FFFF,0xAA6AFFBF,0x55555665,0x00000000,0x07BD0555,0x0555066D,
    0x00050055,0x00000000,0x7ED05550,0x555069D0,0x50005500,0xFCFCF000,0x5555FFFF,0xA9ABFEFF,
    0x55555995,0x30FF000F,0x5555FFFF,0xAA6AFFBF,0x55555665,0x00000000,0x07BD0555,0x0555066D,
    0x00050055,0x00000000,0x7ED05550,0x555069D0,0x50005500,0xFFF0FF00,0x5555FFFF,0xA9ABFEFF,
    0x55555995,0x3C0F0000,0x5555FFFF,0xAA6AFFBF,0x55555665,0x00000000,0x07BD0555,0x0555066D,
    0x00050055,
};

const uint16 WaterfallTopMap[12] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
    0x0008,0x0009,0x000A,0x000B,
};

const uint32 WaterfallTopTilesFrameOffsets[3] __attribute__((aligned(4))) =
{
    0x00000001,0x00000011,0x00000021,
};
