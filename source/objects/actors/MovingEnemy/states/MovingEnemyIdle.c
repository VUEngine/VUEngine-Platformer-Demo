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

#include <Optics.h>

#include <MovingEnemy.h>
#include <Hero.h>

#include "MovingEnemyIdle.h"
#include "MovingEnemyMoving.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void MovingEnemyIdle_constructor(MovingEnemyIdle this);
void MovingEnemyIdle_destructor(MovingEnemyIdle this);
void MovingEnemyIdle_enter(MovingEnemyIdle this, void* owner);
void MovingEnemyIdle_execute(MovingEnemyIdle this, void* owner);
void MovingEnemyIdle_exit(MovingEnemyIdle this, void* owner);
bool MovingEnemyIdle_handleMessage(MovingEnemyIdle this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(MovingEnemyIdle, State);
__SINGLETON(MovingEnemyIdle);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void MovingEnemyIdle_constructor(MovingEnemyIdle this)
{
	// construct base
	__CONSTRUCT_BASE();
}

// class's destructor
void MovingEnemyIdle_destructor(MovingEnemyIdle this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void MovingEnemyIdle_enter(MovingEnemyIdle this, void* owner)
{
	// do not move
    // Actor_stopMovement(__SAFE_CAST(Actor, owner), __XAXIS | __YAXIS | __ZAXIS);

	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, owner), "Idle");
}

// state's execute
void MovingEnemyIdle_execute(MovingEnemyIdle this, void* owner)
{
    StateMachine_swapState(Actor_getStateMachine(__SAFE_CAST(Actor, owner)), __SAFE_CAST(State, MovingEnemyMoving_getInstance()));
}

// state's exit
void MovingEnemyIdle_exit(MovingEnemyIdle this, void* owner)
{
}

// state's handle message
bool MovingEnemyIdle_handleMessage(MovingEnemyIdle this, void* owner, Telegram telegram)
{
	return false;
}