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
#include <Container.h>
#include <Stage.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <Screen.h>
#include <PhysicalWorld.h>
#include <Lava.h>
#include <CustomScreenEffectManager.h>
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
__CLASS_NEW_DEFINITION(LavaTrigger, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(LavaTrigger, inanimatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void LavaTrigger_constructor(LavaTrigger this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(InanimatedInGameEntity, inanimatedInGameEntityDefinition, id, internalId, name);
}

// class's destructor
void LavaTrigger_destructor(LavaTrigger this)
{
    // discard pending delayed messages
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kLavaTriggerEnd);

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// state's handle message
bool LavaTrigger_handleMessage(LavaTrigger this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
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
    MessageDispatcher_dispatchMessage(3000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kLavaTriggerEnd, NULL);

    // deactivate shape so I won't get triggered again
    Shape_setActive(this->shape, false);
}

void LavaTrigger_triggerEventEnd(LavaTrigger this)
{
    // TODO: stop rumble BGM
    // TODO: start rotating cogwheel

    // get lava entity from stage and start its movement
    Lava lava = (Lava)Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "Lava", true);
    Lava_startMoving(lava);

    // release player
    PlatformerLevelState platformerState = (PlatformerLevelState)Game_getCurrentState(Game_getInstance());
    PlatformerLevelState_setModeToPlaying(platformerState);

    // remove me from stage so I don't waste resources
	Container_deleteMyself(__SAFE_CAST(Container, this));
}
