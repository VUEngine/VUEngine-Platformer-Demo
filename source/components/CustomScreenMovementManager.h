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
#define SCREEN_POSITIVE_EASING_Y_DISPLACEMENT		300
#define SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT		400
//#define SCREEN_EASING_Y_DISPLACEMENT				(3 << __FRAME_CYCLE)
#define SCREEN_HORIZONTAL_DISPLACEMENT 				30
#define SCREEN_VERTICAL_DISPLACEMENT 				(__SCREEN_HEIGHT / 2) + 30
#define SCREEN_WIDTH_REDUCTION						64
#define SCREEN_HEIGHT_REDUCTION						64

// delay between screen movements during shaking effect (in ms)
#define MINIMUM_SHAKE_DELAY							20
#define SHAKE_DELAY_DELTA							60

enum CustomScreenFX
{
	kShake = kScreenLastFX,
};

//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define CustomScreenMovementManager_METHODS(ClassName)													\
    	ScreenMovementManager_METHODS(ClassName)														\

// declare the virtual methods which are redefined
#define CustomScreenMovementManager_SET_VTABLE(ClassName)												\
    	ScreenMovementManager_SET_VTABLE(ClassName)														\
		__VIRTUAL_SET(ClassName, CustomScreenMovementManager, position);								\
		__VIRTUAL_SET(ClassName, CustomScreenMovementManager, startEffect);								\
		__VIRTUAL_SET(ClassName, CustomScreenMovementManager, stopEffect);								\
		__VIRTUAL_SET(ClassName, CustomScreenMovementManager, handleMessage);							\

#define CustomScreenMovementManager_ATTRIBUTES															\
        /* super's attributes */																		\
        ScreenMovementManager_ATTRIBUTES;																\
        /* temporary variable to hold the focus entity during shaking fx */								\
        InGameEntity tempFocusInGameEntity;																\
        /* last offset set by shake function */															\
        VBVec3D lastShakeOffset;																		\
        /* time left in current shaking fx (in ms) */													\
        int shakeTimeLeft;																				\
        /* update axis flag */																			\
        VBVec3DFlag positionFlag;																		\
        /* to calculate elapsed time */																	\
        u32 previousTime;																    			\

// declare a CustomScreenMovementManager
__CLASS(CustomScreenMovementManager);


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

CustomScreenMovementManager CustomScreenMovementManager_getInstance();

void CustomScreenMovementManager_destructor(CustomScreenMovementManager this);
void CustomScreenMovementManager_position(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving);
void CustomScreenMovementManager_startEffect(CustomScreenMovementManager this, int effect, int duration);
void CustomScreenMovementManager_stopEffect(CustomScreenMovementManager this, int effect);
void CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager this, VBVec3DFlag positionFlag);
VBVec3DFlag CustomScreenMovementManager_getPositionFlag(CustomScreenMovementManager this);
bool CustomScreenMovementManager_handleMessage(CustomScreenMovementManager this, Telegram telegram);


#endif
