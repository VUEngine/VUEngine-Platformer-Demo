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

const Size level1_intersection_stage_collision_112_128_8 = {112, 128, 8};
const Size level1_intersection_stage_collision_16_48_8 = {16, 48, 8};
const Size level1_intersection_stage_collision_224_16_8 = {224, 16, 8};
const Size level1_intersection_stage_collision_224_64_8 = {224, 64, 8};
const Size level1_intersection_stage_collision_272_16_8 = {272, 16, 8};
const Size level1_intersection_stage_collision_32_64_8 = {32, 64, 8};
const Size level1_intersection_stage_collision_48_32_8 = {48, 32, 8};
const Size level1_intersection_stage_collision_48_34_8 = {48, 34, 8};
extern EntitySpec COIN_EN;
extern EntitySpec COLLISION_CL;
extern EntitySpec COLLISION_TOP_CL;
extern EntitySpec DOOR_EN;
extern EntitySpec GUI_EN;
extern EntitySpec HERO_AC;
extern EntitySpec LEVEL1_INTERSECTION_STAGE_BACK_1_IM;
extern EntitySpec LEVEL1_INTERSECTION_STAGE_MAIN_1_IM;
extern EntitySpec LEVEL1_INTERSECTION_STAGE_MAIN_BACK_1_IM;
extern EntitySpec LOW_POWER_INDICATOR_LB;
extern EntitySpec SAW_BLADE_H8_AC;
extern EntitySpec TORCH_OFF_IM;
extern EntitySpec TORCH_SMOKE_PS;
extern EntitySpec TORCH_LIGHT_EN;
extern StageEntryPointROMSpec LEVEL1_COIN_ROOM_STAGE_EXIT_EP;
extern StageEntryPointROMSpec LEVEL_1_MAIN_INTERSECTION_ENTRY_DOOR_EP;
extern StageEntryPointROMSpec LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec LEVEL1_INTERSECTION_STAGE_ST_ENTITIES[] =
{
	{&COLLISION_CL, {(7), (152), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_16_48_8, false}, // Left Collision
	{&DOOR_EN, {(36), (160), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "IntEntr2", NULL, (void*)&LEVEL1_COIN_ROOM_STAGE_EXIT_EP, false}, // Door (Lower Entrance)
	//{&TORCH_LIGHT_EN, {(56), (148), (0), 0}, 0, NULL, NULL, NULL, false}, // Lower Left Torch Light
	{&TORCH_OFF_IM, {(56), (146), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Lower Left Torch
	{&TORCH_SMOKE_PS, {(56), (136), LAYER_0_FOREGROUND + 12, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&COLLISION_CL, {(111), (95), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_224_64_8, false}, // Center Collision
	{&COLLISION_CL, {(135), (184), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_272_16_8, false}, // Bottom Collision
	{&COLLISION_CL, {(143), (32), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_32_64_8, false}, // Top Left Collision
	//{&SAW_BLADE_H8_AC, {(172), (176), LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Saw Blade
	{&DOOR_EN, {(178), (48), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "IntEntr1", NULL, (void*)&LEVEL_1_MAIN_INTERSECTION_ENTRY_DOOR_EP, false}, // Door (Upper Entrance)
	{&LEVEL1_INTERSECTION_STAGE_MAIN_BACK_1_IM, {(192), (96), (-SORT_INCREMENT), 0}, 0, NULL, NULL, NULL, false}, // MainBack
	{&LEVEL1_INTERSECTION_STAGE_BACK_1_IM, {(192), (96), 32, LAYER_0_BACKGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Back
	{&LEVEL1_INTERSECTION_STAGE_MAIN_1_IM, {(192), (96), (-SORT_INCREMENT * 2), 0}, 0, NULL, NULL, NULL, false}, // Main
	{&TORCH_OFF_IM, {(206), (34), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Upper Left Torch
	//{&TORCH_LIGHT_EN, {(206), (148), (0), 0}, 0, NULL, NULL, NULL, false}, // Lower Right Torch Light
	{&TORCH_OFF_IM, {(206), (146), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Lower Right Torch
	//{&TORCH_LIGHT_EN, {(206), (36), (0), 0}, 0, NULL, NULL, NULL, false}, // Upper Left Torch Light
	{&COIN_EN, {(236), (108), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "47", NULL, NULL, false}, // Coin
	{&COLLISION_TOP_CL, {(248), (79), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_48_32_8, false}, // Upper One-Way
	{&COLLISION_TOP_CL, {(248), (135), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_48_34_8, false}, // Lower One-Way
	{&COIN_EN, {(260), (108), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "46", NULL, NULL, false}, // Coin
	{&COLLISION_CL, {(271), (8), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_224_16_8, false}, // Top Collision
	//{&TORCH_LIGHT_EN, {(320), (36), (0), 0}, 0, NULL, NULL, NULL, false}, // Upper Right Torch Light
	{&TORCH_OFF_IM, {(320), (34), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Upper Right Torch
	{&TORCH_SMOKE_PS, {(320), (24), LAYER_0_FOREGROUND + 12, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&COLLISION_CL, {(327), (127), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_112_128_8, false}, // Bottom Right Collision
	{&DOOR_EN, {(350), (48), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "IntExit", NULL, (void*)&LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP, false}, // Door (Exit)
	{&COLLISION_CL, {(375), (40), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_16_48_8, false}, // Top Right Collision

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL1_INTERSECTION_STAGE_ST_UI_ENTITIES[] =
{
	{&LOW_POWER_INDICATOR_LB, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GUI_EN, {192, 215, -2, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const LEVEL1_INTERSECTION_STAGE_ST_FONTS[] =
{
	&PlatformerFont,
	&AstonishSFont,
	&PlatformerGuiFont,

	NULL
};

const PostProcessingEffect LEVEL1_INTERSECTION_STAGE_ST_POST_PROCESSING_EFFECTS[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec LEVEL1_INTERSECTION_STAGE_ST =
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
			__SCREEN_DEPTH + LAYER_5,
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
		40,
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
				__BRIGHTNESS_DARK_RED >> 1,
				// medium red
				__BRIGHTNESS_MEDIUM_RED >> 1,
				// bright red
				__BRIGHTNESS_BRIGHT_RED >> 1,
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
			15,
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
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)LEVEL1_INTERSECTION_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetSpec**)NULL,

		// textures to preload
		(TextureSpec**)NULL,

		// background sounds
		(Sound**)LEVEL_1_SOUNDS,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)LEVEL1_INTERSECTION_STAGE_ST_UI_ENTITIES,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)LEVEL1_INTERSECTION_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)LEVEL1_INTERSECTION_STAGE_ST_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec LEVEL1_INTERSECTION_STAGE_EXIT_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL1_INTERSECTION_STAGE_ST,

	// name of the entity to start at
	"IntExit",

	// offset from entry point (x, y, z)
	{
		-19,
		0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__LEFT,

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMSpec LEVEL1_INTERSECTION_STAGE_LOWER_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL1_INTERSECTION_STAGE_ST,

	// name of the entity to start at
	"IntEntr2",

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

StageEntryPointROMSpec LEVEL1_INTERSECTION_STAGE_UPPER_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL1_INTERSECTION_STAGE_ST,

	// name of the entity to start at
	"IntEntr1",

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

