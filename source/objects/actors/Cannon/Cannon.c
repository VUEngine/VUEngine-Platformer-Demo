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
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Cannon::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

// class's destructor
void Cannon::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageCannonShoot);

	// not necessary to manually destroy the CannonBall here as all children are automatically
	// destroyed as well when an entity is unloaded

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Cannon::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// send delayed message to self to trigger first shot
	MessageDispatcher::dispatchMessage(CANNON_INITIAL_SHOOT_DELAY, Object::safeCast(this), Object::safeCast(this), kMessageCannonShoot, NULL);
}

// state's handle message
bool Cannon::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageCannonShoot:

			Cannon::shoot(this);
			break;
	}

	return false;
}

// start shooting a cannon ball
void Cannon::shoot()
{
	if(!this->children)
	{
		// add cannon ball as child
		extern PositionedEntityROMSpec CANNON_BALL;

		Stage::spawnEntity(Game::getStage(Game::getInstance()), &CANNON_BALL, Container::safeCast(this), (EventListener)Cannon::onCannonBallSpawned);
		return;
	}

	// start shooting sequence
	AnimatedEntity::playAnimation(this, "Shoot");

	// send delayed message to self to trigger next shot
	MessageDispatcher::dispatchMessage(CANNON_SHOOT_DELAY, Object::safeCast(this), Object::safeCast(this), kMessageCannonShoot, NULL);
}

void Cannon::onCannonBallSpawned(Object eventFirer __attribute__ ((unused)))
{
	// start shooting sequence
	AnimatedEntity::playAnimation(this, "Shoot");

	// send delayed message to self to trigger next shot
	MessageDispatcher::dispatchMessage(CANNON_SHOOT_DELAY, Object::safeCast(this), Object::safeCast(this), kMessageCannonShoot, NULL);
}

// spawn a cannon ball, this is the callback of the "Shoot" animation
void Cannon::spawnCannonBall()
{
	// start short screen shake
	Camera::startEffect(Camera::getInstance(), kShake, 250);

	// play boom sound
	//SoundManager::playFxSound(SoundManager::getInstance(), FIRE_SND, this->transformation.globalPosition);

	// set cannon ball to moving state
	ASSERT(1 == VirtualList::getSize(this->children), "Cannon::spawnCannonBall: no children");
	CannonBall cannonBall = CannonBall::safeCast(VirtualList::front(this->children));

	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(cannonBall), kMessageCannonShoot, NULL);
}
