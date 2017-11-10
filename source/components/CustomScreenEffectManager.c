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
//												INCLUDES
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
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CustomScreenEffectManager, ScreenEffectManager);
__CLASS_FRIEND_DEFINITION(Screen);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
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
//												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Screen _screen = NULL;

BrightnessRepeatROMDef* SCREEN_PULSATE_STEPS[] =
{
	&EDGE_FADE_OUT_BRIGHTNESS_REPEAT,
	&EDGE_FADE_OUT_WIDE_BRIGHTNESS_REPEAT,
	//&EDGE_FADE_OUT_VERY_WIDE_BRIGHTNESS_REPEAT,
	//&EDGE_FADE_OUT_WIDE_BRIGHTNESS_REPEAT,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
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

			__CALL_BASE_METHOD(ScreenEffectManager, stopEffect, this, effect);
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

	this->lastShakeOffset.x = __I_TO_FIX19_13(4);

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
