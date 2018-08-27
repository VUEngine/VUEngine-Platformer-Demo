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

#include <PostProcessingRain.h>
#include <Optics.h>
#include <Utilities.h>
#include <Hero.h>
#include <DirectDraw.h>
#include <Game.h>
#include <Container.h>
#include <Entity.h>
#include <VIPManager.h>
#include <Camera.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define SIZE_OF_U16_POWER		1
#define SIZE_OF_S16_POWER		1
#define Y_STEP_SIZE				16
#define Y_STEP_SIZE_2_EXP		4
#define __MODULO(n, m)		(n & (m - 1))


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

static void PostProcessingRain::waterStream(
	u32 currentDrawingFrameBufferSet,
	s16 xStart,
	s16 xEnd,
	s16 xDisplacement,
	u16 xStep,
	s16 yStart,
	s16 yEnd,
	s16 yDisplacement,
	const u16 yStep[],
	u16 numberOfYSpeeds,
	u16* yStepIndex,
	s16 yStepThrottle,
	s16 y[],
	u16 numberOfYs,
	const u16 dropletLength[],
	u16 numberOfDropletSize,
	u16* dropletLengthIndex,
	int minimumDropletLength,
	const s16 dropletParallax[],
	u16 numberOfDropletParallax
)
{
	int yIndex = 0;

	if(xStart < _cameraFrustum->x0)
	{
		xStart = _cameraFrustum->x0;
	}

	if(xEnd > _cameraFrustum->x1 - 1)
	{
		xEnd = _cameraFrustum->x1 - 1;
	}

	if(yStart < _cameraFrustum->y0)
	{
		yStart = _cameraFrustum->y0;
	}

	if(yEnd > _cameraFrustum->y1 - 1)
	{
		yEnd = _cameraFrustum->y1 - 1;
	}

	int x = xDisplacement + xStart;

	if(x < _cameraFrustum->x0)
	{
		x = xEnd + x % xEnd;
	}

	if(x > xEnd)
	{
		x = x % xEnd;
	}

	// write to framebuffers for both screens
	int counter = 1;

	for(; counter <= xEnd; counter += xStep)
	{
		if(++yIndex >= numberOfYs)
		{
			yIndex = 0;
		}

		x += xStep;

		if(x >= xEnd)
		{
			x -= xEnd;
			x += xStart;
		}

		int leftColumn = x;
		int rightColumn = x;

		s16 dropletParallaxValue = dropletParallax[counter % numberOfDropletParallax];

		leftColumn -= dropletParallaxValue;
		rightColumn += dropletParallaxValue;

		if(0 >= leftColumn || 0 >= rightColumn)
		{
			continue;
		}
		else if(leftColumn >= xEnd || rightColumn >= xEnd)
		{
			continue;
		}

		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (leftColumn << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (rightColumn << 4);

		if(_cameraFrustum->y0 > y[yIndex] + yStart)
		{
			continue;
		}

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		u32 yStep = (y[yIndex] + yStart) >> Y_STEP_SIZE_2_EXP;
		u32 subY = __MODULO((y[yIndex] + yStart), Y_STEP_SIZE);
		u32 dropletMask = 0xFFFFFFFF << (subY << 1);

		if(++*dropletLengthIndex >= numberOfDropletSize)
		{
			*dropletLengthIndex = 0;
		}

		int effectiveDropletLength = (signed)dropletLength[*dropletLengthIndex] + yStepThrottle;

		if(minimumDropletLength > effectiveDropletLength)
		{
			continue;
		}

		if(effectiveDropletLength >= (signed)Y_STEP_SIZE)
		{
			effectiveDropletLength = Y_STEP_SIZE - 1;
		}

		int dropletLengthDifference = (Y_STEP_SIZE - (subY + effectiveDropletLength)) << 1;

		if(0 < dropletLengthDifference)
		{
			dropletMask &= (0xFFFFFFFF >> dropletLengthDifference);
		}

		u32* sourcePointerLeft = columnSourcePointerLeft + yStep;
		u32* sourcePointerRight = columnSourcePointerRight + yStep;
		u32 sourceValue = *sourcePointerLeft;

		if(!sourceValue)
		{
			if(__MODULO((int)dropletLengthDifference, Y_STEP_SIZE_2_EXP))
			{
				continue;
			}

			u32 content = 0x55555555 & ((dropletMask & ~sourceValue) | (sourceValue & ~dropletMask));
			*sourcePointerLeft = content;
			*sourcePointerRight = content;
		}
		else
		{
			u32 content = (dropletMask & ~sourceValue) | (sourceValue & ~dropletMask);
			*sourcePointerLeft = content;
			*sourcePointerRight = content;

			if(0 > dropletLengthDifference)
			{
				dropletMask = (0xFFFFFFFF << -dropletLengthDifference);
				sourceValue = *(sourcePointerLeft + 1);
				content = (~dropletMask & ~sourceValue) | (sourceValue & dropletMask);
				*(sourcePointerLeft + 1) = content;
				*(sourcePointerRight + 1) = content;
			}
		}
	}

	u16 i = 0;

	for(; i < numberOfYs; i++)
	{
		if(++*yStepIndex >= numberOfYSpeeds)
		{
			*yStepIndex = 0;
		}

		y[i] += yStep[*yStepIndex] + yStepThrottle;

		int cumulativeY = y[i] + yStart + yDisplacement;

		if(yEnd - (Y_STEP_SIZE >> 1) < cumulativeY)
		{
			y[i] = 0;
		}
	}
}

static void PostProcessingRain::calculateRainPrecipitation(fix19_13* yStepThrottle, fix19_13* xStep, fix19_13 maximumYThrottle, fix19_13 minimumYThrottle, fix19_13 maximumXStep, fix19_13 minimumXStep)
{
	static u32 previousTime = 0;
	static u8 timePeriodIndex = 0;
	static u8 rainAccelerationIndex = 0;

	const u8 timePeriod[] =
	{
		30, 25, 40, 35, 50, 50, 40, 45,
		30, 30, 35, 40, 50, 60, 20, 45,
	};

	const s8 rainAcceleration[] =
	{
		1, 0, -1, 0,
	};

	u32 currentTime = Clock::getTime(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()));

	if((currentTime - previousTime) / 1000 > timePeriod[timePeriodIndex])
	{
		previousTime = currentTime;

		if(++timePeriodIndex >= sizeof(timePeriod) / sizeof(u8))
		{
			timePeriodIndex = 0;
		}

		if(++rainAccelerationIndex >= sizeof(rainAcceleration) / sizeof(s8))
		{
			rainAccelerationIndex = 0;
		}
	}

	// multiply by the game cycle per second
	int rainPeriod =  __I_TO_FIX19_13(((int)timePeriod[timePeriodIndex] + previousTime % timePeriod[timePeriodIndex]) * 50);

	*yStepThrottle += __FIX10_6_TO_FIX19_13(__FIX10_6_DIV(__FIX19_13_TO_FIX10_6(rainAcceleration[rainAccelerationIndex] * (maximumYThrottle - minimumYThrottle)), __FIX19_13_TO_FIX10_6(rainPeriod)));
	*xStep -= __FIX10_6_TO_FIX19_13(__FIX10_6_DIV(__FIX19_13_TO_FIX10_6(rainAcceleration[rainAccelerationIndex] * (maximumXStep - minimumXStep)), __FIX19_13_TO_FIX10_6(rainPeriod)));

	if(*yStepThrottle < minimumYThrottle)
	{
		*yStepThrottle = minimumYThrottle;
	}
	else if(*yStepThrottle > maximumYThrottle)
	{
		*yStepThrottle = maximumYThrottle;
	}

	if(*xStep < minimumXStep)
	{
		*xStep = minimumXStep;
	}
	else if(*xStep > maximumXStep)
	{
		*xStep = maximumXStep;
	}
}

static void PostProcessingRain::rain(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
 	#define RAIN_X_RANGE_1					383
 	#define RAIN_MINIMUM_DROPLET_LENGTH		3
 	#define RAIN_MINIMUM_Y_THROTTLE_1		__I_TO_FIX19_13(-5)
 	#define RAIN_MAXIMUM_Y_THROTTLE_1		__I_TO_FIX19_13(2)
 	#define RAIN_MINIMUM_X_STEP_1			__I_TO_FIX19_13(15)
 	#define RAIN_MAXIMUM_X_STEP_1			__I_TO_FIX19_13(90)
	static u16 yStepIndex = 0;
	static u16 dropletLengthIndex = 0;
	static fix19_13 yStepThrottle = RAIN_MINIMUM_Y_THROTTLE_1;
	static fix19_13 xStep = RAIN_MAXIMUM_X_STEP_1;
 	static Vector3D cameraPreviousPosition = {0, 0, 0};
 	static int cumulativeX = 0;
 	fix19_13 yScreenDisplacement = __I_TO_FIX19_13(__METERS_TO_PIXELS(_cameraPosition->y - cameraPreviousPosition.y));

 	cumulativeX += __METERS_TO_PIXELS(_cameraPosition->x - cameraPreviousPosition.x);
	PostProcessingRain::calculateRainPrecipitation(&yStepThrottle, &xStep, RAIN_MAXIMUM_Y_THROTTLE_1, RAIN_MINIMUM_Y_THROTTLE_1, RAIN_MAXIMUM_X_STEP_1, RAIN_MINIMUM_X_STEP_1);
	cameraPreviousPosition = *_cameraPosition;

 	const s16 dropletParallax[] =
 	{
 		0, 5, -2, 3, -3, 6, 9, -4, 0, 0, 8,
		7, -3, 2, -2, 0, 5, -3, 4, -4, 6, -7,
		0, 6, -6, 1, 0, 0, 5, -5, -7, 8, 9, 0
		,
 	};

 	const u16 dropletLength[] =
 	{
 		3, 4, 5, 5, 4, 3, 6, 6, 5, 6, 8, 5, 5,
 	};

	static s16 y[] =
	{
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
	};

	const u16 yStep[] =
	{
		4, 5, 6, 6, 7, 8, 8, 6, 5, 4, 4, 5,
		6, 7, 8, 4, 5, 5, 5, 6, 7, 5, 4, 8,
		4, 4, 7, 8, 8, 5, 7, 3, 4, 7, 5, 3,
		6, 7, 4, 5, 6, 8, 5, 5, 6, 7, 8, 6,
		6, 7, 8, 4, 5, 6, 5, 4, 8, 5, 4, 4,
		8, 5, 7, 3, 4, 4, 7, 8, 4, 7, 5, 3,


/*		9, 7, 8, 7, 6, 7, 8, 5, 6, 8, 4, 5,
		5, 6, 8, 7, 7, 6, 5, 5, 6, 4, 7, 8,
		8, 7, 9, 6, 8, 7, 6, 6, 5, 7, 8, 7,
		7, 6, 7, 7, 6, 5, 6, 7, 6, 6, 5, 8,
		5, 6, 8, 4, 4, 6, 5, 5, 6, 6, 7, 8,
		6, 7, 8, 7, 6, 7, 8, 4, 6, 8, 6, 5,
		7, 6, 7, 5, 6, 5, 6, 7, 6, 9, 5, 8,
		*/
	};

	// must account for the camera displacement
	yStepThrottle -= yScreenDisplacement;

	PostProcessingRain::waterStream(
		currentDrawingFrameBufferSet,
		0,
		__SCREEN_WIDTH - 1,
		-cumulativeX,
		__FIX19_13_TO_I(xStep),
		_cameraFrustum->y0,
		_cameraFrustum->y1,
		0,
		yStep,
		sizeof(yStep) >> SIZE_OF_U16_POWER,
		&yStepIndex,
		__FIX19_13_TO_I(yStepThrottle),
		y,
		sizeof(y) >> SIZE_OF_S16_POWER,
		dropletLength,
		sizeof(dropletLength) >> SIZE_OF_U16_POWER,
		&dropletLengthIndex,
		RAIN_MINIMUM_DROPLET_LENGTH,
		dropletParallax,
		sizeof(dropletParallax) >> SIZE_OF_S16_POWER
	);

	yStepThrottle += yScreenDisplacement;
}

static void PostProcessingRain::waterFall(u32 currentDrawingFrameBufferSet, Vector3D position, int width, int height, int yStepThrottle)
{
	static u16 yStepIndex = 0;
	static u16 dropletLengthIndex = 0;

 	const s16 dropletParallax[] =
 	{
 		-2
		,
 	};

 	const u16 dropletLength[] =
 	{
 		5, 6, 9, 11, 4, 13, 11, 4, 7, 9, 5, 12, 9,
 		11, 10, 4, 7, 12, 12, 10, 8, 5, 4, 8, 10
 	};

	static s16 y[] =
	{
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,

	};

	const u16 yStep[] =
	{
		4, 5, 6, 6, 7, 8, 8, 6, 5, 4, 4, 5,
		6, 7, 8, 4, 5, 5, 5, 6, 7, 5, 4, 8,
		4, 4, 7, 8, 8, 5, 7, 3, 4, 7, 5, 3,
		6, 7, 4, 5, 6, 8, 5, 5, 6, 7, 8, 6,
		6, 7, 8, 4, 5, 6, 5, 4, 8, 5, 4, 4,
		8, 5, 7, 3, 4, 4, 7, 8, 4, 7, 5, 3,
	};

	PostProcessingRain::waterStream(
		currentDrawingFrameBufferSet,
		__FIX10_6_TO_I(position.x) - (width >> 1),
		__FIX10_6_TO_I(position.x) + (width >> 1),
		0,
		1,
		__FIX10_6_TO_I(position.y) - (height >> 1),
		__FIX10_6_TO_I(position.y) + (height >> 1),
		0,
		yStep,
		sizeof(yStep) >> SIZE_OF_U16_POWER,
		&yStepIndex,
		yStepThrottle,
		y,
		sizeof(y) >> SIZE_OF_S16_POWER,
		dropletLength,
		sizeof(dropletLength) >> SIZE_OF_U16_POWER,
		&dropletLengthIndex,
		1,
		dropletParallax,
		sizeof(dropletParallax) >> SIZE_OF_S16_POWER
	);
}

static void PostProcessingRain::waterFall20x100(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
	if(isDeleted(spatialObject))
	{
		return;
	}

	Vector3D spatialObjectPosition = Vector3D::getRelativeToCamera(*SpatialObject::getPosition(spatialObject));

	PostProcessingRain::waterFall(currentDrawingFrameBufferSet, spatialObjectPosition, 20, 100, 0);
}