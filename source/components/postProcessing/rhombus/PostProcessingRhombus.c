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

#include <PostProcessingRhombus.h>
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
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

/**
 * Uses directdraw to draw a rhombus around the spatialObject.
 * This effect only writes to the framebuffers, but does not read them. Since write access is much quicker
 * than reading, and since only a few pixels are affected, this effect runs well on hardware.
 *
 * @param currentDrawingFrameBufferSet	The framebuffer set that's currently being accessed
 */
static void PostProcessingRhombus::rhombus(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject)
{
	// runtime working variable
	static int radius = 4;

	if(isDeleted(spatialObject))
	{
		return;
	}

	PixelVector screenPixelPosition = Vector3D::projectToPixelVector(Vector3D::getRelativeToCamera(*SpatialObject::getPosition(spatialObject)), 0);

	// increase radius by 1 in each cycle
	radius++;

	if(radius > 184)
	{
		// reset radius when reaching a certain length
		radius = 4;
	}
	else if(radius > 64)
	{
		// pause for a little bit before restarting
		return;
	}

	// draw a rhombus around object with given radius and color
	PostProcessingRhombus::drawRhombus((radius), __COLOR_BLACK, screenPixelPosition, -((radius + 4) >> 5));
//	PostProcessingRhombus::drawRhombus((radius >> 1), __COLOR_BLACK, screenPixelPosition, -(((radius >> 1) + 4) >> 5));
}

/**
 * Helper function used by the rhombus emitter effect that prints a rhombus shape to the frame buffer
 *
 * @param radius
 * @param color
 * @param screenPixelPosition
 */
static void PostProcessingRhombus::drawRhombus(int radius, u32 color, PixelVector screenPixelPosition, int parallax)
{
	DirectDraw directDraw = DirectDraw::getInstance();

	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {screenPixelPosition.x - radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y - radius,	0, parallax},
		color
	);

	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {screenPixelPosition.x + radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y - radius,	0, parallax},
		color
	);

	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {screenPixelPosition.x + radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y + radius,	0, parallax},
		color
	);

	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {screenPixelPosition.x - radius,	screenPixelPosition.y,			0, parallax},
		(PixelVector) {screenPixelPosition.x,			screenPixelPosition.y + radius,	0, parallax},
		color
	);
}

