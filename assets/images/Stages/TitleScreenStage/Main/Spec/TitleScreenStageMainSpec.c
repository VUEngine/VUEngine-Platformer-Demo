/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <BgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 TitleScreenStageMainTiles[];
extern uint16 TitleScreenStageMain1Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec TitleScreenStageMainCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	16,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	TitleScreenStageMainTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec TitleScreenStageMain1Texture =
{
	// charset spec
	(CharSetSpec*)&TitleScreenStageMainCharset,

	// bgmap spec
	TitleScreenStageMain1Map,

	// cols (max 64)
	48,

	// rows (max 64)
	8,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
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

BgmapSpriteROMSpec TitleScreenStageMain1Sprite =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&TitleScreenStageMain1Texture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{
			0, // x
			0, // y
			0, // z
			1, // parallax
		},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const TitleScreenStageMain1Sprites[] =
{
	&TitleScreenStageMain1Sprite,
	NULL
};

EntityROMSpec TitleScreenStageMain1Entity =
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
	(SpriteSpec**)TitleScreenStageMain1Sprites,

	// use z displacement in projection
	false,
			
	/// meshes
	(MeshSpec*)NULL,

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

