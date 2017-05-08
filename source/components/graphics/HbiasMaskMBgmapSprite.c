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

#include <HbiasMaskMBgmapSprite.h>
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


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

/**
 * @class	HbiasMaskMBgmapSprite
 * @extends BgmapSprite
 * @brief	Sprite which holds a texture and a drawing specification.
 */
__CLASS_DEFINITION(HbiasMaskMBgmapSprite, MBgmapSprite);
__CLASS_FRIEND_DEFINITION(Texture);
__CLASS_FRIEND_DEFINITION(BgmapTexture);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

// globals


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(HbiasMaskMBgmapSprite, const HbiasMaskMBgmapSpriteDefinition* hotAirMBgmapSpriteDefinition, Object owner)
__CLASS_NEW_END(HbiasMaskMBgmapSprite, hotAirMBgmapSpriteDefinition, owner);

/**
 * Class constructor
 *
 * @memberof							HbiasMaskMBgmapSprite
 * @public
 *
 * @param this							Function scope
 * @param mBgmapSpriteDefinition		Definition to use
 * @param owner							Sprite's owner
 */
void HbiasMaskMBgmapSprite_constructor(HbiasMaskMBgmapSprite this, const HbiasMaskMBgmapSpriteDefinition* hotAirMBgmapSpriteDefinition, Object owner)
{
	__CONSTRUCT_BASE(MBgmapSprite, &hotAirMBgmapSpriteDefinition->mBgmapSpriteDefinition, owner);

	this->hotAirMBgmapSpriteDefinition = hotAirMBgmapSpriteDefinition;
	this->owner = NULL;
	this->referenceSprite = NULL;
	this->step = 0;
	this->owner = __SAFE_CAST(Entity, owner);
}

/**
 * Class destructor
 *
 * @memberof		HbiasMaskMBgmapSprite
 * @public
 *
 * @param this		Function scope
 */
void HbiasMaskMBgmapSprite_destructor(HbiasMaskMBgmapSprite this)
{
	ASSERT(this, "HbiasMaskMBgmapSprite::destructor: null this");

	this->owner = NULL;
	this->referenceSprite = NULL;

	// destroy the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

/**
 * Write WORLD data to DRAM
 *
 * @memberof		HbiasMaskMBgmapSprite
 * @public
 *
 * @param this		Function scope
 */
void HbiasMaskMBgmapSprite_render(HbiasMaskMBgmapSprite this)
{
	ASSERT(this, "HbiasMaskMBgmapSprite::render: null this");

	// if render flag is set
	if(!this->texture || !this->worldLayer || !this->owner)
	{
		return;
	}

	if(!__IS_OBJECT_ALIVE(this->referenceSprite))
	{
		Container referenceSpriteOwner = Container_getChildByName(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), this->hotAirMBgmapSpriteDefinition->referenceSpriteOwnerName, true);

		if(__IS_OBJECT_ALIVE(referenceSpriteOwner))
		{
			this->referenceSprite = __SAFE_CAST(Sprite, VirtualList_front(Entity_getSprites(__SAFE_CAST(Entity, referenceSpriteOwner))));
		}
	}

	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesBaseAddress[this->worldLayer];

	if(!__IS_OBJECT_ALIVE(this->owner) || !__IS_OBJECT_ALIVE(this->referenceSprite))
	{
		this->owner = NULL;
		this->referenceSprite = NULL;

		worldPointer->head = __WORLD_OFF;
#ifdef __PROFILE_GAME
		worldPointer->w = 0;
		worldPointer->h = 0;
#endif
		return;
	}

	VirtualList ownerSprites = Entity_getSprites(this->owner);

	u16 ownerSpriteGY = 0;
	bool ownerSpriteGYSet = false;

	if(ownerSprites)
	{
		Sprite ownerFirstSprite = VirtualList_front(ownerSprites);

		if(ownerFirstSprite && ownerFirstSprite != this)
		{
			ownerSpriteGY = Sprite_getWorldGY(ownerFirstSprite);
			ownerSpriteGYSet = true;
		}
	}

	if(!ownerSpriteGYSet)
	{
		VBVec3D ownerPosition3D = *__VIRTUAL_CALL(SpatialObject, getPosition, this->owner);
		__OPTICS_NORMALIZE(ownerPosition3D);

		VBVec3D ownerPosition2D;
		__OPTICS_PROJECT_TO_2D(ownerPosition3D, ownerPosition2D);

		ownerSpriteGY = FIX19_13TOI(ownerPosition2D.y);
	}

	u8 referenceSpriteWorldLayer = Sprite_getWorldLayer(this->referenceSprite);

	WorldAttributes* referenceSpriteWorldPointer = &_worldAttributesBaseAddress[referenceSpriteWorldLayer];

	// get coordinates
	worldPointer->gx = referenceSpriteWorldPointer->gx;
	worldPointer->gy = ownerSpriteGY - this->hotAirMBgmapSpriteDefinition->effectHeight > referenceSpriteWorldPointer->gy ? ownerSpriteGY - this->hotAirMBgmapSpriteDefinition->effectHeight : referenceSpriteWorldPointer->gy;
	worldPointer->gp = referenceSpriteWorldPointer->gp + FIX19_13TOI((this->displacement.z + this->displacement.p) & 0xFFFFE000);


	if(!referenceSpriteWorldLayer
    	||
    	!Texture_isWritten(Sprite_getTexture(this->referenceSprite))
    	||
		ownerSpriteGY < worldPointer->gy
		||
		_cameraFrustum->y1 <= ownerSpriteGY - this->hotAirMBgmapSpriteDefinition->effectHeight
		||
		referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h < worldPointer->gy
		||
		__WORLD_OFF == referenceSpriteWorldPointer->head)
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
	worldPointer->h = ownerSpriteGY - worldPointer->gy + this->hotAirMBgmapSpriteDefinition->effectHeightExcess;

	if(referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h < worldPointer->gy + worldPointer->h)
	{
		worldPointer->h = referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h - worldPointer->gy;
	}

	// set the head
	worldPointer->head = this->head | (__SAFE_CAST(BgmapTexture, this->texture))->segment;

	BgmapSprite_processHbiasEffects(__SAFE_CAST(BgmapSprite, this));
}

s16 HbiasMaskMBgmapSprite_wave(HbiasMaskMBgmapSprite this)
{
	s32 spriteHeight = Sprite_getWorldHeight(__SAFE_CAST(Sprite, this));
	s16 i = this->paramTableRow;
	s16 j = 0;

	// look up table of wave shifts
	#define HBIAS_LAVA_HEAT_LUT_LENGTH 	32
	#define HBIAS_LAVA_HEAT_THROTTLE 	1
	const s16 lavaWaveLut[HBIAS_LAVA_HEAT_LUT_LENGTH] =
	{
		-1, -1, -1, -1, -1, -1,
		 0,  0,  0,  0,
		 1,  1,  1,  1,  1,  1,
		 1,  1,  1,  1,  1,  1,
		 0,  0,  0,  0,
		-1, -1, -1, -1, -1, -1,
	};

	// look up table offset
	this->step = (this->step < ((HBIAS_LAVA_HEAT_LUT_LENGTH << HBIAS_LAVA_HEAT_THROTTLE) - 1)) ? this->step + 1 : 0;

	HbiasEntry* hbiasEntry = (HbiasEntry*)this->param;

	// write param table rows
	for(j = 0; i < spriteHeight; i++, j++)
	{
		hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = lavaWaveLut[(i + (this->step >> HBIAS_LAVA_HEAT_THROTTLE)) % HBIAS_LAVA_HEAT_LUT_LENGTH];
		if((j < 16) && (hbiasEntry[i].offsetLeft < 0))
		{
			hbiasEntry[i].offsetLeft = hbiasEntry[i].offsetRight = hbiasEntry[i].offsetLeft + 1;
		}
	}

	// return 0 so this effect never stops
	return 0;
}