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

extern SoundROMSpec* const Level1Sounds[];

const Size level1_intersection_stage_collision_112_128_8 = {112, 128, 8};
const Size level1_intersection_stage_collision_16_48_8 = {16, 48, 8};
const Size level1_intersection_stage_collision_224_16_8 = {224, 16, 8};
const Size level1_intersection_stage_collision_224_64_8 = {224, 64, 8};
const Size level1_intersection_stage_collision_272_16_8 = {272, 16, 8};
const Size level1_intersection_stage_collision_32_64_8 = {32, 64, 8};
const Size level1_intersection_stage_collision_48_32_8 = {48, 32, 8};
const Size level1_intersection_stage_collision_48_34_8 = {48, 34, 8};
extern EntitySpec CoinEntity;
extern EntitySpec CollisionCl;
extern EntitySpec CollisionTopCl;
extern EntitySpec DoorEntity;
extern EntitySpec GuiEntity;
extern EntitySpec HeroEntity;
extern EntitySpec Level1IntersectionStageBack1Entity;
extern EntitySpec Level1IntersectionStageMain1Entity;
extern EntitySpec Level1IntersectionStageMainBack1Entity;
extern EntitySpec LowPowerIndicatorEntitySpec;
extern EntitySpec SawBladeH8Entity;
extern EntitySpec TorchOffEntity;
extern EntitySpec TorchSmokeParticleSystem;
extern EntitySpec TorchLightEntity;
extern StageEntryPointROMSpec Level1CoinRoomStageExitEntryPoint;
extern StageEntryPointROMSpec Level1MainIntersectionEntryDoorEntryPoint;
extern StageEntryPointROMSpec Level1MainIntersectionExitDoorEntryPoint;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Level1IntersectionStageEntities[] =
{
	{&CollisionCl, {(7), (152), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_16_48_8, false}, // Left Collision
	{&DoorEntity, {(36), (160), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "IntEntr2", NULL, (void*)&Level1CoinRoomStageExitEntryPoint, false}, // Door (Lower Entrance)
	//{&TorchLightEntity, {(56), (148), (0), 0}, 0, NULL, NULL, NULL, false}, // Lower Left Torch Light
	{&TorchOffEntity, {(56), (146), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Lower Left Torch
	{&TorchSmokeParticleSystem, {(56), (136), LAYER_0_FOREGROUND + 12, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&CollisionCl, {(111), (95), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_224_64_8, false}, // Center Collision
	{&CollisionCl, {(135), (184), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_272_16_8, false}, // Bottom Collision
	{&CollisionCl, {(143), (32), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_32_64_8, false}, // Top Left Collision
	//{&SawBladeH8Entity, {(172), (176), LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Saw Blade
	{&DoorEntity, {(178), (48), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "IntEntr1", NULL, (void*)&Level1MainIntersectionEntryDoorEntryPoint, false}, // Door (Upper Entrance)
	{&Level1IntersectionStageMainBack1Entity, {(192), (96), (-SORT_INCREMENT), 0}, 0, NULL, NULL, NULL, false}, // MainBack
	{&Level1IntersectionStageBack1Entity, {(192), (96), 32, LAYER_0_BACKGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Back
	{&Level1IntersectionStageMain1Entity, {(192), (96), (-SORT_INCREMENT * 2), 0}, 0, NULL, NULL, NULL, false}, // Main
	{&TorchOffEntity, {(206), (34), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Upper Left Torch
	//{&TorchLightEntity, {(206), (148), (0), 0}, 0, NULL, NULL, NULL, false}, // Lower Right Torch Light
	{&TorchOffEntity, {(206), (146), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Lower Right Torch
	//{&TorchLightEntity, {(206), (36), (0), 0}, 0, NULL, NULL, NULL, false}, // Upper Left Torch Light
	{&CoinEntity, {(236), (108), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "47", NULL, NULL, false}, // Coin
	{&CollisionTopCl, {(248), (79), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_48_32_8, false}, // Upper One-Way
	{&CollisionTopCl, {(248), (135), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_48_34_8, false}, // Lower One-Way
	{&CoinEntity, {(260), (108), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "46", NULL, NULL, false}, // Coin
	{&CollisionCl, {(271), (8), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_224_16_8, false}, // Top Collision
	//{&TorchLightEntity, {(320), (36), (0), 0}, 0, NULL, NULL, NULL, false}, // Upper Right Torch Light
	{&TorchOffEntity, {(320), (34), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Upper Right Torch
	{&TorchSmokeParticleSystem, {(320), (24), LAYER_0_FOREGROUND + 12, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&CollisionCl, {(327), (127), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_112_128_8, false}, // Bottom Right Collision
	{&DoorEntity, {(350), (48), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "IntExit", NULL, (void*)&Level1MainIntersectionExitDoorEntryPoint, false}, // Door (Exit)
	{&CollisionCl, {(375), (40), (0), 0}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_16_48_8, false}, // Top Right Collision

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1IntersectionStageUiEntities[] =
{
	{&LowPowerIndicatorEntitySpec, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GuiEntity, {192, 215, 0, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Level1IntersectionStageFonts[] =
{
	&PlatformerFontSpec,
	&AstonishSFontSpec,
	&PlatformerGuiFontSpec,

	NULL
};

const PostProcessingEffect Level1IntersectionStage_POST_PROCESSING_EFFECTS[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Level1IntersectionStage =
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
		(FontSpec**)Level1IntersectionStageFonts,

		// char sets to preload
		(CharSetSpec**)NULL,

		// textures to preload
		(TextureSpec**)NULL,

		// background sounds
		(SoundSpec**)Level1Sounds,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)Level1IntersectionStageUiEntities,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Level1IntersectionStageEntities,
	},

	// post processing effects
	(PostProcessingEffect*)Level1IntersectionStage_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec Level1IntersectionStageExitEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1IntersectionStage,

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

StageEntryPointROMSpec Level1IntersectionStageLowerEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1IntersectionStage,

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

StageEntryPointROMSpec Level1IntersectionStageUpperEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1IntersectionStage,

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

