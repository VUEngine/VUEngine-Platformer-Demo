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

extern SoundROM* const LEVEL_1_SOUNDS[];

const Size level1_house_stage_collision_128_16_8 = {128, 16, 8};
const Size level1_house_stage_collision_16_96_8 = {16, 96, 8};
const Size level1_house_stage_collision_24_24_8 = {24, 24, 8};
extern CharSetSpec LEVEL_1_HOUSE_MAIN_CH;
extern EntitySpec CLOCK_EN;
extern EntitySpec CLOUDS_IM;
extern EntitySpec COIN_EN;
extern EntitySpec COLLISION_CL;
extern EntitySpec COLLISION_TOP_CL;
extern EntitySpec FIRE_SMALL_EN;
extern EntitySpec GUI_EN;
extern EntitySpec HERO_AC;
extern EntitySpec KEY_DOOR_EN;
extern EntitySpec LEVEL_1_HOUSE_LIGHT_IM;
extern EntitySpec LEVEL_1_HOUSE_MAIN_IM;
extern EntitySpec LOW_POWER_INDICATOR_LB;
extern EntitySpec MOUND_BG_BACK_IM;
extern StageEntryPointROMSpec LEVEL_1_MAIN_HOUSE_EP;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec LEVEL1_HOUSE_STAGE_ST_ENTITIES[] =
{
	{&COLLISION_CL, {(119), (128), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_16_96_8, false}, // Left Collision
	{&KEY_DOOR_EN, {(148), (144), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "EntryDoor", NULL, (void*)&LEVEL_1_MAIN_HOUSE_EP, false}, // Door
	{&CLOCK_EN, {(180), (128), (LAYER_0 + 32), 0}, 0, NULL, NULL, NULL, false}, // Clock
	{&LEVEL_1_HOUSE_MAIN_IM, {(192), (112), 0, 0}, 0, NULL, NULL, NULL, false}, // House Background
	{&COLLISION_CL, {(191), (168), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_128_16_8, false}, // Bottom Collision
	{&COLLISION_CL, {(191), (88), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_128_16_8, false}, // Top Collision
	{&CLOUDS_IM, {(194), (138), (LAYER_4), 0}, 0, NULL, NULL, NULL, false}, // Clouds
	{&LEVEL_1_HOUSE_LIGHT_IM, {(197), (139), (LAYER_0_ITEMS - 1), 0}, 0, NULL, NULL, NULL, false}, // Light
	{&COIN_EN, {(204), (146), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "26", NULL, NULL, false}, // Coin
	{&FIRE_SMALL_EN, {(240), (155), (32), 0}, 0, NULL, NULL, NULL, false}, // Fire
	{&COLLISION_TOP_CL, {(240), (152), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_24_24_8, false}, // Fireplace Collision
	{&MOUND_BG_BACK_IM, {(255), (104), (LAYER_5), 0}, 0, NULL, NULL, NULL, false}, // Mountains
	{&COLLISION_CL, {(263), (128), (0), 0}, 0, NULL, NULL, (void*)&level1_house_stage_collision_16_96_8, false}, // Right Collision

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL1_HOUSE_STAGE_ST_UI_ENTITIES[] =
{
	{&LOW_POWER_INDICATOR_LB, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GUI_EN, {192, 215, -2, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const LEVEL1_HOUSE_STAGE_ST_FONTS[] =
{
	&PLATFORMER_FONT,
	&ASTONISH_S_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMSpec* const LEVEL1_HOUSE_STAGE_ST_CHARSETS[] =
{
	&LEVEL_1_HOUSE_MAIN_CH,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec LEVEL1_HOUSE_STAGE_ST =
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
			0,
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
			__DISTANCE_EYE_SCREEN,
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
		(FontSpec**)LEVEL1_HOUSE_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetSpec**)LEVEL1_HOUSE_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureSpec**)NULL,

		// background sounds
		(Sound**)LEVEL_1_SOUNDS,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)LEVEL1_HOUSE_STAGE_ST_UI_ENTITIES,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)LEVEL1_HOUSE_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec LEVEL1_HOUSE_STAGE_MAIN_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL1_HOUSE_STAGE_ST,

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

