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

#ifndef CUSTOM_SCREEN_EFFECT_MANAGER_H_
#define CUSTOM_SCREEN_EFFECT_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <ScreenEffectManager.h>
#include <Telegram.h>
#include <InGameEntity.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

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
#define CustomScreenEffectManager_METHODS(ClassName)														\
    	ScreenEffectManager_METHODS(ClassName)															\

// declare the virtual methods which are redefined
#define CustomScreenEffectManager_SET_VTABLE(ClassName)													\
    	ScreenEffectManager_SET_VTABLE(ClassName)														\
		__VIRTUAL_SET(ClassName, CustomScreenEffectManager, startEffect);								\
		__VIRTUAL_SET(ClassName, CustomScreenEffectManager, stopEffect);									\
		__VIRTUAL_SET(ClassName, CustomScreenEffectManager, handleMessage);								\

#define CustomScreenEffectManager_ATTRIBUTES																\
        /* super's attributes */																		\
        ScreenEffectManager_ATTRIBUTES																	\
        /* temporary variable to hold the focus entity during shaking fx */								\
        InGameEntity tempFocusInGameEntity;																\
        /* last offset set by shake function */															\
        VBVec3D lastShakeOffset;																		\
        /* time left in current shaking fx (in ms) */													\
        int shakeTimeLeft;																				\

// declare a CustomScreenEffectManager
__CLASS(CustomScreenEffectManager);


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

CustomScreenEffectManager CustomScreenEffectManager_getInstance();

void CustomScreenEffectManager_destructor(CustomScreenEffectManager this);
void CustomScreenEffectManager_startEffect(CustomScreenEffectManager this, int effect, va_list args);
void CustomScreenEffectManager_stopEffect(CustomScreenEffectManager this, int effect);
bool CustomScreenEffectManager_handleMessage(CustomScreenEffectManager this, Telegram telegram);


#endif
