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
#include <macros.h>

//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_Main_1_Main_6Map[];

extern CharSetROMSpec Level1Main1MainCharset;

extern BgmapSpriteROMSpec Level1Main1MainBack6Sprite;
extern BgmapSpriteROMSpec Level1Main1MainFront6Sprite;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMSpec Level1Main1Main6Texture =
{
	// charset spec
	(CharSetSpec*)&Level1Main1MainCharset,

	// bgmap spec
	Level_1_Main_1_Main_6Map,

	// cols (max 64)
	64,

	// rows (max 64)
	34,

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

TextureROMSpec* const Level1Main1Main6Textures[] =
{
	(TextureSpec*)&Level1Main1Main6Texture,
	NULL
};

BgmapSpriteROMSpec Level1Main1Main6Sprite =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&Level1Main1Main6Texture,

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
};

BgmapSpriteROMSpec* const Level1Main1Main6Sprites[] =
{
	(BgmapSpriteROMSpec*)&Level1Main1Main6Sprite,
	(BgmapSpriteROMSpec*)&Level1Main1MainBack6Sprite,
	(BgmapSpriteROMSpec*)&Level1Main1MainFront6Sprite,
	NULL
};

EntityROMSpec Level1Main1Main6Entity =
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
	(SpriteSpec**)Level1Main1Main6Sprites,

	// use z displacement in projection
	false,

	// collision shapes
	(ShapeSpec*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNoShape,

	// physical specification
	(PhysicalSpecification*)NULL,
};
