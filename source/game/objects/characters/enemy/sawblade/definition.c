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

#include <AnimatedSprite.h>

#include "SawBlade.h"


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


extern BYTE SAW_BLADE_CH[];
extern BYTE SAW_BLADE_MP[];


AnimationFunction SAW_BLADE_SPIN_ANIM = {
	
	// function's name
	"Spin",

	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{0,1},
	
	// number of cycles a frame of animation is displayed
	8 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
};

// an animation definition
AnimationDescription SAW_BLADE_ANIM = {
	
	// number of animation frames
	2,
	
	// animation functions
	{
		&SAW_BLADE_SPIN_ANIM,
		NULL,
	}
	
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureDefinition SAW_BLADE_TX = {
		
		// Chargroup
		{
				// chDefinition,				 
				SAW_BLADE_CH,	
				
				// numChars,
				18,
				
				// allocation type
				__ANIMATED_SHARED
		},
		
		// bgmap definition
		SAW_BLADE_MP,
		
		// cols (max 48)
		3,
		
		// rows (max 28)
		3,
		
		//pallet number,
		1
};

SpriteROMDef SAW_BLADE_SPRITES[] = {
	{
		// the texture
		&SAW_BLADE_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_AFFINE,
		
		// display mode
		WRLD_ON,
	}
};


SawBladeDefinition SAW_BLADE_MC = {
		{
			{
				{
					// object's class			   
					__TYPE(SawBlade),  
			
					// Sprites
					__SPRITE_ARRAY(SAW_BLADE_SPRITES)
				},
				
				// deep
				10,
				
				//collision detection gap			
				//up,	down,	left,	right,
				{1,		2,		2,		1,},		
				
				// in game type
				kSawBlade
			},
			
			// pointer to the animation definition for the character
			&SAW_BLADE_ANIM,
		},
		
		// axis
		__YAXIS,
		
		// direction
		__UP
};



