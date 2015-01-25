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

#include <string.h>

#include <Game.h>
#include <Screen.h>
#include <MessageDispatcher.h>
#include <VBJaEngineSplashScreenState.h>
#include <TitleScreenState.h>
#include <stages.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void VBJaEngineSplashScreenState_destructor(VBJaEngineSplashScreenState this);
static void VBJaEngineSplashScreenState_constructor(VBJaEngineSplashScreenState this);
static void VBJaEngineSplashScreenState_enter(VBJaEngineSplashScreenState this, void* owner);
static void VBJaEngineSplashScreenState_execute(VBJaEngineSplashScreenState this, void* owner);
static void VBJaEngineSplashScreenState_exit(VBJaEngineSplashScreenState this, void* owner);
static void VBJaEngineSplashScreenState_resume(VBJaEngineSplashScreenState this, void* owner);
static bool VBJaEngineSplashScreenState_handleMessage(VBJaEngineSplashScreenState this, void* owner, Telegram telegram);
static void VBJaEngineSplashScreenState_processInput(VBJaEngineSplashScreenState this, u16 pressedKey);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(VBJaEngineSplashScreenState);
__SINGLETON_DYNAMIC(VBJaEngineSplashScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void VBJaEngineSplashScreenState_constructor(VBJaEngineSplashScreenState this)
{
	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void VBJaEngineSplashScreenState_destructor(VBJaEngineSplashScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void VBJaEngineSplashScreenState_enter(VBJaEngineSplashScreenState this, void* owner)
{
	GameState_loadStage((GameState)this, (StageDefinition*)&VBJAENGINE_SPLASH_SCREEN_ST, true, true);

	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}

// state's execute
static void VBJaEngineSplashScreenState_execute(VBJaEngineSplashScreenState this, void* owner)
{
    VBVec3D translation =
    {
        ITOFIX19_13(1),
        ITOFIX19_13(0),
        ITOFIX19_13(0)
    };

    Screen_move(Screen_getInstance(), translation, false);

 	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void VBJaEngineSplashScreenState_exit(VBJaEngineSplashScreenState this, void* owner)
{
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void VBJaEngineSplashScreenState_resume(VBJaEngineSplashScreenState this, void* owner)
{
	GameState_resume((GameState)this, owner);
	
#ifdef __DEBUG_TOOLS
	if (!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if (!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __ANIMATION_EDITOR
	if (!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
	
	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY >> 1);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_EDITOR
	}
#endif
}

// state's on message
static bool VBJaEngineSplashScreenState_handleMessage(VBJaEngineSplashScreenState this, void* owner, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
	{
		case kKeyPressed:
		{
            u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

            VBJaEngineSplashScreenState_processInput(VBJaEngineSplashScreenState_getInstance(), pressedKey);
        }
        break;
	}

	return false;
}

static void VBJaEngineSplashScreenState_processInput(VBJaEngineSplashScreenState this, u16 pressedKey)
{
	Game_changeState(Game_getInstance(), (GameState)TitleScreenState_getInstance());
}