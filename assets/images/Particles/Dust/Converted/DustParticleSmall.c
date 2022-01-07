//---------------------------------------------------------------------------------------------------------
//
//	DustParticleSmall
//  • 8×8 pixels
//  • 1 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 1×1 map, not compressed
//  Size: 20 + 2 = 22
//
//---------------------------------------------------------------------------------------------------------

const uint32 DustParticleSmallTiles[5] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x0BF003C0,0x02800AF0,0x00000000,
};

const uint16 DustParticleSmallMap[1] __attribute__((aligned(4))) =
{
    0x0000,
};
