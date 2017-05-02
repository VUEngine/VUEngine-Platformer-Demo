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

#include <PostProcessingEffects.h>
#include <Optics.h>
#include <Utilities.h>
#include <Hero.h>
#include <DirectDraw.h>
#include <Game.h>
#include <Container.h>
#include <Entity.h>
#include <VIPManager.h>
#include <Screen.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern const VBVec3D* _screenPosition;
extern const CameraFrustum* _cameraFrustum;


u32 PostProcessingEffects_writeToFrameBuffer(u16 y, u16 shift, u32* columnSourcePointer, u32 previousSourcePointerValue);
void PostProcessingEffects_drawRhombus(fix19_13 radiusFix19_13, u32 color, VBVec3D spatialObjectPosition);


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

void PostProcessingEffects_waterStream(u32 currentDrawingFrameBufferSet, int xStart, int xReset,
								int xRange, s16 y[], int yRange, s16 yDisplacement, u16 numberOfYs,
								const u16 ySpeed[], u16 numberOfYSpeeds, u16* ySpeedIndex,
								s16 yThrottle, u16 xStep, const u16 dropletSize[],
								u16 numberOfDropletSize, u16* dropletSizeIndex, u32 lightUpMask __attribute__ ((unused)),
								const s16 dropletParallax[], u16 numberOfDropletParallax)
{
	int yIndex = 0;

	int x = xStart;

	if(x < 0)
	{
		x = xRange + x % xRange;
	}

	if(x > xRange)
	{
		x = x % xRange;
	}

	// write to framebuffers for both screens
	int counter = 1;

	// loop columns that shall be shifted
	for(; counter <= xRange; counter += xStep)
	{
		if(++yIndex >= numberOfYs)
		{
			yIndex = 0;
		}

		x += xStep;

		if(x >= xRange)
		{
			x -= xRange;
			x += xReset;
		}

		u16 ySpeedValue = ySpeed[*ySpeedIndex] + 1;

		int leftColumn = x;
		int rightColumn = x;

		s16 dropletParallaxValue = dropletParallax[counter % numberOfDropletParallax];

		leftColumn -= dropletParallaxValue;
		rightColumn += dropletParallaxValue;

		if(0 >= leftColumn || 0 >= rightColumn)
		{
			continue;
		}
		else if(leftColumn >= xRange || rightColumn >= xRange)
		{
			continue;
		}

		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (leftColumn << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (rightColumn << 4);

		if(_cameraFrustum->y0 > y[yIndex] + yDisplacement)
		{
			continue;
		}

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		u32 stepSize = (sizeof(u32) << 2);
		u32 yStep = (y[yIndex] + yDisplacement) / stepSize;
		u32 subY = ((y[yIndex] + yDisplacement) % stepSize);
		u32 dropletMask = 0xFFFFFFFF << (subY << 1);

		if(++*dropletSizeIndex >= numberOfDropletSize)
		{
			*dropletSizeIndex = 0;
		}

		int effectiveDropletSize = (signed)dropletSize[*dropletSizeIndex] + yThrottle;

		if(0 > effectiveDropletSize)
		{
			continue;
		}

		if(effectiveDropletSize >= (signed)stepSize)
		{
			effectiveDropletSize = stepSize - 1;
		}

		int dropletSizeDifference = (stepSize - (subY + effectiveDropletSize)) << 1;

		if(0 < dropletSizeDifference)
		{
			dropletMask &= (0xFFFFFFFF >> dropletSizeDifference);
		}

		u32* sourcePointerLeft = columnSourcePointerLeft + yStep;
		u32* sourcePointerRight = columnSourcePointerRight + yStep;
		u32 sourceValue = *sourcePointerLeft;
		u32 content = (dropletMask & ~sourceValue) | (sourceValue & ~dropletMask);
		*sourcePointerLeft = content;
		*sourcePointerRight = content;

		bool doubleDropletWidth = !(ySpeedValue % (*dropletSizeIndex + 1));

		if(doubleDropletWidth)
		{
			columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + ((leftColumn + 1) << 4);
			columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + ((rightColumn + 1) << 4);
			sourcePointerLeft = columnSourcePointerLeft + yStep;
			sourcePointerRight = columnSourcePointerRight + yStep;
			*sourcePointerLeft = content;
			*sourcePointerRight = content;
		}

		if(0 > dropletSizeDifference)
		{
			dropletMask = (0xFFFFFFFF << -dropletSizeDifference);
			sourceValue = *(sourcePointerLeft + 1);
			content = (~dropletMask & ~sourceValue) | (sourceValue & dropletMask);
			*(sourcePointerLeft + 1) = content;
			*(sourcePointerRight + 1) = content;

			if(doubleDropletWidth)
			{
				columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + ((leftColumn + 1) << 4);
				columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + ((rightColumn + 1) << 4);
				sourcePointerLeft = columnSourcePointerLeft + yStep;
				sourcePointerRight = columnSourcePointerRight + yStep;
				*(sourcePointerLeft + 1) = content;
				*(sourcePointerRight + 1) = content;
			}
		}
	}

	u16 i = 0;

	int stepSize = (sizeof(u32) << 2);

	for(; i < numberOfYs; i++)
	{
		if(++*ySpeedIndex >= numberOfYSpeeds)
		{
			*ySpeedIndex = 0;
		}

		y[i] += ySpeed[*ySpeedIndex] + yThrottle;

		if((_cameraFrustum->y1 - stepSize < y[i] + yDisplacement)
			||
			(yRange - stepSize < y[i] + yDisplacement)
		)
		{
			y[i] = _cameraFrustum->y0;
		}
	}
}

void PostProcessingEffects_calculateRainPrecipitation(fix19_13* yThrottle, fix19_13* xStep, fix19_13 maximumYThrottle, fix19_13 minimumYThrottle, fix19_13 maximumXStep, fix19_13 minimumXStep)
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

	u32 currentTime = Clock_getTime(PlatformerLevelState_getClock(PlatformerLevelState_getInstance()));

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
	int rainPeriod =  ITOFIX19_13(((int)timePeriod[timePeriodIndex] + previousTime % timePeriod[timePeriodIndex]) * 50);

	*yThrottle += FIX19_13_DIV(rainAcceleration[rainAccelerationIndex] * (maximumYThrottle - minimumYThrottle), rainPeriod);
	*xStep -= FIX19_13_DIV(rainAcceleration[rainAccelerationIndex] * (maximumXStep - minimumXStep), rainPeriod);

	if(*yThrottle < minimumYThrottle)
	{
		*yThrottle = minimumYThrottle;
	}

	if(*xStep < minimumXStep)
	{
		*xStep = minimumXStep;
	}
}

void PostProcessingEffects_rain1(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
 	#define RAIN_X_RANGE_1					383
 	#define RAIN_LIGHT_MASK_1				0x55555555
 	#define RAIN_MINIMUM_Y_THROTTLE_1		ITOFIX19_13(-2)
 	#define RAIN_MAXIMUM_Y_THROTTLE_1		ITOFIX19_13(4)
 	#define RAIN_MINIMUM_X_STEP_1			ITOFIX19_13(20)
 	#define RAIN_MAXIMUM_X_STEP_1			ITOFIX19_13(90)
	static u16 ySpeedIndex = 0;
	static u16 dropletSizeIndex = 0;
	static fix19_13 yThrottle = RAIN_MINIMUM_Y_THROTTLE_1;
	static fix19_13 xStep = RAIN_MAXIMUM_X_STEP_1;

	PostProcessingEffects_calculateRainPrecipitation(&yThrottle, &xStep, RAIN_MAXIMUM_Y_THROTTLE_1, RAIN_MINIMUM_Y_THROTTLE_1, RAIN_MAXIMUM_X_STEP_1, RAIN_MINIMUM_X_STEP_1);

 	static VBVec3D screenPreviousPosition = {0, 0, 0};
 	static fix19_13 cumulativeX = 0;

 	cumulativeX += _screenPosition->x - screenPreviousPosition.x;
	screenPreviousPosition = *_screenPosition;

 	const s16 dropletParallax[] =
 	{
 		0, 5, -2, 3, -3, 6, 9, -4, 0, 0, 8,
		7, -3, 1, -1, 0, 5, -3, 4, -4, 6, -7
		,
 	};

 	const u16 dropletSize[] =
 	{
 		3, 4, 5, 5, 4, 3, 6, 7, 7, 6, 6, 4, 5,
 	};

	static s16 y[] =
	{
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74, 59,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
	};

	const u16 ySpeed[] =
	{
		9, 7, 8, 7, 6, 7, 8, 5, 6, 8, 4, 5,
		5, 6, 8, 7, 7, 6, 5, 5, 6, 4, 7, 8,
		8, 7, 9, 6, 8, 7, 6, 6, 5, 7, 8, 7,
		7, 6, 7, 7, 6, 5, 6, 7, 6, 6, 5, 8,
		5, 6, 8, 4, 4, 6, 5, 5, 6, 6, 7, 8,
		6, 7, 8, 7, 6, 7, 8, 4, 6, 8, 6, 5,
		7, 6, 7, 5, 6, 5, 6, 7, 6, 9, 5, 8,
	};

	PostProcessingEffects_waterStream(currentDrawingFrameBufferSet, FIX19_13TOI(-cumulativeX),
										0, RAIN_X_RANGE_1, y, __SCREEN_HEIGHT, 0,
										sizeof(y) / sizeof(s16), ySpeed,
										sizeof(ySpeed) / sizeof(u16), &ySpeedIndex,
										FIX19_13TOI(yThrottle), FIX19_13TOI(xStep),
										dropletSize, sizeof(dropletSize) / sizeof(u16),
										&dropletSizeIndex, RAIN_LIGHT_MASK_1, dropletParallax,
										sizeof(dropletParallax) / sizeof(s16));
}

void PostProcessingEffects_rain2(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
 	#define RAIN_X_RANGE_2					383
 	#define RAIN_LIGHT_MASK_2				0
 	#define RAIN_MINIMUM_Y_THROTTLE_2		ITOFIX19_13(-2)
 	#define RAIN_MAXIMUM_Y_THROTTLE_2		ITOFIX19_13(3)
 	#define RAIN_MINIMUM_X_STEP_2			ITOFIX19_13(10)
 	#define RAIN_MAXIMUM_X_STEP_2			ITOFIX19_13(80)
	static u16 ySpeedIndex = 0;
	static u16 dropletSizeIndex = 0;
	static fix19_13 yThrottle = RAIN_MINIMUM_Y_THROTTLE_2;
	static fix19_13 xStep = RAIN_MAXIMUM_X_STEP_2;

	PostProcessingEffects_calculateRainPrecipitation(&yThrottle, &xStep, RAIN_MAXIMUM_Y_THROTTLE_2, RAIN_MINIMUM_Y_THROTTLE_2, RAIN_MAXIMUM_X_STEP_2, RAIN_MINIMUM_X_STEP_2);

 	static VBVec3D screenPreviousPosition = {0, 0, 0};
 	static fix19_13 cumulativeX = 0;

 	cumulativeX += _screenPosition->x - screenPreviousPosition.x;
	screenPreviousPosition = *_screenPosition;

 	const s16 dropletParallax[] =
 	{
 		 -5, -4, -4, -6, -6, -7, -5, -1, -1, 0,
 		 -3, -5, 0, -5, -6, -6, -9, -4, 0, 0, -8,
 	};

 	const u16 dropletSize[] =
 	{
 		6, 5, 6, 7, 8, 8, 7, 7, 6, 5
 	};

	static s16 y[] =
	{
		59, 14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74,
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		59, 14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
		59, 14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74,
	};

	const u16 ySpeed[] =
	{
		5, 6, 8, 7, 7, 6, 5, 5, 6, 4, 7, 8,
		9, 7, 8, 7, 6, 7, 8, 5, 6, 8, 4, 5,
		8, 7, 9, 6, 8, 7, 6, 6, 5, 7, 8, 7,
		7, 6, 7, 7, 6, 5, 6, 7, 6, 6, 5, 8,
		5, 6, 8, 4, 4, 6, 5, 5, 6, 6, 7, 8,
		9, 7, 8, 7, 6, 7, 8, 5, 6, 8, 4, 5,
		6, 7, 8, 7, 6, 7, 8, 4, 6, 8, 6, 5,
		7, 6, 7, 5, 6, 5, 6, 7, 6, 9, 5, 8,
	};

	PostProcessingEffects_waterStream(currentDrawingFrameBufferSet, FIX19_13TOI(-cumulativeX),
										0, RAIN_X_RANGE_2, y, __SCREEN_HEIGHT, 0,
										sizeof(y) / sizeof(s16), ySpeed,
										sizeof(ySpeed) / sizeof(u16), &ySpeedIndex,
										FIX19_13TOI(yThrottle), FIX19_13TOI(xStep),
										dropletSize, sizeof(dropletSize) / sizeof(u16),
										&dropletSizeIndex, RAIN_LIGHT_MASK_2, dropletParallax,
										sizeof(dropletParallax) / sizeof(s16));
}

void PostProcessingEffects_glitch1(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
	if(!__IS_OBJECT_ALIVE(spatialObject))
	{
		return;
	}

	VBVec3D position = *Container_getGlobalPosition(__SAFE_CAST(Container, spatialObject));
	__OPTICS_NORMALIZE(position);
	position.x = FIX19_13TOI(position.x);
	position.y = FIX19_13TOI(position.y);

 	#define GLITCH_1_X_RANGE				35
 	#define GLITCH_1_Y_RANGE				70
 	#define GLITCH_1_LIGHT_MASK			0
	static u16 ySpeedIndex = 0;
	u16 xStep = 1;
	static u16 dropletSizeIndex = 0;
	u16 yThrottle = 1;

 	static s16 dropletParallax[] =
 	{
 		 -5, -4, -3,
 	};

 	static u16 dropletSize[] =
 	{
		0, 1, 2, 1, 0, 0, 1, 2, 0, 0, 1, 0, 0
 	};

	static s16 y[] =
	{
		59, 14, 97,
	};

	const u16 ySpeed[] =
	{
		1,
	};

	PostProcessingEffects_waterStream(currentDrawingFrameBufferSet, position.x - (GLITCH_1_X_RANGE >> 1), position.x - (GLITCH_1_X_RANGE >> 1), position.x + (GLITCH_1_X_RANGE >> 1), y, position.y + (GLITCH_1_Y_RANGE >> 1), position.y - (GLITCH_1_Y_RANGE >> 1), sizeof(y) / sizeof(s16), ySpeed, sizeof(ySpeed) / sizeof(u16), &ySpeedIndex, yThrottle, xStep, dropletSize, sizeof(dropletSize) / sizeof(u16), &dropletSizeIndex, GLITCH_1_LIGHT_MASK, dropletParallax, sizeof(dropletParallax) / sizeof(s16));
}

void PostProcessingEffects_waterFall(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
	if(!__IS_OBJECT_ALIVE(spatialObject))
	{
		return;
	}

	VBVec3D position = *Container_getGlobalPosition(__SAFE_CAST(Container, spatialObject));
	__OPTICS_NORMALIZE(position);
	position.x = FIX19_13TOI(position.x);
	position.y = FIX19_13TOI(position.y);

 	#define WATER_FALL_X_RANGE				20
 	#define WATER_FALL_Y_RANGE				90
 	#define WATER_FALL_LIGHT_MASK			0
	static u16 ySpeedIndex = 0;
	u16 xStep = 1;
	static u16 dropletSizeIndex = 0;
	u16 yThrottle = -2;

 	static s16 dropletParallax[] =
 	{
 		 -5, -4, -3,
 	};

 	static u16 dropletSize[] =
 	{
		8, 9, 10, 12, 9, 9, 12,
 	};

	static s16 y[] =
	{
		59, 14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74,
		12, 30, 85, 21, 74, 59, 14, 97, 62, 92, 44, 2,
		59, 14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74,
		12, 30, 85, 92, 44, 2, 74, 59, 14, 97, 62, 92,
		12, 30, 85, 21, 21, 74, 59, 14, 97, 62, 44, 2,
		59, 14, 97, 62, 92, 44, 2, 12, 30, 85, 21, 74,
	};

	const u16 ySpeed[] =
	{
		5, 6, 8, 7, 7, 6, 5, 5, 6, 4, 7, 8,
		9, 7, 8, 7, 6, 7, 8, 5, 6, 8, 4, 5,
		8, 7, 9, 6, 8, 7, 6, 6, 5, 7, 8, 7,
		7, 6, 7, 7, 6, 5, 6, 7, 6, 6, 5, 8,
		5, 6, 8, 4, 4, 6, 5, 5, 6, 6, 7, 8,
		9, 7, 8, 7, 6, 7, 8, 5, 6, 8, 4, 5,
		6, 7, 8, 7, 6, 7, 8, 4, 6, 8, 6, 5,
		7, 6, 7, 5, 6, 5, 6, 7, 6, 9, 5, 8,
	};

	PostProcessingEffects_waterStream(currentDrawingFrameBufferSet, position.x - (WATER_FALL_X_RANGE >> 1), position.x - (WATER_FALL_X_RANGE >> 1), position.x + (WATER_FALL_X_RANGE >> 1), y, position.y + (WATER_FALL_Y_RANGE >> 1), position.y - (WATER_FALL_Y_RANGE >> 1), sizeof(y) / sizeof(s16), ySpeed, sizeof(ySpeed) / sizeof(u16), &ySpeedIndex, yThrottle, xStep, dropletSize, sizeof(dropletSize) / sizeof(u16), &dropletSizeIndex, WATER_FALL_LIGHT_MASK, dropletParallax, sizeof(dropletParallax) / sizeof(s16));
}

void PostProcessingEffects_applyMask(u32 currentDrawingFrameBufferSet, int xStart, int xEnd, int yStart, int yEnd, u32 mask)
{
	if(xEnd < xStart || yEnd < yStart)
	{
		return;
	}

	if(xStart < _cameraFrustum->x0)
	{
		xStart = _cameraFrustum->x0;
	}

	if(xEnd > _cameraFrustum->x1)
	{
		xEnd = _cameraFrustum->x1;
	}

	if(yStart < _cameraFrustum->y0)
	{
		yStart = _cameraFrustum->y0;
	}

	if(yEnd > _cameraFrustum->y1)
	{
		yEnd = _cameraFrustum->y1;
	}

	for(; xStart <= xEnd; xStart++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (xStart << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (xStart << 4);

		int y = yStart;

		for(; y < yEnd; y++)
		{
			u32* sourcePointerLeft = columnSourcePointerLeft + y;
			u32* sourcePointerRight = columnSourcePointerRight + y;
			*sourcePointerLeft &= mask;
			*sourcePointerRight &= mask;
		}
	}
}

void PostProcessingEffects_ellipticalWindow(u32 currentDrawingFrameBufferSet, VBVec3D position, s16 ellipsisArc[], u16 ellipsisHorizontalAxisSize, u32 penumbraMask)
{
	int pixelsPerU32Pointer = sizeof(u32) << 2;
 	int xPosition = FIX19_13TOI(position.x);
 	int yPosition = FIX19_13TOI(position.y);
	// move y position to the closest 16 multiple
	int tempYPosition = yPosition + (pixelsPerU32Pointer >> 1);
	yPosition = tempYPosition - tempYPosition % pixelsPerU32Pointer;

	int ellipsisArcIndex = 0 > xPosition - ellipsisHorizontalAxisSize ? (ellipsisHorizontalAxisSize - xPosition) : 0;
	int ellipsisArcIndexDelta = 1;
	int x = 0;

	for(x = _cameraFrustum->x0; x < _cameraFrustum->x1; x++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (x << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		int yStart = _cameraFrustum->y0 / pixelsPerU32Pointer;
		int yEnd = _cameraFrustum->y1 / pixelsPerU32Pointer;
		int y = yStart;

		int ellipsisY = ellipsisArc[ellipsisArcIndex];
		int maskDisplacement = ellipsisY % pixelsPerU32Pointer * 2;
		u32 upperMask = ~(0xFFFFFFFF >> maskDisplacement);
		u32 lowerMask = ~(0xFFFFFFFF << maskDisplacement);

		int yLowerLimit =  (yPosition + ellipsisY) / pixelsPerU32Pointer;
		int yUpperLimit = yPosition / pixelsPerU32Pointer - (yLowerLimit - yPosition / pixelsPerU32Pointer);

		if(yUpperLimit > yEnd)
		{
			yUpperLimit = yEnd;
		}

		if(yLowerLimit < yStart)
		{
			yLowerLimit = yStart;
		}

		u32* sourcePointerLeft = columnSourcePointerLeft + y;
		u32* sourcePointerRight = columnSourcePointerRight + y;

		if((unsigned)(x - (xPosition - ellipsisHorizontalAxisSize)) < (unsigned)(ellipsisHorizontalAxisSize << 1))
		{
			for(; y < yUpperLimit; y++)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}

			if(y == yUpperLimit && y < yEnd)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft &= upperMask & penumbraMask;
				*sourcePointerRight &= upperMask & penumbraMask;
			}

			if(penumbraMask)
			{
				y = yUpperLimit + 1;

				if(y >= yStart && y < yEnd)
				{
					u32* sourcePointerLeft = columnSourcePointerLeft + y;
					u32* sourcePointerRight = columnSourcePointerRight + y;
					*sourcePointerLeft &= penumbraMask | upperMask;
					*sourcePointerRight &= penumbraMask | upperMask;
				}

				y = yLowerLimit - 1;

				if(y >= yStart && y < yEnd)
				{
					u32* sourcePointerLeft = columnSourcePointerLeft + y;
					u32* sourcePointerRight = columnSourcePointerRight + y;
					*sourcePointerLeft &= penumbraMask | lowerMask;
					*sourcePointerRight &= penumbraMask | lowerMask;
				}
			}

			y = yLowerLimit;

			if(y >= yStart && y < yEnd)
			{
				sourcePointerLeft = columnSourcePointerLeft + y;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft &= lowerMask & penumbraMask;
				*sourcePointerRight &= lowerMask & penumbraMask;
			}

			for(; ++y < yEnd;)
			{
				u32* sourcePointerLeft = columnSourcePointerLeft + y;
				u32* sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}

			ellipsisArcIndex += ellipsisArcIndexDelta;

			if(ellipsisArcIndex >= ellipsisHorizontalAxisSize)
			{
				ellipsisArcIndexDelta = -1;
				ellipsisArcIndex = ellipsisHorizontalAxisSize - 1;
			}
			else if(0 > ellipsisArcIndex)
			{
				ellipsisArcIndexDelta = 1;
				ellipsisArcIndex = 0;
			}
		}
		else
		{
			for(; y < yEnd; y++)
			{
				sourcePointerLeft = columnSourcePointerLeft + y ;
				sourcePointerRight = columnSourcePointerRight + y;
				*sourcePointerLeft = 0;
				*sourcePointerRight = 0;
			}
		}
	}
}

void PostProcessingEffects_lantern(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
 	static bool ellipsisArcCalculated = false;

	Hero hero = Hero_getInstance();

 	if(!hero)
 	{
 		if(ellipsisArcCalculated)
 		{
 			PostProcessingEffects_applyMask(currentDrawingFrameBufferSet, _cameraFrustum->x0, _cameraFrustum->x1, _cameraFrustum->y0, _cameraFrustum->y1, 0);
 		}
 		return;
 	}

 	VBVec3D heroPosition = *Container_getGlobalPosition(__SAFE_CAST(Container, hero));

 	extern const VBVec3D* _screenPosition;
 	__OPTICS_NORMALIZE(heroPosition);

 	#define ELLIPSIS_X_AXIS_LENGTH		80
 	#define ELLIPSIS_Y_AXIS_LENGTH		70
	#define PENUMBRA_MASK				0x55555555

 	static s16 ellipsisArc[ELLIPSIS_X_AXIS_LENGTH];

 	if(!ellipsisArcCalculated)
	{
		ellipsisArcCalculated = true;

		u16 i = 0;
		float x = 0;

		for(i = sizeof(ellipsisArc) / sizeof(s16); --i; x++)
		{
			ellipsisArc[i] = ELLIPSIS_Y_AXIS_LENGTH * Math_squareRoot(((ELLIPSIS_X_AXIS_LENGTH * ELLIPSIS_X_AXIS_LENGTH) - (x * x)) / (ELLIPSIS_X_AXIS_LENGTH * ELLIPSIS_X_AXIS_LENGTH));
		}
	}

	PostProcessingEffects_ellipticalWindow(currentDrawingFrameBufferSet, heroPosition, ellipsisArc, ELLIPSIS_X_AXIS_LENGTH, PENUMBRA_MASK);
}

/**
 * Uses directdraw to draw a rhombus around the spatialObject.
 * This effect only writes to the framebuffers, but does not read them. Since write access is much quicker
 * than reading, and since only a few pixels are affected, this effect runs well on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_rhombusEmitter(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject)
{
	u32 color;

	// runtime working variable
	static int radius = -62;

	if(!__IS_OBJECT_ALIVE(spatialObject))
	{
		return;
	}

	VBVec3D spatialObjectPosition = *__VIRTUAL_CALL(SpatialObject, getPosition, spatialObject);
	extern const VBVec3D* _screenPosition;
	__OPTICS_NORMALIZE(spatialObjectPosition);

	// increase radius by 1 in each cycle
	radius++;

	// gradually decrease color with larger radius
	if(radius < 46)
	{
		color = __COLOR_BRIGHT_RED;
	}
	else if(radius < 90)
	{
		color = __COLOR_MEDIUM_RED;
	}
	else if(radius < 140)
	{
		color = __COLOR_DARK_RED;
	}
	else if(radius < 206)
	{
		// pause for a little bit before restarting
		return;
	}
	else
	{
		// reset radius when reaching a certain length
		radius = 24;
		return;
	}

	// draw a rhombus around object with given radius and color
	PostProcessingEffects_drawRhombus(ITOFIX19_13(radius), color, spatialObjectPosition);
//	PostProcessingEffects_drawRhombus(ITOFIX19_13(radius >> 1), color, spatialObjectPosition);
}

/**
 * Applies a full screen wobble distortion that is reminiscent of water waves. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_wobble(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	u16 x = 0, y = 0;
	u32 previousSourcePointerValueLeft = 0;
	u32 previousSourcePointerValueRight = 0;

	// runtime working variables
	static int waveLutIndex = 0;

	// look up table of bitshifts performed on rows
	// values must be multiples of 2
	const u32 waveLut[128] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	// write to framebuffers for both screens
	// loop columns
	for(x = 0; x < 384; x++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (x << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		// the shifted out pixels on top should be black
		previousSourcePointerValueLeft = 0;
		previousSourcePointerValueRight = 0;

		// increase look up table index, wrap around if necessary
		waveLutIndex += (waveLutIndex < 127) ? 1 : -127;

		// we can skip further processing for the current column if no shifting would be done on it
		if(waveLut[waveLutIndex] == 0)
		{
			continue;
		}

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		for(y = 0; y < 13; y++)
		{
			previousSourcePointerValueLeft = PostProcessingEffects_writeToFrameBuffer(y, waveLut[waveLutIndex], columnSourcePointerLeft, previousSourcePointerValueLeft);
			previousSourcePointerValueRight = PostProcessingEffects_writeToFrameBuffer(y, waveLut[waveLutIndex], columnSourcePointerRight, previousSourcePointerValueRight);
		}
	}

	// move the wave one pixel in the next frame
	waveLutIndex++;
}

/**
 * "Tilts" the game image by a few percent by gradually shifting columns. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_tiltScreen(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	u8 buffer = 0, currentShift = 0;
	u16 x = 0, y = 0;
	u32 previousSourcePointerValue = 0;

	// write to framebuffers for both screens
	for(; buffer < 2; buffer++)
	{
		// loop columns that shall be shifted
		for(x = 0; x < 360; x++)
		{
			// get pointer to currently manipulated 32 bits of framebuffer
			u32* columnSourcePointer = (u32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0)) + (x << 4);

			// the shifted out pixels on top should be black
			previousSourcePointerValue = 0;

			// get shift for current column
			currentShift = 30 - ((x / 24) << 1);

			// loop current column in steps of 16 pixels (32 bits)
			// ignore the bottom 16 pixels of the screen (gui)
			for(y = 0; y < 13; y++)
			{
				previousSourcePointerValue = PostProcessingEffects_writeToFrameBuffer(y, currentShift, columnSourcePointer, previousSourcePointerValue);
			}
		}
	}
}

/**
 * "Bends down" the left and right edges of the screen to make the world look like a very small planet.
 * This effect reads and write a fourth of the screen and is therefore running OK-ish on hardware, but
 * still cutting the frame rate in half.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_dwarfPlanet(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	u8 buffer = 0;
	u16 x = 0, y = 0;
	u32 previousSourcePointerValue = 0;

	// runtime working variables
	static int lutIndex = 0;

	// look up table of bitshifts performed on rows
	const u32 lut[96] =
	{
		2,
		4,
		6,	6,
		8,	8,
		10, 10, 10,
		12, 12, 12,
		14, 14, 14, 14,
		16, 16, 16, 16, 16,
		18, 18, 18, 18, 18, 18,
		20, 20, 20, 20, 20, 20, 20,
		22, 22, 22, 22, 22, 22, 22, 22,
		24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
		26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
		28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
		30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	};

	// write to framebuffers for both screens
	for(; buffer < 2; buffer++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* bufferSourcePointer = (u32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));

		// loop columns of left fourth of screen
		for(x = 0; x < 96; x++)
		{
			// get pointer to currently manipulated 32 bits of framebuffer
			u32* columnSourcePointer = (u32*) (bufferSourcePointer) + (x << 4);

			// the shifted out pixels on top should be black
			previousSourcePointerValue = 0;

			// loop current column in steps of 16 pixels (32 bits)
			// ignore the bottom 16 pixels of the screen (gui)
			for(y = 0; y < 13; y++)
			{
				previousSourcePointerValue = PostProcessingEffects_writeToFrameBuffer(y, 32 - lut[lutIndex], columnSourcePointer, previousSourcePointerValue);
			}

			// iterate lut from left to right
			lutIndex++;
		}

		// loop columns of right fourth of screen
		for(x = 288; x < 384; x++)
		{
			// get pointer to currently manipulated 32 bits of framebuffer
			u32* columnSourcePointer = (u32*) (bufferSourcePointer) + (x << 4);

			// the shifted out pixels on top should be black
			previousSourcePointerValue = 0;

			// iterate lut back from right to left
			lutIndex--;

			// loop current column in steps of 16 pixels (32 bits)
			// ignore the bottom 16 pixels of the screen (gui)
			for(y = 0; y < 13; y++)
			{
				previousSourcePointerValue = PostProcessingEffects_writeToFrameBuffer(y, 32 - lut[lutIndex], columnSourcePointer, previousSourcePointerValue);
			}
		}
	}
}

/**
 * Increases the palette index within a square area around the hero, effectively "lightening" it up.
 * This effect reads and write only a small portion of the screen and is therefore semi-feasible on
 * hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_lightingTest(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	// the frameBufferSetToModify dictates which frame buffer set (remember that there are 4 frame buffers,
	// 2 per eye) has been written by the VPU and you can work on

	// will add a post processing effect around the hero
	Hero hero = Hero_getInstance();

	if(!hero)
	{
		return;
	}

	VBVec3D heroPosition = *Container_getGlobalPosition(__SAFE_CAST(Container, hero));
	extern const VBVec3D* _screenPosition;
	__OPTICS_NORMALIZE(heroPosition);
	heroPosition.x = FIX19_13TOI(heroPosition.x);
	heroPosition.y = FIX19_13TOI(heroPosition.y);

	// the pixel in screen coordinates (x: 0 - 383, y: 0 - 223)
	int x = 0;
	int y = 0;

	// these will be used to dictate the size of the screen portion to be affected
	int xCounter = 0;
	int yCounter = 0;

	// this is just a test, so that's why these are static
	static bool vibrate = false;
	static int wait = 0;

	// write to framebuffers for both screens
	u32 buffer = 0;
	for(; buffer < 2; buffer++)
	{
		for(xCounter = 48, x = heroPosition.x - (xCounter >> 1); xCounter--; x++)
		{
			for(yCounter = 48, y = heroPosition.y - (yCounter >> 1); yCounter >= 0; yCounter -= 4, y += 4)
			{
				BYTE* sourcePointer = (BYTE*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));
				sourcePointer += ((x << 6) + (y >> 2));

				/*
				// negative
				*sourcePointer = ~*sourcePointer;
				*/

				// noise
				if(vibrate)
				{
					if(xCounter & 1)
					{
						// shift down one pixel
						*sourcePointer = (*sourcePointer & 0x03) | (*sourcePointer << 2);
					}
					else
					{
						// shift up one pixel
						*sourcePointer = (*sourcePointer & 0xC0) | (*sourcePointer >> 2);
					}
				}

				// add 1 to each pixel's color to "light it up"
				*sourcePointer |= 0x55;
			}
		}
	}

	// this just create a simple delay to not shift the pixels on each cycle
	if(--wait < 0)
	{
		wait = 4;
		vibrate = !vibrate;
	}
}

/**
 * Helper function used by various post processing effects to write a 32 bit value to the framebuffer
 * (16 pixels)
 *
 * @param y								Y coordinate (true y value = y * 16)
 * @param shift							Number of bits to shift the pixels by
 * @param columnSourcePointer			Framebuffer address of the current column (x value)
 * @param previousSourcePointerValue	Value from the loop's previous cycle (effectively where y - 1)
 */
u32 PostProcessingEffects_writeToFrameBuffer(u16 y, u16 shift, u32* columnSourcePointer, u32 previousSourcePointerValue)
{
	// pointer to currently manipulated 32 bits of framebuffer
	u32* sourcePointer = columnSourcePointer + y;

	// save current pointer value to temp var and shift highest x bits of it, according to lut,
	// to the lowest bits, since we want to insert these
	u32 sourcePointerCurrentValue = *sourcePointer;
	u32 previousSourcePointerValueTemp = sourcePointerCurrentValue >> (32 - shift);

	// manipulate current 32 bits in frame buffer
	*sourcePointer =
		// shift bits according to wave lut
		// it's two bits per pixel, so 2 bits shifted left = 1 pixel shifted down on screen
		(sourcePointerCurrentValue << shift)

		// since the above shifting creates black pixels, we need to carry over these pixels
		// from the previous loop
		| previousSourcePointerValue;

	// we need the current source pointer value from _before_ we modified it, therefore we save it
	// it to a temp variable while modifying
	return previousSourcePointerValueTemp;
}

/**
 * Helper function used by the rhombus emitter effect that prints a rhombus shape to the frame buffer
 *
 * @param radiusFix19_13
 * @param color
 * @param spatialObjectPosition
 */
void PostProcessingEffects_drawRhombus(fix19_13 radiusFix19_13, u32 color, VBVec3D spatialObjectPosition)
{
	DirectDraw directDraw = DirectDraw_getInstance();

	DirectDraw_drawLine(
		directDraw,
		(VBVec2D) {spatialObjectPosition.x - radiusFix19_13,	spatialObjectPosition.y,					spatialObjectPosition.z, 0},
		(VBVec2D) {spatialObjectPosition.x,						spatialObjectPosition.y - radiusFix19_13,	spatialObjectPosition.z, 0},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(VBVec2D) {spatialObjectPosition.x + radiusFix19_13,	spatialObjectPosition.y,					spatialObjectPosition.z, 0},
		(VBVec2D) {spatialObjectPosition.x,						spatialObjectPosition.y - radiusFix19_13,	spatialObjectPosition.z, 0},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(VBVec2D) {spatialObjectPosition.x + radiusFix19_13,	spatialObjectPosition.y,					spatialObjectPosition.z, 0},
		(VBVec2D) {spatialObjectPosition.x,						spatialObjectPosition.y + radiusFix19_13,	spatialObjectPosition.z, 0},
		color
	);

	DirectDraw_drawLine(
		directDraw,
		(VBVec2D) {spatialObjectPosition.x - radiusFix19_13,	spatialObjectPosition.y,					spatialObjectPosition.z, 0},
		(VBVec2D) {spatialObjectPosition.x,						spatialObjectPosition.y + radiusFix19_13,	spatialObjectPosition.z, 0},
		color
	);
}
