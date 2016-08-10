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

#include <MovingEntity.h>
#include <Hero.h>

#include "MovingEntityIdle.h"
#include "MovingEntityMoving.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void MovingEntityIdle_constructor(MovingEntityIdle this);
void MovingEntityIdle_destructor(MovingEntityIdle this);
void MovingEntityIdle_enter(MovingEntityIdle this, void* owner);
void MovingEntityIdle_execute(MovingEntityIdle this, void* owner);
bool MovingEntityIdle_processMessage(MovingEntityIdle this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(MovingEntityIdle, State);
__SINGLETON(MovingEntityIdle);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) MovingEntityIdle_constructor(MovingEntityIdle this)
{
	// construct base
	__CONSTRUCT_BASE(State);
}

// class's destructor
void MovingEntityIdle_destructor(MovingEntityIdle this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void MovingEntityIdle_enter(MovingEntityIdle this __attribute__ ((unused)), void* owner)
{
	// do not move
	MovingEntity_stopMovement(__SAFE_CAST(MovingEntity, owner));
}

// state's execute
void MovingEntityIdle_execute(MovingEntityIdle this __attribute__ ((unused)), void* owner)
{
    StateMachine_swapState(Actor_getStateMachine(__SAFE_CAST(Actor, owner)), __SAFE_CAST(State, MovingEntityMoving_getInstance()));
}


// state's handle message
bool MovingEntityIdle_processMessage(MovingEntityIdle this __attribute__ ((unused)), void* owner, Telegram telegram)
{
	// handle messages that any state would handle here
	switch(Telegram_getMessage(telegram))
    {
		case 1001:

			StateMachine_swapState(Actor_getStateMachine(__SAFE_CAST(Actor, owner)), __SAFE_CAST(State, MovingEntityIdle_getInstance()));
			break;
    }

	return false;
}
