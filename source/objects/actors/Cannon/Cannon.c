/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
void Cannon::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
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
		extern PositionedEntity CannonBallPositionedEntity;

		Stage::spawnEntity(Game::getStage(Game::getInstance()), &CannonBallPositionedEntity, Container::safeCast(this), (EventListener)Cannon::onCannonBallSpawned);
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
	extern Sound FireSound;
	SoundManager::playSound(SoundManager::getInstance(), &FireSound, kPlayAll, (const Vector3D*)&this->transformation.globalPosition, kSoundWrapperPlaybackNormal, NULL, NULL);

	// set cannon ball to moving state
	NM_ASSERT(1 == VirtualList::getSize(this->children), "Cannon::spawnCannonBall: no children");
	CannonBall cannonBall = CannonBall::safeCast(VirtualList::front(this->children));

	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(cannonBall), kMessageCannonShoot, NULL);
}
