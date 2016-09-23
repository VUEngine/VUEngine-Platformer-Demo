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

#ifndef CUSTOM_SCREEN_MOVEMENT_MANAGER_H_
#define CUSTOM_SCREEN_MOVEMENT_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <ScreenMovementManager.h>
#include <Telegram.h>
#include <InGameEntity.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

#define SCREEN_EASING_X_DISPLACEMENT				200
#define SCREEN_POSITIVE_EASING_Y_DISPLACEMENT		250
#define SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT		250
//#define SCREEN_EASING_Y_DISPLACEMENT				(3 << __FRAME_CYCLE)
#define SCREEN_HORIZONTAL_DISPLACEMENT 				30
#define SCREEN_VERTICAL_DISPLACEMENT 				(__SCREEN_HEIGHT / 2) + 30
#define SCREEN_WIDTH_REDUCTION						64
#define SCREEN_HEIGHT_REDUCTION						32


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define CustomScreenMovementManager_METHODS(ClassName)													\
    	ScreenMovementManager_METHODS(ClassName)														\

// declare the virtual methods which are redefined
#define CustomScreenMovementManager_SET_VTABLE(ClassName)												\
    	ScreenMovementManager_SET_VTABLE(ClassName)														\
		__VIRTUAL_SET(ClassName, CustomScreenMovementManager, focus);								    \

#define CustomScreenMovementManager_ATTRIBUTES															\
        /* super's attributes */																		\
        ScreenMovementManager_ATTRIBUTES																\
        /* update axis flag */																			\
        VBVec3DFlag positionFlag;																		\
        /* pointer to function that implements the required focusing */									\
        bool (*focusFunction)(CustomScreenMovementManager, u32, u32);                                   \
        bool (*previuosFocusFunction)(CustomScreenMovementManager, u32, u32);                           \

// declare a CustomScreenMovementManager
__CLASS(CustomScreenMovementManager);


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

CustomScreenMovementManager CustomScreenMovementManager_getInstance();

void CustomScreenMovementManager_destructor(CustomScreenMovementManager this);
void CustomScreenMovementManager_focus(CustomScreenMovementManager this, u32 checkIfFocusEntityIsMoving);
void CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager this, VBVec3DFlag positionFlag);
VBVec3DFlag CustomScreenMovementManager_getPositionFlag(CustomScreenMovementManager this);
void CustomScreenMovementManager_enable(CustomScreenMovementManager this);
void CustomScreenMovementManager_disable(CustomScreenMovementManager this);
void CustomScreenMovementManager_enableFocusEasing(CustomScreenMovementManager this);
void CustomScreenMovementManager_disableFocusEasing(CustomScreenMovementManager this);
void CustomScreenMovementManager_alertWhenTargetFocused(CustomScreenMovementManager this);
void CustomScreenMovementManager_dontAlertWhenTargetFocused(CustomScreenMovementManager this);


#endif
