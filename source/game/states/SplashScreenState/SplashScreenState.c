/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
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

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <GameState.h>
#include <Screen.h>
#include <I18n.h>
#include <Printing.h>

#include "SplashScreenState.h"
#include <objects.h>
#include <macros.h>
#include <lang.h>
#include "stages.h"

#include <AdjustmentScreenState.h>
#include <PrecautionScreenState.h>
#include <AutomaticPauseSelectionScreenState.h>
#include <LanguageSelectionScreenState.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void SplashScreenState_destructor(SplashScreenState this);
static void SplashScreenState_constructor(SplashScreenState this);
static void SplashScreenState_enter(SplashScreenState this, void* owner);
static void SplashScreenState_exit(SplashScreenState this, void* owner);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

#define SplashScreenState_ATTRIBUTES											\
																				\
	/* inherits */																\
	GameState_ATTRIBUTES														\
																				\
	/* currently active screen */												\
	u8 currentScreen;															\
																				\
	/* screens */																\
	GameState screens[];														\

__CLASS_DEFINITION(SplashScreenState);
__SINGLETON_DYNAMIC(SplashScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void SplashScreenState_constructor(SplashScreenState this)
{
	__CONSTRUCT_BASE(GameState);
	
	this->currentScreen = 0;
	this->screens[0] = (GameState)AdjustmentScreenState_getInstance();
	this->screens[1] = (GameState)PrecautionScreenState_getInstance();
	this->screens[2] = (GameState)AutomaticPauseSelectionScreenState_getInstance();
}

// class's destructor
static void SplashScreenState_destructor(SplashScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void SplashScreenState_enter(SplashScreenState this, void* owner)
{
    Game_changeState(Game_getInstance(), (GameState)AdjustmentScreenState_getInstance());
    //Game_changeState(Game_getInstance(), (GameState)this->screens[this->currentScreen]);
}

// state's exit
static void SplashScreenState_exit(SplashScreenState this, void* owner)
{
    // TODO: check if last state reached
    // sizeof(this->screens)/sizeof(this->screens[0])
    if (true)
    {
        // destroy the state
        __DELETE(this);
    }
}