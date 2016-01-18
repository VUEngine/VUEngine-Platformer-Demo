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
#include <MovingEnemy.h>

#include "MovingEnemyMoving.h"
#include "MovingEnemyIdle.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void MovingEnemyMoving_constructor(MovingEnemyMoving this);
void MovingEnemyMoving_destructor(MovingEnemyMoving this);
void MovingEnemyMoving_enter(MovingEnemyMoving this, void* owner);
void MovingEnemyMoving_execute(MovingEnemyMoving this, void* owner);
void MovingEnemyMoving_exit(MovingEnemyMoving this, void* owner);
bool MovingEnemyMoving_handleMessage(MovingEnemyMoving this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(MovingEnemyMoving, State);
__SINGLETON(MovingEnemyMoving);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void MovingEnemyMoving_constructor(MovingEnemyMoving this)
{
	// construct base
	__CONSTRUCT_BASE();
}

// class's destructor
void MovingEnemyMoving_destructor(MovingEnemyMoving this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void MovingEnemyMoving_enter(MovingEnemyMoving this, void* owner)
{
	MovingEnemy_startMovement((MovingEnemy)owner);
	
	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, owner), "Spin");
}

// state's execute
void MovingEnemyMoving_execute(MovingEnemyMoving this, void* owner)
{	
	// if not waiting
	if(!Enemy_getActionTime((Enemy)owner))
    {
		// update movement
		MovingEnemy_move((MovingEnemy)owner);
	}
	else
    {
		// if wait time elapsed
		if(MOVING_ENTITY_WAIT_DELAY < Clock_getTime(Game_getInGameClock(Game_getInstance())) - Enemy_getActionTime((Enemy)owner))
		{
			// start movement in opposite direction
			MovingEnemy_startMovement((MovingEnemy)owner);
		}
	}
	
}

// state's exit
void MovingEnemyMoving_exit(MovingEnemyMoving this, void* owner)
{
}

// state's handle message
bool MovingEnemyMoving_handleMessage(MovingEnemyMoving this, void* owner, Telegram telegram)
{

	return false;
}