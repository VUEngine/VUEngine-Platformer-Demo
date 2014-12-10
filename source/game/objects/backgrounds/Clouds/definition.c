/* CLOUDS: bitmap graphics engine for the Nintendo Virtual Boy 
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

#include <ScrollBackground.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

extern BYTE CloudsTiles[];
extern BYTE CloudsMap[];


TextureROMDef CLOUDS_TX = {
		// Chargroup
		{
			// numChars
			22,
			
			// allocation type
			__NO_ANIMATED,
			
			// chDefinition				 
			CloudsTiles,
		},
		
		// bgmap definition
		CloudsMap,
		
		// cols (max 48)
		48,
		
		// rows (max 28)
		7,
		
		//pallet number,
		0
};

SpriteROMDef CLOUDS_SB_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&CLOUDS_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,

	},
	// Sprite
	{
		// the texture
		(TextureDefinition*)&CLOUDS_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
};

ScrollBackgroundROMDef CLOUDS_SB = {
	__TYPE(ScrollBackground),  
	__SPRITE_ARRAY(CLOUDS_SB_SPRITES),   
};
