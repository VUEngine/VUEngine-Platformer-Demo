//---------------------------------------------------------------------------------------------------------
//
//	Overworld_1
//  • 384×224 pixels
//  • 331 tiles, reduced by non-unique and flipped tiles, not compressed
//  • 48×28 map, not compressed
//  Size: 5300 + 2688 = 7988
//
//---------------------------------------------------------------------------------------------------------

const uint32 Overworld_1Tiles[1325] __attribute__((aligned(4))) =
{
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0xA8000000,0xBFFCABC0,
    0xFFFEFFFC,0x00000000,0x00000000,0xFC00C000,0xFFFCFFC0,0xFC00C000,0xFFFCFFC0,0xFFFFFFFF,
    0xFFFFFFFF,0xFFFAFFFA,0xFFAAFFEA,0xAAAAFAAA,0xAAABAAAA,0x00000000,0x00020000,0x02AA002A,
    0x0AAB02AA,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x003F0003,0x3FFF03FF,0xFFFFFFFF,
    0x3FFF3FFF,0x00000000,0xABC0A800,0xFFFCBFFC,0xFFFAFFFE,0x00000000,0x002A0002,0xF2AAC2AA,
    0xCAABCAAB,0xF0000000,0xFF00FF00,0xFE80FF80,0xFA80FE80,0x0AAA00AA,0xAABFAAAF,0xAAFFAAFF,
    0xAAFFAAFF,0xAAAFAAAB,0xAAFCAABC,0xFFF2AFF2,0xFFF2FFF2,0x00000000,0x00000000,0x28000000,
    0x2B003E80,0xCAAB8AAB,0x0AAB8AAB,0xCAAB8AAB,0xCA568AA6,0xEBEBAAAA,0xEBEABEBE,0xEA2BBEA2,
    0x2BEBA2BE,0xEBEBAAAA,0xEBEBBEBE,0xEBEBBEBE,0xEBEABEBE,0xEBEBAAAA,0xEBEBBEBE,0xEBEBBEBE,
    0xEBEBBEBE,0xE8AB8A2A,0xEBE8BE8A,0xEBEBBEBE,0xEBEBBEBE,0xFC28FFC0,0x2AA8C2A8,0xAAA8AAA8,
    0xAAA8AAA8,0xFFFFFFFF,0xFFFCFFFF,0xFC2AFFC2,0x2AAAC2AA,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
    0xFFFCFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x0FFFFFFF,0x3FFF3FFF,0x3FFF3FFF,0x3C3F03FF,
    0x30AA3F00,0xFFEAFFFA,0xFAAAFFAA,0xAAAAAAAA,0xAAABAAAB,0xCAABCAAB,0x0AABCAAB,0x8AA68AAB,
    0x85568A56,0xFFFFFFFF,0x3FFFFFFF,0x543F43FF,0x55545543,0x143F03FF,0x15541543,0x15551555,
    0x15551555,0xAA80EA80,0xAA80AA80,0xAAC0AAC0,0xAFC0ABC0,0xAAFEAAFF,0xA9AAAAEA,0x55AA95AA,
    0x55AA55AA,0xFFF2FFF2,0xFFA2FFE2,0xAAA1FAA2,0xAAA1AAA1,0x00000000,0x00000000,0xE8008000,
    0xEBE8BE80,0xF0000000,0xFF28FF00,0xFE8BFF8E,0xFA8BFE8E,0x0AAA30AA,0xAABFAAAF,0xAAFFAAFF,
    0xAAFFAAFF,0xC5568556,0xC5568556,0xC5568556,0xC5AB855B,0xEBEBBEBE,0xEBEBBEBE,0xEBEBBEBE,
    0xEBEBBEBE,0xEA2BBEA2,0x2BEBA2BE,0xEBEBBEBE,0xEBEBBEBE,0xEBEBBEBE,0xEBEABEBE,0xEA2BBEA2,
    0x2BEBA2BE,0xEBEBBEBE,0xABEBBEBE,0x5413000E,0x15554154,0xE8AB8ABE,0xEBE8BE8A,0x55550000,
    0x55545555,0xEBEBBEBE,0xEBEBBEBE,0x15558000,0x55555555,0xEBEBBEBE,0xEBEBBEBE,0xEBE8BEBE,
    0xE815BE81,0xAAA8AAA8,0xAAA8AAA8,0xAAA8AAA8,0xAAA8AAA8,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,
    0xAAAAAAAA,0xFC2AFFC2,0x2AAAC2AA,0xAAAAAAAA,0xAAAAAAAA,0xFFFFFFFF,0x3FFFFFFF,0xFC3FC3FF,
    0xFFFCFFC3,0xFF3FF0FF,0xFF8CFF03,0xFE8FFE8F,0xEA8FFA8F,0xAAAF0AAA,0xAAFFAABF,0xAAFFAAFF,
    0xAAFFAAFF,0xAABCAAAF,0xAFF2AAFC,0xFFF2FFF2,0xFFF2FFF2,0x85568556,0x85568556,0x855B8556,
    0x86AB85AB,0x543F43FF,0x55545543,0x55555555,0x55555555,0x55555555,0x55555555,0x55555555,
    0x55555555,0x15551555,0x15551555,0x15551555,0x15551555,0xFFC0BFC0,0xFFC0FFC0,0xFE80FF80,
    0xFA80FE80,0x55AB55AA,0x56FF55BF,0xAAFF6AFF,0xAAFFAAFF,0xAAA1AAA1,0xAAF1AAB1,0xFFF2AFF1,
    0xFFF2FFF2,0xE8008000,0xEBE8BE80,0xEBEBBEBE,0xEBEBBEBE,0xAA8BEA8E,0xAA8AAA8E,0xAACBAAC2,
    0xAFCBABCE,0xC6AB86AB,0xC6AB86AB,0xC6AB06AB,0xE256C6A6,0xEBEBBEBE,0x2A83803E,0xABFFAABC,
    0xBFFFAFFF,0xEBEBBEBE,0xABE8BEBE,0xE82A8A82,0x28AABE2A,0x50AB4ABE,0x5528548A,0x5553554E,
    0x55555554,0x54155541,0x15554155,0x55555555,0x55555555,0x55555555,0x55545555,0x54155541,
    0x15554155,0x15558155,0x55555555,0x55555555,0x55545555,0xAAA8AAA8,0xA815AA81,0x15558155,
    0x55555555,0xAAAAAAAA,0xAAAAAAAA,0xAAA8AAAA,0xA815AA81,0xAA8FAA8F,0xAACCAA8F,0xABCAAAC2,
    0xBFCAAFCA,0xAAEAAAFE,0x95AAA9AA,0x55AA55AA,0x55AA55AA,0xFFE2FFF2,0xFAA2FFA2,0xAAA1AAA1,
    0xAAA1AAA1,0x86AB86AB,0x06AB86AB,0xC6A6C6AB,0xA156E256,0x802AAAAA,0xAABC2A82,0xAFFFABFF,
    0xBFFFBFFF,0xAAAAAAAA,0xAA82AAA8,0xAA2AAA2A,0xA8AAA8AA,0xAA8BEA8A,0xAA8BAA8E,0xAACBAACE,
    0xAFCBABCE,0xFFCBBFCE,0xFFCBFFCE,0xFE8BFF8E,0xFA8BFE8E,0xA156A156,0xA156A156,0xA156A156,
    0xB1ABA15B,0xBFFFBFFF,0xBFFABFFE,0xBAAABFAA,0x2AAA6AAA,0x50AA4CAA,0x552A54AA,0x5552554A,
    0x55555554,0x00154141,0x00210001,0x2AA102A1,0x2AA12AA1,0x55545555,0x54005540,0x54545440,
    0x14554055,0xAAA8AAAA,0xA815AA81,0x15558155,0x55555555,0xFFCAFFCA,0xFF8AFFCA,0xFE8AFE8A,
    0xEA8AFA8A,0x55BF55AB,0x6AFF56FF,0xAAFFAAFF,0xAAFFAAFF,0xAAB1AAA1,0xAFF1AAF1,0xFFF2FFF2,
    0xFFF2FFF2,0xA156A156,0xA156A156,0xA15BA156,0xB2ABB1AB,0xBFFEBFFF,0xBFAABFFA,0x6AAABAAA,
    0x6AAA6AAA,0xA8AAA8AA,0xA8AAA8AA,0xA8AAA8AA,0xA855A8A5,0x15551555,0x15551555,0x15551555,
    0x81551555,0xEBEBBEBE,0xABEBBEBE,0xE8AB8ABE,0xE82ABE80,0xFFCBBFCE,0xFFC8FFCA,0xFE8BFF8E,
    0xFA8BFE8A,0xAAA1AAA1,0xAAF1AAB1,0x0022AFC1,0xEBE2AAA2,0x80000000,0xFFC0BC00,0xFFE0FFC0,
    0xFFA0FFA0,0xE82ABE80,0x2AAB82AA,0xAABF2AAF,0xAABFAABF,0xEBEBBEBE,0xEBEABEBE,0xEA28BEA2,
    0x2BE8A2BC,0xEBEBBEBE,0xEBEBBEBE,0xEBEBBEBE,0xEBEABEBE,0xAA8BEA8E,0xAA8BAA8E,0xAACBAACE,
    0xAFCBABCE,0xF2ABB2AB,0xF2ABF2AB,0xF2ABF2AB,0xE256F2A6,0x2AAA4AAA,0x6AAF6AAB,0x6FFF6AFF,
    0xBFFFBFFF,0x55545555,0x54215541,0x2BF142B1,0xFEA2BFE1,0x55555555,0x55555555,0x55545555,
    0x542B5542,0x2AA12AA1,0x2AA12AA1,0x20552A05,0x55550555,0x54555455,0x55455515,0x55545551,
    0x55555555,0x54155541,0x15554155,0x55555555,0x05551555,0x55555555,0x55545555,0x00000001,
    0x00000000,0x15558155,0x55555555,0x00000000,0x00000000,0xAA8AAA8A,0xAACAAA8A,0xABCAAACA,
    0xBFCAAFCA,0xF2ABF2AB,0xF2ABF2AB,0xF2A6F2AB,0xA156E256,0x6AAB6AAA,0x6AFF6AAF,0xBFFF6FFF,
    0xBFFFBFFF,0xA855A855,0xA855A855,0xA855A855,0xA8AAA85A,0xFFC5BC15,0xFFE1FFC5,0xFFA1FFA1,
    0xFAA1FEA1,0x2AAB82AA,0xAABF2AAF,0xAABFAABF,0xAABFAABF,0xA0ABEA2E,0xEBE80ABE,0xEA28BEA0,
    0x2BE8A2BC,0x0AFEAAFF,0xEBEBA000,0xEBEBBEBE,0xEBEABEBE,0xEBEABEB8,0xEBEBBEBE,0xEBEBBEBE,
    0xEBEBBEBE,0xFAA0FEA0,0xAAA0AAA0,0xAAB0AAA0,0xAAF0AAB0,0xAABFAABF,0xAABAAABF,0xA56AAA6A,
    0x556A556A,0xEBE8BEBC,0xEBE8BEBC,0xEBE8BEBC,0xEBE8BEBC,0xFFCBBFCE,0xFFC8FFCA,0xFE8FFF8E,
    0xFA8BFE8A,0xA156A156,0xA156A156,0xA280A016,0xB3EBA2AA,0xBFFFBFFF,0xBFFABFFE,0xBAAABFAA,
    0x6AAA6AAA,0xFA82FAA2,0xFFE2F832,0xFEA2FEA2,0xFF31FE82,0x2BFF42BF,0xFFFFBFFF,0xFFFFFFFF,
    0xFFFFFFFF,0x55545555,0x542B5542,0x2BFF42BF,0xFFFFBFFF,0x55555555,0x55555555,0x55555555,
    0x05551555,0x00550155,0x00050015,0x00000001,0x00000000,0x00000000,0x00000000,0xA8008000,
    0x2AA8AA80,0xA8008000,0xA8280280,0xBFFCABC2,0xFFFEFFFC,0xAAA8AAA8,0x2A82AAA8,0xF2AAC02A,
    0xCAABF2AA,0xFFCAFFCA,0xFF8CFFC2,0xFE8BFE8F,0xEA2FFA8B,0xAAB1AAA1,0xAFC1AAF1,0xAAA20022,
    0xFFF8FFE2,0xA156A156,0xA016A156,0xA3EAA280,0xB3FFB3FF,0xA8AAA8AA,0x3CAA80AA,0xFCAAFCAA,
    0xFC55FCA5,0xAAAAAAAA,0xAAA8AAAA,0xA83FAA83,0x3FFF83FF,0xAAA1AAA1,0xAAB1AAA1,0xAAF1AAB1,
    0xAFF1ABF1,0xAABAAABF,0xA56AAA6A,0x556A556A,0x556A556A,0xAFF0ABF0,0xFFF0FFF0,0xFFE0FFF0,
    0xFFA0FFA0,0x556A556A,0x556F556A,0x5ABF55BF,0xAABFAABF,0xEBE8BEBC,0xEBE8BEBC,0xEBE8BEBC,
    0xABE8BEBC,0xA0ABEA2E,0xABEA0ABE,0xEA2BBEA2,0x2BEBA2BE,0x0AFEAAFF,0xEAAAA000,0xEBEBBEBE,
    0xEBEABEBE,0xF2EBB2BE,0xCAEBF2BE,0xABEB2EBE,0xEBEBBEBE,0x6AAA6AAA,0x6AAF6AAB,0x00026AFC,
    0xABEBAAAA,0xFFE1FFF1,0xFAA1FEA1,0xF830FA80,0xFEA0FFE2,0x80AFFAFF,0xC0F23F0B,0xAAB22A32,
    0xAAB2AAB2,0xFFFFFFFF,0xFFFCFFFE,0xFFE3FFF3,0xFF8EFF8C,0x55555555,0x55555555,0x55545555,
    0x042B1542,0x00550155,0x00050015,0xA8008001,0xAAA8AA80,0xA8008000,0xAAA8AA80,0xAAAAAAAA,
    0xAAAAAAAA,0x2AAA2AAA,0x2AAA2AAA,0x2AAA2AAA,0x2A002AAA,0xCAABCAAB,0x0AABCAAB,0x8AAB8AAB,
    0x8A568AA6,0x0AFFA0BF,0xFFFCAFFF,0xFC2AFFC2,0x2AAAC2AA,0xA0000AFE,0xFFFFFAAA,0xFFFFFFFF,
    0xFFFCFFFF,0xFFFFFFFE,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xF2FFF3FF,0x2FFFCBFF,0xFFFFBFFF,
    0xFFFFFFFF,0x6AAB6AAA,0x6AFC6AAF,0xAAAB0002,0x3FFFFFFF,0xF855F855,0x3F81FE15,0x543E43E8,
    0x55545543,0x55555554,0x55555554,0x55555554,0x55555554,0xFFF1FFF1,0xFFE1FFF1,0xFFA1FFA1,
    0xFAA1FEA1,0x556F556A,0x5ABF55BF,0xAABFAABF,0xAABFAABF,0xE8A88ABC,0xEBE8BE88,0xEBE8BEBC,
    0xEBE8BEBC,0xEBEBBEBE,0xEBEABEBE,0xEA2BBEB2,0x2BEBA2BE,0xFE83FEA2,0xFFF3FF32,0xFFE3FFF2,
    0xEA83FEA2,0xAAB2AAB2,0xAAB2AAB2,0xEAB2AAB2,0xAAB22AB2,0xFF8EFF8E,0xFF8EFF8E,0xFF8EFF8E,
    0xFF8EFF8E,0xFFFFFFFF,0xBFFFFFFF,0xCBFF2FFF,0xF2FF32FF,0xFFFFFFFF,0xFFFEFFFF,0xFF83FFE8,
    0xF8CFFE3F,0xABFF82BF,0xFEFFBFFF,0xAAFFEAFF,0x97FFABFF,0xAAAAAAAA,0xAA6AAAAA,0xAA55AA55,
    0xAA81AA95,0xF0AA0AAA,0xFF2AFF2A,0xFE8AFF8A,0xFA8AFE8A,0x0AAA20AA,0xAABFAAAF,0xAAFFAAFF,
    0xAAFFAAFF,0x85568556,0x85568556,0x85568556,0x85AB855B,0x55555555,0x55555555,0x55555555,
    0x15555555,0x55555554,0x55555554,0x55555554,0x55545554,0xAFF0ABF0,0xFFF0FFF0,0xFFE3FFF2,
    0xFFA3FFA2,0xEBE8BEBC,0xEBE8BEBC,0xEA28BEA0,0x2BE8A2BC,0xE8AB8ABE,0xEBE8BE8A,0xEBEBBEBE,
    0xAAABAABE,0x83EBA83E,0xEBEB3EBE,0xEBEBBEBE,0xEBEABEBE,0xAAB2AAB2,0xAA83AAB0,0x83EBA83E,
    0xEBEB3EBE,0xFF8EFF8E,0xFF8EFF8E,0xFF8EFF8E,0xEA83FE8C,0xF8FFF8FF,0xFE3CF8CF,0xFFEBFF82,
    0xFFFFFFFF,0xEBFF7FFF,0xABFFABFF,0x7FFF9FFF,0xEAFFFEFF,0xAA96AAA8,0xAA95AA95,0xAAA8AAA1,
    0xAA56AA6A,0xAA8AEA8A,0xAA8AAA8A,0xAACAAACA,0xAFCAABCA,0x86AB86AB,0x86AB86AB,0xC6AB06AB,
    0xE256C6A6,0xAAAAAAAA,0x2A82802A,0xABFFAABC,0xBFFFAFFF,0xAAAAAAAA,0xAAA8AAAA,0xAA2AAA82,
    0xA8AAAA2A,0x55555555,0x15555555,0xFC15C155,0xFFFCFFC1,0xFC15C155,0xFFFCFFC1,0xFFFFFFFF,
    0xFFFFFFFF,0x55555555,0x15555555,0xE8158155,0xEBE8BE81,0xFFF1FFF1,0xFFE0FFF1,0xFFA3FFA2,
    0xFAA3FEA2,0xFAA3FEA2,0xAAA3AAA2,0xAAB3AAA2,0xAAF2AAB2,0xABEBBEBE,0x2AABAABE,0xFC2BC2AE,
    0xFFCAFFCA,0xFC2A02AA,0xFFFCFFC2,0x03FFFFFF,0xAAFFA8FF,0x83EBA83E,0xABEB3EBE,0xE8AB8ABE,
    0xEBE8BE8A,0xFFEAFFFE,0xEA80FEA8,0x83EBA83E,0xEBEB3EBE,0xFFFFFFFF,0xFFFFFFFF,0xFFEAFFFE,
    0xEA83FEA8,0xABFFAAFF,0x7FFF97FF,0xABFFEBFF,0x9FFFABFF,0xAA95AA55,0xAAA8AA81,0xAA95AA96,
    0xAAA1AA95,0xFFCABFCA,0xFFCAFFCA,0xFE8AFF8A,0xFA86FE8A,0xA8AAA8AA,0xA8AAA8AA,0xA8AAA8AA,
    0xA8A5A8AA,0x55545554,0x15545554,0xFC14C154,0xFFFCFFC0,0xAAA3AAA2,0xAAB3AAA2,0xAAF2AAB2,
    0xAFCBABF2,0xAABAAABF,0xA56AAA6A,0x556A556A,0x156A556A,0xEBE8BEBC,0xEBE8BEBC,0xEBE8BEBC,
    0xEBEABEB8,0xE828BE80,0x2AA882A8,0xAAA8AAA8,0xAAA8AAA8,0xEBEBBEBE,0xEBE8BEBE,0xE82ABE82,
    0x2AAA82AA,0xEBEBBEBE,0xEBEBBEBE,0xEBEBBEBE,0xEBE8BEBE,0xAFCBABF2,0x02ABFC2E,0xEBEBAABE,
    0xEBEBBEBE,0x156A556A,0xE800816A,0xEBEBBEAA,0xEBEBBEBE,0xEBEABEB8,0xEBEBBEBE,0xEBEBBEBE,
    0xABEBBEBE,0xFC2BFFCA,0x2AABC2AE,0xABEBAABE,0xEBEABEBE,0xABFFAAFF,0xFFFCFFFF,0xFC2AFFC2,
    0xAAAB02AA,0xFFEAFFAA,0xFFFFFFFF,0x3C3FFFFF,0xAAAA8280,0xA83FA3FF,0xA83F83FF,0x2AA8AA83,
    0xFC2AC2AA,0xEBEABEBE,0xAAAABEAA,0xA83CAA82,0xA83F83FF,0xE8AB8ABE,0xEBE8BE8A,0xEBEABEBE,
    0xEAAABEAA,0xFFEA7FFE,0xEA83FEA8,0x83EBA83E,0xEBEB3EBE,0x56AA6AA8,0xC156156A,0xEBC1BC15,
    0xEBEBBEBC,0xAA81EA85,0xAA8BAA8C,0xAACBAACE,0xAFCBABCE,0x6AAA6AAA,0x6AAF6AAB,0x6FFF6AFF,
    0xBFFFBFFF,0xA855A855,0xA855A855,0xA855A855,0xA85AA855,0x02ABFC2E,0xEBEBAABE,0xEBEBBEBE,
    0xEBEBBEBE,0xE800816A,0xEBEBBEAA,0xEBEBBEBE,0xEBEBBEBE,0xE82ABE82,0x2AAA82AA,0xAAAAAAAA,
    0xAAAAAAAA,0xEBEBAABE,0xEBEABEBE,0xEA2BBEA2,0x2BEBA2BE,0xABEBAAAA,0xABEBBEBE,0xE8AB8ABE,
    0xEBE8BE8A,0x3C2AFFC2,0xAAA882AA,0xABEBAABE,0xEBEBBEBE,0x2AA8AA83,0xFC2AC2AA,0xFC2AFFC2,
    0x2AABC2AA,0xA83CAA82,0x3FFF83FF,0xFFFFFFFF,0xFFFCFFFF,0xEBEABEBE,0xEAA8BEAA,0xE83FAA83,
    0xE8FFA8FF,0xA8AAA8AA,0x28AA80AA,0xE8AABCAA,0xE8A5BCAA,0xAAAAAAAA,0xAAA8AAAA,0xA82BAA82,
    0x2BEB82BE,0xE8158155,0xEBE8BE81,0xEBEBBEBE,0xEBEBBEBE,0xEBEBBEBE,0xABEBBEBE,0xE8AB8ABE,
    0x0000AA8A,0xE8AB8ABE,0xEBE8BE8A,0xEBEBBEBE,0x0000AAAA,0xEBEBBEBE,0xEBEBBEBE,0xEBEBBEBE,
    0x0000AAAA,0xAAA8AAA8,0xA954AA94,0x55549554,0x55545554,0xAAAAAAAA,0xAAAAAAAA,0xAAA9AAAA,
    0xA955AA95,0xE828BE82,0x2AA882AA,0xAAA8AAAA,0xAAA8AAAA,0x80AB0ABE,0xFFC8BC0A,0xFFE3FFCE,
    0xFFA3FFA2,0xABEBAABE,0xEBEBBEBE,0xEBEBBEBE,0xEBEABEBE,0xFF2AFFC2,0xFF2BFF2A,0xFF2BFF2A,
    0xFF2BFF2A,0xE8FFA8FF,0xE8FFA8FF,0xE8FFA8FF,0xE8FFA8FF,0xA0ABEA2E,0xEBEA0ABE,0xEA2BBEA2,
    0x2BEBA2BE,0xF2EBB2BE,0xCAEBF2BE,0xEBEB2EBE,0xEBEBBEBE,0x6AAA6AAA,0x6AAF6AAB,0x00026AFC,
    0xABEBBEBE,0xE855BC55,0xAA15B855,0xE8A88A81,0xEBE8BE8A,0xA82BAA82,0x2BEB82BE,0xEBEBBEBE,
    0xEBEBBEBE,0x55545554,0x15545554,0xE8148154,0xEBE8BE80,0xEBEBBEBE,0x2BEBBEBE,0x542B42BE,
    0x55545542,0x842B82BE,0x85548542,0x85558555,0x85558555,0x55545554,0x55545554,0x55545554,
    0x55405554,0x55559555,0x55555555,0x55555555,0x55555555,0xAAA9AAAA,0xA955AA95,0x55559555,
    0x55555555,0xAAA8AAAA,0xAAA8AAAA,0xAAA8AAAA,0xAAA8AAAA,0xFAA3FEA2,0xAAA3AAA2,0xAAB3AAA2,
    0xAAF3AAB2,0xFF2BFF2A,0xFF2AFF2A,0xFF2BFF2A,0xFF2BFF2A,0xEA2BBEA2,0x2BEBA2BE,0xEBEBBEBE,
    0x2BEBBEBE,0xEBEBBEBE,0xA82A02BE,0xBFFCABC2,0xFFFEFFFC,0xEBEBBEBE,0xABC2BEBC,0xE2AA882A,
    0xCAABB2AA,0xEA2BBE82,0x2BEBA2BE,0xEBEBBEBE,0xEBEBBEBE,0x542B42BE,0x55545542,0x55555555,
    0x55555555,0x85558555,0x85558555,0x85558555,0x85558555,0x41405414,0x40401404,0x40000400,
    0x00000100,0x55555555,0x55415554,0x41405414,0x40401404,0x55555555,0x55555555,0x55555555,
    0x55415554,0xAAA8AAAA,0xA954AA95,0x55549555,0x55545555,0xAFF3ABF2,0xFFF3FFF2,0xFFE3FFF2,
    0xFFA3FFA2,0xFF2BFF2A,0xFF28FF2A,0xFF2BFF2A,0xFF2BFF2A,0x2BEB3EBE,0x2BEB3EBE,0x28AB0ABE,
    0x2B003E8A,0x28AB0ABE,0x2BE82E8A,0x2BEB2EBE,0x2BEB2EBE,0x55555555,0x55555555,0x01551555,
    0x00010015,0x41558555,0x40014015,0x40004000,0x40004000,0x5555AAAA,0x55555555,0x55555555,
    0x55555555,0x40000401,0x00000100,0x00000000,0x00000000,0x41405414,0x40401404,0x40000401,
    0x00000100,0x55545555,0x55545555,0x55545555,0x55405554,0xFAA3FEA2,0xAAA0AAA2,0xAAB2AAA2,
    0xAAF2AAB2,0xF0AB0ABE,0xFF28FF0A,0xFE8BFF8E,0xFA8BFE8E,0x2BEB2EBE,0x2BEB2EBE,0x2BEB2EBE,
    0x2BEB2EBE,0x01551555,0x00010015,0x00000000,0x00000000,0x40004000,0xA8000000,0xBFFCABC0,
    0xFFFEFFFC,0x55555555,0x55425554,0x52AA542A,0x4AAB02AA,0x55555555,0x55555555,0x55555555,
    0x55550000,0xAAAAAAAA,0xAAAAAAAA,0xAAA9AAAA,0x2955AA95,0xAFF2ABF2,0xFFF0FFF2,0xFFE3FFF2,
    0xFFA3FFA2,0xEBEBBEBE,0xABE8BEBE,0xE82A8A82,0xE8AABE2A,0x4AAB0AAB,0x0AAB0AAB,0x0AAB0AAB,
    0x0A560AA6,0x44440000,0x00000000,0x00000101,0x00000000,0x55545555,0x15545555,0xE8148155,
    0xEBE9BE80,0xE8AABCAA,0xE8AABCAA,0xE8AABCAA,0xE8A5BCAA,0x2BEB2EBE,0x2BEA2EBE,0x2A2B2EA2,
    0x2BEB22BE,0x05560556,0x05560556,0x05560556,0x05AB055B,0xE855BC55,0xE855BC55,0xE855BC55,
    0xE85ABC55,0x142B12BE,0x15541542,0x15551555,0x15551555,0x06AB06AB,0x06AB06AB,0xC6AB06AB,
    0xE256C6A6,0x00000000,0x2A800000,0xABFFAABC,0xBFFFAFFF,0x00000000,0x00000000,0x002A0002,
    0x00AA002A,0xFF2AFF2A,0xFFFCFFC2,0x03FFFFFF,0xAAFFA8FF,0xE8AABCAA,0x28AAA0AA,0xE8AABCAA,
    0xE8A5BCAA,0x00AA00AA,0x00AA00AA,0x00AA00AA,0x00A500AA,0xFFEAFFAA,0xFFFFFFFF,0xFC3FFFFF,
    0x2AAAC280,0xA83FA3FF,0x3FFF83FF,0xFFFFFFFF,0xFFFCFFFF,0xEBEABEBE,0xAAA8BEAA,0xA83FAA83,
    0x3FFF83FF,0xE8AB8ABE,0xEBE8BE8A,0xEBEABEBE,0xEAA8BEAA,0x6AAA6AAA,0x6AAF6AAB,0x00026AFC,
    0x2BEBBEBE,0xE855BC55,0x2A15B855,0x54284281,0x55545542,0x142B42BE,0x15545542,0x15555555,
    0x15555555,0x55555555,0x55555555,0x15555555,0x00150155,0x15551555,0x00150155,0x00000001,
    0x00000000,0xE855A855,0xE855BC55,0xE855BC55,0xE85ABC55,0xFC2AFFC2,0x2AA8C2AA,0xABEBAABE,
    0xEBEBBEBE,0xFFFFFFFF,0xFFFCFFFF,0xFC2AFFC2,0x2AABC2AA,0xA83FAA83,0x3FFF83FF,0xFFFFFFFF,
    0xFFFCFFFF,0xEBEABEBE,0xEAA8BEAA,0xA83FAA83,0x3FFF83FF,0xEBEBBEBE,0xEBEBBEBE,0xEBEABEBE,
    0xEAA8BEAA,0x15555555,0x00150155,0x00000001,0x00000000,0x00000001,0x00000000,0x00000000,
    0x00000000,0xFFC0BFC0,0xFFC8FFC0,0xFE8FFF8E,0xFA8BFE8A,0xFC2AFFC2,0x2AABC2AA,0xABEBAABE,
    0xEBEBBEBE,0xEBEABEBE,0x2AA8BEAA,0xA83FAA83,0x3FFF83FF,0x142B42BE,0x15545542,0x142A5542,
    0x2AA842AA,0xABEBAABE,0x2BEBBEBE,0x542B42BE,0x55545542,0xFC2AFFC2,0x2AA8C2AA,0xA815AA81,
    0x15558155,0xFFFFFFFF,0xFFFCFFFF,0xFC2AFFC2,0x2AA8C2AA,0x542A5542,0x2AA842AA,0xA83FAA83,
    0x3FFF83FF,0x15555555,0x00140155,0x002A0002,0x2AA802AA,0xA815AA81,0x15558155,0x15555555,
    0x00150155,0xFC2AFFC2,0x2AA8C2AA,0xA800AA81,0x00008000,0x002A0002,0x2AA802AA,0xA83FAA83,
    0x3FFF83FF,0xE8008000,0xEBE8BE00,0xEBEABEBE,0xEAA8BEAA,
};

const uint16 Overworld_1Map[1344] __attribute__((aligned(4))) =
{
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0002,0x0003,
    0x2003,0x2002,0x0000,0x0000,0x0000,0x0000,0x0002,0x0003,
    0x2003,0x2002,0x0000,0x0000,0x0000,0x0000,0x0000,0x0004,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0001,0x0005,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0002,0x0003,0x0006,0x0006,
    0x0006,0x0006,0x0007,0x0008,0x0009,0x0003,0x0006,0x0006,
    0x0006,0x0006,0x2003,0x2002,0x0000,0x000A,0x000B,0x000C,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x000D,0x0004,0x000E,0x000F,0x0010,0x0011,
    0x0011,0x2010,0x200F,0x0012,0x0013,0x0014,0x0015,0x0006,
    0x0006,0x0016,0x0017,0x0018,0x0019,0x0014,0x0015,0x0006,
    0x0006,0x2015,0x001A,0x001B,0x0000,0x001C,0x001D,0x001E,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x001F,0x0020,0x0021,0x000C,0x0022,0x0023,0x0024,0x0025,
    0x0026,0x0027,0x0028,0x0029,0x002A,0x002B,0x002C,0x0014,
    0x002D,0x002E,0x002F,0x0030,0x0031,0x002B,0x002C,0x0014,
    0x001A,0x0032,0x0033,0x0034,0x0000,0x0035,0x0036,0x0037,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x001F,0x0038,
    0x0024,0x0039,0x001D,0x001E,0x003A,0x003B,0x003C,0x003D,
    0x0033,0x003E,0x003F,0x0040,0x0041,0x0042,0x002B,0x002B,
    0x0013,0x0043,0x0044,0x0045,0x0046,0x0047,0x0048,0x002B,
    0x2034,0x0033,0x0033,0x0034,0x0011,0x0049,0x001D,0x001E,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x001F,0x0038,0x0023,0x0023,
    0x0023,0x004A,0x0036,0x0037,0x004B,0x004C,0x004D,0x0033,
    0x0033,0x0033,0x0033,0x004E,0x004F,0x0040,0x0050,0x0042,
    0x002A,0x0051,0x0052,0x0053,0x0054,0x0055,0x0056,0x002B,
    0x2034,0x0033,0x0033,0x0057,0x0058,0x0059,0x0036,0x005A,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x005B,0x005C,0x005D,0x005E,0x0023,
    0x0023,0x005F,0x001D,0x001E,0x0060,0x0061,0x0062,0x0063,
    0x0033,0x0033,0x0033,0x0064,0x0065,0x0066,0x0067,0x0068,
    0x002A,0x0069,0x0044,0x0045,0x006A,0x006B,0x006C,0x002B,
    0x2034,0x0033,0x0033,0x006D,0x006E,0x006F,0x0070,0x0071,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0072,0x0073,0x0074,0x0024,0x0025,
    0x2025,0x0075,0x0036,0x005A,0x0076,0x0077,0x0078,0x0079,
    0x007A,0x0063,0x0033,0x0033,0x007B,0x007C,0x007D,0x007E,
    0x007F,0x0080,0x0052,0x0081,0x0082,0x0055,0x0083,0x0084,
    0x2034,0x0033,0x0033,0x0085,0x0086,0x0074,0x0024,0x0025,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0087,0x0088,0x0089,0x2025,0x2024,
    0x0024,0x008A,0x008B,0x0071,0x008C,0x008D,0x008E,0x008F,
    0x0090,0x0079,0x007A,0x0091,0x0092,0x0093,0x0094,0x0004,
    0x0095,0x0096,0x0097,0x0098,0x0099,0x009A,0x009B,0x0032,
    0x009C,0x0033,0x0033,0x009D,0x009E,0x0089,0x2025,0x2024,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0072,0x0073,0x009F,0x0023,0x0023,
    0x0023,0x0023,0x0024,0x00A0,0x2025,0x2024,0x00A1,0x00A2,
    0x00A3,0x00A4,0x00A5,0x00A6,0x00A7,0x00A8,0x00A9,0x000C,
    0x00AA,0x002B,0x002C,0x0014,0x001A,0x0032,0x0033,0x00AB,
    0x00AC,0x0033,0x0033,0x0085,0x0086,0x009F,0x0023,0x0023,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x001F,0x00AD,0x0088,0x00AE,0x005E,0x0023,
    0x0023,0x205E,0x2025,0x00AF,0x20AF,0x0025,0x00B0,0x00B1,
    0x00B2,0x10A4,0x00B3,0x00B4,0x00B5,0x00B6,0x001D,0x001E,
    0x00B7,0x00B8,0x00B9,0x002B,0x2034,0x00AB,0x00BA,0x00BB,
    0x20BB,0x20BA,0x00BC,0x00BD,0x009E,0x00AE,0x005E,0x0023,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x001F,0x0038,0x0023,0x00BE,0x0073,0x0074,0x0024,0x0025,
    0x2025,0x2024,0x00BF,0x00C0,0x20C0,0x20BF,0x0024,0x0025,
    0x00C1,0x00C2,0x00C3,0x00C4,0x00C5,0x00C6,0x0036,0x0037,
    0x004B,0x0077,0x00C7,0x002B,0x00C8,0x00BB,0x0006,0x2015,
    0x001A,0x001B,0x0023,0x00C9,0x00CA,0x00CB,0x0024,0x0025,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x00CC,0x00CD,0x00CE,0x00CF,0x00D0,0x00D1,0x2025,0x2024,
    0x0024,0x0025,0x00D2,0x00D3,0x00D4,0x00D5,0x00D6,0x00D7,
    0x0024,0x0025,0x00B0,0x00D8,0x00D9,0x00DA,0x001D,0x001E,
    0x0060,0x00DB,0x00DC,0x002B,0x0013,0x0014,0x001A,0x0032,
    0x0033,0x0034,0x005E,0x00DD,0x00DE,0x205E,0x2025,0x2024,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x002A,0x002B,0x00DF,0x00CD,0x2025,0x2024,0x0023,0x0023,
    0x0023,0x0023,0x0024,0x00E0,0x00E1,0x00E2,0x00E3,0x00E4,
    0x00E5,0x0023,0x0024,0x0025,0x2025,0x0059,0x0036,0x005A,
    0x0076,0x0077,0x00E6,0x00E7,0x002A,0x002B,0x2034,0x00AB,
    0x00BC,0x00E8,0x0024,0x0025,0x00E9,0x00EA,0x00EB,0x00EB,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x00EC,0x00ED,0x002B,0x002B,0x00EE,0x00CD,0x00CE,0x0023,
    0x0023,0x205E,0x2025,0x00EF,0x005C,0x005D,0x00F0,0x00F1,
    0x00F2,0x205E,0x2025,0x2024,0x0024,0x00F3,0x0070,0x0071,
    0x00F4,0x00F5,0x00F6,0x2024,0x00F7,0x00E7,0x00F8,0x00E8,
    0x0023,0x20CE,0x00F9,0x00FA,0x002B,0x002B,0x002B,0x002B,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x00FB,0x00FC,0x00FD,0x00ED,0x00FE,0x002B,0x00DF,0x00CD,
    0x2025,0x2024,0x0023,0x00FF,0x0073,0x0074,0x0024,0x0100,
    0x2100,0x2024,0x0023,0x0023,0x0023,0x0023,0x0101,0x0102,
    0x0103,0x2024,0x0023,0x0023,0x0023,0x0023,0x0104,0x0025,
    0x00F9,0x0105,0x0033,0x0106,0x002B,0x002B,0x002B,0x002B,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0107,0x0108,0x0109,0x00FC,0x010A,0x00ED,0x002B,0x002B,
    0x00EE,0x00CD,0x00CE,0x010B,0x0088,0x0089,0x2025,0x010C,
    0x210C,0x0025,0x005E,0x0023,0x0023,0x205E,0x010D,0x0004,
    0x000E,0x0025,0x005E,0x0023,0x0023,0x205E,0x2025,0x010E,
    0x0033,0x0033,0x010F,0x0110,0x0111,0x0111,0x0111,0x0111,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0112,0x0113,0x0108,0x0114,0x00FC,0x00FD,0x00ED,
    0x00FE,0x002B,0x00DF,0x0115,0x0073,0x009F,0x0023,0x20F2,
    0x00F2,0x0023,0x0024,0x0025,0x2025,0x0116,0x0021,0x000C,
    0x0022,0x0023,0x0024,0x0025,0x2025,0x2024,0x0023,0x0117,
    0x010F,0x0118,0x0000,0x0119,0x011A,0x011B,0x011B,0x011B,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0112,0x0113,0x0108,0x0109,0x00FC,
    0x010A,0x011C,0x20E7,0x011D,0x0088,0x00AE,0x005E,0x20F2,
    0x00F2,0x205E,0x2025,0x2024,0x0024,0x0039,0x001D,0x001E,
    0x003A,0x003B,0x011E,0x2024,0x0024,0x0025,0x005E,0x0117,
    0x0000,0x0000,0x0000,0x0004,0x011F,0x0120,0x0120,0x0120,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0112,0x0113,0x0108,
    0x0121,0x00E8,0x0023,0x00BE,0x0073,0x0074,0x0024,0x0100,
    0x2100,0x2024,0x0023,0x0023,0x0023,0x004A,0x0036,0x0037,
    0x004B,0x0077,0x0122,0x0023,0x0023,0x0023,0x0024,0x0123,
    0x0000,0x000A,0x000B,0x000C,0x0124,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0112,
    0x210E,0x0025,0x005E,0x00CF,0x00D0,0x00D1,0x2025,0x010C,
    0x210C,0x0025,0x005E,0x0023,0x0023,0x005F,0x001D,0x001E,
    0x0060,0x00DB,0x0125,0x0023,0x0023,0x20CE,0x00F9,0x0126,
    0x0000,0x001C,0x001D,0x001E,0x0127,0x0128,0x0129,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x2117,0x0023,0x0024,0x0025,0x2025,0x2024,0x00BF,0x012A,
    0x212A,0x20BF,0x0024,0x0025,0x2025,0x0075,0x0036,0x005A,
    0x0076,0x0077,0x012B,0x0025,0x00F9,0x0105,0x0033,0x0034,
    0x0000,0x0035,0x0036,0x0037,0x004B,0x0077,0x012C,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x2117,0x205E,0x2025,0x2024,0x0024,0x0025,0x00D2,0x00D3,
    0x012D,0x012E,0x012F,0x0130,0x0024,0x008A,0x008B,0x0071,
    0x00F4,0x0131,0x0132,0x0133,0x0033,0x0033,0x0134,0x0135,
    0x0000,0x001C,0x001D,0x001E,0x0060,0x00DB,0x0136,0x0011,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x2123,0x2024,0x0023,0x0023,0x0023,0x0023,0x0024,0x00E0,
    0x00E1,0x0137,0x0138,0x0139,0x013A,0x013B,0x0024,0x00A0,
    0x00F9,0x0105,0x0033,0x309C,0x0134,0x013C,0x013D,0x0000,
    0x001F,0x013E,0x0036,0x005A,0x0076,0x0077,0x012B,0x0025,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x00CC,0x00CD,0x00CE,0x0023,0x0023,0x205E,0x2025,0x2024,
    0x0024,0x0025,0x00F0,0x013F,0x0138,0x0139,0x0140,0x0141,
    0x20AB,0x0033,0x0134,0x013C,0x013D,0x0000,0x001F,0x0038,
    0x0024,0x008A,0x008B,0x0071,0x008C,0x008D,0x00F6,0x2024,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x002A,0x002B,0x00DF,0x00CD,0x00E9,0x00EA,0x00EB,0x00EB,
    0x00EB,0x00EB,0x20EA,0x20E9,0x0142,0x0143,0x0144,0x0139,
    0x0145,0x0146,0x013D,0x0000,0x001F,0x0038,0x0023,0x0023,
    0x0023,0x0023,0x0024,0x0025,0x2025,0x2024,0x0023,0x0023,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x00EC,0x00ED,0x002B,0x002B,0x00FE,0x002B,0x002B,0x002B,
    0x002B,0x002B,0x002B,0x002B,0x2034,0x0033,0x0147,0x0148,
    0x0144,0x0139,0x0149,0x014A,0x0024,0x0025,0x005E,0x0023,
    0x0023,0x205E,0x2025,0x2024,0x0024,0x0025,0x005E,0x0023,
};
