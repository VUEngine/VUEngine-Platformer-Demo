//---------------------------------------------------------------------------------------------------------
//
//  TorchOff
//  • 8×16 pixels
//  • 2 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 1×2 map, not compressed
//  Size: 36 + 4 = 40
//
//---------------------------------------------------------------------------------------------------------

const uint32 TorchOffTiles[9] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x10100000,0x2AA02560,0xFFFC1550,0x0540FFFC,0x0A800A80,0x00000200,
    0x00000000,
};

const uint16 TorchOffMap[2] __attribute__((aligned(4))) =
{
    0x0000,0x0001,
};
