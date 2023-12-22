///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              THIS FILE WAS AUTO-GENERATED - DO NOT EDIT                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------------
//                                                INCLUDES                                                 
//---------------------------------------------------------------------------------------------------------

#include <Printing.h>


//---------------------------------------------------------------------------------------------------------
//                                              DECLARATIONS                                               
//---------------------------------------------------------------------------------------------------------

const uint32 PlatformerGuiFontTiles[44] __attribute__((aligned(4))) =
{
    0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x022002A0,0x08080808,0x20022002,0x20022002,0x08080808,0x02A00220,0x00000000,
    0x00000000,0x03E003E0,0x0FF80FF8,0x3FFE3FFE,0x3FFE3FFE,0x0FF80FF8,0x03E003E0,0x00000000,
    0x3E000000,0xFFE0FF80,0xF8FEF8F8,0xFFF8FFFE,0x8000E3E0,0xA0008000,0x8000E000,0x00000000,
    0x00000000,0x00030000,0x00000003,0x00030000,0x003F000F,0x03FB00FE,0x000B03EE,0x00000000,
};


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS                                               
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec PlatformerGuiFontCharSet =
{
	// number of chars
	10,

	// whether it is shared or not
	true,

	// whether the tiles are optimized or not
	false,

	// char data
	(uint32*)PlatformerGuiFontTiles,

	// pointer to the frames offsets
	NULL    
};

FontROMSpec PlatformerGuiFontSpec =
{
	// font charset spec pointer
	(CharSetSpec*)&PlatformerGuiFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	32,

	// number of characters in this font
	5,

	// number of characters per line in charset
	1,

	// size of a single character (in chars) ({width, height})
	{1, 2},

	// font's name
	"PlatformerGui",
};
