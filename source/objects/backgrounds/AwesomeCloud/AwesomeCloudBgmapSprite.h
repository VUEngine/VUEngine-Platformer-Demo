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

#ifndef AWESOME_CLOUD_BGMAP_SPRITE_H_
#define AWESOME_CLOUD_BGMAP_SPRITE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <BgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/**
 * A AwesomeCloudBgmapSprite spec
 *
 * @memberof AwesomeCloudBgmapSprite
 */
typedef struct AwesomeCloudBgmapSpriteSpec
{
	/// the normal sprite spec
	BgmapSpriteSpec bgmapSpriteSpec;

	/// X Displacement each render cycle
	s16 mxStep;

	/// Y Displacement each render cycle
	s16 myStep;

} AwesomeCloudBgmapSpriteSpec;

/**
 * A AwesomeCloudBgmapSprite spec that is stored in ROM
 *
 * @memberof AwesomeCloudBgmapSprite
 */
typedef const AwesomeCloudBgmapSpriteSpec AwesomeCloudBgmapSpriteROMSpec;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/// @ingroup graphics-2d-sprites-bgmap
class AwesomeCloudBgmapSprite : BgmapSprite
{
	AwesomeCloudBgmapSpriteSpec* awesomeCloudBgmapSpriteSpec;

	/// @publicsection
	void constructor(const AwesomeCloudBgmapSpriteSpec* awesomeCloudBgmapSpriteSpec, Object owner);
	override void position(const Vector3D* position);
	override void setPosition(const PixelVector* position);
	override u16 doRender(u16 index, bool evenFrame);
}


#endif
