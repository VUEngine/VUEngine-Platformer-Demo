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
#include "Hero.h"



extern BYTE HERO_MP[];

extern BYTE HERO_CH[];



// a function which defines the frames to play
AnimationFunctionROMDef HERO_IDLE_ANIM = {
	
	// function's name
	"Idle",

	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{0,1},
	
	// number of cicles a frame of animation is displayed
	14 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call function completion
	NULL,
	
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_WALKING_ANIM = {
	
	// function's name
	"Walk",

	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{10, 11},
	
	// number of cicles a frame of animation is displayed
	9 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_JUMPING_ANIM = {
	
	// function's name
	"Jump",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{2},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_FALLING_ANIM = {
	
	// function's name
	"Fall",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{3},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_SLIDING_ANIM = {
	
	// function's name
	"Slide",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{3},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_HIT_FRONT_ANIM = {
	
	// function's name
	"HitFront",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{5},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_HIT_BEHIND_ANIM = {
	
	// function's name
	"HitBehind",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{5},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_HIT_FIRE_ANIM = {
	
	// function's name
	"HitFire",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{10},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_JUMP_BACK_ANIM = {
	
	// function's name
	"JumpBack",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{12},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_JUMP_FRONT_ANIM = {
	
	// function's name
	"JumpFront",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{13},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_FRONT_ANIM = {
	
	// function's name
	"Front",

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
AnimationFunctionROMDef HERO_BACK_ANIM = {
	
	// function's name
	"Back",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{6},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
};


// an animation definition
AnimationDescriptionROMDef HERO_ANIM = {
	
	// number of animation frames
	12, 
	
	// animation functions
	{
		(AnimationFunction*)&HERO_IDLE_ANIM,
		(AnimationFunction*)&HERO_WALKING_ANIM,
		(AnimationFunction*)&HERO_JUMPING_ANIM,
		(AnimationFunction*)&HERO_FALLING_ANIM,
		(AnimationFunction*)&HERO_SLIDING_ANIM,
		(AnimationFunction*)&HERO_HIT_FRONT_ANIM,
		(AnimationFunction*)&HERO_HIT_BEHIND_ANIM,
		(AnimationFunction*)&HERO_JUMP_BACK_ANIM,
		(AnimationFunction*)&HERO_JUMP_FRONT_ANIM,
		(AnimationFunction*)&HERO_FRONT_ANIM,
		(AnimationFunction*)&HERO_BACK_ANIM,
		NULL,
	}
	
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef HERO0_TX = {
		
		// Chargroup
		{
				// chDefinition,				 
				HERO_CH,	
				
				// numChars,
				6,
				
				// allocation type
				__ANIMATED
		},
		
		// bgmap definition
		HERO_MP,
		
		// cols (max 48)
		2,
		
		// rows (max 28)
		3,
		
		//pallet number,
		0
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef HERO1_TX = {
		
		// Chargroup
		{
				// chDefinition,				 
				HERO_CH,	
				
				// numChars,
				6,
				
				// allocation type
				__ANIMATED
		},
		
		// bgmap definition
		HERO_MP,
		
		// cols (max 48)
		2,
		
		// rows (max 28)
		3,
		
		//pallet number,
		1
};

SpriteROMDef HERO_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&HERO0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_AFFINE,
		//WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},

	// Sprite
	{
		// the texture
		(TextureDefinition*)&HERO0_TX,
		
		// bgmap mode ( BGMAP, AFFINE, H-BIAS)
		WRLD_AFFINE,
		//WRLD_BGMAP,
		
		// display mode
		WRLD_ON,
	},
};

ActorROMDef HERO_MC = {
		{
			{
				// object's class			   
				__TYPE(Hero),
						
				__SPRITE_ARRAY(HERO_SPRITES),
			},
			
			// deep
			8,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{6,		0,		0,		0},		
			//{0,		0,		0,		0,},
			
			// in game type
			kHero,
			
		},
		
		// pointer to the animation definition for the character
		(AnimationDescription*)&HERO_ANIM,
};

