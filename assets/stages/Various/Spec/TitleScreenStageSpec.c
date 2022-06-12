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

#include <Stage.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <VIPManager.h>
#include <Fonts.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntitySpec BushEntity;
extern EntitySpec CloudsEntity;
extern EntitySpec CoinEntity;
extern EntitySpec GrassEntity;
extern EntitySpec HeroBandanaEntity;
extern EntitySpec LogoEntity;
extern EntitySpec LowPowerIndicatorEntity;
extern EntitySpec MoundBgBackEntity;
extern EntitySpec MoundBgCastleFlagEntity;
extern EntitySpec MoundBgCastleEntity;
extern EntitySpec MoundBgFrontEntity;
extern EntitySpec StarEntity;
extern EntitySpec TitleScreenStageMain1Entity;
extern EntitySpec TitleScreenStageMainFront1Entity;
extern EntitySpec VUEngineLogoEntity;
extern TextureSpec LogoLTexture;
extern TextureSpec LogoOutlineLTexture;
extern TextureSpec LogoOutlineRTexture;
extern TextureSpec LogoRTexture;
extern EntitySpec CloudsBackgroundEntity;

//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec TitleScreenStageEntities[] =
{
	{&LowPowerIndicatorEntity, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
//	{&CloudsBackgroundEntity, 				{192, 112 - 112/2 - 12, LAYER_3, 0}, 		0, NULL, NULL, NULL, true}, // Front
	{&MoundBgFrontEntity, 					{  0, 136, LAYER_2, 0}, 		0, NULL, NULL, NULL, false}, // Front
	{&GrassEntity, 							{ 32, 152, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Grass
	{&CoinEntity, 								{ 56, 134, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Coin
	{&CoinEntity, 								{ 72, 134, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Coin
	{&TitleScreenStageMain1Entity, 		{192, 168, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Main Layer
	{&LogoEntity, 								{192,  53, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Logo
	{&VUEngineLogoEntity, 					{192,  18, LAYER_1, 0}, 		0, NULL, NULL, NULL, false}, // VUEngine
	{&HeroBandanaEntity, 						{192, 157, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Hero
	{&TitleScreenStageMainFront1Entity, 	{192, 168, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Main Layer Front
	{&CloudsEntity, 							{194, 128, LAYER_4, 0}, 		0, NULL, NULL, NULL, false}, // Clouds
	{&MoundBgBackEntity, 					{280,  72, LAYER_5, 0}, 		0, NULL, NULL, NULL, false}, // Mountains
	{&MoundBgCastleEntity, 					{300, 104, LAYER_2 + 32, 0}, 	0, NULL, NULL, NULL, false}, // Castle
	{&MoundBgCastleFlagEntity, 				{274,  85, LAYER_2 + 32, 0}, 	0, NULL, NULL, NULL, false}, // Castle Flag L
	{&MoundBgCastleFlagEntity, 				{304,  95, LAYER_2 + 32, 0}, 	0, NULL, NULL, NULL, false}, // Castle Flag M
	{&MoundBgCastleFlagEntity, 				{334,  85, LAYER_2 + 32, 0}, 	0, NULL, NULL, NULL, false}, // Castle Flag R
	{&StarEntity, 								{392,  16, LAYER_5 - 1, 0},		0, NULL, NULL, NULL, false}, // Star
	{&BushEntity, 								{368, 148, LAYER_0, 0},			0, NULL, NULL, NULL, false}, // Bush

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec TitleScreenStageUiEntities[] =
{
	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const TitleScreenStageFonts[] =
{
	NULL
};

TextureSpec* const TitleScreenStageTextures[] =
{
	NULL
};


extern Sound Soundtrack01;

SoundROM* const TitleScreenStageSounds[] =
{
	&Soundtrack01,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec TitleScreenStage =
{
	// allocator
	__TYPE(Stage),

	// Timer config
	{
		__TIMER_100US,
		10,
		kMS
	},

	// Sound config
	{
		__DEFAULT_PCM_HZ,
		false	},

	// level
	{
		// size
		{
			// x
			__SCREEN_WIDTH,
			// y
			__SCREEN_HEIGHT,
			// z
			__SCREEN_DEPTH,
		},

		// camera's initial position inside the game world
		{
			// x
			0,
			// y
			0,
			// z
			0,
			// p
			0
		},

		// camera's frustum
		{
			// x0
			0,
			// y0
			0,
			// z0
			-10,
			// x1
			__SCREEN_WIDTH,
			// y1
			__SCREEN_HEIGHT,
			// z1
			__SCREEN_WIDTH * 5
		}
	},

	// streaming
	{
		// load padding
		40,
		// unload padding
		16,
		// streaming amplitude
		24,
		// particle removal delay cycles
		0,
		// deferred
		false
	},

	// rendering
	{
		// maximum number of texture's rows to write each time the texture writing is active
		12,

		// maximum number of rows to compute on each call to the affine functions
		16 * 8,

		// colors config
		{
			// background color
			__COLOR_BLACK,

			// brightness
			// these values times the repeat values specified in the column table (max. 16) make the final
			// brightness values on the respective regions of the screen. maximum brightness is 128.
			{
				// dark red
				__BRIGHTNESS_DARK_RED,
				// medium red
				__BRIGHTNESS_MEDIUM_RED,
				// bright red
				__BRIGHTNESS_BRIGHT_RED,
			},

			// brightness repeat
			(BrightnessRepeatSpec*)NULL,
		},

		// palettes' config
		{
			{
				// bgmap palette 0
				__BGMAP_PALETTE_0,
				// bgmap palette 1
				__BGMAP_PALETTE_1,
				// bgmap palette 2
				__BGMAP_PALETTE_2,
				// bgmap palette 3
				__BGMAP_PALETTE_3,
			},
			{
				// object palette 0
				__OBJECT_PALETTE_0,
				// object palette 1
				__OBJECT_PALETTE_1,
				// object palette 2
				__OBJECT_PALETTE_2,
				// object palette 3
				__OBJECT_PALETTE_3,
			},
		},

		// bgmap segments configuration
		// number of segments reserved for the param table
		5,

		// object segments sizes (up to 1024 in total)
		// can impact performance, make sure to configure only as large as maximally needed
		{
			// __spt0
			0,
			// __spt1
			0,
			// __spt2
			64,
			// __spt3
			64,
		},

		// object segments z coordinates
		// note that each spt's z coordinate much be larger than or equal to the previous one's,
		// since the vip renders obj worlds in reverse order (__spt3 to __spt0)
		{
			// __spt0
			LAYER_0_PARTICLES,
			// __spt1
			LAYER_0_PARTICLES,
			// __spt2
			LAYER_0_PARTICLES,
			// __spt3
			LAYER_0_PARTICLES,
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE, __MAXIMUM_Y_VIEW_DISTANCE,
			// distance of the eyes to the screen
			__CAMERA_NEAR_PLANE,
			// distance from left to right eye (depth sensation)
			__BASE_FACTOR,
			// horizontal view point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// vertical view point center
			__VERTICAL_VIEW_POINT_CENTER,
			// scaling factor
			__SCALING_MODIFIER_FACTOR,
		},
	},

	// physics
	{
		// gravity
		{
			__I_TO_FIX10_6(0),
			__F_TO_FIX10_6(0),
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)TitleScreenStageFonts,

		// char sets to preload
		(CharSetSpec**)NULL,

		// textures to preload
		(TextureSpec**)TitleScreenStageTextures,

		// background sounds
		(Sound**)TitleScreenStageSounds,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)TitleScreenStageUiEntities,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)TitleScreenStageEntities,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};
