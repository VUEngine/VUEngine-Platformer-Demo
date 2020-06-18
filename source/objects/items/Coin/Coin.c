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

extern EntitySpec LEVEL_1_HOUSE_IM;
extern AnimatedEntityROMSpec COIN_BACK_AG;
extern AnimatedEntityROMSpec COIN_SILHOUETTE_AG;
extern AnimatedEntityROMSpec COIN_BACK_SILHOUETTE_AG;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Coin::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);

	// if coin has already been collected, show silhouette representation
	int coinId = atoi(this->name);
	if(ProgressManager::getCoinStatus(ProgressManager::getInstance(), coinId))
	{
		AnimatedEntitySpec* animatedEntitySpec = this->animatedEntitySpec;

		if((AnimatedEntitySpec*)&COIN_BACK_AG == animatedEntitySpec)
		{
			animatedEntitySpec = (AnimatedEntitySpec*)&COIN_BACK_SILHOUETTE_AG;
		}
		else
		{
			animatedEntitySpec = (AnimatedEntitySpec*)&COIN_SILHOUETTE_AG;
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
