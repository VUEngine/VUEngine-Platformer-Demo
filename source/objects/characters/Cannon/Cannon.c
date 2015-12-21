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
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <UserDataManager.h>
#include <Container.h>
#include <Screen.h>
#include <ParticleSystem.h>

#include <CustomScreenMovementManager.h>
#include <objects.h>
#include "Cannon.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Cannon, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Cannon_shoot(Cannon this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Cannon, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(Cannon, animatedInGameEntityDefinition, id, name);

// class's constructor
void Cannon_constructor(Cannon this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
    //this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __SAFE_CAST(SpatialObject, this), kCuboid);
}

// class's destructor
void Cannon_destructor(Cannon this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Cannon_ready(Cannon this)
{
	ASSERT(this, "Cannon::ready: null this");

	Entity_ready(__SAFE_CAST(Entity, this));
	
    // send delayed message to self to trigger first shot
    MessageDispatcher_dispatchMessage(CANNON_SHOOT_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonShoot, NULL);
}

// state's on message
bool Cannon_handleMessage(Cannon this, Telegram telegram)
{
	ASSERT(this, "Cannon::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
    {
		case kCannonShoot:

            Cannon_shoot(this);
			break;
	}
	
	return false;
}

void Cannon_suspend(Cannon this)
{
	ASSERT(this, "Cannon::suspend: null this");

	Entity_suspend(__SAFE_CAST(Entity, this));
}

// start shooting a cannon ball
void Cannon_shoot(Cannon this)
{
	ASSERT(this, "Cannon::shoot: null this");

    // start shooting sequence
	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Shoot");

    // send delayed message to self to trigger next shot
    MessageDispatcher_dispatchMessage(CANNON_SHOOT_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonShoot, NULL);
}

// spawn a cannon ball
void Cannon_spawnCannonBall(Cannon this)
{
	ASSERT(this, "Cannon::spawnCannonBall: null this");

    // start short screen shake
    Screen_startEffect(Screen_getInstance(), kShake, 250);

    // play boom sound
    extern const u16 FIRE_SND[];
    SoundManager_playFxSound(SoundManager_getInstance(), FIRE_SND, this->transform.globalPosition);

    // add cannon ball entity to stage
	Stage_addEntity(GameState_getStage(Game_getCurrentState(Game_getInstance())), (EntityDefinition*)&CANNON_BALL_IG, NULL, Container_getLocalPosition(__SAFE_CAST(Container, this)), NULL, false);
}