#ifndef FONTS_H_
#define FONTS_H_


extern const u16 FontDefaultTiles[];
FontROMDef PLATFORMER_DEFAULT_FONT =
{
    // font chars definition pointer
    FontDefaultTiles,

	// number of characters in font
    256,

	// at which character number the font starts
    0,

	// size of a single character (in chars) ({width, height})
    {1, 1},

	// font's name
    "DefaultFont",
};

extern const u16 FontGUITiles[];
FontROMDef PLATFORMER_GUI_FONT =
{
    // font chars definition pointer
    FontGUITiles,

	// number of characters in font
    96,

	// at which character number the font starts
    32,

	// size of a single character (in chars) ({width, height})
    {1, 2},

	// font's name
    "GUIFont",
};

extern const u16 FontLargeTiles[];
FontROMDef PLATFORMER_LARGE_FONT =
{
    // font chars definition pointer
    FontLargeTiles,

	// number of characters in font
    64,

	// at which character number the font starts
    32,

	// size of a single character (in chars) ({width, height})
    {2, 2},

	// font's name
    "LargeFont",
};


#endif