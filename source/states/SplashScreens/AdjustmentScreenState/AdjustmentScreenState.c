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
#include <PostProcessingEffects.h>


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
void AdjustmentScreenState_rhombusEmitterPostProcessingEffect(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject);


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

// state's enter
void AdjustmentScreenState_enter(AdjustmentScreenState this, void* owner)
{
	// call base
	SplashScreenState_enter(__SAFE_CAST(SplashScreenState, this), owner);

	// add rhombus effect
    Game_addPostProcessingEffect(Game_getInstance(), AdjustmentScreenState_rhombusEmitterPostProcessingEffect, NULL);
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

void AdjustmentScreenState_rhombusEmitterPostProcessingEffect(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
    u32 color;

    // runtime working variables
    // negative value to achieve an initial delay
    static int radius = -256;

    // increase radius by 1 in each cycle
    radius++;

    // gradually decrease color with larger radius
    if(radius < 68)
    {
        return;
    }
    else if(radius < 160)
    {
        color = __COLOR_BRIGHT_RED;
    }
    else if(radius < 224)
    {
        color = __COLOR_MEDIUM_RED;
    }
    else if(radius < 280)
    {
        color = __COLOR_DARK_RED;
    }
    else if(radius < 400)
    {
        // pause for a little bit before restarting
        return;
    }
    else
    {
        // reset radius when reaching a certain length
        radius = 68;
        return;
    }

    // draw rhombuses around object with given radius and color
    VBVec3D spatialObjectPosition = {FTOFIX19_13(192), FTOFIX19_13(112), FTOFIX19_13(0)};
    PostProcessingEffects_drawRhombus(ITOFIX19_13(radius), color, spatialObjectPosition);
	PostProcessingEffects_drawRhombus(ITOFIX19_13(radius + radius - 72), color, spatialObjectPosition);
}
