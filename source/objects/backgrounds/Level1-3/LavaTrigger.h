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

#ifndef LAVA_TRIGGER_H_
#define LAVA_TRIGGER_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define LavaTrigger_METHODS																\
	InanimatedInGameEntity_METHODS;
	

#define LavaTrigger_SET_VTABLE(ClassName)												\
	InanimatedInGameEntity_SET_VTABLE(ClassName);										\
	__VIRTUAL_SET(ClassName, LavaTrigger, handleMessage);								\

__CLASS(LavaTrigger);

#define LavaTrigger_ATTRIBUTES															\
																						\
	/* it is derivated from */															\
	InanimatedInGameEntity_ATTRIBUTES													\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(LavaTrigger, InanimatedInGameEntityDefinition* animatedEntityDefinition, int ID);

void LavaTrigger_constructor(LavaTrigger this, InanimatedInGameEntityDefinition* definition, int ID);
void LavaTrigger_destructor(LavaTrigger this);
bool LavaTrigger_handleMessage(LavaTrigger this, Telegram telegram);


#endif