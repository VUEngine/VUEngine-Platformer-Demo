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
#include <VUEngine.h>
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
void Key::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

// class's destructor
void Key::destructor()
{
	// remove post processing effect
	VUEngine::removePostProcessingEffect(VUEngine::getInstance(), PostProcessingRhombus::rhombus, SpatialObject::safeCast(this));

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Key::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// add post processing effect to make key emit rhombuses
	VUEngine::pushBackPostProcessingEffect(VUEngine::getInstance(), PostProcessingRhombus::rhombus, SpatialObject::safeCast(this));
}

void Key::collect()
{
	// fire item taken event
	ListenerObject::fireEvent(EventManager::getInstance(), kEventKeyTaken);

	// call base
	Base::collect(this);
}

void Key::suspend()
{
	Base::suspend(this);

	// remove post processing effect
	VUEngine::removePostProcessingEffect(VUEngine::getInstance(), PostProcessingRhombus::rhombus, SpatialObject::safeCast(this));
}

void Key::resume()
{
	Base::resume(this);

	// add post processing effect to make key emit rhombuses
	VUEngine::pushBackPostProcessingEffect(VUEngine::getInstance(), PostProcessingRhombus::rhombus, SpatialObject::safeCast(this));
}
