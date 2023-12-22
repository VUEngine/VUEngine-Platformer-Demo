/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HbiasEffects.h>
#include <Entity.h>
#include <VUEngine.h>
#include <SpriteManager.h>
#include <ParamTableManager.h>


//---------------------------------------------------------------------------------------------------------
//												FUNCTIONS
//---------------------------------------------------------------------------------------------------------

static int16 HbiasEffects::wave(BgmapSprite bgmapSprite)
{
	uint32 param = BgmapSprite::getParam(bgmapSprite);
	int32 spriteHeight = Texture::getRows(Sprite::getTexture(bgmapSprite)) << 3;
	int16 i = BgmapSprite::getParamTableRow(bgmapSprite);
	// if you want to defer the effect, compute up to counter rows
	// int counter = SpriteManager::getMaximumParamTableRowsToComputePerCall(SpriteManager::getInstance());

	// look up table of wave shifts
	#define HBIAS_WAVE_LUT_LENGTH 	32
	#define HBIAS_WAVE_THROTTLE 	2
	const int16 waveLut[HBIAS_WAVE_LUT_LENGTH] =
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
	static uint8 step = 0;
	step = (step < ((HBIAS_WAVE_LUT_LENGTH << HBIAS_WAVE_THROTTLE) - 1)) ? step + 1 : 0;

	HbiasEntry* hbiasEntry = (HbiasEntry*)param;
	// write param table rows
	// if you want to defer the effect, compute up to counter rows
	// for(; counter && i < spriteHeight; i++, counter--)
	// if you want to bypass the deferring, just write the whole table without paying attention to the
	// value returned by SpriteManager::getMaximumParamTableRowsToComputePerCall and return -1
	for(; i < spriteHeight; i++)
	{
		register int16 waveLutValue = waveLut[(i + (step >> HBIAS_WAVE_THROTTLE)) & (HBIAS_WAVE_LUT_LENGTH - 1)];
		hbiasEntry[i].offsetLeft = waveLutValue;
		hbiasEntry[i].offsetRight = waveLutValue;
	}

	// Possible return values and their effects:
	//
	// 0:  forces the effect to be triggered on the next rendering cycle without having to call
	//	 Sprite::applyHbiasEffects.
	//
	// >0: forces the effect to be triggered on the next rendering cycle without having to call
	//	 Sprite::applyHbiasEffects. The returned value means the next param table row to compute.
	//	 Only used when deferring the effect across multiple rendering cycles.
	//
	// -1: means that the param table writing has been completed. To trigger the effect again,
	//	 Sprite::applyHbiasEffects must be called.

	return 0;

	/*
	if(i < spriteHeight)
	{
		return i;
	}

	return -1;
	*/
}
