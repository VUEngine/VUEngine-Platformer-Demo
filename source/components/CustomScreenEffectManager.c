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
#include <CustomScreenMovementManager.h>
#include <Screen.h>
#include <MessageDispatcher.h>
#include <Actor.h>
#include <Game.h>
#include <PhysicalWorld.h>
#include <EventManager.h>
#include <Utilities.h>
#include <VIPManager.h>

#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CustomScreenEffectManager, ScreenEffectManager);
__CLASS_FRIEND_DEFINITION(Screen);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void CustomScreenEffectManager_constructor(CustomScreenEffectManager this);
static void CustomScreenEffectManager_FXShakeStart(CustomScreenEffectManager this, u16 duration);
static void CustomScreenEffectManager_FXScreenPulsateStart(CustomScreenEffectManager this);
void CustomScreenEffectManager_FXShakeStop(CustomScreenEffectManager this);
void CustomScreenEffectManager_FXScreenPulsateStop(CustomScreenEffectManager this);
static void CustomScreenEffectManager_onScreenShake(CustomScreenEffectManager this);
static void CustomScreenEffectManager_onScreenPulsate(CustomScreenEffectManager this);

extern BrightnessRepeatROMDef EDGE_FADE_OUT_BRIGHTNESS_REPEAT;
extern BrightnessRepeatROMDef EDGE_FADE_OUT_WIDE_BRIGHTNESS_REPEAT;
extern BrightnessRepeatROMDef EDGE_FADE_OUT_VERY_WIDE_BRIGHTNESS_REPEAT;


//---------------------------------------------------------------------------------------------------------
// 												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Screen _screen = NULL;

BrightnessRepeatROMDef* SCREEN_PULSATE_STEPS[] =
{
    &EDGE_FADE_OUT_BRIGHTNESS_REPEAT,
    &EDGE_FADE_OUT_WIDE_BRIGHTNESS_REPEAT,
    &EDGE_FADE_OUT_VERY_WIDE_BRIGHTNESS_REPEAT,
    &EDGE_FADE_OUT_WIDE_BRIGHTNESS_REPEAT,
    NULL
};


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

	this->lastShakeOffset.x = 0;
	this->lastShakeOffset.y = 0;
	this->lastShakeOffset.z = 0;

	this->shakeTimeLeft = 0;

	this->pulsateNextStep = 0;

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

		case kScreenPulsate:

			CustomScreenEffectManager_FXScreenPulsateStart(this);
			break;

		default:

			ScreenEffectManager_startEffect(ScreenEffectManager_getInstance(), effect, args);
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

		case kScreenPulsate:

			CustomScreenEffectManager_FXScreenPulsateStop(this);
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

		case kScreenPulsate:

			CustomScreenEffectManager_onScreenPulsate(this);
            break;
	}

	return false;
}

// start shaking the screen
static void CustomScreenEffectManager_FXShakeStart(CustomScreenEffectManager this, u16 duration)
{
	ASSERT(this, "CustomScreenEffectManager::FXShakeStart: null this");

	// don't follow the focus entity while shaking
	//Screen _screen = Screen_getInstance();
    CustomScreenMovementManager_disable(CustomScreenMovementManager_getInstance());

    // set desired fx duration
    this->shakeTimeLeft = duration;

    this->lastShakeOffset.x = ITOFIX19_13(4);

    // discard pending messages from previously started fx
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kShake);

    // instantly send message to self to start fx
    MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kShake, NULL);
}

// start screen pulsating effect
static void CustomScreenEffectManager_FXScreenPulsateStart(CustomScreenEffectManager this)
{
	ASSERT(this, "CustomScreenEffectManager::FXScreenPulsateStart: null this");

    // discard pending messages from previously started fx
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kScreenPulsate);

    this->pulsateNextStep = 0;

    // instantly send message to self to start fx
    MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kScreenPulsate, NULL);
}

// stop shaking the _screen
void CustomScreenEffectManager_FXShakeStop(CustomScreenEffectManager this)
{
	ASSERT(this, "CustomScreenEffectManager::FXShakeStop: null this");

    this->shakeTimeLeft = 0;
}

// stop shaking the _screen
void CustomScreenEffectManager_FXScreenPulsateStop(CustomScreenEffectManager this)
{
	ASSERT(this, "CustomScreenEffectManager::FXScreenPulsateStop: null this");

    this->pulsateNextStep = 0;
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kScreenPulsate);
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

        CustomScreenMovementManager_enable(CustomScreenMovementManager_getInstance());
        return;
    }

	long seed = Utilities_randomSeed();

    int nextShakeDelay = MINIMUM_SHAKE_DELAY + Utilities_random(seed, __ABS(SHAKE_DELAY_DELTA));

    // subtract time until next shake
    this->shakeTimeLeft = (this->shakeTimeLeft <= nextShakeDelay) ? 0 : this->shakeTimeLeft - nextShakeDelay;

    // new offset
    this->lastShakeOffset.x = -this->lastShakeOffset.x;

    // move screen a bit
    Screen_move(_screen, this->lastShakeOffset, false);

    // send message for next screen movement
	MessageDispatcher_dispatchMessage(nextShakeDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kShake, NULL);
}

// write new brightness repeat values
static void CustomScreenEffectManager_onScreenPulsate(CustomScreenEffectManager this)
{
	ASSERT(this, "CustomScreenEffectManager::onScreenPulsate: null this");

    VIPManager_setupBrightnessRepeat(VIPManager_getInstance(), (BrightnessRepeatDefinition*)SCREEN_PULSATE_STEPS[this->pulsateNextStep]);

    // send message for next fx step
    this->pulsateNextStep = (SCREEN_PULSATE_STEPS[this->pulsateNextStep + 1] != NULL)
        ? this->pulsateNextStep + 1
        : 0;
	MessageDispatcher_dispatchMessage(SCREEN_PULSATE_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kScreenPulsate, NULL);
}
