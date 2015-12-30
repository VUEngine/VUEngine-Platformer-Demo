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

#include <Telegram.h>

#include "EnemyDead.h"
#include <Enemy.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void EnemyDead_constructor(EnemyDead this);
void EnemyDead_destructor(EnemyDead this);
void EnemyDead_enter(EnemyDead this, void* owner);
void EnemyDead_execute(EnemyDead this, void* owner);
void EnemyDead_exit(EnemyDead this, void* owner);
bool EnemyDead_handleMessage(EnemyDead this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(EnemyDead, State);
__SINGLETON(EnemyDead);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void EnemyDead_constructor(EnemyDead this)
{
	// construct base
	__CONSTRUCT_BASE();
}

// class's destructor
void EnemyDead_destructor(EnemyDead this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void EnemyDead_enter(EnemyDead this, void* owner)
{
	Direction direction = InGameEntity_getDirection(__SAFE_CAST(InGameEntity, owner));
	direction.z = __NEAR;
	InGameEntity_setDirection(__SAFE_CAST(InGameEntity, owner), direction);
}

// state's execute
void EnemyDead_execute(EnemyDead this, void* owner)
{
}

// state's exit
void EnemyDead_exit(EnemyDead this, void* owner)
{
}

// state's on message
bool EnemyDead_handleMessage(EnemyDead this, void* owner, Telegram telegram)
{
	return false;
}