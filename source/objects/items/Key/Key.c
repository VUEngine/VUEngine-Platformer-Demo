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
#include <PostProcessingRhombus.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Key::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

// class's destructor
void Key::destructor()
{
	// remove post processing effect
	Game::removePostProcessingEffect(Game::getInstance(), PostProcessingRhombus::rhombus, SpatialObject::safeCast(this));

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Key::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// add post processing effect to make key emit rhombuses
	Game::pushBackProcessingEffect(Game::getInstance(), PostProcessingRhombus::rhombus, SpatialObject::safeCast(this));
}

void Key::collect()
{
	// fire item taken event
	Object::fireEvent(EventManager::getInstance(), kEventKeyTaken);

	// call base
	Base::collect(this);
}

void Key::suspend()
{
	Base::suspend(this);

	// remove post processing effect
	Game::removePostProcessingEffect(Game::getInstance(), PostProcessingRhombus::rhombus, SpatialObject::safeCast(this));
}

void Key::resume()
{
	Base::resume(this);

	// add post processing effect to make key emit rhombuses
	Game::pushBackProcessingEffect(Game::getInstance(), PostProcessingRhombus::rhombus, SpatialObject::safeCast(this));
}
