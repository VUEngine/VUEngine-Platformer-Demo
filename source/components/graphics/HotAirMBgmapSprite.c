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

#include <HotAirMBgmapSprite.h>
#include <Optics.h>
#include <Screen.h>
#include <BgmapTexture.h>
#include <Game.h>
#include <Entity.h>
#include <ParamTableManager.h>
#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
//											 CLASS' MACROS
//---------------------------------------------------------------------------------------------------------

#define EFFECT_HEIGHT 			64
#define EFFECT_HEIGHT_EXCESS	5


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

/**
 * @class	HotAirMBgmapSprite
 * @extends BgmapSprite
 * @brief	Sprite which holds a texture and a drawing specification.
 */
__CLASS_DEFINITION(HotAirMBgmapSprite, MBgmapSprite);
__CLASS_FRIEND_DEFINITION(Texture);
__CLASS_FRIEND_DEFINITION(BgmapTexture);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

// globals
extern const VBVec3D* _screenPosition;
extern Optical* _optical;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(HotAirMBgmapSprite, const HotAirMBgmapSpriteDefinition* hotAirMBgmapSpriteDefinition, Object owner)
__CLASS_NEW_END(HotAirMBgmapSprite, hotAirMBgmapSpriteDefinition, owner);

/**
 * Class constructor
 *
 * @memberof							HotAirMBgmapSprite
 * @public
 *
 * @param this							Function scope
 * @param mBgmapSpriteDefinition		Definition to use
 * @param owner							Sprite's owner
 */
void HotAirMBgmapSprite_constructor(HotAirMBgmapSprite this, const HotAirMBgmapSpriteDefinition* hotAirMBgmapSpriteDefinition, Object owner)
{
	__CONSTRUCT_BASE(MBgmapSprite, &hotAirMBgmapSpriteDefinition->mBgmapSpriteDefinition, owner);

	this->hotAirMBgmapSpriteDefinition = hotAirMBgmapSpriteDefinition;
	this->lavaSprite = NULL;
	this->referenceSprite = NULL;
}

/**
 * Class destructor
 *
 * @memberof		HotAirMBgmapSprite
 * @public
 *
 * @param this		Function scope
 */
void HotAirMBgmapSprite_destructor(HotAirMBgmapSprite this)
{
	ASSERT(this, "HotAirMBgmapSprite::destructor: null this");

	this->lavaSprite = NULL;
	this->referenceSprite = NULL;

	// destroy the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

/**
 * Write WORLD data to DRAM
 *
 * @memberof		HotAirMBgmapSprite
 * @public
 *
 * @param this		Function scope
 */
void HotAirMBgmapSprite_render(HotAirMBgmapSprite this)
{
	ASSERT(this, "HotAirMBgmapSprite::render: null this");

	// if render flag is set
	if(!this->texture || !this->worldLayer)
	{
		return;
	}

	if(!this->lavaSprite)
	{
		Entity referenceSpriteOwner = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), this->hotAirMBgmapSpriteDefinition->referenceSpriteOwnerName, true));

		if(referenceSpriteOwner)
		{
			this->referenceSprite = __SAFE_CAST(Sprite, VirtualList_front(Entity_getSprites(referenceSpriteOwner)));

			Entity lava = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), "Lava", true));

			if(lava)
			{
				VirtualNode node = VirtualList_begin(Entity_getSprites(lava));

				for(; node; node = VirtualNode_getNext(node))
				{
					this->lavaSprite = __SAFE_CAST(Sprite, VirtualNode_getData(node));

					extern TextureROMDef LAVA_TX;

					if(&LAVA_TX == Texture_getTextureDefinition(Sprite_getTexture(this->lavaSprite)))
					{
						break;
					}
				}
			}
		}
	}

	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesBaseAddress[this->worldLayer];

	if(!__IS_OBJECT_ALIVE(this->lavaSprite) || !__IS_OBJECT_ALIVE(this->referenceSprite))
	{
		this->lavaSprite = NULL;
		this->referenceSprite = NULL;

		worldPointer->head = __WORLD_OFF;
#ifdef __PROFILE_GAME
		worldPointer->w = 0;
		worldPointer->h = 0;
#endif

		return;
	}

	u16 laveSpriteGY = Sprite_getWorldGY(this->lavaSprite);

	WorldAttributes* referenceSpriteWorldPointer = &_worldAttributesBaseAddress[Sprite_getWorldLayer(this->referenceSprite)];

	// get coordinates
	worldPointer->gx = referenceSpriteWorldPointer->gx;
	worldPointer->gy = laveSpriteGY - EFFECT_HEIGHT > referenceSpriteWorldPointer->gy ? laveSpriteGY - EFFECT_HEIGHT : referenceSpriteWorldPointer->gy;
	worldPointer->gp = referenceSpriteWorldPointer->gp;

	if(laveSpriteGY < worldPointer->gy || __SCREEN_HEIGHT <= laveSpriteGY - EFFECT_HEIGHT || referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h < worldPointer->gy || __WORLD_OFF == referenceSpriteWorldPointer->head)
	{
		worldPointer->head = __WORLD_OFF;
#ifdef __PROFILE_GAME
		worldPointer->w = 0;
		worldPointer->h = 0;
#endif
		return;
	}

	worldPointer->mx = referenceSpriteWorldPointer->mx;
	worldPointer->my = referenceSpriteWorldPointer->my - referenceSpriteWorldPointer->gy + worldPointer->gy;
	worldPointer->mp = referenceSpriteWorldPointer->mp;

	worldPointer->w = referenceSpriteWorldPointer->w;
	worldPointer->h = laveSpriteGY - worldPointer->gy + EFFECT_HEIGHT_EXCESS;

	if(referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h < worldPointer->gy + worldPointer->h)
	{
		worldPointer->h = referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h - worldPointer->gy;
	}

	// set the head
	worldPointer->head = this->head | (__SAFE_CAST(BgmapTexture, this->texture))->segment;

	BgmapSprite_processHbiasEffects(__SAFE_CAST(BgmapSprite, this));
}

s16 HotAirMBgmapSprite_lavaHotAir(HotAirMBgmapSprite this)
{
	u32 param = BgmapSprite_getParam(__SAFE_CAST(BgmapSprite, this));
	s32 spriteHeight = Sprite_getWorldHeight(__SAFE_CAST(Sprite, this));
	s16 i = BgmapSprite_getParamTableRow(__SAFE_CAST(BgmapSprite, this));
	s16 j = 0;

	// look up table of wave shifts
	#define HBIAS_LAVA_HEAT_LUT_LENGTH 	32
	#define HBIAS_LAVA_HEAT_THROTTLE 	2
	const s16 lavaWaveLut[HBIAS_LAVA_HEAT_LUT_LENGTH] =
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
	step = (step < ((HBIAS_LAVA_HEAT_LUT_LENGTH << HBIAS_LAVA_HEAT_THROTTLE) - 1)) ? step + 1 : 0;

	// write param table rows
	for(j = 0; i < spriteHeight; i++, j++)
	{
		HbiasEntry* hbiasEntry = (HbiasEntry*)param;
		hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = lavaWaveLut[(i + (step >> HBIAS_LAVA_HEAT_THROTTLE)) % HBIAS_LAVA_HEAT_LUT_LENGTH];
		if((j < 8) && (hbiasEntry[i].offsetLeft < -1))
		{
			hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = hbiasEntry[i].offsetLeft + 2;
		}
		else if((j < 16) && (hbiasEntry[i].offsetLeft < 0))
		{
			hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = hbiasEntry[i].offsetLeft + 1;
		}
		else if((j < 16) && (hbiasEntry[i].offsetLeft > 0))
		{
			hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = hbiasEntry[i].offsetLeft - 1;
		}
	}

	// return 0 so this effect never stops
	return 0;
}
