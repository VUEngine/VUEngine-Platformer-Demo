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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <SoundManager.h>
#include <EventManager.h>
#include <ProgressManager.h>
#include "Collectable.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Collectable::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

// class's destructor
void Collectable::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's handle message
bool Collectable::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageTakeItem:
		{
			// play collect sound
			extern Sound CollectSound;
			SoundManager::playSound(SoundManager::getInstance(), &CollectSound, kPlayAll, (const Vector3D*)&this->transformation.globalPosition, kSoundWrapperPlaybackNormal, NULL, NULL);

			// set shape to inactive so no other hits with this item can occur
			Collectable::allowCollisions(this, false);

			// additional action
			Collectable::collect(this);

			// delete myself now
			Collectable::deleteMyself(this);

			break;
		}
	}

	return false;
}

void Collectable::collect()
{}
