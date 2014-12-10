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

extern BYTE AdjustmentScreenIconTiles[];
extern BYTE AdjustmentScreenIconMap[];


TextureROMDef ADJUSTMENT_SCREEN_ICON_TX = {
		// Chargroup
		{				
			// numChars,
			5,
			
			// allocation type
			__NO_ANIMATED,
			
			// chDefinition	 
			AdjustmentScreenIconTiles,	
		},
		
		// ICONmap definition
		AdjustmentScreenIconMap,
		
		// cols (max 48)
		2,
		
		// rows (max 28)
		2,
		
		//pallet number,
		0
};

SpriteROMDef ADJUSTMENT_SCREEN_ICON_IM_L_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&ADJUSTMENT_SCREEN_ICON_TX,
		
		// ICONmap mode ( ICONMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,

		// parallax displacement
		0,

	},
};

SpriteROMDef ADJUSTMENT_SCREEN_ICON_IM_R_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&ADJUSTMENT_SCREEN_ICON_TX,
		
		// ICONmap mode ( ICONMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,

		// parallax displacement
		0,

	},
};

ImageROMDef ADJUSTMENT_SCREEN_ICON_IM_L = {
	__TYPE(Image),  
	__SPRITE_ARRAY(ADJUSTMENT_SCREEN_ICON_IM_L_SPRITES),	   
};

ImageROMDef ADJUSTMENT_SCREEN_ICON_IM_R = {
	__TYPE(Image),  
	__SPRITE_ARRAY(ADJUSTMENT_SCREEN_ICON_IM_R_SPRITES),		   
};
