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
#include <Entity.h>
#include <Game.h>
#include <SpriteManager.h>
#include <ParamTableManager.h>


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

s16 HbiasEffects_smallWave(BgmapSprite bgmapSprite)
{
	u32 param = BgmapSprite_getParam(bgmapSprite);
	s32 spriteHeight = Texture_getRows(Sprite_getTexture(__SAFE_CAST(Sprite, bgmapSprite))) << 3;
	s16 i = BgmapSprite_getParamTableRow(bgmapSprite);
	// if you want to defer the effect, compute up to counter rows
	// int counter = SpriteManager_getMaximumParamTableRowsToComputePerCall(SpriteManager_getInstance());

	// look up table of wave shifts
	#define HBIAS_WAVE_LUT_LENGTH 	32
	#define HBIAS_WAVE_THROTTLE 	1
	const s16 smallWaveLut[HBIAS_WAVE_LUT_LENGTH] =
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
	step = (step < ((HBIAS_WAVE_LUT_LENGTH << HBIAS_WAVE_THROTTLE) - 1)) ? step + 1 : 0;

	// write param table rows
	// if you want to defer the effect, compute up to counter rows
	// for(; counter && i < spriteHeight; i++, counter--)
	// if you want to bypass the deferring, just write the whole table without paying attention to the
	// value returned by SpriteManager_getMaximumParamTableRowsToComputePerCall and return -1
	for(; i < spriteHeight; i++)
	{
		HbiasEntry* hbiasEntry = (HbiasEntry*)param;
		hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = smallWaveLut[((i + step) >> HBIAS_WAVE_THROTTLE) & (HBIAS_WAVE_LUT_LENGTH - 1)];
	}

	// Possible return values and their effects:
	//
	// 0:  forces the effect to be triggered on the next rendering cycle without having to call
	//     Sprite_applyHbiasEffects.
	//
	// >0: forces the effect to be triggered on the next rendering cycle without having to call
	//     Sprite_applyHbiasEffects. The returned value means the next param table row to compute.
	//     Only used when deferring the effect across multiple rendering cycles.
	//
	// -1: means that the param table writing has been completed. To trigger the effect again,
	//     Sprite_applyHbiasEffects must be called.

	return 0;

	/*
	if(i < spriteHeight)
	{
		return i;
	}

	return -1;
	*/
}

s16 HbiasEffects_lavaHotAir(BgmapSprite bgmapSprite)
{
	static Entity lava = NULL;

	if(!lava)
	{
		lava = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "Lava", true));
	}

	if(!__IS_OBJECT_ALIVE(lava))
	{
		lava = NULL;
		return 0;
	}

	Sprite lavaSprite = __SAFE_CAST(Sprite, VirtualList_front(Entity_getSprites(lava)));
	s16 laveSpriteGY = Sprite_getWorldGY(lavaSprite);

	u32 param = BgmapSprite_getParam(bgmapSprite);
	s16 spriteGY = Sprite_getWorldGY(__SAFE_CAST(Sprite, bgmapSprite));

	s32 spriteHeight = __SCREEN_HEIGHT; //Texture_getRows(Sprite_getTexture(__SAFE_CAST(Sprite, bgmapSprite))) << 3;
	s16 i = spriteGY;

	if (spriteGY > spriteHeight)
	{
		return 0;
	}

	// if you want to defer the effect, compute up to counter rows
	// int counter = SpriteManager_getMaximumParamTableRowsToComputePerCall(SpriteManager_getInstance());

	// look up table of wave shifts
	#define HBIAS_WAVE_LUT_LENGTH 	32
	#define HBIAS_WAVE_THROTTLE 	1
	const s16 smallWaveLut[HBIAS_WAVE_LUT_LENGTH] =
	{
        1, 1, 1, 1, 1,
        -1, -1, -1,
        0, 0,
        1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1,
        0, 0,
        -1, -1, -1,
        1, 1, 1, 1, 1
	};

	// look up table offset
	static u8 step = 0;
	step = (step < ((HBIAS_WAVE_LUT_LENGTH << HBIAS_WAVE_THROTTLE) - 1)) ? step + 1 : 0;

	// write param table rows
	// if you want to defer the effect, compute up to counter rows
	// for(; counter && i < spriteHeight; i++, counter--)
	// if you want to bypass the deferring, just write the whole table without paying attention to the
	// value returned by SpriteManager_getMaximumParamTableRowsToComputePerCall and return -1
	spriteHeight = spriteHeight < __SCREEN_HEIGHT ? spriteHeight : __SCREEN_HEIGHT;

	#define EFFECT_HEIGHT	50

	for(i = 0; i < (laveSpriteGY - spriteGY) - EFFECT_HEIGHT && i < (spriteHeight - spriteGY); i++)
	{
		HbiasEntry* hbiasEntry = (HbiasEntry*)param;
		hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = 0;
	}

	for(; i < (laveSpriteGY - spriteGY) && i < (spriteHeight - spriteGY); i++)
	{
		HbiasEntry* hbiasEntry = (HbiasEntry*)param;
		hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = smallWaveLut[((i + step) >> HBIAS_WAVE_THROTTLE) & (HBIAS_WAVE_LUT_LENGTH - 1)];
	}
/*
	for(; i < (spriteHeight - spriteGY); i++)
	{
		HbiasEntry* hbiasEntry = (HbiasEntry*)param;
		hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = 0;
	}
*/
	// Possible return values and their effects:
	//
	// 0:  forces the effect to be triggered on the next rendering cycle without having to call
	//     Sprite_applyHbiasEffects.
	//
	// >0: forces the effect to be triggered on the next rendering cycle without having to call
	//     Sprite_applyHbiasEffects. The returned value means the next param table row to compute.
	//     Only used when deferring the effect across multiple rendering cycles.
	//
	// -1: means that the param table writing has been completed. To trigger the effect again,
	//     Sprite_applyHbiasEffects must be called.

	return 0;

	/*
	if(i < spriteHeight)
	{
		return i;
	}

	return -1;
	*/
}
