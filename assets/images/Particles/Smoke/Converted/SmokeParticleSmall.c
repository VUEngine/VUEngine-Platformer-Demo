//---------------------------------------------------------------------------------------------------------
//
//	SmokeParticleSmall
//  • 8×32 pixels
//  • 4 tiles, not compressed
//  • 1×4 map, not compressed
//  Size: 68 + 8 = 76
//
//---------------------------------------------------------------------------------------------------------

const uint32 SmokeParticleSmallTiles[17] __attribute__((aligned(4))) =
{
    0x00000000,0x0FC00000,0xBFFF2FFC,0xAFFEBFFF,0x0AA02AE8,0x0BC00000,0x2FFC2FF0,0x2BF82FFC,
    0x00000AA0,0x00000000,0x0BF003C0,0x02800BF0,0x00000000,0x00000000,0x03C00000,0x00000280,
    0x00000000,
};

const uint16 SmokeParticleSmallMap[4] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,
};
