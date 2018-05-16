/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <Entity.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <Container.h>
#include <Camera.h>
#include <ParticleSystem.h>
#include <SoundManager.h>
#include <CustomCameraEffectManager.h>
#include <CannonBall.h>
#include "Cannon.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Cannon::shoot(Cannon this);
static void Cannon::onCannonBallSpawned(Cannon this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Cannon::constructor(Cannon this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Cannon::constructor: null this");

	// construct base
	Base::constructor(animatedEntityDefinition, id, internalId, name);
}

// class's destructor
void Cannon::destructor(Cannon this)
{
	ASSERT(this, "Cannon::destructor: null this");

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kCannonShoot);

	// not necessary to manually destroy the CannonBall here as all children are automatically
	// destroyed as well when an entity is unloaded

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Cannon::ready(Cannon this, bool recursive)
{
	ASSERT(this, "Cannon::ready: null this");

	// call base
	Base::ready(this, recursive);

	// send delayed message to self to trigger first shot
	MessageDispatcher::dispatchMessage(CANNON_INITIAL_SHOOT_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonShoot, NULL);
}

// state's handle message
bool Cannon::handleMessage(Cannon this, Telegram telegram)
{
	ASSERT(this, "Cannon::handleMessage: null this");

	switch(Telegram::getMessage(telegram))
	{
		case kCannonShoot:

			Cannon::shoot(this);
			break;
	}

	return false;
}

// start shooting a cannon ball
void Cannon::shoot(Cannon this)
{
	ASSERT(this, "Cannon::shoot: null this");

	if(!this->children)
	{
		// add cannon ball as child
		extern PositionedEntityROMDef CANNON_BALL;

		Stage::spawnEntity(Game::getStage(Game::getInstance()), &CANNON_BALL, __SAFE_CAST(Container, this), (EventListener)Cannon::onCannonBallSpawned);
		return;
	}

	// start shooting sequence
	AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Shoot");

	// send delayed message to self to trigger next shot
	MessageDispatcher::dispatchMessage(CANNON_SHOOT_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonShoot, NULL);
}

static void Cannon::onCannonBallSpawned(Cannon this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Cannon::onCannonBallSpawned: null this");

	// start shooting sequence
	AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Shoot");

	// send delayed message to self to trigger next shot
	MessageDispatcher::dispatchMessage(CANNON_SHOOT_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonShoot, NULL);
}

// spawn a cannon ball, this is the callback of the "Shoot" animation
void Cannon::spawnCannonBall(Cannon this)
{
	ASSERT(this, "Cannon::spawnCannonBall: null this");

	// start short screen shake
	Camera::startEffect(Camera::getInstance(), kShake, 250);

	// play boom sound
	extern const u16 FIRE_SND[];
	SoundManager::playFxSound(SoundManager::getInstance(), FIRE_SND, this->transformation.globalPosition);

	// set cannon ball to moving state
	ASSERT(1 == VirtualList::getSize(this->children), "Cannon::spawnCannonBall: no children");
	CannonBall cannonBall = __SAFE_CAST(CannonBall, VirtualList::front(this->children));

	MessageDispatcher::dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, cannonBall), kCannonShoot, NULL);
}
