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

#include <HbiasMaskMBgmapSprite.h>
#include <Optics.h>
#include <Camera.h>
#include <BgmapTexture.h>
#include <VUEngine.h>
#include <Entity.h>
#include <ParamTableManager.h>
#include <VirtualList.h>
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
void HbiasMaskMBgmapSprite::constructor(const HbiasMaskMBgmapSpriteSpec* hbiasMaskMBgmapSpriteSpec, ListenerObject owner)
{
	Base::constructor(&hbiasMaskMBgmapSpriteSpec->mBgmapSpriteSpec, owner);

	this->hbiasMaskMBgmapSpriteSpec = hbiasMaskMBgmapSpriteSpec;
	this->owner = NULL;
	this->referenceSprite = NULL;
	this->step = 0;
	this->owner = owner;
	this->spriteHeight = 0;
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

void HbiasMaskMBgmapSprite::registerWithManager()
{
	Base::registerWithManager(this);

	HbiasMaskMBgmapSprite::getReferenceSprite(this);
}

void HbiasMaskMBgmapSprite::getReferenceSprite()
{
	if(isDeleted(this->referenceSprite))
	{
		Container referenceSpriteOwner = Container::getChildByName(Container::safeCast(VUEngine::getStage(VUEngine::getInstance())), this->hbiasMaskMBgmapSpriteSpec->referenceSpriteOwnerName, true);

		if(!isDeleted(referenceSpriteOwner))
		{
			VirtualList referenceSpriteOwnerSpritesList = Entity::getSprites(referenceSpriteOwner);

			if(!isDeleted(referenceSpriteOwnerSpritesList))
			{
				this->referenceSprite = Sprite::safeCast(VirtualList::front(referenceSpriteOwnerSpritesList));
				this->position.z = Sprite::getDisplacedPosition(this->referenceSprite).z - 1;

				this->texture = Sprite::getTexture(this->referenceSprite);
				this->param = ParamTableManager::allocate(ParamTableManager::getInstance(), BgmapSprite::safeCast(this));
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
uint16 HbiasMaskMBgmapSprite::doRender(uint16 index, bool evenFrame __attribute__((unused)))
{
	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesCache[index];

	if(isDeleted(this->owner) || isDeleted(this->referenceSprite))
	{
		this->referenceSprite = NULL;

		return __NO_RENDER_INDEX;
	}

	if(!this->referenceSprite->positioned || !this->referenceSprite->texture || kTexturePendingWriting >= this->referenceSprite->texture->status)
	{
		return __NO_RENDER_INDEX;
	}

	VirtualList ownerSprites = Entity::getSprites(this->owner);

	uint16 ownerSpriteGY = 0;
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

	int16 referenceSpriteWorldLayer = Sprite::getIndex(this->referenceSprite);

	if(__NO_RENDER_INDEX == referenceSpriteWorldLayer || !(referenceSpriteWorldLayer > index))
	{
		return __NO_RENDER_INDEX;
	}

	WorldAttributes* referenceSpriteWorldPointer = &_worldAttributesCache[referenceSpriteWorldLayer];

	// get coordinates
	int16 gx = referenceSpriteWorldPointer->gx;
	int16 gy = ownerSpriteGY - this->hbiasMaskMBgmapSpriteSpec->effectHeight > referenceSpriteWorldPointer->gy ? ownerSpriteGY - this->hbiasMaskMBgmapSpriteSpec->effectHeight : referenceSpriteWorldPointer->gy;
	int16 gp = referenceSpriteWorldPointer->gp + this->displacement.parallax;

	if(
		ownerSpriteGY < gy
		||
		_cameraFrustum->y1 <= ownerSpriteGY - this->hbiasMaskMBgmapSpriteSpec->effectHeight
		||
		referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h < gy
		||
		!Sprite::isVisible(this->referenceSprite))
	{
		return __NO_RENDER_INDEX;
	}

	worldPointer->gx = gx;
	worldPointer->gy = gy;
	worldPointer->gp = gp;

	worldPointer->mx = referenceSpriteWorldPointer->mx;
	worldPointer->my = referenceSpriteWorldPointer->my - referenceSpriteWorldPointer->gy + worldPointer->gy;
	worldPointer->mp = referenceSpriteWorldPointer->mp;
	worldPointer->w = referenceSpriteWorldPointer->w;
	worldPointer->h = ownerSpriteGY - worldPointer->gy + this->hbiasMaskMBgmapSpriteSpec->effectHeightExcess;

	if(referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h < worldPointer->gy + worldPointer->h)
	{
		worldPointer->h = referenceSpriteWorldPointer->gy + referenceSpriteWorldPointer->h - worldPointer->gy;
	}

	this->spriteHeight = worldPointer->h;

	// set the head
	worldPointer->head = this->head | (BgmapTexture::safeCast(this->texture))->segment;
	worldPointer->param = (uint16)(((this->param) - 0x20000) >> 1) & 0xFFF0;

	return index;
}

static int16 HbiasMaskMBgmapSprite::wave(BgmapSprite bgmapSprite)
{
	HbiasMaskMBgmapSprite this = HbiasMaskMBgmapSprite::safeCast(bgmapSprite);

	int16 i = this->paramTableRow;
	int16 j = 0;

	// look up table of wave shifts
	#define HBIAS_LAVA_HEAT_LUT_LENGTH 	32
	#define HBIAS_LAVA_HEAT_THROTTLE 	2
	const int16 lavaWaveLut[HBIAS_LAVA_HEAT_LUT_LENGTH] =
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
	for(j = 0; i < this->spriteHeight; i++, j++)
	{
		register int16 waveLutValue = lavaWaveLut[(i + (this->step >> HBIAS_LAVA_HEAT_THROTTLE)) % HBIAS_LAVA_HEAT_LUT_LENGTH];

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
