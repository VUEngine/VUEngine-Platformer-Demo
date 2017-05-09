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

#include "WaterPond.h"
#include <Game.h>
#include <Optics.h>
#include <Screen.h>
#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS' MACROS
//---------------------------------------------------------------------------------------------------------

#define POINTER_TYPE		u32
#define Y_SHIFT					4
// sizeof(POINTER_TYPE) << 2
#define Y_STEP_SIZE				16
#define Y_STEP_SIZE_2_EXP		4
// sizeof(POINTER_TYPE) << 3
#define BITS_PER_STEP 			32

#define MODULO(n, m)		(n & (m - 1))



//---------------------------------------------------------------------------------------------------------
//											CLASS' DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(WaterPond, ReflectiveEntity);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(WaterPond, WaterPondDefinition* mirrorDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(WaterPond, mirrorDefinition, id, internalId, name);

// class's constructor
void WaterPond_constructor(WaterPond this, WaterPondDefinition* mirrorDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "WaterPond::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(ReflectiveEntity, &mirrorDefinition->reflectiveEntityDefinition, id, internalId, name);

	this->waveLutThrottleFactorIncrement = 0;
}

// class's destructor
void WaterPond_destructor(WaterPond this)
{
	ASSERT(this, "WaterPond::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void WaterPond_ready(WaterPond this, bool recursive)
{
	ASSERT(this, "WaterPond::ready: null this");

	// call base

	__CALL_BASE_METHOD(ReflectiveEntity, ready, this, recursive);

//	Shape_setCheckForCollisions(this->shape, true);
//	Shape_setActive(this->shape, false);
}


bool WaterPond_handleMessage(WaterPond this, void* telegram)
{
	ASSERT(this, "WaterPond::handleMessage: null this");

	ReflectiveEntityDefinition* mirrorDefinition = (ReflectiveEntityDefinition*)this->entityDefinition;

	// handle messages that any state would handle here
	switch(Telegram_getMessage(telegram))
	{
//		case kReactToCollision:
		case kCollision:

			if(!this->waveLutThrottleFactorIncrement)
			{
				this->waveLutThrottleFactorIncrement = ((WaterPondDefinition*)this->entityDefinition)->waveLutThrottleFactorIncrement;
				this->waveLutIndexIncrement = FIX19_13_MULT(this->waveLutThrottleFactorIncrement + mirrorDefinition->waveLutThrottleFactor, FIX19_13_DIV(ITOFIX19_13(mirrorDefinition->numberOfWaveLutEntries), ITOFIX19_13(mirrorDefinition->width)));
				MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kStopReactToCollision);
				MessageDispatcher_dispatchMessage(((WaterPondDefinition*)this->entityDefinition)->waveLutThrottleFactorIncrementDuration, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kStopReactToCollision, NULL);
				Shape_setActive(this->shape, false);
			}
			return true;
			break;

		case kStopReactToCollision:

			this->waveLutThrottleFactorIncrement = 0;
			this->waveLutIndexIncrement = FIX19_13_MULT(mirrorDefinition->waveLutThrottleFactor, FIX19_13_DIV(ITOFIX19_13(mirrorDefinition->numberOfWaveLutEntries), ITOFIX19_13(mirrorDefinition->width)));
			Shape_setActive(this->shape, true);
			return true;
			break;

	}

	return false;
}

