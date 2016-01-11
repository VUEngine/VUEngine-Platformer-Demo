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

extern BYTE Level_1_Tower_MainTiles[];
extern BYTE Level_1_Tower_Main_1Map[];

extern BgmapSpriteROMDef LEVEL_1_TOWER_BACK_1_IM_SPRITE;
extern BgmapSpriteROMDef LEVEL_1_TOWER_MAIN_BACK_1_IM_SPRITE;


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef LEVEL_1_TOWER_MAIN_1_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    30,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    Level_1_Tower_MainTiles,
};

TextureROMDef LEVEL_1_TOWER_MAIN_1_TX =
{
    // charset definition
    (CharSetDefinition*)&LEVEL_1_TOWER_MAIN_1_CH,

    // bgmap definition
    Level_1_Tower_Main_1Map,

    // cols (max 64)
    48,

    // rows (max 64)
    64,

    // number of frames
    1,

    // palette number
    0,
};

TextureROMDef* LEVEL_1_TOWER_MAIN_1_IM_TEXTURES[] = 
{
	(TextureDefinition*)&LEVEL_1_TOWER_MAIN_1_TX,
	NULL
};
 
MBgmapSpriteROMDef LEVEL_1_TOWER_MAIN_1_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(MBgmapSprite),

		// texture definition
		NULL,

		// displacement vector
		{0, 0, 0},
		
		// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
		WRLD_BGMAP,
		
		// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
		WRLD_ON,
	},
	
	(TextureDefinition**)LEVEL_1_TOWER_MAIN_1_IM_TEXTURES,
	
	// SCX/SCY
	WRLD_1x1,

	// x loop
	false,
	
	// y loop
	false
};

BgmapSpriteROMDef* const LEVEL_1_TOWER_MAIN_1_IM_SPRITES[] =
{
	(BgmapSpriteROMDef*)&LEVEL_1_TOWER_BACK_1_IM_SPRITE,
	(BgmapSpriteROMDef*)&LEVEL_1_TOWER_MAIN_BACK_1_IM_SPRITE,
	(BgmapSpriteROMDef*)&LEVEL_1_TOWER_MAIN_1_IM_SPRITE,
	NULL
};

MBackgroundROMDef LEVEL_1_TOWER_MAIN_1_IM =
{
	__TYPE(MBackground),
	(SpriteROMDef**)LEVEL_1_TOWER_MAIN_1_IM_SPRITES,
};