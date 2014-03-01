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

#include "PiranhaPlant.h"
#include "PiranhaPlant.h"


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


extern BYTE PIRANHA_PLANT_V_CH[];
extern BYTE PIRANHA_PLANT_V_MP[];


AnimationFunction PIRANHA_PLANT_V_IDLE_ANIM = {
	
	// function's name
	"Idle",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{0},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunction PIRANHA_PLANT_V_BITE_ANIM = {
	
	// function's name
	"Bite",

	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{0, 1},
	
	// number of cicles a frame of animation is displayed
	25,
	
	// whether to play it in loop or not
	true,
	
	// method to call function completion
	NULL,
	
};

// an animation definition
AnimationDescription PIRANHA_PLANT_V_ANIM = {
	
	// number of animation frames
	2,
	
	// animation functions
	{
		&PIRANHA_PLANT_V_IDLE_ANIM,
		&PIRANHA_PLANT_V_BITE_ANIM,
		NULL,
	}
	
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureDefinition PIRANHA_PLANT_V_TX = {
		
		// Chargroup
		{
				// chDefinition,				 
				PIRANHA_PLANT_V_CH,	
				
				// numChars,
				11 * 2,
				
				// allocation type
				__ANIMATED_SHARED
		},
		
		// bgmap definition
		PIRANHA_PLANT_V_MP,
		
		// cols (max 48)
		2,
		
		// rows (max 28)
		3,
		
		//pallet number,
		1
};


PiranhaPlantDefinition PIRANHA_PLANT_V_MC = {
		{
			{
				{
					// object's class			   
					__TYPE(PiranhaPlant),  
			
					// Sprite
					{
						// the texture
						&PIRANHA_PLANT_V_TX,
						
						// bgmap mode ( BGMAP, AFFINE, H-BIAS)
						WRLD_AFFINE,
						
						// display mode
						WRLD_ON,
					},
				},
				
				// deep
				5,
				
				// friction factor
				5.5,
				
				//collision detection gap			
				//up,	down,	left,	right,
				{4,		0,		0,		0,},		
				
				// in game type
				kPiranhaPlant,
				
			},
			
			// pointer to the animation definition for the character
			&PIRANHA_PLANT_V_ANIM,
		},
		
		// axis
		__YAXIS,
		
		// direction
		__UP
};



