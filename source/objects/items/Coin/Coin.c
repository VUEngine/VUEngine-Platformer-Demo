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

extern EntityDefinition LEVEL_1_HOUSE_IM;
extern AnimatedEntityROMDef COIN_BACK_AG;
extern AnimatedEntityROMDef COIN_SILHOUETTE_AG;
extern AnimatedEntityROMDef COIN_BACK_SILHOUETTE_AG;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Coin::constructor(Coin this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntityDefinition, id, internalId, name);

	// if coin has already been collected, show silhouette representation
	if(ProgressManager::getCoinStatus(ProgressManager::getInstance(), this->id))
	{
		AnimatedEntityDefinition* animatedEntityDefinition = this->animatedEntityDefinition;

		if((AnimatedEntityDefinition*)&COIN_BACK_AG == animatedEntityDefinition)
		{
			animatedEntityDefinition = (AnimatedEntityDefinition*)&COIN_BACK_SILHOUETTE_AG;
		}
		else
		{
			animatedEntityDefinition = (AnimatedEntityDefinition*)&COIN_SILHOUETTE_AG;
		}

		AnimatedEntity::setDefinition(__SAFE_CAST(AnimatedEntity, this), animatedEntityDefinition);
	}
}

// class's destructor
void Coin::destructor(Coin this)
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Coin::collect(Coin this)
{
	ASSERT(this, "Collectable::collect: null this");

	// "collect" coin if it wasn't already
	if(!ProgressManager::getCoinStatus(ProgressManager::getInstance(), this->id))
	{
		// set coin status to taken
		ProgressManager::setCoinStatus(ProgressManager::getInstance(), this->id, true);

		// fire "taken" event
		Object::fireEvent(__SAFE_CAST(Object, EventManager::getInstance()), kEventCoinTaken);
	}
}
