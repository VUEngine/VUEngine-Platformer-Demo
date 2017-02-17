/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

// layers
#define LAYER_INCREMENT		32
#define SORT_INCREMENT		0.001f
#define LAYER_0 			1
#define LAYER_1 			(LAYER_0 + LAYER_INCREMENT)
#define LAYER_2 			(LAYER_1 + LAYER_INCREMENT)
#define LAYER_3 			(LAYER_2 + LAYER_INCREMENT)
#define LAYER_4 			(LAYER_3 + LAYER_INCREMENT)
#define LAYER_5 			(LAYER_4 + LAYER_INCREMENT)

#define LAYER_0_ENEMIES 	LAYER_0 + (SORT_INCREMENT * 1)
#define LAYER_0_ITEMS 		LAYER_0 + (SORT_INCREMENT * 2)
#define LAYER_0_PARTICLES	LAYER_0 + (SORT_INCREMENT * 3)
#define LAYER_0_BACKGROUND	LAYER_0 + (SORT_INCREMENT * 4)
#define LAYER_0_DOORS		LAYER_0 - (SORT_INCREMENT * 5)
#define LAYER_0_FOREGROUND	LAYER_0 - (SORT_INCREMENT * 4)

#define LAYER_2_ENEMIES 	LAYER_2 + (SORT_INCREMENT * 1)
#define LAYER_2_ITEMS 		LAYER_2 + (SORT_INCREMENT * 2)
#define LAYER_2_PARTICLES	LAYER_2 + (SORT_INCREMENT * 3)
#define LAYER_2_BACKGROUND	LAYER_2 + (SORT_INCREMENT * 4)
#define LAYER_2_DOORS		LAYER_2 - (SORT_INCREMENT * 5)
#define LAYER_2_FOREGROUND	LAYER_2 - (SORT_INCREMENT * 4)

// physics
#define NO_FRICTION 		0
#define FLOOR_FRICTION 		150.0f
#define FLOOR_ELASTICITY 	1.0f

// entity collision types
enum PlatformerTypes
{
	kHero = 1,
	kSolid,
	kTopSolid,
	kNotSolid,
	kCameraTarget,
	kHit,
	kHideLayer,
	kFloor,
	kDoor,
	kCoin,
	kBandana,
	kKey,
	kLava,
	kLavaTrigger,
	kSawBlade,
	kSnail,
	kCannonBall,
	kCannonBallStartMoving,
	kMovingPlatform,
	kMovingEntityStartMoving,
};


#endif
