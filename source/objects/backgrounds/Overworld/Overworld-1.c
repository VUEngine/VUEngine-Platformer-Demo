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
#include <ManagedMBackground.h>
#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE OverworldTiles[];
extern BYTE Overworld_1Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef OVERWORLD_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    332,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    OverworldTiles,
};

TextureROMDef OVERWORLD_1_TX =
{
    // charset definition
    (CharSetDefinition*)&OVERWORLD_CH,

    // bgmap definition
    Overworld_1Map,

    // cols (max 64)
    48,

    // rows (max 64)
    28,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    0,
};

TextureROMDef* OVERWORLD_1_IM_TEXTURES[] =
{
	(TextureDefinition*)&OVERWORLD_1_TX,
	NULL
};

MBgmapSpriteROMDef OVERWORLD_1_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(MBgmapSprite),

		// texture definition
		NULL,

		// displacement
		{0, 0, 0},
		
		// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
		WRLD_BGMAP,
		
		// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
		WRLD_ON,
	},
	
	(TextureDefinition**)OVERWORLD_1_IM_TEXTURES,
	
	// SCX/SCY
	WRLD_1x1,

	// x loop
	false,
	
	// y loop
	false,
};

BgmapSpriteROMDef* const OVERWORLD_1_IM_SPRITES[] =
{
	(BgmapSpriteROMDef*)&OVERWORLD_1_IM_SPRITE,
	NULL
};

MBackgroundROMDef OVERWORLD_1_IM =
{
	__TYPE(ManagedMBackground),
	(SpriteROMDef**)OVERWORLD_1_IM_SPRITES,
};