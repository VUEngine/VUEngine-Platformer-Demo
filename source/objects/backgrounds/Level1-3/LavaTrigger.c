/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <Container.h>
#include <Stage.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <Screen.h>
#include <PhysicalWorld.h>
#include <Lava.h>
#include <CustomScreenMovementManager.h>

#include <objects.h>
#include "LavaTrigger.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LavaTrigger, InanimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void LavaTrigger_triggerEventStart(LavaTrigger this);
void LavaTrigger_triggerEventEnd(LavaTrigger this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(LavaTrigger, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(LavaTrigger, inanimatedInGameEntityDefinition, id, name);

// class's constructor
void LavaTrigger_constructor(LavaTrigger this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(inanimatedInGameEntityDefinition, id, name);
}

// class's destructor
void LavaTrigger_destructor(LavaTrigger this)
{
	// delete the super object
	__DESTROY_BASE;
}

// state's on message
bool LavaTrigger_handleMessage(LavaTrigger this, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
    {
		case kLavaTriggerStart:

            LavaTrigger_triggerEventStart(this);
			break;

		case kLavaTriggerEnd:

            LavaTrigger_triggerEventEnd(this);
			break;
	}
	
	return false;
}

void LavaTrigger_triggerEventStart(LavaTrigger this)
{
    // set level mode to paused so that player can't move
    PlatformerLevelState platformerState = (PlatformerLevelState)Game_getCurrentState(Game_getInstance());
    PlatformerLevelState_setModeToPaused(platformerState);

    // initialize a dramatic screen shake effect
    Screen_startEffect(Screen_getInstance(), kShake, 3000);

    // TODO: play rumble BGM

    // remind myself to stop the trigger event soon
    MessageDispatcher_dispatchMessage(3000, __GET_CAST(Object, this), __GET_CAST(Object, this), kLavaTriggerEnd, NULL);

    // deactivate shape so I won't get triggered again
    Shape_setActive(this->shape, false);
}

void LavaTrigger_triggerEventEnd(LavaTrigger this)
{
    // TODO: stop rumble BGM
    // TODO: start rotating cogwheel

    // get lava entity from stage and start its movement
    Lava lava = (Lava)Container_getChildByName(__GET_CAST(Container, Game_getStage(Game_getInstance())), "Lava", true);
    Lava_startMoving(lava);

    // release player
    PlatformerLevelState platformerState = (PlatformerLevelState)Game_getCurrentState(Game_getInstance());
    PlatformerLevelState_setModeToPlaying(platformerState);
    
    // remove me from stage so I don't waste resources
	Container_deleteMyself(__GET_CAST(Container, this));
}