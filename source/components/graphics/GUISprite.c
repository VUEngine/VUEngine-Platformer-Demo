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

#include <GUISprite.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

/**
 * @class 	GUISprite
 * @extends BgmapAnimatedSprite
 * @ingroup graphics-2d-sprites-bgmap
 */


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern int strcmp(const char *, const char *);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other



/**
 * Class constructor
 *
 * @memberof						GUISprite
 * @public
 *
 * @param this						Function scope
 * @param bgmapSpriteDefinition		Sprite definition
 * @param owner						Owner
 */
void GUISprite::constructor(GUISprite this, const BgmapSpriteDefinition* bgmapSpriteDefinition, Object owner)
{
	ASSERT(this, "GUISprite::constructor: null this");

	// construct base object
	Base::constructor(bgmapSpriteDefinition, owner);
}


/**
 * Class destructor
 *
 * @memberof						GUISprite
 * @public
 *
 * @param this						Function scope
 */
void GUISprite::destructor(GUISprite this)
{
	ASSERT(this, "GUISprite::destructor: null this");

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

/**
 * Render
 *
 * @memberof		GUISprite
 * @public
 *
 * @param this		Function scope
 * @param evenFrame
 */
void GUISprite::render(GUISprite this, bool evenFrame)
{
	ASSERT(this, "GUISprite::render: null this");

	Base::render(this, evenFrame);

	if(!this->positioned)
	{
		return;
	}

	if(!this->worldLayer)
	{
		return;
	}

	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesBaseAddress[this->worldLayer];

	// set the head
	worldPointer->head = this->head | BgmapTexture::getSegment(__SAFE_CAST(BgmapTexture, this->texture));

	// get coordinates
	worldPointer->gx = this->position.x + this->displacement.x - this->halfWidth;
	worldPointer->gy = this->position.y + this->displacement.y - this->halfHeight;
	worldPointer->gp = this->position.parallax + this->displacement.parallax;

	worldPointer->mx = this->drawSpec.textureSource.mx;
	worldPointer->my = this->drawSpec.textureSource.my;
	worldPointer->mp = this->drawSpec.textureSource.mp;

	worldPointer->w = this->halfWidth << 1;
	worldPointer->h = this->halfHeight << 1;
}
