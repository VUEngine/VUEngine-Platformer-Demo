/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef WATER_POND_H_
#define WATER_POND_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <ReflectiveEntity.h>
#include <ParticleSystem.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct WaterPondSpec
{
	ReflectiveEntitySpec reflectiveEntitySpec;

	// throttle increment
	fix10_6 waveLutThrottleFactorIncrement;

	// throttle increment duration
	uint32 waveLutThrottleFactorIncrementDuration;

	// throttle increment duration step
	uint32 waveLutThrottleFactorIncrementDurationStep;

	// surface height
	uint16 surfaceHeight;

	// wave amplitude factor
	fix10_6 amplitudeFactor;

} WaterPondSpec;

typedef const WaterPondSpec WaterPondROMSpec;

class WaterPond : ReflectiveEntity
{
	fix10_6 waveLutThrottleFactorIncrement;
	fix10_6 amplitudeFactor;
	ParticleSystem waterSplash;

	void constructor(WaterPondSpec* mirrorSpec, int16 internalId, const char* const name);
	override bool handleMessage(void* telegram);
	override void ready(bool recursive);
	override void applyReflection(uint32 currentDrawingFrameBufferSet);
}


#endif
