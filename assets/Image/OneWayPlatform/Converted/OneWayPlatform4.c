//---------------------------------------------------------------------------------------------------------
//
//  OneWayPlatform4
//  • 32×16 pixels
//  • 4 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 4×2 map, not compressed
//  Size: 68 + 16 = 84
//
//---------------------------------------------------------------------------------------------------------

const uint32 OneWayPlatform4Tiles[17] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x55400000,0xAAB4FFD0,0xD5E4FFE4,0x00000000,0x15500000,0xEAAF7FF5,
    0xB57ABFFA,0xD5E4DDE4,0xAA90FFE4,0x00005540,0x00000000,0xB57AB77A,0x6AA5BFFA,0x00001550,
    0x00000000,
};

const uint16 OneWayPlatform4Map[8] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x2001,0x2000,0x0002,0x0003,0x2003,0x2002,
};
