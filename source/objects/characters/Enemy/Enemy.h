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

#ifndef ENEMY_H_
#define ENEMY_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>

#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Enemy_METHODS						\
	Actor_METHODS;							\
	__VIRTUAL_DEC(canAttack);				\
	__VIRTUAL_DEC(takeHit);
	
	

#define Enemy_SET_VTABLE(ClassName)					\
	Actor_SET_VTABLE(ClassName);					\
	__VIRTUAL_SET(ClassName, Enemy, canAttack);
	
	

// Abstract class
__CLASS(Enemy);

#define Enemy_ATTRIBUTES							\
													\
	/* it is derivated from */						\
	Actor_ATTRIBUTES								\
													\
	/* Enemy has energy	*/							\
	u8 energy;										\
													\
	/* to know when a specific state begins */		\
	u32 actionTime;

	



//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

void Enemy_constructor(Enemy this, ActorDefinition* definition, int id, const char* const name);
void Enemy_destructor(Enemy this);
u32 Enemy_getActionTime(Enemy this);
bool Enemy_canAttack(Enemy this);
bool Enemy_onPlatformEdge(Enemy this);


#endif