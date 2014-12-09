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

extern BYTE Floor4x3FloatLTiles[];
extern BYTE Floor4x3FloatLMap[];
extern BYTE Floor4x3FloatRTiles[];
extern BYTE Floor4x3FloatRMap[];


TextureROMDef FLOOR_4x3_FLOAT_L_TX = {
		// Chargroup
		{
			// chDefinition,				 
			Floor4x3FloatLTiles,
			// numChars,
			16,

			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		Floor4x3FloatLMap,
		
		// cols (max 48)
		5,
		
		// rows (max 28)
		4,
		
		//pallet number,
		1
};

TextureROMDef FLOOR_4x3_FLOAT_R_TX = {
		// Chargroup
		{
			// chDefinition,				 
			Floor4x3FloatRTiles,
			// numChars,
			17,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		Floor4x3FloatRMap,
		
		// cols (max 48)
		5,
		
		// rows (max 28)
		4,
		
		//pallet number,
		1
};

SpriteROMDef FLOOR_4x3_FLOAT_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&FLOOR_4x3_FLOAT_L_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,
		
		// parallax displacement
		-1,
	},
	// Sprite
	{
		// the texture
		(TextureDefinition*)&FLOOR_4x3_FLOAT_R_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,

		// parallax displacement
		-1,
	},
};

InanimatedInGameEntityROMDef FLOOR_4x3_FLOAT_BG = {
		{
			{
				// object's class			   
				__TYPE(InanimatedInGameEntity),  
		
				__SPRITE_ARRAY(FLOOR_4x3_FLOAT_BG_SPRITES)
			},
			
			// deep
			20,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{6,		4,		4,		8,},
			
			// in game type
			kSolid,
		},

		// register shape
		true,
		
		// friction FTOFIX19_13
		FTOFIX19_13(0.5f),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(1.0f)
};
