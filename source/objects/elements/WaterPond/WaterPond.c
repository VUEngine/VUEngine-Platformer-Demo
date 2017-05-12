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
#include <Utilities.h>
#include <CollisionManager.h>
#include <debugConfig.h>


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

void WaterPond_drawReflection(WaterPond this, u32 currentDrawingFrameBufferSet,
								s16 xSourceStart, s16 ySourceStart,
								s16 xOutputStart, s16 yOutputStart,
								s16 width, s16 height,
								u32 reflectionMask,
								s16 parallaxDisplacement,
								const u8 waveLut[], int numberOfWaveLutEntries, fix19_13 waveLutThrottleFactor,
								fix19_13 amplitudeFactor,
								bool flattenTop __attribute__ ((unused)), bool flattenBottom,
								u32 topBorderMask __attribute__ ((unused)), u32 bottomBorderMask __attribute__ ((unused)),
								u16 surfaceHeight);

//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(WaterPond, WaterPondDefinition* reflectiveEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(WaterPond, reflectiveEntityDefinition, id, internalId, name);

// class's constructor
void WaterPond_constructor(WaterPond this, WaterPondDefinition* reflectiveEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "WaterPond::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(ReflectiveEntity, &reflectiveEntityDefinition->reflectiveEntityDefinition, id, internalId, name);

	this->waveLutThrottleFactorIncrement = 0;
	this->amplitudeFactor = ITOFIX19_13(1);
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

/*	Shape_setCheckForCollisions(this->shape, true);
	Shape_setMovesFlag(this->shape, true);
	CollisionManager_shapeStartedMoving(Game_getCollisionManager(Game_getInstance()), this->shape);
	*/
}

void WaterPond_transform(WaterPond this, const Transformation* environmentTransform)
{
	ASSERT(this, "WaterPond::transform: null this");

	__CALL_BASE_METHOD(ReflectiveEntity, transform, this, environmentTransform);

//	Shape_setChecked(this->shape, false);
}

bool WaterPond_handleMessage(WaterPond this, void* telegram)
{
	ASSERT(this, "WaterPond::handleMessage: null this");

	ReflectiveEntityDefinition* reflectiveEntityDefinition = (ReflectiveEntityDefinition*)this->entityDefinition;
	WaterPondDefinition* waterPondDefinition = (WaterPondDefinition*)this->entityDefinition;

//	bool entityTypeChecked = true;

	// handle messages that any state would handle here
	switch(Telegram_getMessage(telegram))
	{
	/*
		case kCollision:
		{
			entityTypeChecked = false;

			VirtualList collidingObjects = __SAFE_CAST(VirtualList, Telegram_getExtraInfo(telegram));

			VirtualNode node = NULL;

			for(node = VirtualList_begin(collidingObjects); node; node = VirtualNode_getNext(node))
			{
				InGameEntity inGameEntity = __SAFE_CAST(InGameEntity, VirtualNode_getData(node));

				switch(InGameEntity_getInGameType(inGameEntity))
				{
					case kHero:
					case kSawBlade:

						entityTypeChecked = __VIRTUAL_CALL(InGameEntity, isMoving, inGameEntity);
						break;
				}

				if(entityTypeChecked)
				{
					break;
				}
			}
		}
	*/
		case kReactToCollision:

//			if(entityTypeChecked &&
			if(
				(this->waveLutThrottleFactorIncrement < waterPondDefinition->waveLutThrottleFactorIncrement
				||
				this->amplitudeFactor < waterPondDefinition->amplitudeFactor)
			)
			{
/*				if(this->waveLutThrottleFactorIncrement)
				{
					this->amplitudeFactor += FIX19_13_DIV(waterPondDefinition->amplitudeFactor - ITOFIX19_13(1), ITOFIX19_13(waterPondDefinition->waveLutThrottleFactorIncrementDurationStep));
					this->waveLutThrottleFactorIncrement += FIX19_13_DIV(waterPondDefinition->waveLutThrottleFactorIncrement, ITOFIX19_13(waterPondDefinition->waveLutThrottleFactorIncrementDurationStep));
				}
				else
*/				{
					this->amplitudeFactor = waterPondDefinition->amplitudeFactor;
					this->waveLutThrottleFactorIncrement = waterPondDefinition->waveLutThrottleFactorIncrement;
				}

				this->waveLutIndexIncrement = FIX19_13_MULT(this->waveLutThrottleFactorIncrement + reflectiveEntityDefinition->waveLutThrottleFactor, FIX19_13_DIV(ITOFIX19_13(reflectiveEntityDefinition->numberOfWaveLutEntries), ITOFIX19_13(reflectiveEntityDefinition->width)));
				MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kStopReactToCollision);
				MessageDispatcher_dispatchMessage(waterPondDefinition->waveLutThrottleFactorIncrementDuration / waterPondDefinition->waveLutThrottleFactorIncrementDurationStep, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kStopReactToCollision, NULL);
			}

			break;

		case kStopReactToCollision:

			this->amplitudeFactor -= FIX19_13_DIV(waterPondDefinition->amplitudeFactor - ITOFIX19_13(1), ITOFIX19_13(waterPondDefinition->waveLutThrottleFactorIncrementDurationStep));
			this->waveLutThrottleFactorIncrement -= FIX19_13_DIV(waterPondDefinition->waveLutThrottleFactorIncrement, ITOFIX19_13(waterPondDefinition->waveLutThrottleFactorIncrementDurationStep));

			if(0 < this->waveLutThrottleFactorIncrement)
			{
				MessageDispatcher_dispatchMessage(waterPondDefinition->waveLutThrottleFactorIncrementDuration / waterPondDefinition->waveLutThrottleFactorIncrementDurationStep, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kStopReactToCollision, NULL);
			}
			else
			{
				this->amplitudeFactor = ITOFIX19_13(1);
				this->waveLutThrottleFactorIncrement = 0;
			}

			this->waveLutIndexIncrement = FIX19_13_MULT(this->waveLutThrottleFactorIncrement + reflectiveEntityDefinition->waveLutThrottleFactor, FIX19_13_DIV(ITOFIX19_13(reflectiveEntityDefinition->numberOfWaveLutEntries), ITOFIX19_13(reflectiveEntityDefinition->width)));
			return true;
			break;

	}

	return false;
}

void WaterPond_applyReflection(WaterPond this, u32 currentDrawingFrameBufferSet)
{
	ASSERT(this, "WaterPond::applyReflection: null this");

	ReflectiveEntityDefinition* reflectiveEntityDefinition = (ReflectiveEntityDefinition*)this->entityDefinition;
	WaterPondDefinition* waterPondDefinition = (WaterPondDefinition*)this->entityDefinition;

	WaterPond_drawReflection(this, currentDrawingFrameBufferSet,
								this->position2D.x + reflectiveEntityDefinition->sourceDisplacement.x,
								this->position2D.y + reflectiveEntityDefinition->sourceDisplacement.y,
								this->position2D.x + reflectiveEntityDefinition->outputDisplacement.x,
								this->position2D.y + reflectiveEntityDefinition->outputDisplacement.y,
								reflectiveEntityDefinition->width,
								reflectiveEntityDefinition->height,
								reflectiveEntityDefinition->reflectionMask,
								reflectiveEntityDefinition->parallaxDisplacement,
								reflectiveEntityDefinition->waveLut,
								reflectiveEntityDefinition->numberOfWaveLutEntries,
								reflectiveEntityDefinition->waveLutThrottleFactor + this->waveLutThrottleFactorIncrement,
								this->amplitudeFactor,
								reflectiveEntityDefinition->flattenTop, reflectiveEntityDefinition->flattenBottom,
								reflectiveEntityDefinition->topBorder, reflectiveEntityDefinition->bottomBorder,
								waterPondDefinition->surfaceHeight);
}

inline void WaterPond_shiftPixels(int pixelShift, POINTER_TYPE* sourceValue, u32 nextSourceValue, POINTER_TYPE* remainderValue, u32 reflectionMask)
{
	*sourceValue &= reflectionMask;
	*remainderValue &= reflectionMask;

	if(0 < pixelShift)
	{
		POINTER_TYPE remainderValueTemp = *remainderValue;
		*remainderValue = (*sourceValue >> (BITS_PER_STEP - pixelShift));
		*sourceValue <<= pixelShift;
		*sourceValue |= remainderValueTemp;
	}
	else if(0 > pixelShift)
	{
		*sourceValue >>= -pixelShift;
		*sourceValue |= (nextSourceValue << (BITS_PER_STEP + pixelShift));
		*remainderValue = nextSourceValue >> (-pixelShift);
	}
}

void WaterPond_drawReflection(WaterPond this, u32 currentDrawingFrameBufferSet,
								s16 xSourceStart, s16 ySourceStart,
								s16 xOutputStart, s16 yOutputStart,
								s16 width, s16 height,
								u32 reflectionMask,
								s16 parallaxDisplacement,
								const u8 waveLut[], int numberOfWaveLutEntries, fix19_13 waveLutThrottleFactor,
								fix19_13 amplitudeFactor,
								bool flattenTop __attribute__ ((unused)), bool flattenBottom,
								u32 topBorderMask __attribute__ ((unused)), u32 bottomBorderMask __attribute__ ((unused)),
								u16 surfaceHeight)
{
	ASSERT(this, "ReflectiveEntity::drawReflection: null this");

    s16 xSourceEnd = xSourceStart + width;
    s16 ySourceEnd = ySourceStart + height;
	s16 xOutputEnd = xOutputStart + width;
	s16 yOutputEnd = yOutputStart + height;

	int xOutputStartSave = xOutputStart;

	// check if source and destination are not out of bounds
	if((xSourceStart > _cameraFrustum->x1) | (ySourceStart > _cameraFrustum->y1)
		|
		(xSourceEnd < _cameraFrustum->x0) | (ySourceEnd < _cameraFrustum->y0)
		|
		(xOutputStart > _cameraFrustum->x1) | (yOutputStart > _cameraFrustum->y1)
		|
		(xOutputStart > _cameraFrustum->x1) | (yOutputStart > _cameraFrustum->y1))
	{
		return;
	}

	int xClamping = 0;

	// clamp values to not write out of the screen
	if(xSourceStart < _cameraFrustum->x0)
	{
		xClamping = _cameraFrustum->x0 - xSourceStart;
		xOutputStart += xClamping;
		xSourceStart = _cameraFrustum->x0;
	}

	if(xSourceEnd > _cameraFrustum->x1 - 1)
	{
		xClamping = xSourceEnd - _cameraFrustum->x1 + 1;
		xOutputEnd -= xClamping;
		xSourceEnd = _cameraFrustum->x1 - 1;
	}

	if(ySourceStart < _cameraFrustum->y0)
	{
		yOutputStart += _cameraFrustum->y0 - ySourceStart;
		ySourceStart = _cameraFrustum->y0;
	}

	if(ySourceEnd > _cameraFrustum->y1)
	{
		yOutputEnd -= ySourceEnd - _cameraFrustum->y1;
		ySourceEnd = _cameraFrustum->y1;
	}

	// must clamp the output too, but moving the wave lut index accordingly
	if(xOutputStart < _cameraFrustum->x0)
	{
		xClamping = _cameraFrustum->x0 - xOutputStart;
		xSourceStart += xClamping;
		xOutputStart = _cameraFrustum->x0;
	}

	if(xOutputEnd > _cameraFrustum->x1)
	{
		xClamping = xOutputEnd - _cameraFrustum->x1 + 1;
		xSourceEnd -= xClamping;
		xOutputEnd = _cameraFrustum->x1 - 1;
	}

	// must clamp the output too, but moving the wave lut index accordingly
	if(yOutputStart < _cameraFrustum->y0)
	{
		ySourceStart += (_cameraFrustum->y0 - yOutputStart);

		yOutputStart = _cameraFrustum->y0;
	}

	if(yOutputEnd > _cameraFrustum->y1)
	{
		yOutputEnd = _cameraFrustum->y1;
	}

	int xSource = xSourceStart;
	int xOutput = xOutputStart;
	int xOutputLimit = xOutputEnd;
	int xOutputIncrement = 1;

	u32 reflectionMaskSave = reflectionMask;

	u8 dummyWaveLut[] =
	{
		0
	};

	fix19_13 waveLutIndexIncrement = this->waveLutIndexIncrement;

	if(!waveLut)
	{
		waveLutIndexIncrement = 0;
		this->waveLutIndex = 0;
		waveLut = dummyWaveLut;
	}

	int ySourceIncrement = 1;
    int ySourceStartHelper = ySourceStart >> Y_STEP_SIZE_2_EXP;
	int xSourceDistance = abs(xSourceEnd - xSourceStart);
	int xOutputDistance = abs(xOutput - xOutputLimit);
	int xTotal = xOutputDistance > xSourceDistance ? xSourceDistance : xOutputDistance;

	u32 time = Game_getTime(Game_getInstance());

	this->waveLutIndex += waveLutIndexIncrement;

	fix19_13 fixedNumberOfWaveLutEntries = FIX19_13_MULT(waveLutThrottleFactor, ITOFIX19_13(numberOfWaveLutEntries));

	if(this->waveLutIndex >= fixedNumberOfWaveLutEntries)
	{
		this->waveLutIndex = 0;
	}

	int xCounter = xOutputStart - xOutputStartSave;

	for(; xTotal--; xOutput += xOutputIncrement, xSource +=xOutputIncrement, xCounter++)
	{
		int leftColumn = xOutput;
		int rightColumn = xOutput;

		if(parallaxDisplacement)
		{
			//leftColumn -= parallaxDisplacement;
			rightColumn += parallaxDisplacement;

			if((unsigned)(leftColumn - _cameraFrustum->x0) >= (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0))
			{
				continue;
			}

			if((unsigned)(rightColumn - _cameraFrustum->x0) >= (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0))
			{
				continue;
			}
		}

		int xRelativeCoordinate = (xCounter % width) + FIX19_13TOI(this->waveLutIndex);
		int xIndex = (numberOfWaveLutEntries * xRelativeCoordinate) / width;
		int waveLutPixelDisplacement = FIX19_13TOI(FIX19_13_MULT(ITOFIX19_13(waveLut[xIndex]), amplitudeFactor));

		int ySource = ySourceStartHelper;
		int yOutput = (yOutputStart + waveLutPixelDisplacement) >> Y_STEP_SIZE_2_EXP;

		int pixelShift = (MODULO((yOutputStart + waveLutPixelDisplacement), Y_STEP_SIZE) - MODULO(ySourceStart, Y_STEP_SIZE)) << 1;

		reflectionMask = reflectionMaskSave;

		u32 effectiveContentMaskDisplacement = (MODULO((yOutputStart + (flattenTop? 0 : waveLutPixelDisplacement)), Y_STEP_SIZE) << 1);
		u32 effectiveContentMask = 0xFFFFFFFF << effectiveContentMaskDisplacement;
		u32 effectiveBackgroundMask = ~effectiveContentMask;

		POINTER_TYPE* columnSourcePointerLeft = (POINTER_TYPE*) (currentDrawingFrameBufferSet) + (xSource << Y_SHIFT) + ySource;
		POINTER_TYPE* columnOutputPointerLeft = (POINTER_TYPE*) (currentDrawingFrameBufferSet) + (leftColumn << Y_SHIFT) + yOutput;
		POINTER_TYPE* columnOutputPointerRight = (POINTER_TYPE*) (currentDrawingFrameBufferSet | 0x00010000) + (rightColumn << Y_SHIFT) + yOutput;

		int columnSourcePointerLeftIncrement = ySourceIncrement;

		POINTER_TYPE sourceCurrentValueLeft = *columnSourcePointerLeft;
		POINTER_TYPE sourceNextValueLeft = *(columnSourcePointerLeft + columnSourcePointerLeftIncrement);
		columnSourcePointerLeft += columnSourcePointerLeftIncrement;

		POINTER_TYPE outputValueLeft = *columnOutputPointerLeft;

		u32 random = time % (xRelativeCoordinate + waveLutPixelDisplacement + 1);
		u32 surfaceDisplacement = (effectiveContentMaskDisplacement + random % FIX19_13TOI(FIX19_13_MULT(ITOFIX19_13(surfaceHeight << 1), waveLutIndexIncrement)));
		u32 surfaceMask = 0xFFFFFFFF << (random % surfaceHeight);
		POINTER_TYPE sourceReflectionValueLeft = (~surfaceMask << surfaceDisplacement);

		waveLutPixelDisplacement =  flattenBottom ? 0 : waveLutPixelDisplacement;

		int yOutputRemainder = MODULO((yOutputEnd + waveLutPixelDisplacement), Y_STEP_SIZE) << 1;

		POINTER_TYPE remainderLeftValue = 0;

		int yOutputLimit = (yOutputEnd + waveLutPixelDisplacement) >> Y_STEP_SIZE_2_EXP;

		for(; yOutput < yOutputLimit; yOutput++, ySource += ySourceIncrement)
		{
			WaterPond_shiftPixels(pixelShift, &sourceCurrentValueLeft, sourceNextValueLeft, &remainderLeftValue, reflectionMask);

			sourceCurrentValueLeft &= effectiveContentMask;
			sourceCurrentValueLeft |= (outputValueLeft & effectiveBackgroundMask);
			sourceCurrentValueLeft |= sourceReflectionValueLeft;
			sourceReflectionValueLeft = 0;

			effectiveContentMask = 0xFFFFFFFF;
			effectiveBackgroundMask = 0;

			*columnOutputPointerLeft = sourceCurrentValueLeft;
			*columnOutputPointerRight = sourceCurrentValueLeft;

			columnOutputPointerLeft++;
			columnOutputPointerRight++;

			sourceCurrentValueLeft = sourceNextValueLeft;

			columnSourcePointerLeft += columnSourcePointerLeftIncrement;

			sourceNextValueLeft = *columnSourcePointerLeft;
		}

		if(yOutputRemainder)
		{
			u32 maskDisplacement = (BITS_PER_STEP - yOutputRemainder);
			effectiveContentMask = 0xFFFFFFFF >> maskDisplacement;
			effectiveContentMask &= ~(bottomBorderMask >> maskDisplacement);

			outputValueLeft = *columnOutputPointerLeft;

			if(0 <= pixelShift)
			{
				remainderLeftValue |= (sourceCurrentValueLeft << pixelShift);
			}

			remainderLeftValue &= reflectionMask;

			*columnOutputPointerLeft = (outputValueLeft & ~effectiveContentMask) | (remainderLeftValue & effectiveContentMask);
			*columnOutputPointerRight = (outputValueLeft & ~effectiveContentMask) | (remainderLeftValue & effectiveContentMask);
		}
	}
}


