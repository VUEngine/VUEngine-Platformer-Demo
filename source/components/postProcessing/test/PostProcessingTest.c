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

#include <PostProcessingTest.h>


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

/**
 * Increases the palette index within a rectangular area around the spatialObject, effectively
 * "lightening" it up. This effect reads and write only a small portion of the screen and is therefore
 * semi-feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingTest::lighting(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject)
{
	// the currentDrawingFrameBufferSet dictates which frame buffer set (remember that there are 4 frame
	// buffers, 2 per eye) has been written by the VPU and you can work on.

	if(isDeleted(spatialObject))
	{
		return;
	}

	PixelVector screenPixelPosition = Vector3D::projectToPixelVector(Vector3D::getRelativeToCamera(*SpatialObject::getPosition(spatialObject)), 0);

	// the pixel in screen coordinates (x: 0 - 383, y: 0 - 223)
	int x = 0;
	int y = 0;

	// these will be used to dictate the size of the screen portion to be affected
	int xCounter = 0;
	int yCounter = 0;

/*
	// this is just a test, so that's why these are static
	static bool vibrate = false;
	static int wait = 0;
*/

	// write to framebuffers for both screens
	u32 buffer = 0;
	for(; buffer < 2; buffer++)
	{
		for(xCounter = 64, x = screenPixelPosition.x - (xCounter >> 1); xCounter--; x++)
		{
			for(yCounter = 64, y = screenPixelPosition.y - (yCounter >> 1); yCounter >= 0; yCounter -= 4, y += 4)
			{
				BYTE* sourcePointer = (BYTE*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));
				sourcePointer += ((x << 6) + (y >> 2));

/*
				// negative
				*sourcePointer = ~*sourcePointer;
*/

/*
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
*/

				// add 1 to each pixel's color to "light it up"
				*sourcePointer |= 0x55;
			}
		}
	}

/*
	// this just creates a simple delay to not shift the pixels on each cycle
	if(--wait < 0)
	{
		wait = 4;
		vibrate = !vibrate;
	}
*/
}

static void PostProcessingTest::dummy(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
	u16 x = 0, y = 0;
	u32 previousSourcePointerValueLeft = 0;
	u32 previousSourcePointerValueRight = 0;

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

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		for(y = 0; y < 13; y++)
		{
			previousSourcePointerValueLeft = PostProcessingTest::writeToFrameBuffer(y, 1, columnSourcePointerLeft, previousSourcePointerValueLeft);
			previousSourcePointerValueRight = PostProcessingTest::writeToFrameBuffer(y, 1, columnSourcePointerRight, previousSourcePointerValueRight);
		}
	}
}

/**
 * Helper function to write a 32 bit value to the framebuffer
 * (16 pixels)
 *
 * @param y								Y coordinate (true y value = y * 16)
 * @param shift							Number of bits to shift the pixels by
 * @param columnSourcePointer			Framebuffer address of the current column (x value)
 * @param previousSourcePointerValue	Value from the loop's previous cycle (effectively where y - 1)
 */
static u32 PostProcessingTest::writeToFrameBuffer(u16 y, u16 shift, u32* columnSourcePointer, u32 previousSourcePointerValue)
{
	// pointer to currently manipulated 32 bits of framebuffer
	u32* sourcePointer = columnSourcePointer + y;

	// save current pointer value to temp var and shift highest x bits of it, according to lut,
	// to the lowest bits, since we want to insert these
	u32 sourcePointerCurrentValue = *sourcePointer;
	u32 previousSourcePointerLeftValueTemp = sourcePointerCurrentValue >> (32 - shift);

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
	return previousSourcePointerLeftValueTemp;
}
