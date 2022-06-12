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

extern SoundROM* const Level1Sounds[];

const Size level1_house_stage_collision_128_16_8 = {128, 16, 8};
const Size level1_house_stage_collision_16_96_8 = {16, 96, 8};
const Size level1_house_stage_collision_24_24_8 = {24, 24, 8};
extern CharSetSpec Level1HouseMainCharset;
extern EntitySpec ClockEntity;
extern EntitySpec CloudsEntity;
extern EntitySpec CoinEntity;
extern EntitySpec CollisionCl;
extern EntitySpec CollisionTopCl;
extern EntitySpec FireSmallEntity;
extern EntitySpec GuiEntity;
extern EntitySpec HeroEntity;
extern EntitySpec KeyDoorEntity;
extern EntitySpec Level1HouseLightEntity;
extern EntitySpec Level1HouseMainEntity;
extern EntitySpec LowPowerIndicatorEntity;
extern EntitySpec MoundBgBackEntity;
extern StageEntryPointROMSpec Level1MainHouseEntryPoint;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Level1HouseStageEntities[] =
{
	{&CollisionCl, {(119), (128), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_16_96_8, false}, // Left Collision
	{&KeyDoorEntity, {(148), (144), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "EntryDoor", NULL, (void*)&Level1MainHouseEntryPoint, false}, // Door
	{&ClockEntity, {(180), (128), (LAYER_0 + 32), 0}, 0, NULL, NULL, NULL, false}, // Clock
	{&Level1HouseMainEntity, {(192), (112), 0, 0}, 0, NULL, NULL, NULL, false}, // House Background
	{&CollisionCl, {(191), (168), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_128_16_8, false}, // Bottom Collision
	{&CollisionCl, {(191), (88), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_128_16_8, false}, // Top Collision
	{&CloudsEntity, {(194), (138), (LAYER_4), 0}, 0, NULL, NULL, NULL, false}, // Clouds
	{&Level1HouseLightEntity, {(197), (139), (LAYER_0_ITEMS - 1), 0}, 0, NULL, NULL, NULL, false}, // Light
	{&CoinEntity, {(204), (146), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "26", NULL, NULL, false}, // Coin
	{&FireSmallEntity, {(240), (155), (32), 0}, 0, NULL, NULL, NULL, false}, // Fire
	{&CollisionTopCl, {(240), (152), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_24_24_8, false}, // Fireplace Collision
	{&MoundBgBackEntity, {(255), (104), (LAYER_5), 0}, 0, NULL, NULL, NULL, false}, // Mountains
	{&CollisionCl, {(263), (128), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_16_96_8, false}, // Right Collision

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1HouseStageUiEntities[] =
{
	{&LowPowerIndicatorEntity, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GuiEntity, {192, 215, 0, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Level1HouseStageFonts[] =
{
	&PlatformerFont,
	&AstonishSFont,
	&PlatformerGuiFont,

	NULL
};

CharSetROMSpec* const Level1HouseStageCharsets[] =
{
	&Level1HouseMainCharset,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Level1HouseStage =
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
			__SCREEN_WIDTH,
		},

		// camera's initial position inside the game world
		{
			// x
			0,
			// y
			0,
			// z
			LAYER_0_FOREGROUND - LAYER_0_DOORS,
			// p
			0,
		},

		// camera's frustum
		{
			// x0
			INGAME_CAMERA_FRUSTUM_X0,
			// y0
			INGAME_CAMERA_FRUSTUM_Y0,
			// z0
			INGAME_CAMERA_FRUSTUM_Z0,
			// x1
			INGAME_CAMERA_FRUSTUM_X1,
			// y1
			INGAME_CAMERA_FRUSTUM_Y1,
			// z1
			INGAME_CAMERA_FRUSTUM_Z1,
		}
	},

	// streaming
	{
		// load padding
		140,
		// unload padding
		16,
		// streaming amplitude
		24,
		// particle removal delay cycles
		0,
		// deferred
		false,
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
			0,
			// __spt3
			128,
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
			16,
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
			__I_TO_FIX10_6(0),
		},

		// friction
		__F_TO_FIX10_6(0),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)Level1HouseStageFonts,

		// char sets to preload
		(CharSetSpec**)Level1HouseStageCharsets,

		// textures to preload
		(TextureSpec**)NULL,

		// background sounds
		(Sound**)Level1Sounds,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)Level1HouseStageUiEntities,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Level1HouseStageEntities,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec Level1HouseStageMainEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1HouseStage,

	// name of the entity to start at
	"EntryDoor",

	// offset from entry point (x, y, z)
	{
		19,
		0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	false,
};

