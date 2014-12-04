/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy 
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

#include <Image.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

extern BYTE AdjustmentScreenBGTiles[];
extern BYTE AdjustmentScreenBGMap[];


TextureROMDef ADJUSTMENT_SCREEN_BG_TX = {
		// Chargroup
		{
			// chDefinition,				 
			AdjustmentScreenBGTiles,					
			// numChars,
			3,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		AdjustmentScreenBGMap,
		
		// cols (max 48)
		12,
		
		// rows (max 28)
		12,
		
		//pallet number,
		0
};

SpriteROMDef ADJUSTMENT_SCREEN_BG_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&ADJUSTMENT_SCREEN_BG_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,

	},
};

ImageROMDef ADJUSTMENT_SCREEN_BG_IM = {
		
	// object's class			   
	__TYPE(Image),  

	__SPRITE_ARRAY(ADJUSTMENT_SCREEN_BG_IM_SPRITES),
};
