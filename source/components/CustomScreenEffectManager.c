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

#include <CustomScreenEffectManager.h>
#include <Screen.h>
#include <MessageDispatcher.h>
#include <Actor.h>
#include <Game.h>
#include <PhysicalWorld.h>
#include <EventManager.h>
#include <Utilities.h>

#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

// define the CustomScreenEffectManager
__CLASS_DEFINITION(CustomScreenEffectManager, ScreenEffectManager);

__CLASS_FRIEND_DEFINITION(Screen);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void CustomScreenEffectManager_constructor(CustomScreenEffectManager this);
static void CustomScreenEffectManager_FXShakeStart(CustomScreenEffectManager this, u16 duration);
static void CustomScreenEffectManager_FXShakeStop(CustomScreenEffectManager this);
static void CustomScreenEffectManager_onScreenShake(CustomScreenEffectManager this);


//---------------------------------------------------------------------------------------------------------
// 												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Screen _screen = NULL;


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(CustomScreenEffectManager);

// class's constructor
static void __attribute__ ((noinline)) CustomScreenEffectManager_constructor(CustomScreenEffectManager this)
{
	ASSERT(this, "CustomScreenEffectManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE(ScreenEffectManager);

	this->tempFocusInGameEntity = NULL;

	this->lastShakeOffset.x = 0;
	this->lastShakeOffset.y = 0;
	this->lastShakeOffset.z = 0;

	this->shakeTimeLeft = 0;

	_screen = Screen_getInstance();

	NM_ASSERT(_screen, "CustomScreenEffectManager::constructor: null _screen");
}

// class's destructor
void CustomScreenEffectManager_destructor(CustomScreenEffectManager this)
{
	ASSERT(this, "CustomScreenEffectManager::destructor: null this");

	// destroy base
	__SINGLETON_DESTROY;
}

void CustomScreenEffectManager_startEffect(CustomScreenEffectManager this, int effect, va_list args)
{
	ASSERT(this, "CustomScreenEffectManager::startEffect: null this");

	switch(effect)
	{
		case kShake:

			CustomScreenEffectManager_FXShakeStart(this, va_arg(args, int));
			break;

		default:

			ScreenEffectManager_startEffect(__SAFE_CAST(ScreenEffectManager, this), effect, args);
			break;
	}
}

void CustomScreenEffectManager_stopEffect(CustomScreenEffectManager this, int effect)
{
	ASSERT(this, "CustomScreenEffectManager::stopEffect: null this");

	switch(effect)
	{
		case kShake:

			CustomScreenEffectManager_FXShakeStop(this);
			break;

		default:

			ScreenEffectManager_stopEffect(__SAFE_CAST(ScreenEffectManager, this), effect);
			break;
	}
}

bool CustomScreenEffectManager_handleMessage(CustomScreenEffectManager this, Telegram telegram)
{
	ASSERT(this, "CustomScreenEffectManager::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
	{
		case kShake:

			CustomScreenEffectManager_onScreenShake(this);
            break;
	}

	return false;
}

// start shaking the screen
static void CustomScreenEffectManager_FXShakeStart(CustomScreenEffectManager this, u16 duration)
{
	ASSERT(this, "CustomScreenEffectManager::FXShakeStart: null this");

	// don't follow the focus entity while shaking
	Screen _screen = Screen_getInstance();
    this->tempFocusInGameEntity = Screen_getFocusInGameEntity(_screen);
	NM_ASSERT(this->tempFocusInGameEntity, "Screen::FXShakeStart: null tempFocusInGameEntity");
	//Screen_unsetFocusInGameEntity(_screen);

    // set desired fx duration
    this->shakeTimeLeft = duration;

    this->lastShakeOffset.x = ITOFIX19_13(4);

    // discard pending screen shake messages from previously started shake fx
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kShake);

    // instantly send shake message to self to start fx
    MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kShake, NULL);
}

// stop shaking the _screen
void CustomScreenEffectManager_FXShakeStop(CustomScreenEffectManager this)
{
	ASSERT(this, "CustomScreenEffectManager::FXShakeStop: null this");

    this->shakeTimeLeft = 0;
}

// shake the _screen
static void CustomScreenEffectManager_onScreenShake(CustomScreenEffectManager this)
{
	ASSERT(this, "CustomScreenEffectManager::onScreenShake: null this");

    // stop if no shaking time left
    if(this->shakeTimeLeft == 0)
    {
        // if needed, undo last offset
        if(this->lastShakeOffset.x != 0 || this->lastShakeOffset.y != 0)
        {
            this->lastShakeOffset.x = 0;
        }

        Screen_setFocusInGameEntity(_screen, this->tempFocusInGameEntity);
        this->tempFocusInGameEntity = NULL;

        return;
    }

	long seed = Utilities_randomSeed();

    int nextShakeDelay = MINIMUM_SHAKE_DELAY + Utilities_random(seed, abs(SHAKE_DELAY_DELTA));

    // subtract time until next shake
    this->shakeTimeLeft = (this->shakeTimeLeft <= nextShakeDelay) ? 0 : this->shakeTimeLeft - nextShakeDelay;

    // new offset
    this->lastShakeOffset.x = -this->lastShakeOffset.x;

    // move screen a bit
    Screen_move(_screen, this->lastShakeOffset, false);

    // send message for next screen movement
	MessageDispatcher_dispatchMessage(nextShakeDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kShake, NULL);
}
