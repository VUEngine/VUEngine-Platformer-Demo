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

#include <PostProcessingLantern.h>
#include <Hero.h>
#include <Container.h>
#include <Camera.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define SIZE_OF_S16_POWER		1
#define Y_STEP_SIZE				16
#define Y_STEP_SIZE_2_EXP		4
#define __MODULO(n, m)			(n & (m - 1))


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

static void PostProcessingLantern::applyMask(u32 currentDrawingFrameBufferSet, int xStart, int xEnd, int yStart, int yEnd, u32 mask)
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

static void PostProcessingLantern::ellipticalWindow(u32 currentDrawingFrameBufferSet, PixelVector position, s16 ellipsisArc[], u16 ellipsisHorizontalAxisSize, u32 penumbraMask, bool roundBorder)
{
 	int xPosition = position.x;
 	int yPosition = position.y;
	// move y position to the closest 16 multiple
	int tempYPosition = yPosition + (Y_STEP_SIZE >> 1);
	yPosition = tempYPosition - __MODULO(tempYPosition, Y_STEP_SIZE);

	int ellipsisArcIndex = 0 > xPosition - ellipsisHorizontalAxisSize ? (ellipsisHorizontalAxisSize - xPosition) : 0;
	int ellipsisArcIndexDelta = 1;
	int x = 0;

	for(x = _cameraFrustum->x0; x < _cameraFrustum->x1; x++)
	{
		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft = (u32*) (currentDrawingFrameBufferSet) + (x << 4);
		u32* columnSourcePointerRight = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x << 4);

		int yStart = _cameraFrustum->y0 >> Y_STEP_SIZE_2_EXP;
		int yEnd = (_cameraFrustum->y1 - 16) >> Y_STEP_SIZE_2_EXP; // do not write over GUI
		int y = yStart;

		int ellipsisY = ellipsisArc[ellipsisArcIndex];
		int maskDisplacement = __MODULO(ellipsisY, Y_STEP_SIZE) << 1;
		u32 upperMask = roundBorder ? ~(0xFFFFFFFF >> maskDisplacement) : 0xFFFFFFFF;
		u32 lowerMask = roundBorder ? ~(0xFFFFFFFF << maskDisplacement) : 0xFFFFFFFF;

		int yLowerLimit =  (yPosition + ellipsisY) >> Y_STEP_SIZE_2_EXP;
		int yUpperLimit = (yPosition >> Y_STEP_SIZE_2_EXP) - (yLowerLimit - (yPosition >> Y_STEP_SIZE_2_EXP));

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

static void PostProcessingLantern::lantern(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
 	static bool ellipsisArcCalculated = false;

	if(isDeleted(spatialObject))
	{
 		if(ellipsisArcCalculated)
 		{
 			PostProcessingLantern::applyMask(currentDrawingFrameBufferSet, _cameraFrustum->x0, _cameraFrustum->x1, _cameraFrustum->y0, _cameraFrustum->y1, 0);
 		}
 		return;
	}

	PixelVector screenPixelPosition = Vector3D::projectToPixelVector(Vector3D::getRelativeToCamera(*SpatialObject::getPosition(spatialObject)), 0);

 	screenPixelPosition.y -= 10;

 	#define ELLIPSIS_X_AXIS_LENGTH		55
 	#define ELLIPSIS_Y_AXIS_LENGTH		60
	#define PENUMBRA_MASK				0x55555555

 	static s16 ellipsisArc[ELLIPSIS_X_AXIS_LENGTH];

 	if(!ellipsisArcCalculated)
	{
		ellipsisArcCalculated = true;

		u16 i = 0;
		float x = 0;

		for(i = sizeof(ellipsisArc) >> SIZE_OF_S16_POWER; --i; x++)
		{
			ellipsisArc[i] = ELLIPSIS_Y_AXIS_LENGTH * Math::squareRoot(((ELLIPSIS_X_AXIS_LENGTH * ELLIPSIS_X_AXIS_LENGTH) - (x * x)) / (ELLIPSIS_X_AXIS_LENGTH * ELLIPSIS_X_AXIS_LENGTH));
		}
	}

	PostProcessingLantern::ellipticalWindow(currentDrawingFrameBufferSet, screenPixelPosition, ellipsisArc, ELLIPSIS_X_AXIS_LENGTH, PENUMBRA_MASK, true);
}

