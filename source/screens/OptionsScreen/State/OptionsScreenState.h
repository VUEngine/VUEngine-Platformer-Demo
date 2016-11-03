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

#ifndef OPTIONS_SCREEN_STATE_H_
#define OPTIONS_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <OptionsSelector.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

enum OptionsScreenOptions
{
	kOptionsScreenOptionAutoPauseSelectScreen,
	kOptionsScreenOptionLanguage
};


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define OptionsScreenState_METHODS(ClassName)															\
		GameState_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define OptionsScreenState_SET_VTABLE(ClassName)														\
		GameState_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, OptionsScreenState, enter);											\
		__VIRTUAL_SET(ClassName, OptionsScreenState, exit);												\
		__VIRTUAL_SET(ClassName, OptionsScreenState, processMessage);									\

__CLASS(OptionsScreenState);

#define OptionsScreenState_ATTRIBUTES																	\
		/* inherits */																					\
		GameState_ATTRIBUTES																			\
        GameState nextState;																			\
		OptionsSelector optionsSelector;																\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

OptionsScreenState OptionsScreenState_getInstance(void);
void OptionsScreenState_setNextState(OptionsScreenState this, GameState nextState);

#endif
