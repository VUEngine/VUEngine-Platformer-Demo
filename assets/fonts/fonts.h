#ifndef FONTS_H_
#define FONTS_H_


extern const u16 FontDefaultTiles[];
extern const u16 Font8x16Tiles[];


FontROMDef PLATFORMER_DEFAULT_FONT =
{
    // font chars definition pointer
    FontDefaultTiles,

	// number of characters in font
    256,

	// at which character number the font starts
    0,

	// size of a single character
    kFont8x8,

	// font's name
    "Default",
};

FontROMDef PLATFORMER_8X16_FONT =
{
    // font chars definition pointer
    Font8x16Tiles,

	// number of characters in font
    96,

	// at which character number the font starts
    32,

	// size of a single character
    kFont8x16,

	// font's name
    "8x16",
};


#endif