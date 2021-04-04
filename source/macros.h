/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MACROS_H_
#define MACROS_H_


//---------------------------------------------------------------------------------------------------------
//												DEFINES
//---------------------------------------------------------------------------------------------------------

// general
#define COINS_PER_LEVEL		64
#define LEVELS_IN_GAME		1

// ingame
#define INGAME_LOW_POWER_ENTITY_X_POSITION		148
#define INGAME_LOW_POWER_ENTITY_Y_POSITION		216
#define INGAME_LOW_POWER_ENTITY_Z_POSITION		0
#define INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT	-4
#define INGAME_CAMERA_FRUSTUM_X0				0
#define INGAME_CAMERA_FRUSTUM_Y0				0
#define INGAME_CAMERA_FRUSTUM_Z0				-32
#define INGAME_CAMERA_FRUSTUM_X1				__SCREEN_WIDTH
#define INGAME_CAMERA_FRUSTUM_Y1				(__SCREEN_HEIGHT - (2 << 3) + 4) // plus 4 to make sure that the GUI is not culled off
#define INGAME_CAMERA_FRUSTUM_Z1				__SCREEN_WIDTH * 5

// layers
#define LAYER_INCREMENT		64
#define SORT_INCREMENT		1
#define LAYER_0 			0
#define LAYER_1 			(LAYER_0 + LAYER_INCREMENT)
#define LAYER_2 			(LAYER_1 + LAYER_INCREMENT)
#define LAYER_3 			(LAYER_2 + LAYER_INCREMENT)
#define LAYER_4 			(LAYER_3 + LAYER_INCREMENT)
#define LAYER_5 			(LAYER_4 + LAYER_INCREMENT)

#define LAYER_0_ENEMIES 		(LAYER_0 + 1)
#define LAYER_0_ITEMS 			(LAYER_0 + 0)
#define LAYER_0_DECORATIONS 	(LAYER_0 + 1)
#define LAYER_0_PARTICLES		(LAYER_0)
#define LAYER_0_BACKGROUND		(LAYER_0 + 24)
#define LAYER_0_DOORS			(LAYER_0 + 1)
#define LAYER_0_FOREGROUND		(LAYER_0)
#define LAYER_0_FOREGROUND_POP	(LAYER_0 - 12)

#define LAYER_0_HERO_DISPLACEMENT		 		-(SORT_INCREMENT * 3)
#define LAYER_0_ENEMIES_DISPLACEMENT	 		(SORT_INCREMENT * 2)
#define LAYER_0_ITEMS_DISPLACEMENT 				(SORT_INCREMENT * 3)
#define LAYER_0_DECORATIONS_DISPLACEMENT 		(SORT_INCREMENT * 3)
#define LAYER_0_PARTICLES_DISPLACEMENT			(SORT_INCREMENT * 1)
#define LAYER_0_BACKGROUND_DISPLACEMENT			(SORT_INCREMENT * 0)
#define LAYER_0_DOORS_DISPLACEMENT				(SORT_INCREMENT * 4)
#define LAYER_0_FOREGROUND_DISPLACEMENT			-(SORT_INCREMENT * 0)

#define LAYER_2_ENEMIES 	LAYER_2
#define LAYER_2_ITEMS 		LAYER_2
#define LAYER_2_PARTICLES	LAYER_2
#define LAYER_2_BACKGROUND	LAYER_2
#define LAYER_2_DOORS		LAYER_2
#define LAYER_2_FOREGROUND	LAYER_2

#define LAYER_2_ENEMIES_DISPLACEMENT 	(SORT_INCREMENT * 0)
#define LAYER_2_ITEMS_DISPLACEMENT 		(SORT_INCREMENT * 0)
#define LAYER_2_PARTICLES_DISPLACEMENT	(SORT_INCREMENT * 3)
#define LAYER_2_BACKGROUND_DISPLACEMENT	(SORT_INCREMENT * 4)
#define LAYER_2_DOORS_DISPLACEMENT		(-SORT_INCREMENT * 1)
#define LAYER_2_FOREGROUND_DISPLACEMENT	(-SORT_INCREMENT * 1)

#define HERO_PARALLAX_DISPLACEMENT								1
#define FOREGROUND_ENEMIES_PARALLAX_DISPLACEMENT 				1
#define BACKGROUND_ENEMIES_PARALLAX_DISPLACEMENT				0
#define FOREGROUND_ITEMS_PARALLAX_DISPLACEMENT 					1
#define BACKGROUND_ITEMS_PARALLAX_DISPLACEMENT					0
#define SIGNS_PARALLAX_DISPLACEMENT 							2
#define PARTICLES_PARALLAX_DISPLACEMENT							0
#define BACKGROUND_PARALLAX_DISPLACEMENT						0
#define DOORS_PARALLAX_DISPLACEMENT								2
#define FOREGROUND_PARALLAX_DISPLACEMENT						0
#define WATERFALLS_PARALLAX_DISPLACEMENT						-1
#define DECORATIONS_PARALLAX_DISPLACEMENT						1
#define LAYER_2_FOREGROUND_PARALLAX_DISPLACEMENT				0

// physics
#define NO_FRICTION 		0
#define FLOOR_FRICTION 		0.75f
#define FLOOR_BOUNCINESS 	0.0f

// entity collision types
enum GameCollisionTypes
{
	kTypeBandana = kTypeNone + 1,
	kTypeCannonBall,
	kTypeCoin,
	kTypeDoor,
	kTypeHero,
	kTypeHideLayer,
	kTypeHit,
	kTypeKey,
	kTypeLava,
	kTypeLavaTrigger,
	kTypeMovingPlatform,
	kTypeNoShape,
	kTypeSawBlade,
	kTypeShape,
	kTypeSnail,
	kTypeTopShape,
	kTypeWaterPond,
};

enum GameCollisionLayers
{
    kLayerSolid		 					= 1 << (kLayerNone + 0), 	// hex 00000001
    kLayerEnemies						= 1 << (kLayerNone + 1), 	// hex 00000002
    kLayerPlayer						= 1 << (kLayerNone + 2), 	// hex 00000004
    kLayerParticles						= 1 << (kLayerNone + 3), 	// hex 00000008
    kLayerCollectables					= 1 << (kLayerNone + 5), 	// hex 00000020
    kLayerTriggers						= 1 << (kLayerNone + 6), 	// hex 00000040
    kLayerCamera						= 1 << (kLayerNone + 7), 	// hex 00000080
    kLayerMovingPlatforms				= 1 << (kLayerNone + 8), 	// hex 00000100
    kLayerAll							= 0xFFFFFFFF,
};


#endif
