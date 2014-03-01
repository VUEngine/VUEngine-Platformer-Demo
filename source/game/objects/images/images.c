/* VbJaEngine: bitmap graphics engine for the Nintendo Virtual Boy 
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef MARIO_TITLE_LEFT_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&MARIO_TITLE_LEFT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,
	},
};

ImageROMDef MARIO_TITLE_LEFT_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(MARIO_TITLE_LEFT_IM_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef MARIO_TITLE_RIGHT_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&MARIO_TITLE_RIGHT_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,
	},
};

ImageROMDef MARIO_TITLE_RIGHT_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(MARIO_TITLE_RIGHT_IM_SPRITES),
		
};

