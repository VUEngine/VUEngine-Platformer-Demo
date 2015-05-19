/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
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

void Cannon_addSmokeParticleSystem(Cannon this);
static void Cannon_hideSmoke(Cannon this);
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

    this->smokeParticleSystem = NULL;

	// register a shape for collision detection
    //this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __GET_CAST(SpatialObject, this), kCuboid);

    // send delayed message to self to trigger first shot
    MessageDispatcher_dispatchMessage(CANNON_SHOOT_DELAY, __GET_CAST(Object, this), __GET_CAST(Object, this), kCannonShoot, NULL);
}

// class's destructor
void Cannon_destructor(Cannon this)
{
    this->smokeParticleSystem = NULL;

	// delete the super object
	__DESTROY_BASE;
}

void Cannon_ready(Cannon this)
{
	ASSERT(this, "Cannon::ready: null this");

	Entity_ready(__GET_CAST(Entity, this));

	Cannon_addSmokeParticleSystem(this);
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

		case kCannonHideSmoke:

            Cannon_hideSmoke(this);
			break;
	}
	
	return false;
}

void Cannon_suspend(Cannon this)
{
	ASSERT(this, "Cannon::suspend: null this");

	Entity_suspend(__GET_CAST(Entity, this));

	ParticleSystem_pause(this->smokeParticleSystem);
}

// start shooting a cannon ball
void Cannon_shoot(Cannon this)
{
	ASSERT(this, "Cannon::shoot: null this");

    // start shooting sequence
	AnimatedInGameEntity_playAnimation(__GET_CAST(AnimatedInGameEntity, this), "Shoot");

    // send delayed message to self to trigger next shot
    MessageDispatcher_dispatchMessage(CANNON_SHOOT_DELAY, __GET_CAST(Object, this), __GET_CAST(Object, this), kCannonShoot, NULL);
}

void Cannon_addSmokeParticleSystem(Cannon this)
{
	ASSERT(this, "Cannon::addSmokeParticleSystem: null this");

	extern EntityDefinition SMOKE_PS;

	VBVec3D position =
	{
		FTOFIX19_13(0), FTOFIX19_13(0), FTOFIX19_13(0)
	};

	this->smokeParticleSystem = __GET_CAST(ParticleSystem, Entity_addChildFromDefinition(__GET_CAST(Entity, this), &SMOKE_PS, -1, NULL, &position, NULL));

	ASSERT(this->smokeParticleSystem, "Cannon::addSmokeParticleSystem: null smokeParticleSystem");
}

static void Cannon_hideSmoke(Cannon this)
{
	ParticleSystem_pause(this->smokeParticleSystem);
}

// spawn a cannon ball
void Cannon_spawnCannonBall(Cannon this)
{
	ASSERT(this, "Cannon::spawnCannonBall: null this");

    // start short screen shake
    Screen_startEffect(Screen_getInstance(), kShake, 250);

    // spawn some smoke particles
	ParticleSystem_start(this->smokeParticleSystem);

	// stop the smoke after some time
	MessageDispatcher_dispatchMessage(1000, __GET_CAST(Object, this), __GET_CAST(Object, this), kCannonHideSmoke, NULL);

    // play boom sound
    extern const u16 FIRE1_SND[];
    SoundManager_playFxSound(SoundManager_getInstance(), FIRE1_SND, this->transform.globalPosition);

    // add cannon ball entity to stage
	Stage_addEntity(GameState_getStage(Game_getCurrentState(Game_getInstance())), (EntityDefinition*)&CANNON_BALL_IG, NULL, Container_getLocalPosition(__GET_CAST(Container, this)), NULL, false);
}