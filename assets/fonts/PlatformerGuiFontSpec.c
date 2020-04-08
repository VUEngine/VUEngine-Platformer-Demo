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

extern BYTE FontGuiTiles[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec PLATFORMER_GUI_FONT_CH =
{
	// number of chars
	10,

	// allocation type
	__NOT_ANIMATED,

	// char spec
	FontGuiTiles,
};

FontROMSpec PLATFORMER_GUI_FONT =
{
	// font charset spec pointer
	(CharSetSpec*)&PLATFORMER_GUI_FONT_CH,

	// character number at which the font starts, allows you to skip the control characters for example
	32,

	// number of characters in this font
	5,

	// number of characters per line in charset
	5,

	// size of a single character (in chars) ({width, height})
	{1, 2},

	// font's name
	"PlatformerGui",
};