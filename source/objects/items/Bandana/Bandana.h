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

#ifndef BANDANA_H_
#define BANDANA_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Bandana_METHODS(ClassName)																		\
	    AnimatedInGameEntity_METHODS(ClassName)														    \


#define Bandana_SET_VTABLE(ClassName)																	\
        AnimatedInGameEntity_SET_VTABLE(ClassName)														\
        __VIRTUAL_SET(ClassName, Bandana, handleMessage);												\

__CLASS(Bandana);

#define Bandana_ATTRIBUTES																				\
        /* it is derived from */																		\
        AnimatedInGameEntity_ATTRIBUTES																	\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Bandana, AnimatedInGameEntityDefinition* animatedEntityDefinition, int id, const char* const name);

void Bandana_constructor(Bandana this, AnimatedInGameEntityDefinition* definition, int id, const char* const name);
void Bandana_destructor(Bandana this);
bool Bandana_handleMessage(Bandana this, Telegram telegram);
void Bandana_removeFromStage(Bandana this);


#endif
