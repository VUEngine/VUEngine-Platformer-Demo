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

extern BYTE SuperAwesomeTiles[];
extern BYTE SuperAwesomeMap[];
extern BYTE VBJaEngineLogoTiles[];
extern BYTE VBJaEngineLogoMap[];
extern BYTE PlatformerDemoLogoLTiles[];
extern BYTE PlatformerDemoLogoLMap[];
extern BYTE PlatformerDemoLogoRTiles[];
extern BYTE PlatformerDemoLogoRMap[];


TextureROMDef LOGO_LEFT_TX = {
		// Chargroup
		{
			// chDefinition,				 
			PlatformerDemoLogoLTiles,					
			// numChars,
			166,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		PlatformerDemoLogoLMap,
		
		// cols (max 48)
		42,
		
		// rows (max 28)
		7,
		
		//pallet number,
		0
};

TextureROMDef LOGO_RIGHT_TX = {
		// Chargroup
		{
			// chDefinition,
			PlatformerDemoLogoRTiles,					
			// numChars,
			166,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		PlatformerDemoLogoRMap,
		
		// cols (max 48)
		42,
		
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
