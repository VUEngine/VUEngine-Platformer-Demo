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


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <Screen.h>
#include <MessageDispatcher.h>
#include <AdjustmentScreenState.h>
#include <AutoPauseSelectScreenState.h>
#include <Languages.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef ADJUSTMENT_SCREEN_ST;


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void AdjustmentScreenState_destructor(AdjustmentScreenState this);
static void AdjustmentScreenState_constructor(AdjustmentScreenState this);
static void AdjustmentScreenState_processInput(AdjustmentScreenState this, u32 pressedKey);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(AdjustmentScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(AdjustmentScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) AdjustmentScreenState_constructor(AdjustmentScreenState this)
{
	__CONSTRUCT_BASE(SplashScreenState);

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, this), __SAFE_CAST(GameState, AutoPauseSelectScreenState_getInstance()));
	this->stageDefinition = (StageDefinition*)&ADJUSTMENT_SCREEN_ST;
}

// class's destructor
static void AdjustmentScreenState_destructor(AdjustmentScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

static void AdjustmentScreenState_processInput(AdjustmentScreenState this, u32 pressedKey __attribute__ ((unused)))
{
    // TODO: replace this ugly hack with a proper Game_isPaused check or something similar
    if(this->nextState == NULL)
    {
		Screen_startEffect(Screen_getInstance(), kFadeOut, __FADE_DURATION);
        Game_unpause(Game_getInstance(), __SAFE_CAST(GameState, this));
    }
    else
    {
	    SplashScreenState_loadNextState(__SAFE_CAST(SplashScreenState, this));
    }
}
