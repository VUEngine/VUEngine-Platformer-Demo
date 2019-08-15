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

#include "WaterPond.h"
#include <Game.h>
#include <Optics.h>
#include <Camera.h>
#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <Utilities.h>
#include <CollisionManager.h>
#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void WaterPond::constructor(WaterPondSpec* reflectiveEntitySpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(&reflectiveEntitySpec->reflectiveEntitySpec, id, internalId, name);

	this->waveLutThrottleFactorIncrement = 0;
	this->amplitudeFactor = __I_TO_FIX10_6(1);
	this->waterSplash = NULL;
}

// class's destructor
void WaterPond::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void WaterPond::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

//	WaterPond::addSplashParticles(this);
}

void WaterPond::addSplashParticles()
{
	Vector3D position = {__F_TO_FIX10_6(-2), __F_TO_FIX10_6(-1), __F_TO_FIX10_6(-1)};

	extern EntitySpec WATER_SPLASH_PS;

	this->waterSplash = ParticleSystem::safeCast(Entity::addChildEntity(this, &WATER_SPLASH_PS, -1, NULL, &position, NULL));

	ParticleSystem::spawnAllParticles(this->waterSplash);
	ParticleSystem::start(this->waterSplash);
}

bool WaterPond::handleMessage(void* telegram)
{
	ReflectiveEntitySpec* reflectiveEntitySpec = (ReflectiveEntitySpec*)this->entitySpec;
	WaterPondSpec* waterPondSpec = (WaterPondSpec*)this->entitySpec;

//	bool entityTypeChecked = true;

	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
	/*
		case kCollision:
		{
			entityTypeChecked = false;

			VirtualList collidingObjects = VirtualList::safeCast(Telegram::getExtraInfo(telegram));

			VirtualNode node = NULL;

			for(node = VirtualList::begin(collidingObjects); node; node = VirtualNode::getNext(node))
			{
				Entity inGameEntity = Entity::safeCast(VirtualNode::getData(node));

				switch(Entity::getInGameType(inGameEntity))
				{
					case kTypeHero:
					case kTypeSawBlade:

						entityTypeChecked = Entity::isMoving(inGameEntity);
						break;
				}

				if(entityTypeChecked)
				{
					break;
				}
			}
		}
	*/
		case kMessageReactToCollision:

//			if(entityTypeChecked &&
			if(
				(this->waveLutThrottleFactorIncrement < waterPondSpec->waveLutThrottleFactorIncrement
				||
				this->amplitudeFactor < waterPondSpec->amplitudeFactor)
			)
			{
/*				if(this->waveLutThrottleFactorIncrement)
				{
					this->amplitudeFactor += __FIX10_6_DIV(waterPondSpec->amplitudeFactor - __I_TO_FIX10_6(1), __I_TO_FIX10_6(waterPondSpec->waveLutThrottleFactorIncrementDurationStep));
					this->waveLutThrottleFactorIncrement += __FIX10_6_DIV(waterPondSpec->waveLutThrottleFactorIncrement, __I_TO_FIX10_6(waterPondSpec->waveLutThrottleFactorIncrementDurationStep));
				}
				else
*/				{
					this->amplitudeFactor = waterPondSpec->amplitudeFactor;
					this->waveLutThrottleFactorIncrement = waterPondSpec->waveLutThrottleFactorIncrement;
				}

				this->waveLutIndexIncrement = __FIX10_6_MULT(this->waveLutThrottleFactorIncrement + reflectiveEntitySpec->waveLutThrottleFactor, __FIX10_6_DIV(__I_TO_FIX10_6(reflectiveEntitySpec->numberOfWaveLutEntries), __I_TO_FIX10_6(reflectiveEntitySpec->width)));
				MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageStopReactToCollision);
				MessageDispatcher::dispatchMessage(waterPondSpec->waveLutThrottleFactorIncrementDuration / waterPondSpec->waveLutThrottleFactorIncrementDurationStep, Object::safeCast(this), Object::safeCast(this), kMessageStopReactToCollision, NULL);

//				ParticleSystem::start(this->waterSplash);
			}

			break;

		case kMessageStopReactToCollision:

			this->amplitudeFactor -= __FIX10_6_DIV(waterPondSpec->amplitudeFactor - __I_TO_FIX10_6(1), __I_TO_FIX10_6(waterPondSpec->waveLutThrottleFactorIncrementDurationStep));
			this->waveLutThrottleFactorIncrement -= __FIX10_6_DIV(waterPondSpec->waveLutThrottleFactorIncrement, __I_TO_FIX10_6(waterPondSpec->waveLutThrottleFactorIncrementDurationStep));

			if(0 < this->waveLutThrottleFactorIncrement)
			{
				MessageDispatcher::dispatchMessage(waterPondSpec->waveLutThrottleFactorIncrementDuration / waterPondSpec->waveLutThrottleFactorIncrementDurationStep, Object::safeCast(this), Object::safeCast(this), kMessageStopReactToCollision, NULL);
			}
			else
			{
				this->amplitudeFactor = __I_TO_FIX10_6(1);
				this->waveLutThrottleFactorIncrement = 0;
//				ParticleSystem::pause(this->waterSplash);
			}

			this->waveLutIndexIncrement = __FIX10_6_MULT(this->waveLutThrottleFactorIncrement + reflectiveEntitySpec->waveLutThrottleFactor, __FIX10_6_DIV(__I_TO_FIX10_6(reflectiveEntitySpec->numberOfWaveLutEntries), __I_TO_FIX10_6(reflectiveEntitySpec->width)));
			return true;
			break;

	}

	return false;
}

void WaterPond::applyReflection(u32 currentDrawingFrameBufferSet)
{
	ReflectiveEntitySpec* reflectiveEntitySpec = (ReflectiveEntitySpec*)this->entitySpec;
	WaterPondSpec* waterPondSpec = (WaterPondSpec*)this->entitySpec;

	WaterPond::drawCustomReflection(this, currentDrawingFrameBufferSet,
								this->position2D.x + reflectiveEntitySpec->sourceDisplacement.x,
								this->position2D.y + reflectiveEntitySpec->sourceDisplacement.y,
								this->position2D.x + reflectiveEntitySpec->outputDisplacement.x,
								this->position2D.y + reflectiveEntitySpec->outputDisplacement.y,
								reflectiveEntitySpec->width,
								reflectiveEntitySpec->height,
								reflectiveEntitySpec->reflectionMask,
								reflectiveEntitySpec->parallaxDisplacement,
								reflectiveEntitySpec->waveLut,
								reflectiveEntitySpec->numberOfWaveLutEntries,
								reflectiveEntitySpec->waveLutThrottleFactor + this->waveLutThrottleFactorIncrement,
								this->amplitudeFactor,
								reflectiveEntitySpec->flattenTop, reflectiveEntitySpec->flattenBottom,
								reflectiveEntitySpec->topBorder, reflectiveEntitySpec->bottomBorder,
								waterPondSpec->surfaceHeight);
}

static inline void WaterPond::shiftPixels(int pixelShift, POINTER_TYPE* sourceValue, u32 nextSourceValue, POINTER_TYPE* remainderValue, u32 reflectionMask)
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

void WaterPond::drawCustomReflection(u32 currentDrawingFrameBufferSet,
								s16 xSourceStart, s16 ySourceStart,
								s16 xOutputStart, s16 yOutputStart,
								s16 width, s16 height,
								u32 reflectionMask,
								s16 parallaxDisplacement,
								const u8 waveLut[], int numberOfWaveLutEntries, fix10_6 waveLutThrottleFactor,
								fix10_6 amplitudeFactor,
								bool flattenTop __attribute__ ((unused)), bool flattenBottom,
								u32 topBorderMask __attribute__ ((unused)), u32 bottomBorderMask __attribute__ ((unused)),
								u16 surfaceHeight __attribute__ ((unused)))
{
	if(!waveLut)
	{
		return;
	}

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

	if(xSourceEnd > _cameraFrustum->x1)
	{
		xClamping = xSourceEnd - _cameraFrustum->x1;
		xOutputEnd -= xClamping;
		xSourceEnd = _cameraFrustum->x1;
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
		xClamping = xOutputEnd - _cameraFrustum->x1;
		xSourceEnd -= xClamping;
		xOutputEnd = _cameraFrustum->x1;
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

	fix10_6 waveLutIndexIncrement = this->waveLutIndexIncrement;

	int ySourceIncrement = 1;
    int ySourceStartHelper = ySourceStart >> Y_STEP_SIZE_2_EXP;
	int xSourceDistance = __ABS(xSourceEnd - xSourceStart);
	int xOutputDistance = __ABS(xOutput - xOutputLimit);
	int xTotal = xOutputDistance > xSourceDistance ? xSourceDistance : xOutputDistance;

	u32 time = Game::getTime(Game::getInstance());

	this->waveLutIndex += waveLutIndexIncrement;

	fix10_6 fixedNumberOfWaveLutEntries = __FIX10_6_MULT(waveLutThrottleFactor, __I_TO_FIX10_6(numberOfWaveLutEntries));

	if(this->waveLutIndex >= fixedNumberOfWaveLutEntries)
	{
		this->waveLutIndex = 0;
	}

	int xCounter = xOutputStart - xOutputStartSave;

	for(; xTotal--; xOutput += xOutputIncrement, xSource +=xOutputIncrement, xCounter++)
	{
		int leftColumn = xOutput;
		int rightColumn = xOutput;

		//leftColumn -= parallaxDisplacement;
		rightColumn += parallaxDisplacement;

		if((unsigned)(leftColumn - _cameraFrustum->x0) > (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0))
		{
			continue;
		}

		if((unsigned)(rightColumn - _cameraFrustum->x0) >= (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0))
		{
			continue;
		}

		int xRelativeCoordinate = xCounter % width;
		int xIndex = (numberOfWaveLutEntries * xRelativeCoordinate) / width + __FIX10_6_TO_I(this->waveLutIndex);
		xIndex = xIndex < numberOfWaveLutEntries ? xIndex : xIndex - numberOfWaveLutEntries;

		int waveLutPixelDisplacement = __FIX10_6_TO_I(__FIX10_6_MULT(__I_TO_FIX10_6(waveLut[xIndex]), amplitudeFactor));

		int ySource = ySourceStartHelper;
		int yOutput = (yOutputStart + waveLutPixelDisplacement) >> Y_STEP_SIZE_2_EXP;

		int pixelShift = (__MODULO((yOutputStart + waveLutPixelDisplacement), Y_STEP_SIZE) - __MODULO(ySourceStart, Y_STEP_SIZE)) << 1;

		reflectionMask = reflectionMaskSave;

		u32 effectiveContentMaskDisplacement = (__MODULO((yOutputStart + (flattenTop? 0 : waveLutPixelDisplacement)), Y_STEP_SIZE) << 1);
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
/*
		u32 random = time % (xRelativeCoordinate + waveLutPixelDisplacement + 1);
		u32 surfaceDisplacement = (effectiveContentMaskDisplacement + random % __FIX10_6_TO_I(__FIX10_6_MULT(__I_TO_FIX10_6(surfaceHeight << 1), waveLutIndexIncrement)));
		u32 surfaceMask = 0xFFFFFFFF << (random % surfaceHeight);
		POINTER_TYPE sourceReflectionValueLeft = (~surfaceMask << surfaceDisplacement);
*/
		POINTER_TYPE sourceReflectionValueLeft = (topBorderMask << effectiveContentMaskDisplacement) & xOutput & time;

		waveLutPixelDisplacement =  flattenBottom ? 0 : waveLutPixelDisplacement;

		int yOutputRemainder = __MODULO((yOutputEnd + waveLutPixelDisplacement), Y_STEP_SIZE) << 1;

		POINTER_TYPE remainderLeftValue = 0;

		int yOutputLimit = (yOutputEnd + waveLutPixelDisplacement) >> Y_STEP_SIZE_2_EXP;

		for(; yOutput < yOutputLimit; ySource += ySourceIncrement)
		{
			WaterPond::shiftPixels(pixelShift, &sourceCurrentValueLeft, sourceNextValueLeft, &remainderLeftValue, reflectionMask);

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

			if(++yOutput >= yOutputLimit)
			{
				break;
			}

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


