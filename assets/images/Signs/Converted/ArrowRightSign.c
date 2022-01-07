//---------------------------------------------------------------------------------------------------------
//
//	ArrowRightSign
//  • 24×24 pixels
//  • 8 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 3×3 map, not compressed
//  Size: 132 + 18 = 150
//
//---------------------------------------------------------------------------------------------------------

const uint32 ArrowRightSignTiles[33] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x07D00140,0x00000000,0xFD005400,0xA900A900,0xA900A900,0x1AA41EB4,0xFFFF5555,0xA96AAAAA,
    0xAAAAAAAA,0x001D0005,0x01EB0079,0x1EAA07AA,0x01AA06AA,0x00005400,0x00000000,0x00000000,
    0x00000000,0x15545555,0x1AA41AA4,0x1AA41AA4,0x1AA41AA4,0x00190069,0x00000005,0x00000000,
    0x00000000,
};

const uint16 ArrowRightSignMap[9] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0000,0x0002,0x0003,0x0004,0x0005,0x0006,
    0x0007,
};
