/* TREE_BG_BACK: bitmap graphics engine for the Nintendo Virtual Boy 
 * 
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include <InanimatedInGameEntity.h>
#include <macros.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

extern BYTE Floor2x2BlockLTiles[];
extern BYTE Floor2x2BlockLMap[];
extern BYTE Floor2x2BlockRTiles[];
extern BYTE Floor2x2BlockRMap[];


TextureROMDef FLOOR_2x2_BLOCK_L_TX = {
		// Chargroup
		{
			// numChars
			10,

			// allocation type
			__NO_ANIMATED,
			
			// chDefinition				 
			Floor2x2BlockLTiles,
		},
		
		// bgmap definition
		Floor2x2BlockLMap,
		
		// cols (max 48)
		3,
		
		// rows (max 28)
		3,
		
		//pallet number,
		1
};

TextureROMDef FLOOR_2x2_BLOCK_R_TX = {
		// Chargroup
		{
			// numChars
			10,
			
			// allocation type
			__NO_ANIMATED,
			
			// chDefinition			 
			Floor2x2BlockRTiles,
		},
		
		// bgmap definition
		Floor2x2BlockRMap,
		
		// cols (max 48)
		3,
		
		// rows (max 28)
		3,
		
		//pallet number,
		1
};

SpriteROMDef FLOOR_2x2_BLOCK_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&FLOOR_2x2_BLOCK_L_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,
		
		// parallax displacement
		0,
	},
	// Sprite
	{
		// the texture
		(TextureDefinition*)&FLOOR_2x2_BLOCK_R_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,

		// parallax displacement
		0,
	},
};

InanimatedInGameEntityROMDef FLOOR_2x2_BLOCK_BG = {
		{
			{
				__TYPE(InanimatedInGameEntity),
				__SPRITE_ARRAY(FLOOR_2x2_BLOCK_BG_SPRITES),
			},
			
			//collision detection gap			
			//up,	down,	left,	right,
			{7,		0,		0,		8,},
			
			// in game type
			kSolid,
			
			// deep
			20,
		},
		
		// friction FTOFIX19_13
		FTOFIX19_13(1.0f),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(1.0f),

		// register shape
		true,
};
