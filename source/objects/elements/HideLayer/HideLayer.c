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
#include <CollisionManager.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include "HideLayer.h"
#include <PlatformerLevelState.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HideLayer::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

// class's destructor
void HideLayer::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void HideLayer::setOverlapping()
{
	AnimatedEntity::playAnimation(this, "ToTransparent");
}

void HideLayer::unsetOverlapping()
{
	AnimatedEntity::playAnimation(this, "ToShape");
}

