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

#ifndef COIN_H_
#define COIN_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Coin_METHODS															\
	AnimatedInGameEntity_METHODS;
	

#define Coin_SET_VTABLE(ClassName)												\
	AnimatedInGameEntity_SET_VTABLE(ClassName);									\
	__VIRTUAL_SET(ClassName, Coin, handleMessage);								\

__CLASS(Coin);

#define Coin_ATTRIBUTES															\
																				\
	/* it is derived from */													\
	AnimatedInGameEntity_ATTRIBUTES												\
																				\
	/* have I been collected yet? */											\
	bool taken;												                    \


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Coin, AnimatedInGameEntityDefinition* animatedEntityDefinition, int id, const char* const name);

void Coin_constructor(Coin this, AnimatedInGameEntityDefinition* definition, int id, const char* const name);
void Coin_destructor(Coin this);
bool Coin_handleMessage(Coin this, Telegram telegram);
void Coin_removeFromStage(Coin this);
bool Coin_taken(Coin this);


#endif