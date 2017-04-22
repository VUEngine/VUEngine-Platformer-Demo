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

#include <HbiasEffects.h>
#include <SpriteManager.h>
#include <ParamTableManager.h>


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

s16 HbiasEffects_logoWave(BgmapSprite bgmapSprite)
{
	u32 param = BgmapSprite_getParam(bgmapSprite);
	s16 spriteHeight = Sprite_getWorldHeight(__SAFE_CAST(Sprite, bgmapSprite));
	s16 i = BgmapSprite_getParamTableRow(bgmapSprite);
	// if you want to defer the effect, compute up to counter rows
	// int counter = SpriteManager_getMaximumParamTableRowsToComputePerCall(SpriteManager_getInstance());

	// look up table of wave shifts
	#define LOGO_WAVE_LUT_LENGTH 32
	const s16 logoWaveLut[LOGO_WAVE_LUT_LENGTH] =
	{
		-2, -2, -2, -2,
        -1, -1, -1,
        0, 0,
        1, 1, 1,
        2, 2, 2, 2,
        2, 2, 2, 2,
        1, 1, 1,
        0, 0,
        -1, -1, -1,
        -2, -2, -2, -2,
	};

	// look up table offset
	static u8 step = 0;
	step = (step < (LOGO_WAVE_LUT_LENGTH - 1)) ? step + 1 : 0;

	// if you want to defer the effect, compute up to counter rows
	// for(; counter && i < spriteHeight; i++, counter--)
	// write param table rows
	for(; i < spriteHeight; i++)
	{
		HbiasEntry* hbiasEntry = (HbiasEntry*)param;
		hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = logoWaveLut[(i + step) & (LOGO_WAVE_LUT_LENGTH - 1)];
	}

	// return 0 to ensure that this effect never finishes and thus runs continuously.
	// avoids having to call applyHbiasEffects manually every cycle.
	return 0;

	// return -1 if the last row was computed, or i (the last computed row) if not
	/*
	if(i < spriteHeight)
	{
		return i;
	}

	return -1;
	*/

	// if you want to bypass the deferring, just write the whole table without paying attention to the
	// value returned by SpriteManager_getMaximumParamTableRowsToComputePerCall and return -1
}
