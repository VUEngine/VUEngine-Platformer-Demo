//---------------------------------------------------------------------------------------------------------
//
//  Mound2
//  • 88×40 pixels
//  • 9 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 11×5 map, not compressed
//  Size: 148 + 110 = 258
//
//---------------------------------------------------------------------------------------------------------

const uint32 Mound2Tiles[37] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0xF5005000,0xFFE4FF50,0xFFEDFFF4,
    0xAFEDFFF9,0x005F0005,0x1EFF05FF,0x59FF1BBF,0x59AA666B,0xAA99AAB9,0xAA99AAA5,0xAA99AAA5,
    0xFFD9FAA5,0x666A59AA,0x59AA59AA,0x6EFE7B6A,0x7BBF6EFF,0xA5005000,0xAAA4AA50,0xAA99AAA4,
    0xFFD9FAA5,0x005A0005,0x19AA05AA,0x6EFE1B6A,0x7BBF6EFF,0xFFEDFFF9,0xFFEDFFF9,0xFFEDFFF9,
    0xAFEDFFF9,0x7BBF6EFF,0x6EFF6EFF,0x59FF7BBF,0x59AA666B,
};

const uint16 Mound2Map[55] __attribute__((aligned(4))) =
{
    0x0000,0x0000,0x0001,0x0002,0x0000,0x0000,0x0000,0x0001,
    0x0002,0x0000,0x0000,0x0000,0x0000,0x0003,0x0004,0x0005,
    0x0006,0x0000,0x0003,0x0004,0x0000,0x0000,0x0001,0x0002,
    0x0007,0x0008,0x0007,0x0008,0x0000,0x0007,0x0008,0x0000,
    0x0000,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0000,
    0x0003,0x0004,0x0001,0x0002,0x0007,0x0008,0x0007,0x0008,
    0x0007,0x0008,0x0000,0x0007,0x0008,0x0003,0x0004,
};
