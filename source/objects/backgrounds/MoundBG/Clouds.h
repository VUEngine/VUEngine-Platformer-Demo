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

#ifndef CLOUDS_H_
#define CLOUDS_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CLOUDS_MOVE_DELAY 100


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Clouds_METHODS															    \
	InanimatedInGameEntity_METHODS;
	

#define Clouds_SET_VTABLE(ClassName)												\
	InanimatedInGameEntity_SET_VTABLE(ClassName);								    \
	__VIRTUAL_SET(ClassName, Clouds, handleMessage);								\
    __VIRTUAL_SET(ClassName, Clouds, isVisible);									\
    __VIRTUAL_SET(ClassName, Clouds, resume);										\
	__VIRTUAL_SET(ClassName, Clouds, moves);										\

__CLASS(Clouds);

#define Clouds_ATTRIBUTES															\
																				    \
	/* it is derivated from */													    \
	InanimatedInGameEntity_ATTRIBUTES											    \


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Clouds, InanimatedInGameEntityDefinition* animatedEntityDefinition, int id, const char* const name);

void Clouds_constructor(Clouds this, InanimatedInGameEntityDefinition* definition, int id, const char* const name);
void Clouds_destructor(Clouds this);
void Clouds_startMoving(Clouds this);
bool Clouds_handleMessage(Clouds this, Telegram telegram);
bool Clouds_isVisible(Clouds this, int pad);
void Clouds_resume(Clouds this);
bool Clouds_moves(Clouds this);


#endif