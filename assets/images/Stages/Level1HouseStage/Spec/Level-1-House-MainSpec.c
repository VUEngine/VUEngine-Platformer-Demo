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
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_House_MainTiles[];
extern BYTE Level_1_House_MainMap[];

extern BgmapSpriteROMSpec LEVEL_1_HOUSE_PIPE_IM_SPRITE;
extern BgmapSpriteROMSpec LEVEL_1_HOUSE_FIREPLACE_IM_SPRITE;
extern BgmapSpriteROMSpec LEVEL_1_HOUSE_OVERLAY_IM_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec LEVEL_1_HOUSE_MAIN_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	31,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	Level_1_House_MainTiles,
};

TextureROMSpec LEVEL_1_HOUSE_MAIN_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_HOUSE_MAIN_CH,

	// bgmap spec
	Level_1_House_MainMap,

	// cols (max 64)
	18,

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

BgmapSpriteROMSpec LEVEL_1_HOUSE_MAIN_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_HOUSE_MAIN_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 16, 32, 2},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const LEVEL_1_HOUSE_MAIN_IM_SPRITES[] =
{
	&LEVEL_1_HOUSE_MAIN_IM_SPRITE,
	&LEVEL_1_HOUSE_PIPE_IM_SPRITE,
	&LEVEL_1_HOUSE_FIREPLACE_IM_SPRITE,
	&LEVEL_1_HOUSE_OVERLAY_IM_SPRITE,
	NULL
};

EntityROMSpec LEVEL_1_HOUSE_MAIN_IM =
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
	(SpriteSpec**)LEVEL_1_HOUSE_MAIN_IM_SPRITES,

	// use z displacement in projection
	false,

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
