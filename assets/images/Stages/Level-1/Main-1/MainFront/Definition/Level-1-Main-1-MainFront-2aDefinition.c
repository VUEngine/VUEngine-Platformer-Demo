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
#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_Main_1_MainFront_2aMap[];
extern CharSetROMDef LEVEL_1_MAIN_1_MAIN_FRONT_CH;


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef LEVEL_1_MAIN_1_MAIN_FRONT_2A_TX =
{
    // charset definition
    (CharSetDefinition*)&LEVEL_1_MAIN_1_MAIN_FRONT_CH,

    // bgmap definition
    Level_1_Main_1_MainFront_2aMap,

    // cols (max 64)
    50,

    // rows (max 64)
    8,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    1,
};

TextureROMDef* const LEVEL_1_MAIN_1_MAIN_FRONT_2A_IM_TEXTURES[] =
{
	(TextureDefinition*)&LEVEL_1_MAIN_1_MAIN_FRONT_2A_TX,
	NULL
};

MBgmapSpriteROMDef LEVEL_1_MAIN_1_MAIN_FRONT_2A_IM_SPRITE =
{
	{
        {
            // sprite's type
            __TYPE(MBgmapSprite),

            // texture definition
            NULL,

            // transparent
            false,

            // displacement
            {ITOFIX19_13(-8), ITOFIX19_13(-112), FTOFIX19_13(-1), 0},
        },

		// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
		// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
		__WORLD_BGMAP,

		// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
		__WORLD_ON,

	},

	(TextureDefinition**)LEVEL_1_MAIN_1_MAIN_FRONT_2A_IM_TEXTURES,

	// SCX/SCY
	__WORLD_1x1,

	// x loop
	false,

	// y loop
	false,
};
