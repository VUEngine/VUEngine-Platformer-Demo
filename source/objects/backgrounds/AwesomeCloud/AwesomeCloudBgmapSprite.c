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
 * Set 2D position
 *
 * @memberof			BgmapSprite
 * @public
 *
 * @param position		New 2D position
 */
void AwesomeCloudBgmapSprite::setPosition(const PixelVector* position)
{
	Base::setPosition(this, position);
}


/**
 * Write WORLD data to DRAM
 *
 * @memberof		AwesomeCloudBgmapSprite
 * @public
 *
 * @param evenFrame
 */
void AwesomeCloudBgmapSprite::render(bool evenFrame __attribute__ ((unused)))
{
	this->drawSpec.textureSource.my += this->awesomeCloudBgmapSpriteSpec->myStep;

	if((u16)this->drawSpec.textureSource.my >= (BgmapTexture::getYOffset(this->texture) << 3) + (BgmapTexture::getRows(this->texture) << 3))
	{
		this->drawSpec.textureSource.my = (BgmapTexture::getYOffset(this->texture) << 3);
	}

	BgmapSprite::invalidateParamTable(this);

	Base::render(this, evenFrame);

	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesBaseAddress[this->worldLayer];

	//worldPointer->gx -= 20;
	//worldPointer->w = __SCREEN_WIDTH + 19;
}

