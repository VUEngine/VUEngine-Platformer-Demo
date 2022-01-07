//---------------------------------------------------------------------------------------------------------
//
//	CannonBall
//  • 24×24 pixels
//  • 9 tiles, not compressed
//  • 3×3 map, not compressed
//  Size: 148 + 18 = 166
//
//---------------------------------------------------------------------------------------------------------

const uint32 CannonBallTiles[37] __attribute__((aligned(4))) =
{
    0x00000000,0x40000000,0xA9009400,0xFA90EA40,0xFEA4FA90,0x7FA91554,0xFFFFFFFA,0xFFFFFFFF,
    0xFFFFFFFF,0x00010000,0x007F0017,0x07FF01FF,0x1FFF07FF,0x7FA9FEA4,0xFFA97FA9,0xFFA9FFA9,
    0xFEA4FFA9,0x7FFDFFFF,0x5FF55FF5,0xFFFFFFFF,0xFFFFFFFF,0x7FFD1FFF,0x7FFF7FFD,0x7FFF7FFF,
    0x1FFF7FFF,0xFA90FEA4,0xEA40FA90,0x9400A900,0x00004000,0xFFFFFFFF,0xFFFFFFFF,0xFFFAFFFF,
    0x15547FA9,0x07FF1FFF,0x01FF07FF,0x0017007F,0x00000001,
};

const uint16 CannonBallMap[9] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,
    0x0008,
};
