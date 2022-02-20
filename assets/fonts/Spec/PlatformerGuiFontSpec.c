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

extern uint32 FontGuiTiles[];


//---------------------------------------------------------------------------------------------------------
//                                               DEFINITIONS                                               
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec PlatformerGuiFontCharSet =
{
	// number of chars
	10,

	// allocation type
	__NOT_ANIMATED,

	// char spec
	FontGuiTiles,

	// pointer to the frames offsets
	NULL,
};

FontROMSpec PlatformerGuiFont =
{
	// font charset spec pointer
	(CharSetSpec*)&PlatformerGuiFontCharSet,

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