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
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <Camera.h>
#include <EventManager.h>
#include <GoalDoor.h>
#include <PlatformerLevelState.h>
#include <LevelDoneScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void GoalDoor::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, id, internalId, name);
}

// class's destructor
void GoalDoor::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// ready
void GoalDoor::ready(bool recursive __attribute__ ((unused)))
{
	// call base
	Base::ready(this, recursive);

	AnimatedEntity::playAnimation(this, "Goal");
}

bool GoalDoor::hasDestination()
{
	return true;
}

// state's handle message
bool GoalDoor::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kHeroEnterDoor:
		{
			// disable user input
			Game::disableKeypad(Game::getInstance());

			// fade out screen
			Brightness brightness = (Brightness){0, 0, 0};
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				&brightness, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))GoalDoor::onFadeOutComplete, // callback function
				Object::safeCast(this) // callback scope
			);

			return true;
			break;
		}
	}

	return Base::handleMessage(this, telegram);
}

bool GoalDoor::canEnter()
{
	return true;
}

// handle event
void GoalDoor::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// announce level completion
	Object::fireEvent(EventManager::getInstance(), kEventLevelCompleted);

	// switch to next screen
	Game::changeState(Game::getInstance(), GameState::safeCast(LevelDoneScreenState::getInstance()));
}
