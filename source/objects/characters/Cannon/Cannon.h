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

#ifndef CANNON_H_
#define CANNON_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CANNON_SHOOT_DELAY 7500


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Cannon_METHODS															\
	AnimatedInGameEntity_METHODS;
	

#define Cannon_SET_VTABLE(ClassName)											\
	AnimatedInGameEntity_SET_VTABLE(ClassName);									\
	__VIRTUAL_SET(ClassName, Cannon, handleMessage);							\
	__VIRTUAL_SET(ClassName, Cannon, ready);									\
	__VIRTUAL_SET(ClassName, Cannon, suspend);									\

__CLASS(Cannon);

#define Cannon_ATTRIBUTES														\
																				\
	/* it is derivated from */													\
	AnimatedInGameEntity_ATTRIBUTES												\
																				\
	/* smoke particle system */													\
	ParticleSystem smokeParticleSystem;											\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Cannon, AnimatedInGameEntityDefinition* animatedEntityDefinition, int id, const char* const name);

void Cannon_constructor(Cannon this, AnimatedInGameEntityDefinition* definition, int id, const char* const name);
void Cannon_destructor(Cannon this);
bool Cannon_handleMessage(Cannon this, Telegram telegram);
void Cannon_ready(Cannon this);
void Cannon_suspend(Cannon this);
void Cannon_shoot(Cannon this);
void Cannon_spawnCannonBall(Cannon this);


#endif