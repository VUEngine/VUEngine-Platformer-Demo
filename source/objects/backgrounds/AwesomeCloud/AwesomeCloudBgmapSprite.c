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

#include <AwesomeCloudBgmapSprite.h>
#include <BgmapTexture.h>


//---------------------------------------------------------------------------------------------------------
//											 CLASS' MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/**
 * Class constructor
 *
 * @memberof							AwesomeCloudBgmapSprite
 * @public
 *
 * @param AwesomeCloudBgmapSpriteSpec		Spec to use
 * @param owner							Sprite's owner
 */
void AwesomeCloudBgmapSprite::constructor(const AwesomeCloudBgmapSpriteSpec* awesomeCloudBgmapSpriteSpec, Object owner)
{
	Base::constructor(&awesomeCloudBgmapSpriteSpec->bgmapSpriteSpec, owner);

	this->awesomeCloudBgmapSpriteSpec = (AwesomeCloudBgmapSpriteSpec*)awesomeCloudBgmapSpriteSpec;
}

/**
 * Class destructor
 *
 * @memberof		AwesomeCloudBgmapSprite
 * @public
 */
void AwesomeCloudBgmapSprite::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}


/**
 * Calculate 2D position
 *
 * @memberof			AwesomeCloudBgmapSprite
 * @public
 *
 * @param position		3D position
 */
void AwesomeCloudBgmapSprite::position(const Vector3D* position)
{
	Base::position(this, position);
}

/**
 * Write WORLD data to DRAM
 *
 * @memberof		AwesomeCloudBgmapSprite
 * @public
 */
uint16 AwesomeCloudBgmapSprite::doRender(uint16 index, bool evenFrame)
{
	this->drawSpec.textureSource.my += this->awesomeCloudBgmapSpriteSpec->myStep;

	if((uint16)this->drawSpec.textureSource.my >= (BgmapTexture::getYOffset(this->texture) << 3) + (BgmapTexture::getRows(this->texture) << 3))
	{
		this->drawSpec.textureSource.my = (BgmapTexture::getYOffset(this->texture) << 3);
	}

	BgmapSprite::invalidateParamTable(this);

	uint16 result = Base::doRender(this, index, evenFrame);

	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesBaseAddress[index];

	//worldPointer->gx -= 20;
	//worldPointer->w = __SCREEN_WIDTH + 19;
	worldPointer->h -= 4;

//	Sprite::print(this, 20, 1);
	return result;
}

