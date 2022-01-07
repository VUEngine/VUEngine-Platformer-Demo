//---------------------------------------------------------------------------------------------------------
//
//	FlowerA
//  • 16×16 pixels
//  • 4 tiles, not compressed
//  • 2×2 map, not compressed
//  Size: 68 + 8 = 76
//
//---------------------------------------------------------------------------------------------------------

const uint32 FlowerATiles[17] __attribute__((aligned(4))) =
{
    0x00000000,0xAF000000,0x5F60FFC0,0x5F60FFE0,0xAA005580,0x000F0000,0x009F003F,0x009F00BF,
    0x000A0025,0xAA000000,0xFFE0AF80,0xFFE0AFA0,0xAA00AF80,0x000A0000,0x00BF002F,0x00BF00AF,
    0x000A002F,
};

const uint16 FlowerAMap[4] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,
};
