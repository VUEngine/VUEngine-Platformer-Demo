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

#include <Entity.h>
#include <MBgmapSprite.h>
#include <HbiasMaskMBgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 Level_1_Tower_MainTiles[];
extern uint16 Level_1_Tower_Main_1Map[];

extern BgmapSpriteROMSpec Level1TowerMainBack1Sprite;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec Level1TowerMainCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	46,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	Level_1_Tower_MainTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec Level1TowerMain1Texture =
{
	// charset spec
	(CharSetSpec*)&Level1TowerMainCharset,

	// bgmap spec
	Level_1_Tower_Main_1Map,

	// cols (max 64)
	48,

	// rows (max 64)
	64,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	0,

	// recyclable
	true,

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec* const Level1TowerMain1Textures[] =
{
	(TextureSpec*)&Level1TowerMain1Texture,
	NULL
};

MBgmapSpriteROMSpec Level1TowerMain1Sprite =
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

	(TextureSpec**)Level1TowerMain1Textures,

	// SCX/SCY (__WORLD_1x1, 1x2, 1x4, 1x8, 2x1, 2x2, 2x4, 4x1, 4x2, or 8x1)
	// textures must be 64x64 for anything other than 1x1
	__WORLD_1x1,

	// x loop
	false,

	// y loop
	false,

	/// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
	0,

	/// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
	0,
};

HbiasMaskMBgmapSpriteROMSpec Level1TowerMain1HotAirSprite =
{
	{
		{
			{
				// sprite's type
				__TYPE(HbiasMaskMBgmapSprite),

				// texture spec
				NULL,

				// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
				__TRANSPARENCY_NONE,

				// displacement
				{0, 0, -2, 0},
			},

			// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
			// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
			__WORLD_HBIAS,

			// pointer to affine/hbias manipulation function
			(ParamTableEffectMethod)HbiasMaskMBgmapSprite_wave,

			// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
			__WORLD_ON,
		},

		(TextureSpec**)Level1TowerMain1Textures,

		// SCX/SCY (__WORLD_1x1, 1x2, 1x4, 1x8, 2x1, 2x2, 2x4, 4x1, 4x2, or 8x1)
		// textures must be 64x64 for anything other than 1x1
		__WORLD_1x1,

		// x loop
		false,

		// y loop
		false,

		// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
		0,

		// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
		0
	},

	// name of the owner of the reference sprite
	"Main_1",

	// height of the effect
	50,

	// height addition
	0
};

BgmapSpriteROMSpec* const Level1TowerMain1Sprites[] =
{
	(BgmapSpriteROMSpec*)&Level1TowerMain1Sprite,
	(BgmapSpriteROMSpec*)&Level1TowerMainBack1Sprite,
	NULL
};

EntityROMSpec Level1TowerMain1Entity =
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
	(SpriteSpec**)Level1TowerMain1Sprites,

	// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec*)NULL,

	// collision shapes
	(ShapeSpec*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	(PhysicalSpecification*)NULL,
};
