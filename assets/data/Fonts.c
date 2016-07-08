/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#ifdef __CUSTOM_FONTS

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Printing.h>


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
    //&PLATFORMER_LARGE_FONT,
    NULL
};


#endif