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


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "EnemyAttack.h"
#include <Enemy.h>
#include "../../hero/Hero.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(EnemyAttack, State);
__SINGLETON(EnemyAttack);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void EnemyAttack_constructor(EnemyAttack this)
{
	// construct base
	__CONSTRUCT_BASE();
}

// class's destructor
void EnemyAttack_destructor(EnemyAttack this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void EnemyAttack_enter(EnemyAttack this, void* owner)
{
	// do not move
//	Actor_stopMovement(__SAFE_CAST(Actor, owner), __XAXIS | __YAXIS | __ZAXIS);
}

// state's execute
void EnemyAttack_execute(EnemyAttack this, void* owner)
{
    // change state
    StateMachine_popState(Actor_getStateMachine(__SAFE_CAST(Actor, owner)));
}

// state's exit
void EnemyAttack_exit(EnemyAttack this, void* owner)
{
}

// state's on message
bool EnemyAttack_handleMessage(EnemyAttack this, void* owner, Telegram telegram)
{
	return false;
}