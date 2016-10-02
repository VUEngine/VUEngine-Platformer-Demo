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

#ifndef HINT_H_
#define HINT_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

enum HintTypes
{
	kEnterHint = 0,
    kPickUpHint,
    kKeyHint
};


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Hint_METHODS(ClassName)																			\
    	AnimatedInGameEntity_METHODS(ClassName)														\

#define Hint_SET_VTABLE(ClassName)																		\
        AnimatedInGameEntity_SET_VTABLE(ClassName)														\
        __VIRTUAL_SET(ClassName, Hint, resume);															\

__CLASS(Hint);

#define Hint_ATTRIBUTES																					\
        /* it is derived from */																		\
        AnimatedInGameEntity_ATTRIBUTES																	\
        /* the current hint type to show */																\
        u8 type;																						\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Hint, AnimatedInGameEntityDefinition* animatedEntityDefinition, int id, const char* const name);

void Hint_constructor(Hint this, AnimatedInGameEntityDefinition* definition, int id, const char* const name);
void Hint_destructor(Hint this);
void Hint_resume(Hint this);
void Hint_open(Hint this, u8 hintType);
void Hint_close(Hint this);
void Hint_onCloseDone(Hint this, Object eventFirer);
void Hint_onHintOpened(Hint this, Object eventFirer);


#endif
