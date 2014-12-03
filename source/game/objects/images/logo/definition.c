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
#include <../assets/images/_o/SuperAwesome.h>
#include <../assets/images/_o/VBJaEngineLogo.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

extern BYTE LOGO_LEFT_CH[];
extern BYTE LOGO_RIGHT_CH[];
extern BYTE LOGO_LEFT_MP[];
extern BYTE LOGO_RIGHT_MP[];

TextureROMDef LOGO_LEFT_TX = {
		// Chargroup
		{
				// chDefinition,				 
				LOGO_LEFT_CH,					
				// numChars,
				165,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		LOGO_LEFT_MP,
		
		// cols (max 48)
		41,
		
		// rows (max 28)
		7,
		
		//pallet number,
		0
};

TextureROMDef LOGO_RIGHT_TX = {
		// Chargroup
		{
				// chDefinition,				 
				LOGO_RIGHT_CH,					
				// numChars,
				165,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		LOGO_RIGHT_MP,
		
		// cols (max 48)
		41,
		
		// rows (max 28)
		7,
		
		//pallet number,
		0
};

SpriteROMDef LOGO_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&LOGO_LEFT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,

		// parallax displacement
		0,
	},

	// Sprite
	{
		// the texture
		&LOGO_RIGHT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,

		// parallax displacement
		0,
	},
};

ImageROMDef LOGO_IM = {
		
	// object's class			   
	__TYPE(Image),  

	__SPRITE_ARRAY(LOGO_IM_SPRITES),
};


TextureROMDef SUPER_AWESOME_TX = {
		// Chargroup
		{
				// chDefinition,				 
				SuperAwesomeTiles,					
				// numChars,
				39,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		SuperAwesomeMap,
		
		// cols (max 48)
		19,
		
		// rows (max 28)
		2,
		
		//pallet number,
		0
};

SpriteROMDef SUPER_AWESOME_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&SUPER_AWESOME_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},

	// Sprite
	{
		// the texture
		&SUPER_AWESOME_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,
	},
};

ImageROMDef SUPER_AWESOME_IM = {
		
	// object's class			   
	__TYPE(Image),  

	__SPRITE_ARRAY(SUPER_AWESOME_IM_SPRITES),
};


TextureROMDef VBJAENGINE_TX = {
		// Chargroup
		{
				// chDefinition,				 
				VBJaEngineLogoTiles,					
				// numChars,
				56,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		VBJaEngineLogoMap,
		
		// cols (max 48)
		16,
		
		// rows (max 28)
		4,
		
		//pallet number,
		0
};

SpriteROMDef VBJAENGINE_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&VBJAENGINE_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},

	// Sprite
	{
		// the texture
		&VBJAENGINE_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,
	},
};

ImageROMDef VBJAENGINE_IM = {
		
	// object's class			   
	__TYPE(Image),  

	__SPRITE_ARRAY(VBJAENGINE_IM_SPRITES),
};
