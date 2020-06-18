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

#include <HbiasMaskMBgmapSprite.h>
#include <Optics.h>
#include <Camera.h>
#include <BgmapTexture.h>
#include <Game.h>
#include <Entity.h>
#include <ParamTableManager.h>
#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

/**
 * @class	HbiasMaskMBgmapSprite
 * @extends BgmapSprite
 * @brief	Sprite which holds a texture and a drawing specification.
 */

friend class Sprite;
friend class Texture;
friend class BgmapTexture;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/**
 * Class constructor
 *
 * @memberof							HbiasMaskMBgmapSprite
 * @public
 *
 * @param this							Function scope
 * @param mBgmapSpriteSpec		Spec to use
 * @param owner							Sprite's owner
 */
void HbiasMaskMBgmapSprite::constructor(const HbiasMaskMBgmapSpriteSpec* hbiasMaskMBgmapSpriteSpec, Object owner)
{
	Base::constructor(&hbiasMaskMBgmapSpriteSpec->mBgmapSpriteSpec, owner);

	this->hbiasMaskMBgmapSpriteSpec = hbiasMaskMBgmapSpriteSpec;
	this->owner = NULL;
	this->referenceSprite = NULL;
	this->step = 0;
	this->owner = Entity::safeCast(owner);
}

/**
 * Class destructor
 *
 * @memberof		HbiasMaskMBgmapSprite
 * @public
 *
 * @param this		Function scope
 */
void HbiasMaskMBgmapSprite::destructor()
{
	this->owner = NULL;
	this->referenceSprite = NULL;

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void HbiasMaskMBgmapSprite::setPosition(const Vector3D* position)
{
	Base::setPosition(this, position);

	HbiasMaskMBgmapSprite::getReferenceSprite(this);
}

void HbiasMaskMBgmapSprite::setMode(u16 display, u16 mode __attribute__ ((unused)))
{
	this->head = display | __WORLD_HBIAS;
}

void HbiasMaskMBgmapSprite::getReferenceSprite()
{
	if(isDeleted(this->referenceSprite))
	{
		Container referenceSpriteOwner = Container::getChildByName(Container::safeCast(Game::getStage(Game::getInstance())), this->hbiasMaskMBgmapSpriteSpec->referenceSpriteOwnerName, true);

		if(!isDeleted(referenceSpriteOwner))
		{
			VirtualList referenceSpriteOwnerSpritesList = Entity::getSprites(referenceSpriteOwner);

			if(!isDeleted(referenceSpriteOwnerSpritesList))
			{
				this->referenceSprite = Sprite::safeCast(VirtualList::front(referenceSpriteOwnerSpritesList));
				this->position.z = Sprite::getDisplacedPosition(this->referenceSprite).z - 1;

				this->texture = Sprite::getTexture(this->referenceSprite);
				this->param = ParamTableManager::allocate(ParamTableManager::getInstance(), this);
			}
		}
	}
	else
	{
		this->position.z = Sprite::getDisplacedPosition(this->referenceSprite).z - 1;
	}
}

/**
 * Write WORLD data to DRAM
 *
 * @memberof		HbiasMaskMBgmapSprite
 * @public
 *
 * @param this		Function scope
 */
u16 HbiasMaskMBgmapSprite::doRender(u16 index, bool evenFrame __attribute__((unused)))
{
	HbiasMaskMBgmapSprite::getReferenceSprite(this);

	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesCache[index];

	if(isDeleted(this->owner) || isDeleted(this->referenceSprite))
	{
		this->referenceSprite = NULL;

#ifdef __PROFILE_GAME
		worldPointer->w = 0;
		worldPointer->h = 0;
#endif
		return __NO_RENDER_INDEX;
	}

	if(!this->referenceSprite->positioned || !this->referenceSprite->texture || !this->referenceSprite->texture->written)
	{
		return __NO_RENDER_INDEX;
	}

	VirtualList ownerSprites = Entity::getSprites(this->owner);

	u16 ownerSpriteGY = 0;
	bool ownerSpriteGYSet = false;

	if(ownerSprites)
	{
		Sprite ownerFirstSprite = VirtualList::front(ownerSprites);

		if(ownerFirstSprite && ownerFirstSprite != Sprite::safeCast(this))
		{
			ownerSpriteGY = Sprite::getWorldGY(ownerFirstSprite);
			ownerSpriteGYSet = true;
		}
	}

	if(!ownerSpriteGYSet)
	{
		Vector3D ownerPosition3D = Vector3D::getRelativeToCamera(*SpatialObject::getPosition(this->owner));
		PixelVector ownerPosition2D = Vector3D::projectToPixelVector(ownerPosition3D, 0);

		ownerSpriteGY = __FIX10_6_TO_I(ownerPosition2D.y);
	}

	u8 referenceSpriteWorldLayer = Sprite::getWorldLayer(this->referenceSprite);

	WorldAttributes* referenceSpriteWorldPointer = &_worldAttributesCache[referenceSpriteWorldLayer];

	// get coordinates
	worldPointer->gx = referenceSpriteWorldPointer->gx;
	worldPointer->gy = ownerSpriteGY - this->hbiasMaskMBgmapSpriteSpec->effectHeight > referenceSpriteWorldPointer->gy ? ownerSpriteGY - this->hbiasMaskMBgmapSpriteSpec->effectHeight : referenceSpriteWorldPointer->gy;
	worldPointer->gp = referenceSpriteWorldPointer->gp + this->displacement.parallax;

	if(__NO_RENDER_INDEX == (signed)referenceSpriteWorldLayer
    	||
		ownerSpriteGY < worldPointer->gy
		||
		_cameraFrustum->y1 <= ownerSpriteGY - this->hbiasMaskMBgmapSpriteSpec->effectHeight
		||
		referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h < worldPointer->gy
		||
		this->referenceSprite->hidden)
	{
#ifdef __PROFILE_GAME
		worldPointer->w = 0;
		worldPointer->h = 0;
#endif
		return __NO_RENDER_INDEX;
	}

	worldPointer->mx = referenceSpriteWorldPointer->mx;
	worldPointer->my = referenceSpriteWorldPointer->my - referenceSpriteWorldPointer->gy + worldPointer->gy;
	worldPointer->mp = referenceSpriteWorldPointer->mp;
	worldPointer->w = referenceSpriteWorldPointer->w;
	worldPointer->h = ownerSpriteGY - worldPointer->gy + this->hbiasMaskMBgmapSpriteSpec->effectHeightExcess;

	if(referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h < worldPointer->gy + worldPointer->h)
	{
		worldPointer->h = referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h - worldPointer->gy;
	}

	// set the head
	worldPointer->head = this->head | (BgmapTexture::safeCast(this->texture))->segment;
	worldPointer->param = (u16)(((this->param) - 0x20000) >> 1) & 0xFFF0;

	return index;
}

static s16 HbiasMaskMBgmapSprite::wave(BgmapSprite bgmapSprite)
{
	HbiasMaskMBgmapSprite this = HbiasMaskMBgmapSprite::safeCast(bgmapSprite);
	s32 spriteHeight = Sprite::getWorldHeight(this);
	s16 i = this->paramTableRow;
	s16 j = 0;

	// look up table of wave shifts
	#define HBIAS_LAVA_HEAT_LUT_LENGTH 	32
	#define HBIAS_LAVA_HEAT_THROTTLE 	2
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
		register s16 waveLutValue = lavaWaveLut[(i + (this->step >> HBIAS_LAVA_HEAT_THROTTLE)) % HBIAS_LAVA_HEAT_LUT_LENGTH];

		hbiasEntry[i].offsetLeft = waveLutValue;
		hbiasEntry[i].offsetRight = waveLutValue;

		if((j < 16) && (hbiasEntry[i].offsetLeft < 0))
		{
			hbiasEntry[i].offsetLeft = waveLutValue  + 1;
			hbiasEntry[i].offsetRight = waveLutValue + 1;
		}
	}

	// return 0 so this effect never stops
	return 0;
}
