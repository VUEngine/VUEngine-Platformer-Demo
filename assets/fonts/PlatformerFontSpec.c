///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              THIS FILE WAS AUTO-GENERATED - DO NOT EDIT                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Printing.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE FontDefaultTiles[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec PLATFORMER_FONT_CH =
{
	// number of chars
	256,

	// allocation type
	__NOT_ANIMATED,

	// char spec
	FontDefaultTiles,
};

FontROMSpec PLATFORMER_FONT =
{
	// font charset spec pointer
	(CharSetSpec*)&PLATFORMER_FONT_CH,

	// character number at which the font starts, allows you to skip the control characters for example
	0,

	// number of characters in this font
	256,

	// number of characters per line in charset
	32,

	// size of a single character (in chars) ({width, height})
	{1, 1},

	// font's name
	"Platformer",
};