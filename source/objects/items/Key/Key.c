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
#include <CollisionManager.h>
#include <SoundManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <EventManager.h>
#include "Key.h"
#include <PlatformerLevelState.h>
#include <PostProcessingEffects.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Key, Item);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Key, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Key, animatedEntityDefinition, id, internalId, name);

// class's constructor
void Key_constructor(Key this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Key::constructor: null this");

	// construct base
	Base_constructor(this, animatedEntityDefinition, id, internalId, name);
}

// class's destructor
void Key_destructor(Key this)
{
	ASSERT(this, "Key::destructor: null this");

	// remove post processing effect
	Game_removePostProcessingEffect(Game_getInstance(), PostProcessingEffects_rhombusEmitter, __SAFE_CAST(SpatialObject, this));

	// delete the super object
	// must always be called at the end of the destructor
	Base_destructor();
}

void Key_ready(Key this, bool recursive)
{
	ASSERT(this, "Key::ready: null this");

	// call base
	Base_ready(this, recursive);

	// add post processing effect to make key emit rhombuses
	Game_pushBackProcessingEffect(Game_getInstance(), PostProcessingEffects_rhombusEmitter, __SAFE_CAST(SpatialObject, this));
}

void Key_collect(Key this)
{
	ASSERT(this, "Key::collect: null this");

	// fire item taken event
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventKeyTaken);

	// call base
	__CALL_BASE_METHOD(Item, collect, this);
}

void Key_suspend(Key this)
{
	ASSERT(this, "Key::suspend: null this");

	__CALL_BASE_METHOD(Item, suspend, this);

	// remove post processing effect
	Game_removePostProcessingEffect(Game_getInstance(), PostProcessingEffects_rhombusEmitter, __SAFE_CAST(SpatialObject, this));
}

void Key_resume(Key this)
{
	ASSERT(this, "Key::resume: null this");

	__CALL_BASE_METHOD(Item, resume, this);

	// add post processing effect to make key emit rhombuses
	Game_pushBackProcessingEffect(Game_getInstance(), PostProcessingEffects_rhombusEmitter, __SAFE_CAST(SpatialObject, this));
}
