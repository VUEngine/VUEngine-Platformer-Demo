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
#include <Screen.h>
#include <MessageDispatcher.h>
#include <VBJaEngineScreenState.h>
#include <TitleScreenState.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef VBJAENGINE_SCREEN_ST;


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void VBJaEngineScreenState_destructor(VBJaEngineScreenState this);
static void VBJaEngineScreenState_constructor(VBJaEngineScreenState this);
static void VBJaEngineScreenState_print(VBJaEngineScreenState this);
static void VBJaEngineScreenState_execute(VBJaEngineScreenState this, void* owner);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(VBJaEngineScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(VBJaEngineScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void VBJaEngineScreenState_constructor(VBJaEngineScreenState this)
{
	__CONSTRUCT_BASE();

	SplashScreenState_setNextstate(__UPCAST(SplashScreenState, this), __UPCAST(GameState, TitleScreenState_getInstance()));
	this->stageDefinition = (StageDefinition*)&VBJAENGINE_SCREEN_ST;
}

// class's destructor
static void VBJaEngineScreenState_destructor(VBJaEngineScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

static void VBJaEngineScreenState_print(VBJaEngineScreenState this)
{
}

// state's execute
static void VBJaEngineScreenState_execute(VBJaEngineScreenState this, void* owner)
{
    VBVec3D translation =
    {
        ITOFIX19_13(1),
        ITOFIX19_13(0),
        ITOFIX19_13(0)
    };

    Screen_move(Screen_getInstance(), translation, false);

 	// call base
    SplashScreenState_execute(__UPCAST(SplashScreenState, this), owner);
}
