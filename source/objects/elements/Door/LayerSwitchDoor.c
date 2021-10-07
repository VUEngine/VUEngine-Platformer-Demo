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
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include "LayerSwitchDoor.h"
#include <PlatformerLevelState.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void LayerSwitchDoor::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

// class's destructor
void LayerSwitchDoor::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's handle message
bool LayerSwitchDoor::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageHeroEnterDoor:

			if(this->destinationSpec)
			{
				// get global position of destination door
				LayerSwitchDoor destinationDoor = (LayerSwitchDoor)Container::getChildByName(Container::safeCast(Game::getStage(Game::getInstance())), (char *)this->destinationSpec->destinationName, true);
				Vector3D destinationDoorPosition = *Container::getGlobalPosition(destinationDoor);

				// apply offset
				destinationDoorPosition.x += __PIXELS_TO_METERS(this->destinationSpec->offset.x);
				destinationDoorPosition.y += __PIXELS_TO_METERS(this->destinationSpec->offset.y);
				destinationDoorPosition.z += __PIXELS_TO_METERS(this->destinationSpec->offset.z + this->destinationSpec->offset.zDisplacement);

				// set hero's position
				Hero::getOutOfDoor(Hero::getInstance(), &destinationDoorPosition);
				// TODO: switch hero's palette according to new layer

				return true;
			}
			break;
	}

	return Base::handleMessage(this, telegram);
}
