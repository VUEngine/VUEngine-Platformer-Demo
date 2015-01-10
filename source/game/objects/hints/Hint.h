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
	kPickUpHint
};


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Hint_METHODS															\
	AnimatedInGameEntity_METHODS;
	

#define Hint_SET_VTABLE(ClassName)												\
	AnimatedInGameEntity_SET_VTABLE(ClassName);									\
	__VIRTUAL_SET(ClassName, Hint, handleMessage);

__CLASS(Hint);

#define Hint_ATTRIBUTES															\
																				\
	/* it is derivated from */													\
	AnimatedInGameEntity_ATTRIBUTES												\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Hint, __PARAMETERS(AnimatedInGameEntityDefinition* animatedEntityDefinition, int ID));

void Hint_constructor(Hint this, AnimatedInGameEntityDefinition* definition, int ID);
void Hint_destructor(Hint this);
bool Hint_handleMessage(Hint this, Telegram telegram);
void Hint_open(Hint this);
void Hint_close(Hint this);
void Hint_delete(Hint this, Object eventFirer);
void Hint_playActiveLanguageHint(Hint this, Object eventFirer);


#endif