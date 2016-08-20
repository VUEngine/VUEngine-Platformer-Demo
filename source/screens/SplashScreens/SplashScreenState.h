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

#ifndef SPLASH_SCREEN_STATE_H_
#define SPLASH_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S ENUMS
//---------------------------------------------------------------------------------------------------------

enum SplashScreensMessageTypes
{
	kScreenStarted = kLastEngineMessage + 1,
	kScreenAllowUserInput
};

//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define SplashScreenState_METHODS(ClassName)															\
        GameState_METHODS(ClassName)											    					\
        __VIRTUAL_DEC(ClassName, void, print);															\
        __VIRTUAL_DEC(ClassName, void, processInput, u16 releasedKey);									\

// declare the virtual methods which are redefined
#define SplashScreenState_SET_VTABLE(ClassName)															\
        GameState_SET_VTABLE(ClassName)								   									\
        __VIRTUAL_SET(ClassName, SplashScreenState, enter);												\
        __VIRTUAL_SET(ClassName, SplashScreenState, exit);												\
        __VIRTUAL_SET(ClassName, SplashScreenState, execute);											\
        __VIRTUAL_SET(ClassName, SplashScreenState, resume);											\
        __VIRTUAL_SET(ClassName, SplashScreenState, processMessage);                                    \
        __VIRTUAL_SET(ClassName, SplashScreenState, processInput);										\
        __VIRTUAL_SET(ClassName, SplashScreenState, print);												\


__CLASS(SplashScreenState);

#define SplashScreenState_ATTRIBUTES								   									\
        /* inherits */																					\
        GameState_ATTRIBUTES																			\
        /* state to enter after this one */																\
        GameState nextState;																			\
        /* definition of screen's stage */																\
        StageDefinition* stageDefinition;																\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

void SplashScreenState_constructor(SplashScreenState this);
void SplashScreenState_destructor(SplashScreenState this);
void SplashScreenState_enter(SplashScreenState this, void* owner);
void SplashScreenState_execute(SplashScreenState this, void* owner);
void SplashScreenState_exit(SplashScreenState this, void* owner);
void SplashScreenState_resume(SplashScreenState this, void* owner);
bool SplashScreenState_processMessage(SplashScreenState this, void* owner, Telegram telegram);
void SplashScreenState_processInput(SplashScreenState this, u16 releasedKey);
void SplashScreenState_print(SplashScreenState this);
void SplashScreenState_setNextState(SplashScreenState this, GameState nextState);
void SplashScreenState_loadNextState(SplashScreenState this);


#endif
