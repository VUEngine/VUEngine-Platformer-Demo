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

#include <EnemyDead.h>
#include <Hero.h>
#include <MovingEntity.h>

#include "MovingEntityMoving.h"
#include "MovingEntityIdle.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void MovingEntityMoving_constructor(MovingEntityMoving this);
void MovingEntityMoving_destructor(MovingEntityMoving this);
void MovingEntityMoving_enter(MovingEntityMoving this, void* owner);
void MovingEntityMoving_execute(MovingEntityMoving this, void* owner);
void MovingEntityMoving_exit(MovingEntityMoving this, void* owner);
bool MovingEntityMoving_handleMessage(MovingEntityMoving this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(MovingEntityMoving, State);
__SINGLETON(MovingEntityMoving);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void MovingEntityMoving_constructor(MovingEntityMoving this)
{
	// construct base
	__CONSTRUCT_BASE();
}

// class's destructor
void MovingEntityMoving_destructor(MovingEntityMoving this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void MovingEntityMoving_enter(MovingEntityMoving this, void* owner)
{
	MovingEntity_startMovement((MovingEntity)owner);
}

// state's execute
void MovingEntityMoving_execute(MovingEntityMoving this, void* owner)
{	
	MovingEntity_checkDisplacement(owner);
}

// state's exit
void MovingEntityMoving_exit(MovingEntityMoving this, void* owner)
{
}

// state's handle message
bool MovingEntityMoving_handleMessage(MovingEntityMoving this, void* owner, Telegram telegram)
{
	return false;
}