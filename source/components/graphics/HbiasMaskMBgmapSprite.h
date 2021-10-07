/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
	uint16 effectHeight;

	// height addition
	uint16 effectHeightExcess;

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
	* @var uint8		step
	* @brief		current lut index
	* @memberof 	HbiasMaskMBgmapSprite
	*/
	uint8 step;

	static int16 wave(BgmapSprite bgmapSprite);

	void constructor(const HbiasMaskMBgmapSpriteSpec* hbiasMaskMBgmapSpriteSpec, Object owner);
	override uint16 doRender(uint16 index, bool evenFrame);
	override void setPosition(const PixelVector* position);
	override void setMode(uint16 display, uint16 mode);
}


#endif
