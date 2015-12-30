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

#include <CannonBall.h>
#include <Hero.h>

#include "CannonBallIdle.h"
#include "CannonBallMoving.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void CannonBallIdle_constructor(CannonBallIdle this);
void CannonBallIdle_destructor(CannonBallIdle this);
void CannonBallIdle_enter(CannonBallIdle this, void* owner);
void CannonBallIdle_execute(CannonBallIdle this, void* owner);
void CannonBallIdle_exit(CannonBallIdle this, void* owner);
bool CannonBallIdle_handleMessage(CannonBallIdle this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CannonBallIdle, State);
__SINGLETON(CannonBallIdle);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void CannonBallIdle_constructor(CannonBallIdle this)
{
	// construct base
	__CONSTRUCT_BASE();
}

// class's destructor
void CannonBallIdle_destructor(CannonBallIdle this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void CannonBallIdle_enter(CannonBallIdle this, void* owner)
{
	// do not move
    // Actor_stopMovement(__SAFE_CAST(Actor, owner), __XAXIS | __YAXIS | __ZAXIS);

	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, owner), "Idle");
}

// state's execute
void CannonBallIdle_execute(CannonBallIdle this, void* owner)
{
    StateMachine_swapState(Actor_getStateMachine(__SAFE_CAST(Actor, owner)), __SAFE_CAST(State, CannonBallMoving_getInstance()));
}

// state's exit
void CannonBallIdle_exit(CannonBallIdle this, void* owner)
{
}

// state's on message
bool CannonBallIdle_handleMessage(CannonBallIdle this, void* owner, Telegram telegram)
{
	return false;
}