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

#include <Clouds.h>
#include <Entity.h>
#include <MBgmapSprite.h>
#include <Entity.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE BackgroundMoundMiddleTiles[];
extern BYTE BackgroundMoundMiddleMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec MOUND_BG_MIDDLE_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	81,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	BackgroundMoundMiddleTiles,
};

TextureROMSpec MOUND_BG_MIDDLE_TX =
{
	// charset spec
	(CharSetSpec*)&MOUND_BG_MIDDLE_CH,

	// bgmap spec
	BackgroundMoundMiddleMap,

	// cols (max 64)
	64,

	// rows (max 64)
	4,

	// padding for affine/hbias transformations (cols, rows)
	{0, 1},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
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

TextureROMSpec* const MOUND_BG_MIDDLE_SB_TEXTURES[] =
{
	(TextureSpec*)&MOUND_BG_MIDDLE_TX,
	NULL
};

MBgmapSpriteROMSpec MOUND_BG_MIDDLE_SB_SPRITE =
{
	{
		{
			// sprite's type
			__TYPE(MBgmapSprite),

			// texture spec
			NULL,

			// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
			__TRANSPARENCY_NONE,

			// displacement
			{0, 0, 0, 0},
		},

		// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
		// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
		__WORLD_BGMAP,

		// pointer to affine/hbias manipulation function
		NULL,

		// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
		__WORLD_ON,
	},

	(TextureSpec**)MOUND_BG_MIDDLE_SB_TEXTURES,

	// SCX/SCY (__WORLD_1x1, 1x2, 1x4, 1x8, 2x1, 2x2, 2x4, 4x1, 4x2, or 8x1)
	// textures must be 64x64 for anything other than 1x1
	__WORLD_1x1,

	// x loop
	true,

	// y loop
	false,

	/// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
	0,

	/// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
	0,
};

BgmapSpriteROMSpec* const MOUND_BG_MIDDLE_SB_SPRITES[] =
{
	(BgmapSpriteROMSpec*)&MOUND_BG_MIDDLE_SB_SPRITE,
	NULL
};

EntityROMSpec MOUND_BG_MIDDLE_IM =
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
	(SpriteSpec**)MOUND_BG_MIDDLE_SB_SPRITES,

	// use z displacement in projection
	false,

	// collision shapes
	NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	NULL,
};

CloudsROMSpec CLOUDS_IM =
{
	{
		// class allocator
		__TYPE(Clouds),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)MOUND_BG_MIDDLE_SB_SPRITES,

		// use z displacement in projection
		false,

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

	// displacement per cycle in pixels
	1
};
