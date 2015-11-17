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

// delay to not allow the player to bypass logo screen
#define SHOWDELAY		2000

#define FADE_DELAY		15

#define LAYER_INCREMENT					24
#define LAYER_0 0
#define LAYER_1 (LAYER_0 + LAYER_INCREMENT)
#define LAYER_2 (LAYER_1 + LAYER_INCREMENT)
#define LAYER_3 (LAYER_2 + LAYER_INCREMENT)
#define LAYER_4 (LAYER_3 + LAYER_INCREMENT)
#define LAYER_5 (LAYER_4 + LAYER_INCREMENT)

#define TOTAL_GAME_LAYERS 	6

#define SCREEN_CENTER_X		384/2
#define SCREEN_CENTER_Y		224/2

#define DEAD_VELOCITY_Y			ITOFIX19_13(70)
#define DEAD_ACCELERATION_Y		ITOFIX19_13(10)
#define DEAD_VELOCITY_Z			ITOFIX19_13(20)
#define DEAD_ACCELERATION_Z		ITOFIX19_13(10)

enum PlatformerTypes
{
	kHero = 1,
	kSawBlade,
	kSolid,
	kTopSolid,
	kNotSolid,
	kFloor,
	kDoor,
	kCoin,
	kKey,
	kLava,
	kLavaTrigger,
	kCogWheel,
};

#define GAMEWORLD_MODES 4

enum GameWorldModes
{
	kPlaying = 1,
	kShowingUp,
	kPaused,
};


#endif