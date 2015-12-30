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
    CannonBall_stopMovement(owner);
}

// state's execute
void CannonBallIdle_execute(CannonBallIdle this, void* owner)
{
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