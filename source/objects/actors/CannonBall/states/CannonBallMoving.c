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
#include <Game.h>
#include <InGameEntity.h>
#include <MessageDispatcher.h>
#include <Prototypes.h>

#include <Hero.h>
#include <CannonBall.h>

#include "CannonBallMoving.h"
#include "CannonBallIdle.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void CannonBallMoving_constructor(CannonBallMoving this);
void CannonBallMoving_destructor(CannonBallMoving this);
void CannonBallMoving_enter(CannonBallMoving this, void* owner);
void CannonBallMoving_execute(CannonBallMoving this, void* owner);
void CannonBallMoving_exit(CannonBallMoving this, void* owner);
bool CannonBallMoving_processMessage(CannonBallMoving this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CannonBallMoving, State);
__SINGLETON(CannonBallMoving);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) CannonBallMoving_constructor(CannonBallMoving this)
{
	// construct base
	__CONSTRUCT_BASE(State);
}

// class's destructor
void CannonBallMoving_destructor(CannonBallMoving this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void CannonBallMoving_enter(CannonBallMoving this, void* owner)
{
	CannonBall_startMovement(owner);
}

// state's execute
void CannonBallMoving_execute(CannonBallMoving this, void* owner)
{
    CannonBall_checkPosition(owner);
}

// state's exit
void CannonBallMoving_exit(CannonBallMoving this, void* owner)
{
}

// state's handle message
bool CannonBallMoving_processMessage(CannonBallMoving this, void* owner, Telegram telegram)
{
	return false;
}
