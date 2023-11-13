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
#include <Lava.h>
#include <HbiasEffects.h>
#include <Box.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 LavaTiles[];
extern uint16 LavaMap[];

extern BgmapSpriteROMSpec Level1TowerBack1HotAirSprite;
extern BgmapSpriteROMSpec Level1TowerMain1HotAirSprite;
extern BgmapSpriteROMSpec Level1TowerMain2HotAirSprite;
extern BgmapSpriteROMSpec Level1TowerMainBack1HotAirSprite;
extern BgmapSpriteROMSpec Level1TowerMainBack2HotAirSprite;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec LavaCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	19,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	LavaTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec LavaTexture =
{
	// charset spec
	(CharSetSpec*)&LavaCharset,

	// bgmap spec
	LavaMap,

	// cols (max 64)
	48,

	// rows (max 64)
	24,

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

BgmapSpriteROMSpec LavaBgSprite =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LavaTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, -2, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_HBIAS,

	// pointer to affine/hbias manipulation function
	(ParamTableEffectMethod)HbiasEffects_wave,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const LavaBgSprites[] =
{
	&LavaBgSprite,
	&Level1TowerBack1HotAirSprite,
//	&Level1TowerMainBack1HotAirSprite,
	&Level1TowerMain1HotAirSprite,
//	&Level1TowerMainBack2HotAirSprite,
	&Level1TowerMain2HotAirSprite,
	NULL
};

ShapeROMSpec LavaShapes[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{48 * 8, 24 * 8, 2 * 8},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kLayerEnemies,

		/// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

LavaROMSpec LavaEntity =
{
	// class allocator
	__TYPE(Lava),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	(SpriteSpec**)LavaBgSprites,

	// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec*)NULL,

	// collision shapes
	(ShapeSpec*)LavaShapes,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeLava,

	// physical specification
	(PhysicalSpecification*)NULL,
};
