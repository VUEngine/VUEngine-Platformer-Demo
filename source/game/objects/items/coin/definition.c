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

/*---------------------------------INCLUDES--------------------------------*/
#include <libgccvb.h>
#include "Coin.h"


extern BYTE COIN_CH[];
extern BYTE COIN_MP[];



// a function which defines the frames to play
AnimationFunctionROMDef COIN_SPIN_ANIM = {
	
	// function's name
	"Spin",

	// number of frames of this animation function
	4,
	
	// frames to play in animation
	{0,1,2,3},
	
	// number of cicles a frame of animation is displayed
	10 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef COIN_TAKEN_ANIM = {
	
	// function's name
	"Taken",

	// number of frames of this animation function
	3,
	
	// frames to play in animation
	{4,5,6},
	
	// number of cicles a frame of animation is displayed
	10 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};

// an animation definition
AnimationDescriptionROMDef COIN_ANIM = {
	
	// number of animation frames
	7, 
	
	// animation functions
	{
		(AnimationFunction*)&COIN_SPIN_ANIM,
		(AnimationFunction*)&COIN_TAKEN_ANIM,
		NULL,
	}
	
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef COIN0_TX = {
		
		// Chargroup
		{
				// chDefinition,				 
				COIN_CH,	
				
				// numChars,
				4,
				
				// allocation type
				__ANIMATED
		},
		
		// bgmap definition
		COIN_MP,
		
		// cols (max 48)
		2,
		
		// rows (max 28)
		2,
		
		//pallet number,
		1
};

SpriteROMDef COIN_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&COIN0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_AFFINE,
		//WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},

};

AnimatedInGameEntityROMDef COIN_MC = {
		{
			{
				// object's class			   
				__TYPE(Coin),
						
				__SPRITE_ARRAY(COIN_SPRITES),
			},
			
			// deep
			4,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{4,		4,		4,		4},
			
			// in game type
			kCoin,
		},
		
		// pointer to the animation definition for the item
		(AnimationDescription*)&COIN_ANIM,
};

