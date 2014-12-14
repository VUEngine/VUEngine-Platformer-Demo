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

#ifndef ENEMY_ATTACK_H_
#define ENEMY_ATTACK_H_



//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <StateMachine.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define EnemyAttack_METHODS								\
	State_METHODS;									

// declare the virtual methods which are redefined
#define EnemyAttack_SET_VTABLE(ClassName)					\
	State_SET_VTABLE(ClassName)								\
	__VIRTUAL_SET(ClassName, EnemyAttack, enter);			\
	__VIRTUAL_SET(ClassName, EnemyAttack, execute);			\
	__VIRTUAL_SET(ClassName, EnemyAttack, exit);			\
	__VIRTUAL_SET(ClassName, EnemyAttack, handleMessage);	\



__CLASS(EnemyAttack);

#define EnemyAttack_ATTRIBUTES			\
										\
	/* inherits */						\
	State_ATTRIBUTES


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// setup the init focus screen
EnemyAttack EnemyAttack_getInstance();

// class's constructor
void EnemyAttack_constructor(EnemyAttack this);

// class's destructor
void EnemyAttack_destructor(EnemyAttack this);

// state's enter
void EnemyAttack_enter(EnemyAttack this, void* owner);

// state's execute
void EnemyAttack_execute(EnemyAttack this, void* owner);

// state's enter
void EnemyAttack_exit(EnemyAttack this, void* owner);

// state's on message
u16 EnemyAttack_handleMessage(EnemyAttack this, void* owner, Telegram telegram);


#endif