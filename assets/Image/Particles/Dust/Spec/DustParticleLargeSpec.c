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

#include <Libgccvb.h>
#include <Entity.h>
#include <ObjectSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 DustParticleLargeTiles[];
extern uint16 DustParticleLargeMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec DustParticleLargeCharset =
{
	// number of chars in function of the number of frames to load at the same time
	2,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	DustParticleLargeTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec DustParticleLargeTexture =
{
	// charset spec
	(CharSetSpec*)&DustParticleLargeCharset,

	// bgmap spec
	DustParticleLargeMap,

	// cols (max 64)
	1,

	// rows (max 64)
	1,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

ObjectSpriteROMSpec DustParticleLargeSprite =
{
	{
		// sprite's type
		__TYPE(ObjectSprite),

		// texture spec
		(TextureSpec*)&DustParticleLargeTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec* const DustParticleLargeSprites[] =
{
	&DustParticleLargeSprite,
	NULL
};

EntityROMSpec DustParticleLargeEntity =
{
	// class allocator
	__TYPE(Entity),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	(SpriteSpec**)DustParticleLargeSprites,

	// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec**)NULL,

	// collision shapes
	(ColliderSpec*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	(PhysicalProperties*)NULL,
};