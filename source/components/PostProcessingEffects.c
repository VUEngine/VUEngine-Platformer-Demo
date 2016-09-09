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


//---------------------------------------------------------------------------------------------------------
// 												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

void PostProcessingEffects_wobble(u32 currentDrawingFrameBufferSet)
{
    u8 buffer = 0;
    u16 x = 0, y = 0;
    u32 previousSourcePointerValue = 0, previousSourcePointerValueTemp = 0;

    // runtime working variables
    static int waveLutIndex = 0;

    // look up table of bitshifts performed on rows
    // values must be multiples of 2
    const u8 waveLut[128] =
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
        // get pointer to currently manipulated 32 bits of framebuffer
        u32* currentDrawingFrameBufferSetSourcePointer = (u32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));

        // loop columns
        for(x = 0; x < 384; x++)
        {
            // the shifted out pixels on top should be black
            previousSourcePointerValue = 0;

            // increase look up table index, wrap around if necessary
            waveLutIndex += (waveLutIndex < 127) ? 1 : -127;

            // we can skip further processing for the current column if no shifting would be done on it
            if(waveLut[waveLutIndex] == 0)
            {
                continue;
            }

            // loop pixels of current column
            // ignore the bottom 16 pixels of the screen (gui)
            for(y = 0; y < 13; y++)
            {
                // pointer to currently manipulated 32 bits of framebuffer
                u32* sourcePointer = currentDrawingFrameBufferSetSourcePointer + ((x << 4) + y);

                // save current pointer value to temp var and shift highest x bits of it, according to lut,
                // to the lowest bits, since we want to insert these
                previousSourcePointerValueTemp = (u32)(*sourcePointer) >> (32 - waveLut[waveLutIndex]);

                // manipulate current 32 bits in frame buffer
                *sourcePointer =
                    // shift bits according to wave lut
                    // it's two bits per pixel, so 2 bits shifted left = 1 pixel shifted down on screen
                    (*sourcePointer << (waveLut[waveLutIndex]))

                    // since the above shifting creates black pixels, we need to carry over these pixels
                    // from the previous loop
                    | previousSourcePointerValue;

                // we need the current source pointer value from _before_ we modified it, therefore we save it
                // it to a temp variable while modifying
                previousSourcePointerValue = previousSourcePointerValueTemp;
            }
        }
    }

    // move the wave one pixel in the next frame
    waveLutIndex++;
}

void PostProcessingEffects_tiltScreen(u32 currentDrawingFrameBufferSet)
{
    u8 x = 0;
    u16 y = 0;
    u32 previousSourcePointerValue = 0;
    u32 previousSourcePointerValueTemp = 0;
    u8 currentShift = 0;

    // write to framebuffers for both screens
    u32 buffer = 0;
    for(; buffer < 2; buffer++)
    {
        // loop columns, each column is 4 pixels wide
        for(x = 0; x < 96; x++)
        {
            // loop pixels of current column
            for(y = 0; y < 256; y += 4)
            {
                if((y & 63) == 0)
                {
                    // the shifted out pixels on top should be black
                    previousSourcePointerValue = 0;
                }
                else if((y & 63) > 48)
                {
                    // ignore the bottom 16 pixels of the screen (gui)
                    continue;
                }

                currentShift = (30 - ((x / 6) << 1));

                if (currentShift == 0)
                {
                    continue;
                }

                // pointer to currently manipulated 32 bits of framebuffer
                u32* sourcePointer = (u32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));
                sourcePointer += ((x << 6) + (y >> 2));

                // save current pointer value to temp var and shift highest x bits of it,
                // to the lowest bits, since we want to insert these
                previousSourcePointerValueTemp = (u32)(*sourcePointer) >> (32 - currentShift);

                // manipulate current 32 bits in frame buffer
                *sourcePointer =
                    // shift bits
                    // it's two bits per pixel, so 2 bits shifted left = 1 pixel shifted down on screen
                    (*sourcePointer << currentShift)

                    // since the above shifting creates black pixels, we need to carry over these pixels
                    // from the previous loop
                    | previousSourcePointerValue;

                // we need the current source pointer value from _before_ we modified it, therefore we save it
                // it to a temp variable while modifying
                previousSourcePointerValue = previousSourcePointerValueTemp;
            }
        }
    }
}

void PostProcessingEffects_dwarfPlanet(u32 currentDrawingFrameBufferSet)
{
    u8 buffer = 0;
    u16 x = 0, y = 0;
    u32 previousSourcePointerValue = 0, previousSourcePointerValueTemp = 0;

    // runtime working variables
    static int lutIndex = 0;

    // look up table of bitshifts performed on rows
    const u8 lut[96] =
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
        u32* currentDrawingFrameBufferSetSourcePointer = (u32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));

        // loop columns of left fourth of screen
        for(x = 0; x < 96; x++)
        {
            // the shifted out pixels on top should be black
            previousSourcePointerValue = 0;

            // loop pixels of current column
            // ignore the bottom 16 pixels of the screen (gui)
            for(y = 0; y < 13; y++)
            {
                // set pointer to currently manipulated 32 bits of framebuffer
                u32* sourcePointer = currentDrawingFrameBufferSetSourcePointer + ((x << 4) + y);

                // save current pointer value to temp var and shift highest x bits of it, according to lut,
                // to the lowest bits, since we want to insert these
                previousSourcePointerValueTemp = (u32)(*sourcePointer) >> (lut[lutIndex]);

                // manipulate current 32 bits in frame buffer
                *sourcePointer =
                    // shift bits according to effect lut
                    // it's two bits per pixel, so 2 bits shifted left = 1 pixel shifted down on screen
                    (*sourcePointer << (32 - lut[lutIndex]))

                    // since the above shifting creates black pixels, we need to carry over these pixels
                    // from the previous loop
                    | previousSourcePointerValue;

                // we need the current source pointer value from _before_ we modified it, therefore we save it
                // it to a temp variable while modifying
                previousSourcePointerValue = previousSourcePointerValueTemp;
            }

            // iterate lut from left to right
            lutIndex++;
        }

        // loop columns of right fourth of screen
        for(x = 288; x < 384; x++)
        {
            // the shifted out pixels on top should be black
            previousSourcePointerValue = 0;

            // iterate lut back from right to left
            lutIndex--;

            // loop pixels of current column
            // ignore the bottom 16 pixels of the screen (gui)
            for(y = 0; y < 13; y++)
            {
                // pointer to currently manipulated 32 bits of framebuffer
                u32* sourcePointer = currentDrawingFrameBufferSetSourcePointer + ((x << 4) + y);

                // save current pointer value to temp var and shift highest x bits of it, according to lut,
                // to the lowest bits, since we want to insert these
                previousSourcePointerValueTemp = (u32)(*sourcePointer) >> (lut[lutIndex]);

                // manipulate current 32 bits in frame buffer
                *sourcePointer =
                    // shift bits according to effect lut
                    // it's two bits per pixel, so 2 bits shifted left = 1 pixel shifted down on screen
                    (*sourcePointer << (32 - lut[lutIndex]))

                    // since the above shifting creates black pixels, we need to carry over these pixels
                    // from the previous loop
                    | previousSourcePointerValue;

                // we need the current source pointer value from _before_ we modified it, therefore we save it
                // it to a temp variable while modifying
                previousSourcePointerValue = previousSourcePointerValueTemp;
            }
        }
    }
}

void PostProcessingEffects_fullScreenWeirdness(u32 currentDrawingFrameBufferSet)
{
    // the pixel in screen coordinates (x: 0 - 383, y: 0 - 223)
    int x = 0;
    int y = 0;
    u32 lastPart;

    // write to framebuffers for both screens
    u32 buffer = 0;
    static int randomDelay = 0;
    static bool dontApply = false;

    // remove me
    if(dontApply)
    {
        return;
    }

    if(--randomDelay  < 0)
    {
        dontApply = !dontApply;
        randomDelay = Utilities_random(Utilities_randomSeed(), dontApply ? 205 : 150);
    }

    /*
    // uncomment me: although the intended randomness doesn't work

    if(dontApply)
    {
        return;
    }
    */

    for(; buffer < 2; buffer++)
    {
        for(x = 0; x < 384; x+=4)
        {
            for(y = 0; y < 224; y+=4)
            {
                u32* sourcePointer = (u32*) (currentDrawingFrameBufferSet | (buffer ? 0x00010000 : 0));
                sourcePointer += ((x << 6) + y);

                lastPart = *sourcePointer;

                *sourcePointer = (*sourcePointer << 2) | (lastPart & 3);
                //*sourcePointer &= *sourcePointer;
            }
        }
    }
}

void PostProcessingEffects_lightingTest(u32 currentDrawingFrameBufferSet)
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
    heroPosition.x = FIX19_13TOI(heroPosition.x);
    heroPosition.y = FIX19_13TOI(heroPosition.y);

    for(; buffer < 2; buffer++)
    {
        for(xCounter = 48, x = heroPosition.x - xCounter / 2; xCounter--; x++)
        {
            for(yCounter = 48, y = heroPosition.y - yCounter / 2; yCounter >= 0; yCounter -= 4, y += 4)
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
                    if(xCounter % 2)
                    {
                        // shift down one pixel
                        *sourcePointer = (*sourcePointer & 0x03)| (*sourcePointer << 2);
                    }
                    else
                    {
                        // shift up one pixel
                        *sourcePointer = (*sourcePointer & 0xC0)| (*sourcePointer >> 2);
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
