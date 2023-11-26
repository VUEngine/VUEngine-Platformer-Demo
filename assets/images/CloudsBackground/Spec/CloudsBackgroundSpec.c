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

#include <AwesomeCloud.h>
#include <AwesomeCloudBgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 CloudsBackgroundTiles[];
extern uint16 CloudsBackgroundMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec CloudsBackgroundCharset =
{
	// number of chars in function of the number of frames to load at the same time
	1146/2,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	CloudsBackgroundTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec CloudsBackgroundTexture =
{
	// charset spec
	(CharSetSpec*)&CloudsBackgroundCharset,

	// bgmap spec
	CloudsBackgroundMap,

	// cols (max 64)
	64,

	// rows (max 64)
	64,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames
	1,

	// palette number (0-3)
	0,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

AwesomeCloudBgmapSpriteROMSpec CloudsBackgroundSprite =
{
	{
		{
			// sprite's type
			__TYPE(AwesomeCloudBgmapSprite),

			// texture spec
			(TextureSpec*)&CloudsBackgroundTexture,

			// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
			__TRANSPARENCY_NONE,

			// displacement
			{0, 0, 200, 0},
		},

		// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
		// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
		__WORLD_AFFINE,

		// pointer to affine/hbias manipulation function
		NULL,

		// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
		__WORLD_ON,
	},

	/// X Displacement each render cycle
	0,

	/// Y Displacement each render cycle
	1
};
SpriteROMSpec* const CloudsBackgroundSprites[] =
{
	(SpriteROMSpec*)&CloudsBackgroundSprite,
	NULL
};

AwesomeCloudROMSpec CloudsBackgroundEntity =
{
	// entity
	{
		// class allocator
		__TYPE(AwesomeCloud),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)CloudsBackgroundSprites,

		// use z displacement in projection
		false,
			
		/// meshes
		(WireframeSpec**)NULL,

		// collision shapes
		NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeNone,

		// physical specification
		NULL,
	},

	/// Rotation around x axis
	-108
};
