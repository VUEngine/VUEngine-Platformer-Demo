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

#include <Background.h>
#include <Image.h>
#include <ScrollBackground.h>

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


SpriteROMDef FLOOR0_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		&FLOOR0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

SpriteROMDef FLOOR1_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		&FLOOR1_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

SpriteROMDef FLOOR2_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		&FLOOR2_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
BackgroundROMDef FLOOR0_BG = {
		{
			{
				// object's class			   
				__TYPE(Background),  
		
				__SPRITE_ARRAY(FLOOR0_BG_SPRITES)
			},
			
			// deep
			20,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{1,		0,		0,		0,},
			
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

BackgroundROMDef FLOOR1_BG = {
		{
			{
				// object's class			   
				__TYPE(Background),  
		
				__SPRITE_ARRAY(FLOOR1_BG_SPRITES),
			},
			
			// deep
			20,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{1,		0,		0,		0},
			
			// in game type
			kSolid,
		},

		// register shape
		true,
		
		// friction FTOFIX19_13
		FTOFIX19_13(1.0f),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(1.0f)
};


BackgroundROMDef FLOOR2_BG = {
		{
			{
				// object's class			   
				__TYPE(Background),  
		
				__SPRITE_ARRAY(FLOOR2_BG_SPRITES),
			},
			
			// deep
			120,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{1,		0,		0,		0},
			
			// in game type
			kSolid,
		},

		// register shape
		true,
		
		// friction FTOFIX19_13
		FTOFIX19_13(0),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(0.9f)
};

BackgroundROMDef FLOOR3_BG = {
		{
			{
				// object's class			   
				__TYPE(Background),  
		
				__SPRITE_ARRAY(FLOOR2_BG_SPRITES),
			},
			
			// deep
			20,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{0,		0,		0,		0},
			
			// in game type
			kSolid,
		},

		// register shape
		true,
		
		// friction FTOFIX19_13
		FTOFIX19_13(1.0f),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(0.1f)
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef PIPE0_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		&PIPE0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_AFFINE,
		
		// display mode
		WRLD_ON,
	},
};
BackgroundROMDef PIPE0_BG = {
		{
			{
				// object's class			   
				__TYPE(Background),  
		
				__SPRITE_ARRAY(PIPE0_BG_SPRITES),
			},
			
			// deep
			20,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{0,		0,		0,		0},
			
			// in game type
			kSolid,
		},

		// register shape
		true,
		
		// friction FTOFIX19_13
		FTOFIX19_13(1.0f),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(1.0f)
};

SpriteROMDef PIPE1_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		&PIPE1_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_AFFINE,
		
		// display mode
		WRLD_ON,
	},
};

BackgroundROMDef PIPE1_BG = {
		{
			{
				// object's class			   
				__TYPE(Background),  
		
				__SPRITE_ARRAY(PIPE1_BG_SPRITES),
			},
			
			// deep
			5,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{0,		0,		0,		0},
			
			// in game type
			kSolid,
		},

		// register shape
		true,
		
		// friction FTOFIX19_13
		FTOFIX19_13(1.0f),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(0.1f)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef WALL0_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		&WALL0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_AFFINE,
		
		// display mode
		WRLD_ON,
	},
};

BackgroundROMDef WALL0_BG = {
		{
			{
				// object's class			   
				__TYPE(Background),  
		
				__SPRITE_ARRAY(WALL0_BG_SPRITES),
			},
			
			// deep
			20,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{0,		0,		0,		0},
			
			// in game type
			kSolid,
		},

		// register shape
		true,
		
		// friction FTOFIX19_13
		FTOFIX19_13(0.02f),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(0.05f)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef JAPANARC_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&JAPANARC_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef JAPANARC_IM = {
		
	// object's class			   
		__TYPE(Image),  

	__SPRITE_ARRAY(JAPANARC_IM_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef MOUNT0_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&MOUNT0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef MOUNT0_IM = {
		
	// object's class			   
	__TYPE(Image),  

	__SPRITE_ARRAY(MOUNT0_IM_SPRITES),
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef MOUNT1_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&MOUNT1_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef MOUNT1_IM = {
		
	// object's class			   
		__TYPE(Image),  

	__SPRITE_ARRAY(MOUNT1_IM_SPRITES),
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef MOUNT2_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&MOUNT2_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef MOUNT2_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(MOUNT2_IM_SPRITES),
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef MOUNTS0_SB_SPRITES[] = {

	// Sprite
	{
		// the texture
		&MOUNTS0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef MOUNTS0_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(MOUNTS0_SB_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef MOUNTS1_SB_SPRITES[] = {
	// Sprite
	{
		// the texture
		&MOUNTS1_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef MOUNTS1_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(MOUNTS1_SB_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef BACKMOUNT0_SB_SPRITES[] = {
	// Sprite
	{
		// the texture
		&BACKMOUNT01_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
	// Sprite
	{
		// the texture
		&BACKMOUNT02_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ScrollBackgroundROMDef BACKMOUNT0_SB = {
		
		// object's class			   
		__TYPE(ScrollBackground),  

		__SPRITE_ARRAY(BACKMOUNT0_SB_SPRITES)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef POLE0_BG_SPRITES[] = {

	// Sprite
	{
		// the texture
		&POLE0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

BackgroundROMDef POLE0_BG = {
		{
			{
				// object's class			   
				__TYPE(Background),  
		
				__SPRITE_ARRAY(POLE0_BG_SPRITES),
			},
			
			// deep
			20,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{0,		0,		0,		0},
			
			// in game type
			kSolid,
		},

		// register shape
		true,
		
		// friction FTOFIX19_13
		FTOFIX19_13(1.0f),
		
		// elasticity FTOFIX19_13
		FTOFIX19_13(1.0f)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef GOAL0_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&GOAL0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef GOAL0_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(GOAL0_IM_SPRITES),
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteROMDef GATE0_IM_SPRITES[] = {

	// Sprite
	{
		// the texture
		&GATE0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ImageROMDef GATE0_IM = {
		
		// object's class			   
		__TYPE(Image),  

		__SPRITE_ARRAY(GATE0_IM_SPRITES),
};