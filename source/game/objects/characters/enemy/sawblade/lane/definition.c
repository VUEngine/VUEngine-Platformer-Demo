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


extern BYTE SAW_BLADE_LANE_CH[];
extern BYTE SAW_BLADE_LANE_V_6_MP[];

TextureROMDef SAW_BLADE_LANE_V_6_TX = {
		// Chargroup
		{
				// chDefinition,				 
				SAW_BLADE_LANE_CH,					
				// numChars,
				2,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		SAW_BLADE_LANE_V_6_MP,
		
		// cols (max 48)
		1,
		
		// rows (max 28)
		6,
		
		//pallet number,
		1
		
};

SpriteROMDef SAW_BLADE_LANE_V_6_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&SAW_BLADE_LANE_V_6_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,

	},
};

ImageROMDef SAW_BLADE_LANE_V_6_IM = {
		
	// object's class			   
	__TYPE(Image),  

	__SPRITE_ARRAY(SAW_BLADE_LANE_V_6_IM_SPRITES),
};
