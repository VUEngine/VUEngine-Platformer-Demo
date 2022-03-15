//---------------------------------------------------------------------------------------------------------
//
//  Level_1_Tower
//  • 224×224 pixels
//  • 29 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 28×28 map, not compressed
//  Size: 468 + 1568 = 2036
//
//---------------------------------------------------------------------------------------------------------

const uint32 Level_1_TowerTiles[117] __attribute__((aligned(4))) =
{
    0x00000000,0xAEB4BAB4,0xAEB4BAB4,0xAEB4BAB4,0xFFD4EAB4,0xFFF7FFF7,0xFFF7FFF7,0xFFF7FFF7,
    0xFFD5AAF7,0x7BFF7BFF,0x7AFF7BFF,0x7AAF7AFF,0x5FFF7AAA,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
    0xFFFDAAAF,0x7BFF7BFF,0x7AFF7BFF,0x7AAB7ABF,0x5FFF7AAA,0xF7BFB7BF,0xF7AFB7BF,0xF7AAB7AF,
    0xD5FFB7AA,0x07AE07AB,0x07AE07AB,0x07AE07AB,0x05FF07EA,0xFFF55554,0xEEADFBBD,0xEEADFBAD,
    0xEEADFBAD,0xFFFF5555,0xFBFFFFFF,0xFBFFFBFF,0xFAFFFAFF,0xFFFF5555,0xFFFFFFFF,0xFFFFFFFF,
    0xFFFFFFFF,0xFFFF5555,0xFBFFFFFF,0xFBFFFBFF,0xFABFFAFF,0x5FFF1555,0x7AEF7EBB,0x7AEF7ABB,
    0x7AEF7ABB,0xAABDFBAD,0x5554FFF5,0xAA945550,0xAAA4AAA4,0xFEAAFAAF,0x5555FFFF,0xAA955555,
    0xAAA6AAA6,0xAAAFFFFF,0x5555FFFF,0x5AAA5555,0x6AAA6AAA,0xFEAAFAAB,0x5555FFFF,0xAAA95555,
    0xAAAAAAAA,0xAAAFFFFF,0x5555FFFF,0x95AA5555,0xA6AAA6AA,0x7EAA7AAB,0x15555FFF,0x05AA0155,
    0x06AA06AA,0xFFD45550,0xEEB4BAB4,0xEEB4BAB4,0xEEB4BAB4,0x5FFF5555,0x7BFF7FFF,0x7BFF7BFF,
    0x7AFF7BFF,0xFFFD5555,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFD5555,0xBFFFFFFF,0xBFFFFFFF,
    0xBFFFFFFF,0x05FF0155,0x07AB07AE,0x07AB07AE,0x07AB07AE,0xEEB4BAB4,0xFFD4AAB4,0xFFD45550,
    0xAEB4FAB4,0x7AAF7AFF,0x5FFF7AAA,0xFFD55555,0xFFF7FFF7,0xFFFFFFFF,0xFFFDAAAF,0x5FFF5555,
    0x7BFF7FFF,0x7AAB7ABF,0x5FFF7AAA,0xFFFD5555,0xFFFFFFFF,0xBFFFFFFF,0xFFFDAAAF,0xD5FF5555,
    0xF7BFB7FF,0x07AA07AE,0x05FF07AA,0x05FF0155,0x07AE07AB,
};

const uint16 Level_1_TowerMap[784] __attribute__((aligned(4))) =
{
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0005,0x0006,0x0007,0x0008,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000B,
    0x000C,0x000D,0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,
    0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,
    0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,
    0x000E,0x000F,0x0010,0x0011,0x0000,0x0001,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0005,0x0006,
    0x0012,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0015,0x0016,0x0017,0x0018,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x001B,0x001C,
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0005,0x0006,0x0012,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0015,0x0016,
    0x0017,0x0018,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x001B,0x001C,0x0000,0x0001,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0005,0x0006,
    0x0007,0x0008,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000B,0x000C,0x000D,0x000E,0x000F,
    0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,
    0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,
    0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,0x0010,0x0011,
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0005,0x0006,0x0012,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0015,0x0016,
    0x0017,0x0018,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x001B,0x001C,0x0000,0x0001,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0005,0x0006,
    0x0012,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0015,0x0016,0x0017,0x0018,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x001B,0x001C,
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0005,0x0006,0x0007,0x0008,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
    0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000B,
    0x000C,0x000D,0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,
    0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,
    0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,0x000E,0x000F,
    0x000E,0x000F,0x0010,0x0011,0x0000,0x0001,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0005,0x0006,
    0x0012,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0015,0x0016,0x0017,0x0018,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x001B,0x001C,
    0x0000,0x0001,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0005,0x0006,0x0012,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,
    0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0015,0x0016,
    0x0017,0x0018,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,0x0019,0x001A,
    0x0019,0x001A,0x001B,0x001C,0x0000,0x0001,0x0002,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,
    0x0004,0x0003,0x0004,0x0003,0x0004,0x0003,0x0005,0x0006,
};
