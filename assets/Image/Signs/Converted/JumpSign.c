//---------------------------------------------------------------------------------------------------------
//
//  JumpSign
//  • 32×32 pixels
//  • 15 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 4×4 map, not compressed
//  Size: 244 + 32 = 276
//
//---------------------------------------------------------------------------------------------------------

const uint32 JumpSignTiles[61] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x55500000,0xAAA9FFF4,0xAAA9AAA9,0xD0004000,0x5555A400,0xAAAAFFFF,
    0xAAAAAAAA,0x00070001,0x5555001E,0xABAAFDFF,0x5AAAAAAA,0x00000000,0x05550000,0x7AAA1FFF,
    0x6AA96AAA,0xAAA5AAA9,0xAAADAAA5,0x55A9AAA9,0x99696569,0xAAAAAAAA,0xAAAAAAAA,0xAAA9AAAA,
    0xAAA5AAA5,0xAA6AA5AA,0xAA6AAA6A,0xAA6AAA6A,0xAA9AAA6A,0x6A6A6A96,0x6A6A6A6A,0x6A6A6A6A,
    0x69AA6A6A,0xA9699969,0x55A99969,0xAAA9AAA9,0xAAA9AAA9,0x5AA5AAA5,0x69A9A6A5,0xA66A9A6A,
    0x666A666A,0xA966AAA6,0xAA6AAA5A,0xA6995A9A,0xAAAAA96A,0x696A69AA,0x6A6A6A6A,0x6A696A6A,
    0x6AAA6A96,0x5550AAA4,0x00000000,0x00000000,0x00000000,0x5555AAAA,0xA4005400,0x75009400,
    0xBB407740,0x5555AAAA,0x001A0015,0x0076001A,0x01EF005D,
};

const uint16 JumpSignMap[16] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
    0x0008,0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x200C,
};