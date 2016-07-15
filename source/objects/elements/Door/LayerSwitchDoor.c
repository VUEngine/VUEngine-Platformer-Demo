/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <objects.h>
#include "LayerSwitchDoor.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LayerSwitchDoor, Door);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(LayerSwitchDoor, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(LayerSwitchDoor, animatedInGameEntityDefinition, id, name);

// class's constructor
void LayerSwitchDoor_constructor(LayerSwitchDoor this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Door, animatedInGameEntityDefinition, id, name);
}

// class's destructor
void LayerSwitchDoor_destructor(LayerSwitchDoor this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// state's handle message
bool LayerSwitchDoor_handleMessage(LayerSwitchDoor this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
		case kHeroEnterDoor:

			if(this->destinationDefinition)
			{
			    // get global position of destination door
                LayerSwitchDoor destinationDoor = (LayerSwitchDoor)Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), (char *)this->destinationDefinition->destinationName, true);
                VBVec3D destinationDoorPosition = *Container_getGlobalPosition(__SAFE_CAST(Container, destinationDoor));

                // apply offset
                destinationDoorPosition.x += this->destinationDefinition->offset.x;
                destinationDoorPosition.y += this->destinationDefinition->offset.y;
                destinationDoorPosition.z += this->destinationDefinition->offset.z;

                // set hero's position
                Hero_setPosition(Hero_getInstance(), &destinationDoorPosition);

				return true;
			}
			break;
	}

	return Door_handleMessage(__SAFE_CAST(Door, this), telegram);
}
