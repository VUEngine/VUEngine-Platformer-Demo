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


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <MBackground.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_SmallRoom_MainBackTiles[];
extern BYTE Level_1_SmallRoom_MainBackMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef LEVEL_1_SMALL_ROOM_MAIN_BACK_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    13,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    Level_1_SmallRoom_MainBackTiles,
};

TextureROMDef LEVEL_1_SMALL_ROOM_MAIN_BACK_TX =
{
    // charset definition
    (CharSetDefinition*)&LEVEL_1_SMALL_ROOM_MAIN_BACK_CH,

    // bgmap definition
    Level_1_SmallRoom_MainBackMap,

    // cols (max 64)
    24,

    // rows (max 64)
    16,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef LEVEL_1_SMALL_ROOM_MAIN_BACK_IM_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&LEVEL_1_SMALL_ROOM_MAIN_BACK_TX,

        // displacement
        {0, 0, 0},
    },

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};
