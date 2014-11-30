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

#include <macros.h>
#include "textures.h"

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */
SpriteROMDef PVBCC_LEFT_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&PVBCC_LEFT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,
	},
};

ImageROMDef PVBCC_LEFT_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(PVBCC_LEFT_IM_SPRITES),
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef PVBCC_RIGHT_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&PVBCC_RIGHT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,
	},
};

ImageROMDef PVBCC_RIGHT_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(PVBCC_RIGHT_IM_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef PRECAUTION_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&PRECAUTION_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef PRECAUTION_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(PRECAUTION_IM_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef PVB_LEFT_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&PVB_LEFT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,
	},
};

ImageROMDef PVB_LEFT_IM = {
		
	// object's class			   
	__TYPE(Image),  

	__SPRITE_ARRAY(PVB_LEFT_IM_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef PVB_RIGHT_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&PVB_RIGHT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,
	},
};

ImageROMDef PVB_RIGHT_IM = {
		
	// object's class			   
	__TYPE(Image),  

	__SPRITE_ARRAY(PVB_RIGHT_IM_SPRITES),
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef VBJAE_LEFT_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&VBJAE_LEFT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,
	},
};

ImageROMDef VBJAE_LEFT_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(VBJAE_LEFT_IM_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef VBJAE_RIGHT_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&VBJAE_RIGHT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,
	},
};

ImageROMDef VBJAE_RIGHT_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(VBJAE_RIGHT_IM_SPRITES),
};
