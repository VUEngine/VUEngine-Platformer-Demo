/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#ifndef MACROS_H_
#define MACROS_H_


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define FADE_DELAY			16

#define LAYER_INCREMENT		32
#define LAYER_0 			0
#define LAYER_1 			(LAYER_0 + LAYER_INCREMENT)
#define LAYER_2 			(LAYER_1 + LAYER_INCREMENT)
#define LAYER_3 			(LAYER_2 + LAYER_INCREMENT)
#define LAYER_4 			(LAYER_3 + LAYER_INCREMENT)
#define LAYER_5 			(LAYER_4 + LAYER_INCREMENT)

#define SORT_INCREMENT		0.001f
#define SORT_FRONT_1		- SORT_INCREMENT
#define SORT_FRONT_2		- (SORT_INCREMENT * 2)
#define SORT_FRONT_3		- (SORT_INCREMENT * 3)
#define SORT_FRONT_4		- (SORT_INCREMENT * 4)
#define SORT_BACK_1			SORT_INCREMENT
#define SORT_BACK_2			SORT_INCREMENT * 2
#define SORT_BACK_3			SORT_INCREMENT * 3
#define SORT_BACK_4			SORT_INCREMENT * 4

#define NO_FRICTION 		0
#define FLOOR_FRICTION 		150.0f
#define FLOOR_ELASTICITY 	1.0f

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
	kCannonBall,
};

enum GameWorldModes
{
	kPlaying = 1,
	kShowingUp,
	kPaused,
};


#endif