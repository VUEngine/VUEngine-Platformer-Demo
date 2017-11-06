/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <CollisionManager.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include "HideLayer.h"
#include <PlatformerLevelState.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HideLayer, AnimatedEntity);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

bool HideLayer_checkStillOverlapping(HideLayer this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(HideLayer, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(HideLayer, animatedEntityDefinition, id, internalId, name);

// class's constructor
void HideLayer_constructor(HideLayer this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedEntity, animatedEntityDefinition, id, internalId, name);

	// init class variables
	this->currentlyOverlappingHero = false;
}

// class's destructor
void HideLayer_destructor(HideLayer this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// class's handle message
bool HideLayer_handleMessage(HideLayer this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kHeroCheckOverlapping:

			if(HideLayer_checkStillOverlapping(this))
			{
				// delayed check if still overlapping hero
				MessageDispatcher_dispatchMessage(HIDE_LAYER_OVERLAPPING_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckOverlapping, NULL);
			}

			return true;
			break;
	}

	return false;
}

void HideLayer_setOverlapping(HideLayer this)
{
	this->currentlyOverlappingHero = true;

	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "ToTransparent");
}

void HideLayer_onToTransparentAnimationComplete(HideLayer this)
{
	// delayed check if still overlapping hero
	MessageDispatcher_dispatchMessage(HIDE_LAYER_OVERLAPPING_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckOverlapping, NULL);
}

bool HideLayer_isOverlapping(HideLayer this)
{
	return this->currentlyOverlappingHero;
}

bool HideLayer_checkStillOverlapping(HideLayer this)
{
	// check if hero has recently overlapped door and is still doing so
	CollisionInformation collisionInformation = __VIRTUAL_CALL(Shape, overlaps, VirtualList_front(Entity_getShapes(__SAFE_CAST(Entity, Hero_getInstance()))), VirtualList_front(this->shapes));

	// check if hero has recently overlapped door and is still doing so
	if(this->currentlyOverlappingHero && !collisionInformation.shape)
	{
		this->currentlyOverlappingHero = false;

		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "ToShape");
	}

	return this->currentlyOverlappingHero;
}
