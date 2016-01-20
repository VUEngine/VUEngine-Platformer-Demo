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

#include <Shape.h>
#include "Enemy.h"


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Enemy, Actor);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Enemy_constructor(Enemy this, ActorDefinition* characterDefinition, int id, const char* const name)
{
	// call base
	__CONSTRUCT_BASE(characterDefinition, id, name);

	// no register time
	this->actionTime = 0;
	
	// default energy
	this->energy = 0;
}

// class's constructor
void Enemy_destructor(Enemy this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// get time in which certain action did
u32 Enemy_getActionTime(Enemy this)
{
	return this->actionTime;
}

// tell whether it is ready to attack hero
bool Enemy_canAttack(Enemy this)
{
	return true;
}

// die
void Enemy_die(Enemy this)
{
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);

	// now change state to dead
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, EnemyDead_getInstance()));
}
