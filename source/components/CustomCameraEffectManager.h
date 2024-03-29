/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CUSTOM_CAMERA_EFFECT_MANAGER_H_
#define CUSTOM_CAMERA_EFFECT_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CameraEffectManager.h>
#include <Telegram.h>
#include <Entity.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

// delay between camera movements during shaking effect (in ms)
#define MINIMUM_SHAKE_DELAY				20
#define SHAKE_DELAY_DELTA				60
#define CAMERA_PULSATE_DELAY			270

enum CustomCameraFX
{
	kShake = kCameraLastFX,
	kScreenPulsate
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class CustomCameraEffectManager : CameraEffectManager
{
	/* temporary variable to hold the focus entity during shaking fx */
	Entity tempFocusEntity;
	/* last offset set by shake function */
	Vector3D lastShakeOffset;
	/* time left in current shaking fx (in ms) */
	int shakeTimeLeft;
	/* values to load on next pulsate fx step */
	uint8 pulsateNextStep;

	// declare a CustomCameraEffectManager
	static CustomCameraEffectManager getInstance();
	override void startEffect(int effect, va_list args);
	override void stopEffect(int effect);
	override bool handleMessage(Telegram telegram);
}


#endif
