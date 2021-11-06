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

#include <stdlib.h>
#include <GameEvents.h>
#include <Game.h>
#include <EventManager.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <ProgressManager.h>
#include <Container.h>
#include <SoundManager.h>
#include "Coin.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntitySpec Level1HouseEntity;
extern AnimatedEntityROMSpec CoinBackEntity;
extern AnimatedEntityROMSpec CoinSilhouetteEntity;
extern AnimatedEntityROMSpec CoinBackSilhouetteEntity;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Coin::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);

	// if coin has already been collected, show silhouette representation
	int coinId = atoi(this->name);
	if(ProgressManager::getCoinStatus(ProgressManager::getInstance(), coinId))
	{
		AnimatedEntitySpec* animatedEntitySpec = this->animatedEntitySpec;

		if((AnimatedEntitySpec*)&CoinBackEntity == animatedEntitySpec)
		{
			animatedEntitySpec = (AnimatedEntitySpec*)&CoinBackSilhouetteEntity;
		}
		else
		{
			animatedEntitySpec = (AnimatedEntitySpec*)&CoinSilhouetteEntity;
		}

		AnimatedEntity::setSpec(this, animatedEntitySpec);
	}
}

// class's destructor
void Coin::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Coin::collect()
{
	// "collect" coin if it wasn't already
	int coinId = atoi(this->name);
	if(!ProgressManager::getCoinStatus(ProgressManager::getInstance(), coinId))
	{
		// set coin status to taken
		ProgressManager::setCoinStatus(ProgressManager::getInstance(), coinId, true);

		// fire "taken" event
		Object::fireEvent(EventManager::getInstance(), kEventCoinTaken);
	}
}
