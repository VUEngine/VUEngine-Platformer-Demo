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


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <Screen.h>
#include <MessageDispatcher.h>
#include <AdjustmentScreenState.h>
#include <AutoPauseSelectScreenState.h>
#include <Languages.h>
#include <DirectDraw.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef ADJUSTMENT_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void AdjustmentScreenState_destructor(AdjustmentScreenState this);
static void AdjustmentScreenState_constructor(AdjustmentScreenState this);
static void AdjustmentScreenState_processInput(AdjustmentScreenState this, u32 pressedKey);
void AdjustmentScreenState_rhombusEmitterPostProcessingEffect(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(AdjustmentScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(AdjustmentScreenState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) AdjustmentScreenState_constructor(AdjustmentScreenState this)
{
	__CONSTRUCT_BASE(SplashScreenState);

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, this), __SAFE_CAST(GameState, AutoPauseSelectScreenState_getInstance()));
	this->stageDefinition = (StageDefinition*)&ADJUSTMENT_SCREEN_STAGE_ST;
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
	__CALL_BASE_METHOD(SplashScreenState, enter, this, owner);

	// add rhombus effect
	Game_addPostProcessingEffect(Game_getInstance(), AdjustmentScreenState_rhombusEmitterPostProcessingEffect, NULL);
}

static void AdjustmentScreenState_processInput(AdjustmentScreenState this, u32 pressedKey __attribute__ ((unused)))
{
	// TODO: replace this ugly hack with a proper Game_isPaused check or something similar
	if(this->nextState == NULL)
	{
		Screen_startEffect(Screen_getInstance(), kFadeOut, __FADE_DELAY);
		Game_unpause(Game_getInstance(), __SAFE_CAST(GameState, this));
	}
	else
	{
		SplashScreenState_loadNextState(__SAFE_CAST(SplashScreenState, this));
	}
}

void AdjustmentScreenState_drawRhombus(fix19_13 radiusFix19_13, u32 color, VBVec3D spatialObjectPosition)
{
	DirectDraw directDraw = DirectDraw_getInstance();

	DirectDraw_drawLine(
		directDraw,
		(VBVec2D) {spatialObjectPosition.x - radiusFix19_13,	spatialObjectPosition.y,					spatialObjectPosition.z, 0},
		(VBVec2D) {spatialObjectPosition.x,						spatialObjectPosition.y - radiusFix19_13,	spatialObjectPosition.z, 0},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(VBVec2D) {spatialObjectPosition.x + radiusFix19_13,	spatialObjectPosition.y,					spatialObjectPosition.z, 0},
		(VBVec2D) {spatialObjectPosition.x,						spatialObjectPosition.y - radiusFix19_13,	spatialObjectPosition.z, 0},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(VBVec2D) {spatialObjectPosition.x + radiusFix19_13,	spatialObjectPosition.y,					spatialObjectPosition.z, 0},
		(VBVec2D) {spatialObjectPosition.x,						spatialObjectPosition.y + radiusFix19_13,	spatialObjectPosition.z, 0},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(VBVec2D) {spatialObjectPosition.x - radiusFix19_13,	spatialObjectPosition.y,					spatialObjectPosition.z, 0},
		(VBVec2D) {spatialObjectPosition.x,						spatialObjectPosition.y + radiusFix19_13,	spatialObjectPosition.z, 0},
		color
	);
}

void AdjustmentScreenState_rhombusEmitterPostProcessingEffect(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
	u32 color;

	// runtime working variables
	// negative value to achieve an initial delay
	static int radius = -32;

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
	AdjustmentScreenState_drawRhombus(ITOFIX19_13(radius), color, spatialObjectPosition);
	AdjustmentScreenState_drawRhombus(ITOFIX19_13(radius + radius - 72), color, spatialObjectPosition);
}
