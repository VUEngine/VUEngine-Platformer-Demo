/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
	int16 mxStep;

	/// Y Displacement each render cycle
	int16 myStep;

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
	override uint16 doRender(uint16 index, bool evenFrame);
}


#endif
