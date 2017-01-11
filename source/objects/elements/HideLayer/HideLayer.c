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
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CollisionManager.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include <objects.h>
#include "HideLayer.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HideLayer, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

bool HideLayer_checkStillOverlapping(HideLayer this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(HideLayer, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(HideLayer, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void HideLayer_constructor(HideLayer this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, internalId, name);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);

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

    AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "ToTransparent");
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
	if(
		this->currentlyOverlappingHero &&
		!__VIRTUAL_CALL(Shape, overlaps, Entity_getShape(__SAFE_CAST(Entity, Hero_getInstance())), Entity_getShape(__SAFE_CAST(Entity, this)))
	)
	{
		this->currentlyOverlappingHero = false;

        AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "ToSolid");
	}

	return this->currentlyOverlappingHero;
}
