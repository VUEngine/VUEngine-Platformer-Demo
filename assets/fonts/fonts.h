#ifdef __CUSTOM_FONTS
#ifndef FONTS_H_
#define FONTS_H_


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE FontDefaultTiles[];
extern BYTE FontGUITiles[];
extern BYTE FontLargeTiles[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

FontROMDef PLATFORMER_DEFAULT_FONT =
{
    // font chars definition pointer
    FontDefaultTiles,

	// number of characters in font
    256,

    // character number at which the font starts, allows you to skip the control characters for example
    0,

	// size of a single character (in chars) ({width, height})
    {1, 1},

	// font's name
    "DefaultFont",
};

FontROMDef PLATFORMER_GUI_FONT =
{
    // font chars definition pointer
    FontGUITiles,

	// number of characters in font
    96,

    // character number at which the font starts, allows you to skip the control characters for example
    32,

	// size of a single character (in chars) ({width, height})
    {1, 2},

	// font's name
    "GUIFont",
};

const FontROMDef PLATFORMER_LARGE_FONT =
{
    // font chars definition pointer
    FontLargeTiles,

	// number of characters in font
    64,

    // character number at which the font starts, allows you to skip the control characters for example
    32,

	// size of a single character (in chars) ({width, height})
    {2, 2},

	// font's name
    "LargeFont",
};

const FontROMDef* __FONTS[] =
{
    &PLATFORMER_DEFAULT_FONT,
    &PLATFORMER_GUI_FONT,
    &PLATFORMER_LARGE_FONT,
    NULL
};


#endif
#endif