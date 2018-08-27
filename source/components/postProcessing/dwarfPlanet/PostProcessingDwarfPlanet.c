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

#include <PostProcessingDwarfPlanet.h>


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

/**
 * "Bends down" the left and right edges of the screen to make the world look like a very small planet.
 * This effect reads and write a fourth of the screen and is therefore running OK-ish on hardware,
 * reducing the frame rate by about 50%.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingDwarfPlanet::dwarfPlanet(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
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

	int lutEntries = sizeof(lut) / sizeof(u32);
	// runtime working variables

	int counter = lutEntries;

	// loop columns of left fourth of screen
	for(; --counter;)
	{
		int x1 = (lutEntries - counter);
		int x2 = __SCREEN_WIDTH - counter;

		// get pointer to currently manipulated 32 bits of framebuffer
		u32* columnSourcePointerLeft1 = (u32*) (currentDrawingFrameBufferSet) + (x1 << 4);
		u32* columnSourcePointerRight1 = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x1 << 4);
		u32* columnSourcePointerLeft2 = (u32*) (currentDrawingFrameBufferSet) + (x2 << 4);
		u32* columnSourcePointerRight2 = (u32*) (currentDrawingFrameBufferSet | 0x00010000) + (x2 << 4);

		// the shifted out pixels on top should be black
		u32 previousSourcePointerValueLeft1 = 0;
		u32 previousSourcePointerValueRight1 = 0;
		u32 previousSourcePointerValueLeft2 = 0;
		u32 previousSourcePointerValueRight2 = 0;

		u16 y = 0;

		// loop current column in steps of 16 pixels (32 bits)
		// ignore the bottom 16 pixels of the screen (gui)
		for(y = 0; y < 13; y++)
		{
			previousSourcePointerValueLeft1 = PostProcessingDwarfPlanet::writeToFrameBuffer(y, 32 - lut[lutEntries - counter], columnSourcePointerLeft1, previousSourcePointerValueLeft1);
			previousSourcePointerValueRight1 = PostProcessingDwarfPlanet::writeToFrameBuffer(y, 32 - lut[lutEntries - counter], columnSourcePointerRight1, previousSourcePointerValueRight1);
			previousSourcePointerValueLeft2 = PostProcessingDwarfPlanet::writeToFrameBuffer(y, 32 - lut[counter], columnSourcePointerLeft2, previousSourcePointerValueLeft2);
			previousSourcePointerValueRight2 = PostProcessingDwarfPlanet::writeToFrameBuffer(y, 32 - lut[counter], columnSourcePointerRight2, previousSourcePointerValueRight2);
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
static u32 PostProcessingDwarfPlanet::writeToFrameBuffer(u16 y, u16 shift, u32* columnSourcePointer, u32 previousSourcePointerValue)
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