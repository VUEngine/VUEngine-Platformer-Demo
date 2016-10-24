/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
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


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

u32 PostProcessingEffects_writeToFrameBuffer(u16 y, u16 shift, u32* columnSourcePointer, u32 previousSourcePointerValue);
void PostProcessingEffects_drawRhombus(fix19_13 radiusFix19_13, u32 color, VBVec3D spatialObjectPosition);


//---------------------------------------------------------------------------------------------------------
// 												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

/**
 * Uses directdraw to draw a rhombus around the spatialObject.
 * This effect only writes to the framebuffers, but does not read them. Since write access is much quicker
 * than reading, and since only a few pixels are affected, this effect runs well on hardware.
 *
 * @param currentDrawingFrameBufferSet  The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_rhombusEmitter(u32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject)
{
    u32 color;

    // runtime working variables
    static int radius = 16;

    if(!spatialObject || !*(u32*)spatialObject)
    {
        return;
    }

    VBVec3D spatialObjectPosition = *__VIRTUAL_CALL(SpatialObject, getPosition, spatialObject);
    extern const VBVec3D* _screenPosition;
	__OPTICS_NORMALIZE(spatialObjectPosition);

    // increase radius by 1 in each cycle
    radius++;

    // gradually decrease color with larger radius
    if(radius < 96)
    {
        color = __COLOR_BRIGHT_RED;
    }
    else if(radius < 140)
    {
        color = __COLOR_MEDIUM_RED;
    }
    else if(radius < 192)
    {
        color = __COLOR_DARK_RED;
    }
    else if(radius < 400)
    {
        // pause for a little bit before restarting
        return;
    }
    else
    {
        // reset radius when reaching a certain length
        radius = 16;
        return;
    }

    // draw rhombuses around object with given radius and color
    PostProcessingEffects_drawRhombus(ITOFIX19_13(radius), color, spatialObjectPosition);
	PostProcessingEffects_drawRhombus(ITOFIX19_13(radius >> 1), color, spatialObjectPosition);
	PostProcessingEffects_drawRhombus(ITOFIX19_13(radius >> 2), color, spatialObjectPosition);
}

/**
 * Applies a full screen wobble distortion that is reminiscent of water waves. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet  The framebuffer set that's currently being accessed
 */
void PostProcessingEffects_wobble(u32 currentDrawingFrameBufferSet, SpatialObject spatialObject __attribute__ ((unused)))
{
    u8 buffer = 0;
    u16 x = 0, y = 0;
    u32 previousSourcePointerValue = 0;

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
    for(; buffer < 2; buffer++)
    {
        // loop columns
        for(x = 0; x < 384; x++)
        {
            // get pointer to currently manipulated 32 bits of framebuffer
            u32* columnSourcePointer = (u32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0)) + (x << 4);

            // the shifted out pixels on top should be black
            previousSourcePointerValue = 0;

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
                previousSourcePointerValue = PostProcessingEffects_writeToFrameBuffer(y, waveLut[waveLutIndex], columnSourcePointer, previousSourcePointerValue);
            }
        }
    }

    // move the wave one pixel in the next frame
    waveLutIndex++;
}

/**
 * "Tilts" the game image by a few percent by gradually shifting columns. This effect reads and write
 * almost the whole screen and is therefore not feasible on hardware.
 *
 * @param currentDrawingFrameBufferSet  The framebuffer set that's currently being accessed
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
 * @param currentDrawingFrameBufferSet  The framebuffer set that's currently being accessed
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
         6,  6,
         8,  8,
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
 * @param currentDrawingFrameBufferSet  The framebuffer set that's currently being accessed
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
 * @param y                             Y coordinate (true y value = y * 16)
 * @param shift                         Number of bits to shift the pixels by
 * @param columnSourcePointer           Framebuffer address of the current column (x value)
 * @param previousSourcePointerValue    Value from the loop's previous cycle (effectively where y - 1)
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
        (VBVec2D) {spatialObjectPosition.x - radiusFix19_13,    spatialObjectPosition.y,                    spatialObjectPosition.z, 0},
        (VBVec2D) {spatialObjectPosition.x,                     spatialObjectPosition.y - radiusFix19_13,   spatialObjectPosition.z, 0},
        color
    );

    DirectDraw_drawLine(
        directDraw,
        (VBVec2D) {spatialObjectPosition.x + radiusFix19_13,    spatialObjectPosition.y,                    spatialObjectPosition.z, 0},
        (VBVec2D) {spatialObjectPosition.x,                     spatialObjectPosition.y - radiusFix19_13,   spatialObjectPosition.z, 0},
        color
    );

    DirectDraw_drawLine(
        directDraw,
        (VBVec2D) {spatialObjectPosition.x + radiusFix19_13,    spatialObjectPosition.y,                    spatialObjectPosition.z, 0},
        (VBVec2D) {spatialObjectPosition.x,                     spatialObjectPosition.y + radiusFix19_13,   spatialObjectPosition.z, 0},
        color
    );

    DirectDraw_drawLine(
        directDraw,
        (VBVec2D) {spatialObjectPosition.x - radiusFix19_13,    spatialObjectPosition.y,                    spatialObjectPosition.z, 0},
        (VBVec2D) {spatialObjectPosition.x,                     spatialObjectPosition.y + radiusFix19_13,   spatialObjectPosition.z, 0},
        color
    );
}
