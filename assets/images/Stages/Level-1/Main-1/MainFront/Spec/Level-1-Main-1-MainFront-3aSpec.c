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

#include <MBgmapSprite.h>

//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_Main_1_MainFront_3aMap[];
extern CharSetROMSpec LEVEL_1_MAIN_1_MAIN_FRONT_CH;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMSpec LEVEL_1_MAIN_1_MAIN_FRONT_3A_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_MAIN_1_MAIN_FRONT_CH,

	// bgmap spec
	Level_1_Main_1_MainFront_3aMap,

	// cols (max 64)
	50,

	// rows (max 64)
	10,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	true,

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec* const LEVEL_1_MAIN_1_MAIN_FRONT_3A_IM_TEXTURES[] =
{
	(TextureSpec*)&LEVEL_1_MAIN_1_MAIN_FRONT_3A_TX,
	NULL
};

BgmapSpriteROMSpec LEVEL_1_MAIN_1_MAIN_FRONT_3A_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_MAIN_1_MAIN_FRONT_3A_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{-8, 24, -1, -1},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};
