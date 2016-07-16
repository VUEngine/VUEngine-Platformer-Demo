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

#ifndef HIDE_LAYER_H_
#define HIDE_LAYER_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

#define HIDE_LAYER_OVERLAPPING_CHECK_DELAY  100


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define HideLayer_METHODS(ClassName)																	\
	    AnimatedInGameEntity_METHODS(ClassName);														\

#define HideLayer_SET_VTABLE(ClassName)																	\
        AnimatedInGameEntity_SET_VTABLE(ClassName);														\
        __VIRTUAL_SET(ClassName, HideLayer, handleMessage);												\

__CLASS(HideLayer);

#define HideLayer_ATTRIBUTES																			\
        /* it is derived from */																		\
        AnimatedInGameEntity_ATTRIBUTES																	\
        /* is hide layer currently being overlapped by hero? */											\
        bool currentlyOverlappingHero;																	\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(HideLayer, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);

void HideLayer_constructor(HideLayer this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);
void HideLayer_destructor(HideLayer this);
bool HideLayer_handleMessage(HideLayer this, Telegram telegram);
void HideLayer_setOverlapping(HideLayer this);
bool HideLayer_isOverlapping(HideLayer this);


#endif
