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

extern uint32 FontDefaultTiles[];


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS                                               
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec PlatformerFontCharSet =
{
	// number of chars
	256,

	// allocation type
	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	FontDefaultTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec PlatformerFont =
{
	// font charset spec pointer
	(CharSetSpec*)&PlatformerFontCharSet,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	256,

	// number of characters per line in charset
	2,

	// size of a single character (in chars) ({width, height})
	{1, 1},

	// font's name
	"Platformer",
};