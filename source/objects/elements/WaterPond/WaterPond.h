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

#define WaterPond_METHODS(ClassName)																	\
		ReflectiveEntity_METHODS(ClassName)																\

#define WaterPond_SET_VTABLE(ClassName)																	\
		ReflectiveEntity_SET_VTABLE(ClassName)															\
		__VIRTUAL_SET(ClassName, WaterPond, handleMessage);												\
		__VIRTUAL_SET(ClassName, WaterPond, ready);														\
		__VIRTUAL_SET(ClassName, WaterPond, applyReflection);											\

__CLASS(WaterPond);

#define WaterPond_ATTRIBUTES																			\
		/* it is derived from */																		\
		ReflectiveEntity_ATTRIBUTES																		\
		fix19_13 waveLutThrottleFactorIncrement;														\
		fix19_13 amplitudeFactor;																		\
		ParticleSystem waterSplash;

typedef struct WaterPondDefinition
{
	ReflectiveEntityDefinition reflectiveEntityDefinition;

	// throttle increment
	fix19_13 waveLutThrottleFactorIncrement;

	// throttle increment duration
	u32 waveLutThrottleFactorIncrementDuration;

	// throttle increment duration step
	u32 waveLutThrottleFactorIncrementDurationStep;

	// surface height
	u16 surfaceHeight;

	// wave amplitude factor
	fix19_13 amplitudeFactor;

} WaterPondDefinition;

typedef const WaterPondDefinition WaterPondROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(WaterPond, WaterPondDefinition* mirrorDefinition, s16 id, s16 internalId, const char* const name);

void WaterPond_constructor(WaterPond this, WaterPondDefinition* mirrorDefinition, s16 id, s16 internalId, const char* const name);
void WaterPond_destructor(WaterPond this);
bool WaterPond_handleMessage(WaterPond this, void* telegram);
void WaterPond_ready(WaterPond this, bool recursive);
void WaterPond_applyReflection(WaterPond this, u32 currentDrawingFrameBufferSet);


#endif
