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

const PixelSize level1_coin_room_stage_collision_16_96_8 = {16, 96, 8};
const PixelSize level1_coin_room_stage_collision_224_16_8 = {224, 16, 8};
const PixelSize level1_coin_room_stage_collision_320_16_8 = {320, 16, 8};
const PixelSize level1_coin_room_stage_collision_32_48_8 = {32, 48, 8};
const PixelSize level1_coin_room_stage_collision_80_48_8 = {80, 48, 8};
extern BrightnessRepeatROMSpec EdgeFadeOutBrightnessRepeat;
extern EntitySpec CoinEntity;
extern EntitySpec CollisionCl;
extern EntitySpec DoorEntity;
extern EntitySpec GuiEntity;
extern EntitySpec HeroEntity;
extern EntitySpec Level1CoinRoomStageBack1Entity;
extern EntitySpec Level1CoinRoomStageMain1Entity;
extern EntitySpec Level1CoinRoomStageMainBack1Entity;
extern EntitySpec LowPowerIndicatorEntity;
extern EntitySpec SawBladeH8Entity;
extern EntitySpec TorchEntity;
extern EntitySpec TorchLightEntity;
extern StageEntryPointROMSpec Level1IntersectionStageLowerEntryPoint;
extern StageEntryPointROMSpec Level1MainCoinRoomEntryDoorEntryPoint;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Level1CoinRoomStageEntities[] =
{
	{&CollisionCl, {(7), (112), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_16_96_8, false}, // Left Collision
	{&CollisionCl, {(15), (40), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_32_48_8, false}, // Top Left Collision
	{&DoorEntity, {(36), (144), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "CoinEntr", NULL, (void*)&Level1MainCoinRoomEntryDoorEntryPoint, false}, // Door (Entrance)
	{&CollisionCl, {(39), (184), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_80_48_8, false}, // Bottom Left Collision
	{&TorchLightEntity, {(64), (128), (0), 0}, 0, NULL, NULL, NULL, false}, // Left Torch Light
	{&TorchEntity, {(64), (126), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Left Torch
	{&CoinEntity, {(144), (104), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "27", NULL, NULL, false}, // Coin
	{&CoinEntity, {(144), (120), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "28", NULL, NULL, false}, // Coin
	{&CoinEntity, {(144), (152), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "30", NULL, NULL, false}, // Coin
	{&CoinEntity, {(144), (136), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "29", NULL, NULL, false}, // Coin
	{&CoinEntity, {(160), (168), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "31", NULL, NULL, false}, // Coin
	{&CoinEntity, {(176), (104), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "35", NULL, NULL, false}, // Coin
	{&CoinEntity, {(176), (120), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "34", NULL, NULL, false}, // Coin
	{&CoinEntity, {(176), (136), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "33", NULL, NULL, false}, // Coin
	{&CoinEntity, {(176), (152), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "32", NULL, NULL, false}, // Coin
	{&Level1CoinRoomStageMainBack1Entity, {(192), (112), (-SORT_INCREMENT), 0}, 0, NULL, NULL, NULL, false}, // MainBack
	{&CollisionCl, {(191), (24), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_320_16_8, false}, // Top Collision
	{&CollisionCl, {(191), (200), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_224_16_8, false}, // Bottom Collision
	{&Level1CoinRoomStageBack1Entity, {(192), (112), 32, LAYER_0_BACKGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Back
	{&SawBladeH8Entity, {(192), (192), LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Saw Blade
	{&Level1CoinRoomStageMain1Entity, {(192), (112), (-SORT_INCREMENT * 2), 0}, 0, NULL, NULL, NULL, false}, // Main
	{&CoinEntity, {(208), (152), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "39", NULL, NULL, false}, // Coin
	{&CoinEntity, {(208), (104), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "36", NULL, NULL, false}, // Coin
	{&CoinEntity, {(208), (120), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "37", NULL, NULL, false}, // Coin
	{&CoinEntity, {(208), (136), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "38", NULL, NULL, false}, // Coin
	{&CoinEntity, {(208), (168), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "40", NULL, NULL, false}, // Coin
	{&CoinEntity, {(224), (136), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "42", NULL, NULL, false}, // Coin
	{&CoinEntity, {(224), (104), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "41", NULL, NULL, false}, // Coin
	{&CoinEntity, {(224), (168), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "43", NULL, NULL, false}, // Coin
	{&CoinEntity, {(240), (120), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "44", NULL, NULL, false}, // Coin
	{&CoinEntity, {(240), (152), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "45", NULL, NULL, false}, // Coin
	{&TorchEntity, {(320), (128), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Right Torch
	{&TorchLightEntity, {(320), (130), (0), 0}, 0, NULL, NULL, NULL, false}, // Right Torch Light
	{&CollisionCl, {(343), (184), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_80_48_8, false}, // Bottom Right Collision
	{&DoorEntity, {(348), (144), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "CoinExit", NULL, (void*)&Level1IntersectionStageLowerEntryPoint, false}, // Door (Exit)
	{&CollisionCl, {(367), (40), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_32_48_8, false}, // Top Right Collision
	{&CollisionCl, {(375), (112), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_16_96_8, false}, // Right Collision

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1CoinRoomStageUiEntities[] =
{
	{&LowPowerIndicatorEntity, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GuiEntity, {192, 215, 0, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Level1CoinRoomStageFonts[] =
{
	&PlatformerFont,
	&AstonishSFont,
	&PlatformerGuiFont,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Level1CoinRoomStage =
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
				2,
				// medium red
				4,
				// bright red
				8,
			},

			// brightness repeat
			(BrightnessRepeatSpec*)&EdgeFadeOutBrightnessRepeat,
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
		(FontSpec**)Level1CoinRoomStageFonts,

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
			(PositionedEntity*)Level1CoinRoomStageUiEntities,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Level1CoinRoomStageEntities,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec Level1CoinRoomStageExitEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1CoinRoomStage,

	// name of the entity to start at
	"CoinExit",

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

StageEntryPointROMSpec Level1CoinRoomStageMainEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1CoinRoomStage,

	// name of the entity to start at
	"CoinEntr",

	// offset from entry point (x, y, z)
	{
		19,
		5,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	false,
};

