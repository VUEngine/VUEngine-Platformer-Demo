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

#ifndef LEVEL_DONE_SCREEN_STATE_H_
#define LEVEL_DONE_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define LevelDoneScreenState_METHODS(ClassName)															\
	    GameState_METHODS(ClassName)												    				\

// declare the virtual methods which are redefined
#define LevelDoneScreenState_SET_VTABLE(ClassName)														\
        GameState_SET_VTABLE(ClassName)								    								\
        __VIRTUAL_SET(ClassName, LevelDoneScreenState, enter);											\
        __VIRTUAL_SET(ClassName, LevelDoneScreenState, exit);											\
        __VIRTUAL_SET(ClassName, LevelDoneScreenState, processMessage);	                                \

__CLASS(LevelDoneScreenState);

#define LevelDoneScreenState_ATTRIBUTES							        								\
        /* inherits */																					\
        GameState_ATTRIBUTES																			\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

LevelDoneScreenState LevelDoneScreenState_getInstance(void);


#endif
