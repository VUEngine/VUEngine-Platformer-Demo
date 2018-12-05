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

#ifndef HOT_AIR_M_BGMAP_SPRITE_H_
#define HOT_AIR_M_BGMAP_SPRITE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct HbiasMaskMBgmapSpriteSpec
{
	// super class spec
	MBgmapSpriteSpec mBgmapSpriteSpec;

	// name of the owner of the reference sprite
	char* referenceSpriteOwnerName;

	// height of the effect
	u16 effectHeight;

	// height addition
	u16 effectHeightExcess;

} HbiasMaskMBgmapSpriteSpec;

typedef const HbiasMaskMBgmapSpriteSpec HbiasMaskMBgmapSpriteROMSpec;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------





class HbiasMaskMBgmapSprite : MBgmapSprite
{
	/**
	* @var SpatialObject 	owner
	* @brief				owner
	* @memberof 			HbiasMaskMBgmapSprite
	*/
	Entity owner;
	/**
	* @var Sprite 	sprite
	* @brief		reference Sprite
	* @memberof 	HbiasMaskMBgmapSprite
	*/
	Sprite referenceSprite;
	/**
	* @var Sprite 	sprite
	* @brief		reference Sprite
	* @memberof 	HbiasMaskMBgmapSprite
	*/
	const HbiasMaskMBgmapSpriteSpec* hbiasMaskMBgmapSpriteSpec;
	/**
	* @var u8		step
	* @brief		current lut index
	* @memberof 	HbiasMaskMBgmapSprite
	*/
	u8 step;

	void constructor(const HbiasMaskMBgmapSpriteSpec* hbiasMaskMBgmapSpriteSpec, Object owner);
	s16 wave();
	override void render(bool evenFrame);
	override void position(const Vector3D* position);
	override void setMode(u16 display, u16 mode);
}


#endif
