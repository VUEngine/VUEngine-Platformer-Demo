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

#include <CustomCameraEffectManager.h>
#include <CustomCameraMovementManager.h>
#include <Camera.h>
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

friend class Camera;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void CustomCameraEffectManager::constructor(CustomCameraEffectManager this);
void CustomCameraEffectManager::fxShakeStart(CustomCameraEffectManager this, u16 duration);
void CustomCameraEffectManager::fxScreenPulsateStart(CustomCameraEffectManager this);
void CustomCameraEffectManager::fxShakeStop(CustomCameraEffectManager this);
void CustomCameraEffectManager::fxScreenPulsateStop(CustomCameraEffectManager this);
void CustomCameraEffectManager::onScreenShake(CustomCameraEffectManager this);
void CustomCameraEffectManager::onScreenPulsate(CustomCameraEffectManager this);

extern BrightnessRepeatROMDef EDGE_FADE_OUT_BRIGHTNESS_REPEAT;
extern BrightnessRepeatROMDef EDGE_FADE_OUT_WIDE_BRIGHTNESS_REPEAT;
extern BrightnessRepeatROMDef EDGE_FADE_OUT_VERY_WIDE_BRIGHTNESS_REPEAT;


//---------------------------------------------------------------------------------------------------------
//												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Camera _camera = NULL;

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

// class's constructor
void __attribute__ ((noinline)) CustomCameraEffectManager::constructor(CustomCameraEffectManager this)
{
	ASSERT(this, "CustomCameraEffectManager::constructor: null this");

	// construct base object
	Base::constructor();

	this->lastShakeOffset.x = 0;
	this->lastShakeOffset.y = 0;
	this->lastShakeOffset.z = 0;

	this->shakeTimeLeft = 0;

	this->pulsateNextStep = 0;

	_camera = Camera::getInstance();

	NM_ASSERT(_camera, "CustomCameraEffectManager::constructor: null _camera");
}

// class's destructor
void CustomCameraEffectManager::destructor(CustomCameraEffectManager this)
{
	ASSERT(this, "CustomCameraEffectManager::destructor: null this");

	// destroy base
	__SINGLETON_DESTROY;
}

void CustomCameraEffectManager::startEffect(CustomCameraEffectManager this, int effect, va_list args)
{
	ASSERT(this, "CustomCameraEffectManager::startEffect: null this");

	switch(effect)
	{
		case kShake:

			CustomCameraEffectManager::fxShakeStart(this, va_arg(args, int));
			break;

		case kScreenPulsate:

			CustomCameraEffectManager::fxScreenPulsateStart(this);
			break;

		default:

			Base::startEffect(CameraEffectManager::getInstance(), effect, args);
			break;
	}
}

void CustomCameraEffectManager::stopEffect(CustomCameraEffectManager this, int effect)
{
	ASSERT(this, "CustomCameraEffectManager::stopEffect: null this");

	switch(effect)
	{
		case kShake:

			CustomCameraEffectManager::fxShakeStop(this);
			break;

		case kScreenPulsate:

			CustomCameraEffectManager::fxScreenPulsateStop(this);
			break;

		default:

			Base::stopEffect(this, effect);
			break;
	}
}

bool CustomCameraEffectManager::handleMessage(CustomCameraEffectManager this, Telegram telegram)
{
	ASSERT(this, "CustomCameraEffectManager::handleMessage: null this");

	switch(Telegram::getMessage(telegram))
	{
		case kShake:

			CustomCameraEffectManager::onScreenShake(this);
			break;

		case kScreenPulsate:

			CustomCameraEffectManager::onScreenPulsate(this);
			break;
	}

	return false;
}

// start shaking the screen
void CustomCameraEffectManager::fxShakeStart(CustomCameraEffectManager this, u16 duration)
{
	ASSERT(this, "CustomCameraEffectManager::fxShakeStart: null this");

	// don't follow the focus entity while shaking
	//Camera _camera = Camera::getInstance();
	CustomCameraMovementManager::disable(CustomCameraMovementManager::getInstance());

	// set desired fx duration
	this->shakeTimeLeft = duration;

	this->lastShakeOffset.x = __PIXELS_TO_METERS(4);

	// discard pending messages from previously started fx
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kShake);

	// instantly send message to self to start fx
	MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kShake, NULL);
}

// start screen pulsating effect
void CustomCameraEffectManager::fxScreenPulsateStart(CustomCameraEffectManager this)
{
	ASSERT(this, "CustomCameraEffectManager::fxScreenPulsateStart: null this");

	// discard pending messages from previously started fx
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kScreenPulsate);

	this->pulsateNextStep = 0;

	// instantly send message to self to start fx
	MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kScreenPulsate, NULL);
}

// stop shaking the _camera
void CustomCameraEffectManager::fxShakeStop(CustomCameraEffectManager this)
{
	ASSERT(this, "CustomCameraEffectManager::fxShakeStop: null this");

	this->shakeTimeLeft = 0;
}

// stop shaking the _camera
void CustomCameraEffectManager::fxScreenPulsateStop(CustomCameraEffectManager this)
{
	ASSERT(this, "CustomCameraEffectManager::fxScreenPulsateStop: null this");

	this->pulsateNextStep = 0;
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kScreenPulsate);
}

// shake the _camera
void CustomCameraEffectManager::onScreenShake(CustomCameraEffectManager this)
{
	ASSERT(this, "CustomCameraEffectManager::onScreenShake: null this");

	// stop if no shaking time left
	if(this->shakeTimeLeft == 0)
	{
		// if needed, undo last offset
		if(this->lastShakeOffset.x != 0 || this->lastShakeOffset.y != 0)
		{
			this->lastShakeOffset.x = 0;
		}

		CustomCameraMovementManager::enable(CustomCameraMovementManager::getInstance());
		return;
	}

	long seed = Utilities::randomSeed();

	int nextShakeDelay = MINIMUM_SHAKE_DELAY + Utilities::random(seed, __ABS(SHAKE_DELAY_DELTA));

	// subtract time until next shake
	this->shakeTimeLeft = (this->shakeTimeLeft <= nextShakeDelay) ? 0 : this->shakeTimeLeft - nextShakeDelay;

	// new offset
	this->lastShakeOffset.x = -this->lastShakeOffset.x;

	// move screen a bit
	Camera::move(_camera, this->lastShakeOffset, false);

	// send message for next screen movement
	MessageDispatcher::dispatchMessage(nextShakeDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kShake, NULL);
}

// write new brightness repeat values
void CustomCameraEffectManager::onScreenPulsate(CustomCameraEffectManager this)
{
	ASSERT(this, "CustomCameraEffectManager::onScreenPulsate: null this");

	VIPManager::setupBrightnessRepeat(VIPManager::getInstance(), (BrightnessRepeatDefinition*)SCREEN_PULSATE_STEPS[this->pulsateNextStep]);

	// send message for next fx step
	this->pulsateNextStep = (SCREEN_PULSATE_STEPS[this->pulsateNextStep + 1] != NULL)
		? this->pulsateNextStep + 1
		: 0;
	MessageDispatcher::dispatchMessage(CAMERA_PULSATE_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kScreenPulsate, NULL);
}
