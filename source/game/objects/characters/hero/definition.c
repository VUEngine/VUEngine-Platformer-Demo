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


// a function which defines the frames to play
AnimationFunctionROMDef HERO_WALKING_ANIM = {
	
	// function's name
	"Walk",

	// number of frames of this animation function
	6,
	
	// frames to play in animation
	{0, 1, 2, 0, 3, 4},
	
	// number of cicles a frame of animation is displayed
	6 * __FPS_ANIM_FACTOR,
	
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
	{3},
	
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
	{4},
	
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
	{5},
	
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
	{11},
	
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
	3,
	
	// frames to play in animation
	{7, 8, 9},
	
	// number of cicles a frame of animation is displayed
	3 * __FPS_ANIM_FACTOR,
	
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
	{15},
	
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
	{14},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_BLINKING_ANIM = {
	
	// function's name
	"Blink",

	// number of frames of this animation function
	4,
	
	// frames to play in animation
	{16, 17, 16, 6},
	
	// number of cicles a frame of animation is displayed
	5 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	Hero_blinkDone,
};



// a function which defines the frames to play
AnimationFunctionROMDef HERO_WALKING_HOLD_ANIM = {
	
	// function's name
	"WalkHolding",

	// number of frames of this animation function
	3,
	
	// frames to play in animation
	{18, 19, 20},
	
	// number of cicles a frame of animation is displayed
	5 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call function completion
	NULL,
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_BLINKING_HOLD_ANIM = {
	
	// function's name
	"BlinkHolding",

	// number of frames of this animation function
	3,
	
	// frames to play in animation
	{22, 23, 22},
	
	// number of cicles a frame of animation is displayed
	5 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	Hero_blinkDone,
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_IDLE_HOLD_ANIM = {
	
	// function's name
	"IdleHolding",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{21},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_JUMPING_HOLD_ANIM = {
	
	// function's name
	"JumpHolding",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{19},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_FALLING_HOLD_ANIM = {
	
	// function's name
	"FallHolding",

	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{20},
	
	// number of cicles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_WALKING_FRONT_ANIM = {
	
	// function's name
	"WalkFront",

	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{26, 27},

	
	// number of cicles a frame of animation is displayed
	10 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call function completion
	NULL,
	
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_WALKING_BACK_ANIM = {
	
	// function's name
	"WalkBack",

	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{24, 25},

	
	// number of cicles a frame of animation is displayed
	10 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call function completion
	NULL,
	
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_WIN_ANIM = {
	
	// function's name
	"Win",

	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{28, 28},

	
	// number of cicles a frame of animation is displayed
	20 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call function completion
	Hero_win,
	
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_ONEDGE_ANIM = {
	
	// function's name
	"OnEdge",

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

// an animation definition
AnimationDescriptionROMDef HERO_ANIM = {
	
	// number of animation frames
	28, 
	
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
		(AnimationFunction*)&HERO_BLINKING_ANIM,
		(AnimationFunction*)&HERO_WALKING_HOLD_ANIM,
		(AnimationFunction*)&HERO_BLINKING_HOLD_ANIM,
		(AnimationFunction*)&HERO_IDLE_HOLD_ANIM,
		(AnimationFunction*)&HERO_JUMPING_HOLD_ANIM,
		(AnimationFunction*)&HERO_FALLING_HOLD_ANIM,
		(AnimationFunction*)&HERO_WALKING_FRONT_ANIM,
		(AnimationFunction*)&HERO_WALKING_BACK_ANIM,
		(AnimationFunction*)&HERO_WIN_ANIM,
		(AnimationFunction*)&HERO_ONEDGE_ANIM,
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
				20,
				
				// allocation type
				__ANIMATED
		},
		
		// bgmap definition
		HERO_MP,
		
		// cols (max 48)
		4,
		
		// rows (max 28)
		5,
		
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
				20,
				
				// allocation type
				__ANIMATED
		},
		
		// bgmap definition
		HERO_MP,
		
		// cols (max 48)
		4,
		
		// rows (max 28)
		5,
		
		//pallet number,
		1
};

SpriteROMDef HERO_SPRITES[] = {

	// Sprite
	{
		// the texture
		(TextureDefinition*)&HERO1_TX,
		
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
			10,
			
			//collision detection gap			
			//up,	down,	left,	right,
			{5,		1,		8,		6},		
			//{0,		0,		0,		0,},
			
			// in game type
			kHero,
			
		},
		
		// pointer to the animation definition for the character
		(AnimationDescription*)&HERO_ANIM,
};

