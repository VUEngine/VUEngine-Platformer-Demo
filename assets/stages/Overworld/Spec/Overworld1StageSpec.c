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
#include <Fonts.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern SoundROM* const Level1Sounds[];

extern EntitySpec FlowerAEntity;
extern EntitySpec GuiOverworldEntity;
extern EntitySpec HeroIdleEntity;
extern EntitySpec LowPowerIndicatorEntity;
extern EntitySpec Overworld1Entity;
extern EntitySpec SmokeParticleSystem;
extern EntitySpec WaterAEntity;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Overworld1StageEntities[] =
{
	{&LowPowerIndicatorEntity, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&WaterAEntity, {(26), (86), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Water
	{&WaterAEntity, {(70), (18), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Water
	{&WaterAEntity, {(74), (176), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Water
	{&FlowerAEntity, {(124), (118), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Flower
	{&FlowerAEntity, {(130), (82), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Flower
	{&FlowerAEntity, {(156), (200), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Flower
	{&HeroIdleEntity, {(160), (92), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Hero (Idle)
	{&Overworld1Entity, {(192), (112), LAYER_0_BACKGROUND, LAYER_0_BACKGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Overworld Static Image
	{&FlowerAEntity, {(218), (168), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Flower
	{&SmokeParticleSystem, {(222.5), (48), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Smoke
	{&FlowerAEntity, {(226), (132), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Flower
	{&FlowerAEntity, {(290), (136), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Flower

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Overworld1StageUiEntities[] =
{
	{&GuiOverworldEntity, {192, 216, -2, 0}, 0, NULL, NULL, NULL, false}, // GUI

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Overworld1StageFonts[] =
{
	&PlatformerFont,
	&PlatformerGuiFont,
	&AstonishSExtFont,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Overworld1Stage =
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
		false
	},

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
		16,

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
		1,

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
			LAYER_0,
			// __spt1
			LAYER_0,
			// __spt2
			LAYER_0,
			// __spt3
			LAYER_0,
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
			__F_TO_FIX10_6(__GRAVITY),
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)Overworld1StageFonts,

		// char sets to preload
		(CharSetSpec**)NULL,

		// textures to preload
		(TextureSpec**)NULL,

		// background sounds
		(Sound**)Level1Sounds,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)Overworld1StageUiEntities,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Overworld1StageEntities,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};
