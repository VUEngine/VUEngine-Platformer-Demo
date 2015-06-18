/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef COG_WHEEL_H_
#define COG_WHEEL_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define CogWheel_METHODS															\
	InanimatedInGameEntity_METHODS;

#define CogWheel_SET_VTABLE(ClassName)												\
	InanimatedInGameEntity_SET_VTABLE(ClassName);									\
	__VIRTUAL_SET(ClassName, CogWheel, ready);										\
	__VIRTUAL_SET(ClassName, CogWheel, handleMessage);								\
    __VIRTUAL_SET(ClassName, CogWheel, resume);										\
	__VIRTUAL_SET(ClassName, CogWheel, moves);										\

__CLASS(CogWheel);

#define CogWheel_ATTRIBUTES															\
																					\
	/* it is derivated from */														\
	InanimatedInGameEntity_ATTRIBUTES												\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(CogWheel, InanimatedInGameEntityDefinition* animatedEntityDefinition, int id, const char* const name);

void CogWheel_constructor(CogWheel this, InanimatedInGameEntityDefinition* definition, int id, const char* const name);
void CogWheel_destructor(CogWheel this);
void CogWheel_ready(CogWheel this);
bool CogWheel_handleMessage(CogWheel this, Telegram telegram);
void CogWheel_resume(CogWheel this);
bool CogWheel_moves(CogWheel this);


#endif