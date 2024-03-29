//---------------------------------------------------------------------------------------------------------
//
//  Ladder24
//  • 24×192 pixels
//  • 6 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 3×24 map, not compressed
//  Size: 100 + 144 = 244
//
//---------------------------------------------------------------------------------------------------------

const uint32 Ladder24Tiles[25] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01400000,
    0x06B406D0,0x00000000,0x00000000,0x05000000,0x1AD01B40,0xFAB406B4,0xA6B4A6B4,0x06B4A6B4,
    0x06B406B4,0xFFFF0000,0xAAAAAAAA,0x0000AAAA,0x00000000,0x1AEF1AD0,0x1ADA1ADA,0x1AD01ADA,
    0x1AD01AD0,
};

const uint16 Ladder24Map[72] __attribute__((aligned(4))) =
{
    0x0001,0x0000,0x0002,0x0003,0x0004,0x0005,0x0003,0x0004,
    0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,
    0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,0x0005,
    0x0003,0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,
    0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,
    0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,0x0005,
    0x0003,0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,
    0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,
    0x0004,0x0005,0x0003,0x0004,0x0005,0x0003,0x0004,0x0005,
};
