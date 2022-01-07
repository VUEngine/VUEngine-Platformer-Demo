//---------------------------------------------------------------------------------------------------------
//
//	Level_1_House_Light
//  • 56×40 pixels
//  • 10 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 7×5 map, not compressed
//  Size: 164 + 70 = 234
//
//---------------------------------------------------------------------------------------------------------

const uint32 Level_1_House_LightTiles[41] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0xC0000000,
    0xFC00F000,0x03C00300,0x03FC03F0,0x3FFF0FFF,0xFFFFFFFF,0x00000000,0x00000000,0x00000000,
    0x00030000,0xFFC0FF00,0xFFFCFFF0,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
    0xFFFFFFFF,0x00FF000F,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x0F000000,0x0FFF0FFF,0x03FF03FF,
    0x03FF03FF,0x00FF00FF,0x00FF00FF,0x003F003F,0x003F003F,0x000F000F,0x000F000F,0x00030003,
    0x00030003,
};

const uint16 Level_1_House_LightMap[35] __attribute__((aligned(4))) =
{
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0001,0x0002,0x0003,0x0000,0x0000,0x0000,
    0x0001,0x0004,0x0005,0x0006,0x0007,0x0000,0x0001,0x0004,
    0x0005,0x0005,0x0005,0x0008,0x0001,0x0004,0x0005,0x0005,
    0x0005,0x0005,0x0009,
};
