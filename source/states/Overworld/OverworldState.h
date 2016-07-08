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

#ifndef OVERWORLD_STATE_H_
#define OVERWORLD_STATE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define PRESS_START_BLINK_DELAY 500


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define OverworldState_METHODS																			\
	GameState_METHODS;											    									\

// declare the virtual methods which are redefined
#define OverworldState_SET_VTABLE(ClassName)															\
	GameState_SET_VTABLE(ClassName)								    									\
	__VIRTUAL_SET(ClassName, OverworldState, enter);													\
	__VIRTUAL_SET(ClassName, OverworldState, exit);														\
	__VIRTUAL_SET(ClassName, OverworldState, execute);													\
	__VIRTUAL_SET(ClassName, OverworldState, resume);													\
	__VIRTUAL_SET(ClassName, OverworldState, suspend);													\
	__VIRTUAL_SET(ClassName, OverworldState, handleMessage);											\

__CLASS(OverworldState);

#define OverworldState_ATTRIBUTES							        									\
														            									\
	/* inherits */																						\
	GameState_ATTRIBUTES																				\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

OverworldState OverworldState_getInstance(void);


#endif