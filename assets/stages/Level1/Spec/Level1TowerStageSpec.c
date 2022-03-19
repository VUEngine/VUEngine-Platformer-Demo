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
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern SoundROM* const Level1Sounds[];

extern StageEntryPointROMSpec Level1MainTowerEntryPoint;
extern BrightnessRepeatROMSpec EdgeFadeOutBrightnessRepeat;

extern EntitySpec BandanaEntity;
extern EntitySpec CoinEntity;
extern EntitySpec CogWheelEntity;
extern EntitySpec CollisionCl;
extern EntitySpec CollisionHitCl;
extern EntitySpec CollisionTopCl;
extern EntitySpec ManagedEntity;
extern EntitySpec KeyDoorEntity;
extern EntitySpec GoalDoorEntity;
extern EntitySpec GrassEntity;
extern EntitySpec GuiEntity;
extern EntitySpec HeroEntity;
extern EntitySpec LavaEntity;
extern EntitySpec LavaTopEntity;
extern EntitySpec LavaTriggerEntity;
extern EntitySpec Level1TowerMain1Entity;
extern EntitySpec Level1TowerMain2Entity;
extern EntitySpec Level1TowerMainBackEntity;
extern EntitySpec LowPowerIndicatorEntity;
extern EntitySpec ManagedEntity;
extern EntitySpec MovingPlatformV6Entity;
extern EntitySpec SawBladeH8Entity;
extern EntitySpec Snail8Entity;
extern EntitySpec TorchEntity;
extern EntitySpec TorchOffEntity;
extern EntitySpec TorchLightEntity;
extern EntitySpec DarknessOverlayEntity;
extern EntitySpec TorchSmokeParticleSystem;

extern TextureSpec CogWheelTexture;
extern TextureSpec DoorTexture;
extern TextureSpec GuiTexture;
extern TextureSpec LavaTopTexture;
extern TextureSpec LavaTexture;
extern TextureSpec Level1TowerBack1Texture;
extern TextureSpec Level1TowerMain1Texture;
extern TextureSpec Level1TowerMainBack1Texture;
extern TextureSpec DarknessOverlayTexture;

extern Size collision_2_64_4;
extern Size collision_4_2_4;
extern Size collision_4_4_4;
extern Size collision_4_8_4;
extern Size collision_6_4_4;
extern Size collision_6_2_4;
extern Size collision_8_4_4;
extern Size collision_8_20_4;
extern Size collision_14_6_4;
extern Size collision_16_2_4;
extern Size collision_20_2_4;
extern Size collision_32_4_4;
extern Size collision_48_2_4;
extern Size collision_48_4_4;
extern Size collision_48_28_4;


//---------------------------------------------------------------------------------------------------------
//												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LEVEL_1_TOWER_HEIGHT 	1024
#define SCREEN_Y_POSITION 		LEVEL_1_TOWER_HEIGHT - __SCREEN_HEIGHT


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMSpec LavaChildEntities[] =
{
	{&LavaTopEntity, 					{0, -104, -1, 0}, 0, NULL, NULL, NULL, false},
	{&DarknessOverlayEntity, 			{0, -460, -4, 0}, 0, NULL, NULL, NULL, false},
	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1TowerMain1Entities[] =
{
	{&Level1TowerMain1Entity,		{   0, 	  0, 	0, -SORT_INCREMENT}, 0, "Main_1", NULL, NULL, false},
	{&TorchLightEntity,				{-107, 	136, 	-SORT_INCREMENT, 0}, 0, NULL, NULL, NULL, false},
	{&TorchEntity,						{-107, 	136, 	LAYER_0_DECORATIONS - LAYER_0_FOREGROUND, LAYER_0_DECORATIONS_DISPLACEMENT - LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
//	{&TorchLightEntity,				{  12, 	136, 	-SORT_INCREMENT, 0}, 0, NULL, NULL, NULL, false},
	{&TorchOffEntity,					{  12, 	140, 	LAYER_0_DECORATIONS - LAYER_0_FOREGROUND, LAYER_0_DECORATIONS_DISPLACEMENT - LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1TowerMain1Collisions1[] =
{
	{&CollisionCl,					{-185,	  0, 	0, 0}, 0, NULL, NULL, (void*)&collision_2_64_4, false}, // outer left wall
	{&CollisionCl,					{ 183,	  0, 	0, 0}, 0, NULL, NULL, (void*)&collision_2_64_4, false}, // outer right wall
	{&CollisionCl,					{-129,	288, 	0, 0}, 0, NULL, NULL, (void*)&collision_48_28_4, false}, // bottom left floor
	{&CollisionCl,					{ 301,	256, 	0, 0}, 0, NULL, NULL, (void*)&collision_48_28_4, false}, // bottom right floor
	{&CollisionCl,					{ 159,	144, 	0, 0}, 0, NULL, NULL, (void*)&collision_4_8_4, false}, // step stone bottom right
	{&CollisionCl,					{  79,	 72, 	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // floating stone

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1TowerMain1Collisions2[] =
{
	{&CollisionCl,					{-173, 	  32,	0, 0}, 0, NULL, NULL, (void*)&collision_48_4_4, false}, // 2nd level floor left
	{&CollisionCl,					{  29,	 -96,	0, 0}, 0, NULL, NULL, (void*)&collision_32_4_4, false}, // 3rd level floor right
	{&CollisionCl,					{ 159,	 -40,	0, 0}, 0, NULL, NULL, (void*)&collision_16_2_4, false}, // small stone right under 3rd
	{&CollisionCl,					{ -81,	-176,	0, 0}, 0, NULL, NULL, (void*)&collision_48_4_4, false}, // 4th level floor left
	{&CollisionCl,					{ -83,	-248,	0, 0}, 0, NULL, NULL, (void*)&collision_48_2_4, false}, // floor below spikes
	{&CollisionCl,					{-137, 	-216,	0, 0}, 0, NULL, NULL, (void*)&collision_14_6_4, false}, // left wall below spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1TowerMain2Collisions1[] =
{
	{&CollisionCl,					{-185, 	  0,	0, 0}, 0, NULL, NULL, (void*)&collision_2_64_4, false}, // outer left wall
	{&CollisionCl,					{ 183,	  0,	0, 0}, 0, NULL, NULL, (void*)&collision_2_64_4, false}, // outer right wall
	{&CollisionCl,					{-105,	256,	0, 0}, 0, NULL, NULL, (void*)&collision_6_4_4, false}, // block between spikes left
	{&CollisionCl,					{ -17,	256,	0, 0}, 0, NULL, NULL, (void*)&collision_4_4_4, false}, // block between spikes middle
	{&CollisionCl,					{  77,	256,	0, 0}, 0, NULL, NULL, (void*)&collision_8_4_4, false}, // block between spikes right
	{&CollisionHitCl,				{-105,  256,	0, 0}, 0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes
	{&CollisionHitCl,				{ -17,	256,	0, 0}, 0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1TowerMain2Collisions2[] =
{
	{&CollisionCl,					{-177,	200,	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // stepstone left
	{&CollisionCl,					{ -97,	168,	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // floating stone 1
	{&CollisionCl,					{ -17,	136,	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // floating stone 2
	{&CollisionCl,					{  63,	104,	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // floating stone 3
	{&CollisionCl,					{ 191,	 72,	0, 0}, 0, NULL, NULL, (void*)&collision_16_2_4, false}, // stepstone right
	{&CollisionCl,					{ -81,	-16,	0, 0}, 0, NULL, NULL, (void*)&collision_48_4_4, false}, // floor above floating platforms

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1TowerMain2Collisions3[] =
{
	{&CollisionTopCl,				{ -81,	-152,	0, 0}, 0, NULL, NULL, (void*)&collision_6_2_4, false}, // top room one way
	{&CollisionCl,					{ 143,	-144,	0, 0}, 0, NULL, NULL, (void*)&collision_48_4_4, false}, // top room right floor
	{&CollisionCl,					{-145,   -80,	0, 0}, 0, NULL, NULL, (void*)&collision_8_20_4, false}, // top room left floor
	{&CollisionCl,					{  -1,	-232,	0, 0}, 0, NULL, NULL, (void*)&collision_48_2_4, false}, // top room ceiling
	{&CollisionCl,					{  79,	-192,	0, 0}, 0, NULL, NULL, (void*)&collision_4_8_4, false}, // top room right wall

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Level1TowerStageChildren[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this spec
	{&Level1TowerMainBackEntity,	{192,	LEVEL_1_TOWER_HEIGHT, 32, LAYER_0_BACKGROUND_DISPLACEMENT + 1}, 0, "BkgImg", NULL, NULL, true},
	{&LavaEntity,						{190,	LEVEL_1_TOWER_HEIGHT + 64, 	LAYER_0, 0}, 0, "Lava", (struct PositionedEntity*)LavaChildEntities, NULL, false},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	// part 1
	{&KeyDoorEntity,					{48, 	LEVEL_1_TOWER_HEIGHT - 96, 		LAYER_0_DOORS - LAYER_0_FOREGROUND, LAYER_0_DOORS_DISPLACEMENT - LAYER_0_FOREGROUND_DISPLACEMENT}, 0, "EntryDoor", NULL, (void*)&Level1MainTowerEntryPoint, false},
	{&ManagedEntity,				{192,	LEVEL_1_TOWER_HEIGHT - 256,		LAYER_0_FOREGROUND, 0}, 0, NULL, (struct PositionedEntity*)Level1TowerMain1Entities, NULL, false},
	{&ManagedEntity,				{192,	LEVEL_1_TOWER_HEIGHT - 257,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)Level1TowerMain1Collisions1, NULL, false},
	{&ManagedEntity,				{192,	LEVEL_1_TOWER_HEIGHT - 257,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)Level1TowerMain1Collisions2, NULL, false},
	{&TorchSmokeParticleSystem,				{204,	LEVEL_1_TOWER_HEIGHT - 126, 	LAYER_0_FOREGROUND + 12, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},

	{&LavaTriggerEntity,				{174,	LEVEL_1_TOWER_HEIGHT - 130, 	LAYER_0, 0}, 0, NULL, NULL, NULL, false},
	{&CogWheelEntity,					{310,	LEVEL_1_TOWER_HEIGHT - 40, 		LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT + 1}, 0, NULL, NULL, NULL, false},

	{&CoinEntity, 						{132,	LEVEL_1_TOWER_HEIGHT - 92, 		LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "48", NULL, NULL, false},
	{&CoinEntity, 						{148,	LEVEL_1_TOWER_HEIGHT - 92, 		LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "49", NULL, NULL, false},
	{&CoinEntity, 						{164,	LEVEL_1_TOWER_HEIGHT - 92, 		LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "50", NULL, NULL, false},
	{&CoinEntity, 						{180,	LEVEL_1_TOWER_HEIGHT - 92, 		LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "51", NULL, NULL, false},

	{&GrassEntity, 					{324,	LEVEL_1_TOWER_HEIGHT - 121, 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&CoinEntity, 						{264,	LEVEL_1_TOWER_HEIGHT - 204, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "52", NULL, NULL, false},
	{&CoinEntity, 						{280,	LEVEL_1_TOWER_HEIGHT - 204, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "53", NULL, NULL, false},

	{&Snail8Entity, 					{132,	LEVEL_1_TOWER_HEIGHT - 248, 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&MovingPlatformV6Entity,		{60,	LEVEL_1_TOWER_HEIGHT - 300, 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&BandanaEntity, 					{296,	LEVEL_1_TOWER_HEIGHT - 317, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "3", NULL, NULL, false},
	{&CoinEntity, 						{312,	LEVEL_1_TOWER_HEIGHT - 317, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "54", NULL, NULL, false},
	{&CoinEntity, 						{328,	LEVEL_1_TOWER_HEIGHT - 317, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "55", NULL, NULL, false},

	{&SawBladeH8Entity, 				{200,	LEVEL_1_TOWER_HEIGHT - 370, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
	{&SawBladeH8Entity, 				{224,	LEVEL_1_TOWER_HEIGHT - 450, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&CoinEntity, 						{120,	LEVEL_1_TOWER_HEIGHT - 464, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "56", NULL, NULL, false},
	{&CoinEntity, 						{136,	LEVEL_1_TOWER_HEIGHT - 464, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "57", NULL, NULL, false},

	{&MovingPlatformV6Entity,		{336,	LEVEL_1_TOWER_HEIGHT - 424, 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	// part 2
	{&Level1TowerMain2Entity,		{192,	LEVEL_1_TOWER_HEIGHT - 768, 	LAYER_0_FOREGROUND, 0}, 0, "Main_2", NULL, NULL, false},
	{&ManagedEntity,				{192,	LEVEL_1_TOWER_HEIGHT - 769,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)Level1TowerMain2Collisions1, NULL, false},
	{&ManagedEntity,				{192,	LEVEL_1_TOWER_HEIGHT - 769,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)Level1TowerMain2Collisions2, NULL, false},

	{&CoinEntity, 						{88,	LEVEL_1_TOWER_HEIGHT - 623, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "58", NULL, NULL, false},
	{&CoinEntity, 						{104,	LEVEL_1_TOWER_HEIGHT - 623, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "59", NULL, NULL, false},

	{&CoinEntity, 						{168,	LEVEL_1_TOWER_HEIGHT - 655, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "60", NULL, NULL, false},
	{&CoinEntity, 						{184,	LEVEL_1_TOWER_HEIGHT - 655, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "61", NULL, NULL, false},

	{&CoinEntity, 						{248,	LEVEL_1_TOWER_HEIGHT - 687, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "62", NULL, NULL, false},
	{&CoinEntity, 						{264,	LEVEL_1_TOWER_HEIGHT - 687, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "63", NULL, NULL, false},

	{&MovingPlatformV6Entity,		{336,	LEVEL_1_TOWER_HEIGHT - 760,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&Snail8Entity, 					{210,	LEVEL_1_TOWER_HEIGHT - 808, 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&MovingPlatformV6Entity,		{112,	LEVEL_1_TOWER_HEIGHT - 852,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
	{&CoinEntity, 						{40, 	LEVEL_1_TOWER_HEIGHT - 942, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "64", NULL, NULL, false},
	{&GoalDoorEntity, 				{208,	LEVEL_1_TOWER_HEIGHT - 944, 	LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "GoalDoor", NULL, NULL, false},
	{&TorchOffEntity,					{176,	LEVEL_1_TOWER_HEIGHT - 948, 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
	{&TorchSmokeParticleSystem,				{176,	LEVEL_1_TOWER_HEIGHT - 958, 	LAYER_0_FOREGROUND + 12, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&TorchOffEntity,					{240,	LEVEL_1_TOWER_HEIGHT - 948, 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&ManagedEntity,				{192,	LEVEL_1_TOWER_HEIGHT - 769,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)Level1TowerMain2Collisions3, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1TowerStageUiChildren[] =
{
	{&LowPowerIndicatorEntity, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GuiEntity, {192, 215, 0, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Level1TowerStageFonts[] =
{
	&PlatformerFont,
	&AstonishSFont,
	&PlatformerGuiFont,

	NULL
};

CharSetROMSpec* const Level1TowerStageCharsets[] =
{
	NULL
};

TextureSpec* const Level1TowerStageTextures[] =
{
/*	&CogWheelTexture,
	&Level1TowerBack1Texture,
	&Level1TowerMainBack1Texture,
	&Level1TowerMainBack1Texture,
	&Level1TowerMain1Texture,
	&Level1TowerMain1Texture,
	&DoorTexture,
	&GuiTexture,
	&LavaTexture,
	&LavaTopTexture,
	&DarknessOverlayTexture,
*/
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Level1TowerStage =
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
			LEVEL_1_TOWER_HEIGHT,
			// z
			__SCREEN_DEPTH,
		},

		// camera's initial position inside the game world
		{
			// x
			0,
			// y
			SCREEN_Y_POSITION - __SCREEN_HEIGHT / 2,
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
		80,
		// unload padding
		32,
		// streaming amplitude
		48,
		// particle removal delay cycles
		4,
		// deferred
		false,
	},

	// rendering
	{
		// maximum number of texture's rows to write each time the texture writing is active
		64,

		// maximum number of rows to compute on each call to the affine functions
		24,

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
		2,

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
			80,
		},

		// object segments z coordinates
		// Note that each SPT's z coordinate must be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
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
			// horizontal View point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// vertical View point center
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
		(FontSpec**)Level1TowerStageFonts,

		// char sets to preload
		(CharSetSpec**)Level1TowerStageCharsets,

		// textures to preload
		(TextureSpec**)Level1TowerStageTextures,

		// background sounds
		(Sound**)NULL,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)Level1TowerStageUiChildren,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Level1TowerStageChildren,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec Level1TowerStageMainEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1TowerStage,

	// name of the entity to start at
	"EntryDoor",

	// offset from entry point (x, y, z)
	{
		19,
		3,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	true,
};
