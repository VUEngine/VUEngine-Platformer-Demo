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

#include <CustomCameraEffectManager.h>
#include <PlatformerCameraMovementManager.h>
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
//												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Camera _camera = NULL;
extern BrightnessRepeatROMSpec EdgeFadeOutBrightnessRepeat;
extern BrightnessRepeatROMSpec EdgeFadeOutWideBrightnessRepeat;
extern BrightnessRepeatROMSpec EdgeFadeOutVeryWideBrightnessRepeat;

BrightnessRepeatROMSpec* SCREEN_PULSATE_STEPS[] =
{
	&EdgeFadeOutBrightnessRepeat,
	&EdgeFadeOutWideBrightnessRepeat,
	//&EdgeFadeOutVeryWideBrightnessRepeat,
	//&EdgeFadeOutWideBrightnessRepeat,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void CustomCameraEffectManager::constructor()
{
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
void CustomCameraEffectManager::destructor()
{
	// destroy base
	Base::destructor();
}

void CustomCameraEffectManager::startEffect(int effect, va_list args)
{
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

void CustomCameraEffectManager::stopEffect(int effect)
{
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

bool CustomCameraEffectManager::handleMessage(Telegram telegram)
{
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
void CustomCameraEffectManager::fxShakeStart(uint16 duration)
{
	// don't follow the focus entity while shaking
	//Camera _camera = Camera::getInstance();
	PlatformerCameraMovementManager::disable(PlatformerCameraMovementManager::getInstance());

	// set desired fx duration
	this->shakeTimeLeft = duration;

	this->lastShakeOffset.x = __PIXELS_TO_METERS(4);

	// discard pending messages from previously started fx
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kShake);

	// instantly send message to self to start fx
	MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(this), kShake, NULL);
}

// start screen pulsating effect
void CustomCameraEffectManager::fxScreenPulsateStart()
{
	// discard pending messages from previously started fx
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kScreenPulsate);

	this->pulsateNextStep = 0;

	// instantly send message to self to start fx
	MessageDispatcher::dispatchMessage(0, Object::safeCast(this), Object::safeCast(this), kScreenPulsate, NULL);
}

// stop shaking the _camera
void CustomCameraEffectManager::fxShakeStop()
{
	this->shakeTimeLeft = 0;
}

// stop shaking the _camera
void CustomCameraEffectManager::fxScreenPulsateStop()
{
	this->pulsateNextStep = 0;
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kScreenPulsate);
}

// shake the _camera
void CustomCameraEffectManager::onScreenShake()
{
	// stop if no shaking time left
	if(this->shakeTimeLeft == 0)
	{
		// if needed, undo last offset
		if(this->lastShakeOffset.x != 0 || this->lastShakeOffset.y != 0)
		{
			this->lastShakeOffset.x = 0;
		}

		PlatformerCameraMovementManager::enable(PlatformerCameraMovementManager::getInstance());
		return;
	}

	long seed = Utilities::randomSeed();

	int nextShakeDelay = MINIMUM_SHAKE_DELAY + Utilities::random(seed, __ABS(SHAKE_DELAY_DELTA));

	// subtract time until next shake
	this->shakeTimeLeft = (this->shakeTimeLeft <= nextShakeDelay) ? 0 : this->shakeTimeLeft - nextShakeDelay;

	// new offset
	this->lastShakeOffset.x = -this->lastShakeOffset.x;

	// move screen a bit
	Camera::translate(_camera, this->lastShakeOffset, false);

	// send message for next screen movement
	MessageDispatcher::dispatchMessage(nextShakeDelay, Object::safeCast(this), Object::safeCast(this), kShake, NULL);
}

// write new brightness repeat values
void CustomCameraEffectManager::onScreenPulsate()
{
	VIPManager::setupBrightnessRepeat(VIPManager::getInstance(), (BrightnessRepeatSpec*)SCREEN_PULSATE_STEPS[this->pulsateNextStep]);

	// send message for next fx step
	this->pulsateNextStep = (SCREEN_PULSATE_STEPS[this->pulsateNextStep + 1] != NULL)
		? this->pulsateNextStep + 1
		: 0;
	MessageDispatcher::dispatchMessage(CAMERA_PULSATE_DELAY, Object::safeCast(this), Object::safeCast(this), kScreenPulsate, NULL);
}
