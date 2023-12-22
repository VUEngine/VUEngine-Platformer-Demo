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
#include <PostProcessingRain.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern SoundROMSpec* const Level1Sounds[];

extern StageEntryPointROMSpec Level1HouseStageMainEntryPoint;
extern StageEntryPointROMSpec Level1CoinRoomStageMainEntryPoint;
extern StageEntryPointROMSpec Level1IntersectionStageUpperEntryPoint;
extern StageEntryPointROMSpec Level1IntersectionStageExitEntryPoint;
extern StageEntryPointROMSpec Level1TowerStageMainEntryPoint;

StageEntryPointROMSpec Level1MainLsBackEntryPoint;
StageEntryPointROMSpec Level1MainLsFrontEntryPoint;

extern EntitySpec BandanaEntity;
extern EntitySpec BushEntity;
extern EntitySpec CannonEntity;
extern EntitySpec CloudAEntity;
extern EntitySpec CloudsEntity;
extern EntitySpec CoinEntity;
extern EntitySpec CoinBackEntity;
extern EntitySpec CollisionCl;
extern EntitySpec CollisionHitCl;
extern EntitySpec CollisionTopCl;
extern EntitySpec ManagedEntity;
extern EntitySpec DoorEntity;
extern EntitySpec DoubleJumpSignEntity;
extern EntitySpec GrassEntity;
extern EntitySpec GuiEntity;
extern EntitySpec HeroEntity;
extern EntitySpec HideLayer10x7Entity;
extern EntitySpec JumpSignEntity;
extern EntitySpec KeyEntity;
extern EntitySpec KeyDoorEntity;
extern EntitySpec LayerSwitchDoorEntity;
extern EntitySpec LayerSwitchDoorBackEntity;
extern EntitySpec Level1HouseEntity;
extern EntitySpec Level1Main1Back1Entity;
extern EntitySpec Level1Main1Back5Entity;
extern EntitySpec Level1Main1Main1Entity;
extern EntitySpec Level1Main1Main2Entity;
extern EntitySpec Level1Main1Main3AEntity;
extern EntitySpec Level1Main1Main3BEntity;
extern EntitySpec Level1Main1Main4Entity;
extern EntitySpec Level1Main1Main5Entity;
extern EntitySpec Level1Main1Main6Entity;
extern EntitySpec Level1TowerEntity;
extern EntitySpec LowPowerIndicatorEntitySpec;
extern EntitySpec ManagedEntity;
extern EntitySpec Mound1Entity;
extern EntitySpec Mound2Entity;
extern EntitySpec MoundBgBackEntity;
extern EntitySpec MoundBgFrontEntity;
extern EntitySpec RunSignEntity;
extern EntitySpec SawBladeH3Entity;
extern EntitySpec SawBladeH8Entity;
extern EntitySpec SawBladeV3Entity;
extern EntitySpec SmokeParticleSystem;
extern EntitySpec Snail3Entity;
extern EntitySpec StarEntity;
extern EntitySpec WaterSplashParticleSystem;
extern EntitySpec WaterfallStream2x16Entity;
extern EntitySpec WaterfallStream2x28Entity;
extern EntitySpec WaterfallTopEntity;
extern EntitySpec WaterPondEntity;

extern CharSetSpec RunSignCharset;
extern CharSetSpec JumpSignCharset;
extern CharSetSpec DoubleJumpSignCharset;
extern CharSetSpec WaterfallStream2x16Charset;
extern CharSetSpec WaterfallStream2x28Charset;
extern CharSetSpec WaterfallTopCharset;
extern CharSetSpec BushCharset;
extern CharSetSpec CannonBallCharset;
extern CharSetSpec SmokeParticleSmallCharset;
extern CharSetSpec CannonCharset;
extern CharSetSpec CoinBackCharset;
extern CharSetSpec CoinBackSilhouetteCharset;
extern CharSetSpec CoinCharset;
extern CharSetSpec CoinSilhouetteCharset;
extern CharSetSpec DoorBackCharset;
extern CharSetSpec DoorCharset;
extern CharSetSpec GrassCharset;
extern CharSetSpec HeroBandanaCharset;
extern CharSetSpec KeyCharset;
extern CharSetSpec Level1HouseCharset;
extern CharSetSpec Level1Main1MainBackCharset;
extern CharSetSpec Level1Main1MainCharset;
extern CharSetSpec Level1Main1MainFrontCharset;
extern CharSetSpec LowPowerIndicatorCharset;
extern CharSetSpec MoundBgBackCharset;
extern CharSetSpec MoundBgFrontCharset;
extern CharSetSpec MoundBgMiddleCharset;
extern CharSetSpec SawBladeCharset;
extern CharSetSpec SnailCharset;

extern TextureSpec WaterfallStream2x16Texture;
extern TextureSpec WaterfallStream2x28Texture;
extern TextureSpec WaterfallTopTexture;
extern TextureSpec CannonBallTexture;
extern TextureSpec CannonTexture;
extern TextureSpec CoinBackSilhouetteTexture;
extern TextureSpec CoinBackTexture;
extern TextureSpec CoinSilhouetteTexture;
extern TextureSpec CoinTexture;
extern TextureSpec DoorBackTexture;
extern TextureSpec DoorTexture;
extern TextureSpec DustParticleSmallTexture;
extern TextureSpec HeroBandanaTexture;
extern TextureSpec KeyTexture;
extern TextureSpec Level1HouseTexture;
extern TextureSpec Level1Main1Back1Texture;
extern TextureSpec Level1Main1Main1Texture;
extern TextureSpec Level1Main1Main2Texture;
extern TextureSpec Level1Main1Main3Texture;
extern TextureSpec Level1Main1MainBack3aTexture;
extern TextureSpec Level1Main1MainBack3bTexture;
extern TextureSpec Level1Main1MainBack3cTexture;
extern TextureSpec Level1Main1MainFront1Texture;
extern TextureSpec Level1Main1MainFront2aTexture;
extern TextureSpec Level1Main1MainFront2bTexture;
extern TextureSpec Level1Main1MainFront3aTexture;
extern TextureSpec Level1Main1MainFront3bTexture;
extern TextureSpec LowPowerIndicatorTextureSpec;
extern TextureSpec MoundBgBackTexture;
extern TextureSpec MoundBgFrontTexture;
extern TextureSpec MoundBgMiddleTexture;
extern TextureSpec SawBladeTexture;
extern TextureROMSpec GuiTexture;

extern Size collision_2_28_4;
extern Size collision_3_2_4;
extern Size collision_6_2_4;
extern Size collision_8_3_4;
extern Size collision_12_4_4;
extern Size collision_14_6_4;
extern Size collision_14_18_4;
extern Size collision_18_6_4;
extern Size collision_20_2_4;
extern Size collision_20_6_4;
extern Size collision_20_32_4;
extern Size collision_28_16_4;
extern Size collision_32_14_4;
extern Size collision_34_30_4;
extern Size collision_38_10_4;
extern Size collision_44_3_4;
extern Size collision_48_10_4;
extern Size collision_48_18_4;
extern Size collision_48_28_4;
extern Size collision_45_5_4;
extern Size collision_62_25_4;


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMSpec Level1Main1Main1Collisions[] =
{
	{&CollisionCl,						{-137, -12, 0, 0},											0, NULL, NULL, (void*)&collision_34_30_4, false}, // left floor
	{&CollisionCl,						{ 111,  12, 0, 0},											0, NULL, NULL, (void*)&collision_34_30_4, false}, // right floor

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main2Collisions1[] =
{
	{&CollisionTopCl,					{-227, -104, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // left top one-way
	{&CollisionCl, 						{-148,  -56, 0, 0},											0, NULL, NULL, (void*)&collision_14_18_4, false}, // floor left to spikes
	{&CollisionCl, 						{ 126,  -56, 0, 0},											0, NULL, NULL, (void*)&collision_14_18_4, false}, // floor right to spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main2Collisions2[] =
{
	{&CollisionCl, 						{  -9, -132, 0, 0},											0, NULL, NULL, (void*)&collision_8_3_4, false}, // floating block over spikes
	{&CollisionHitCl,					{  -9,  -94, 0, 0},											0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes hit collision
	{&CollisionCl, 						{  -9,  -40, 0, 0},											0, NULL, NULL, (void*)&collision_32_14_4, false}, // floor below spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main2Collisions3[] =
{
	{&CollisionTopCl,					{-227,   72, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // left bottom one-way
	{&CollisionCl, 						{ -11,  136, 0, 0},											0, NULL, NULL, (void*)&collision_48_18_4, false}, // secret bottom floor
	{&CollisionTopCl,					{ 209,  -72, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // right top one-way

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main2Collisions4[] =
{
	{&CollisionTopCl,					{ 209,  24, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // right bottom one-way
	{&CollisionCl,						{ 126,  38, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // wall right to the secret door
	{&CollisionCl,						{ 238,  88, 0, 0},											0, NULL, NULL, (void*)&collision_18_6_4, false}, // floor under the one-way passage

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main3Collisions1[] =
{
	{&CollisionTopCl, 					{-227,   -8, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // top one-way
	{&CollisionTopCl, 					{-227,   88, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // bottom one-way
	{&CollisionCl, 						{  -9, -138, 0, 0},											0, NULL, NULL, (void*)&collision_48_18_4, false}, // above hidden area

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main3Collisions2[] =
{
	{&CollisionCl, 						{ -49,  24,	0, 0},											0, NULL, NULL, (void*)&collision_38_10_4, false},
	{&CollisionCl, 						{  -9, -13,	0, 0},											0, NULL, NULL, (void*)&collision_28_16_4, false},
	{&CollisionCl, 						{  31, -41,	0, 0},											0, NULL, NULL, (void*)&collision_38_10_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main3Collisions3[] =
{
	{&CollisionCl, 						{  -9,	88, 0, 0},											0, NULL, NULL, (void*)&collision_48_10_4, false}, // ceiling above steps area
	{&CollisionCl,						{-162, 232, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // 2nd lowest left step
	{&CollisionCl,						{-113, 256, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // lowest left step

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main3Collisions4[] =
{
	{&CollisionCl,						{ 103, 272, 0, 0},											0, NULL, NULL, (void*)&collision_28_16_4, false}, // lowest right step

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main4Collisions1[] =
{
	{&CollisionCl,						{-297,  40, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // lowest step after ceiling
	{&CollisionCl,						{-217,   8, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // middle step after ceiling
	{&CollisionCl,						{-137, -24, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // highest step after ceiling

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main4Collisions2[] =
{
	{&CollisionCl,						{ -33,  -56, 0, 0},											0, NULL, NULL, (void*)&collision_20_6_4, false}, // floor left to spikes
	{&CollisionCl, 						{ 127,  -84, 0, 0},											0, NULL, NULL, (void*)&collision_8_3_4, false}, // floating block over spikes
	{&CollisionCl,						{ 123,  -24, 0, 0},											0, NULL, NULL, (void*)&collision_20_6_4, false}, // floor right to spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main4Collisions3[] =
{
	{&CollisionHitCl, 					{ 127,	-46, 0, 0},													0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes hit collision
	{&CollisionCl, 						{ 287,	 48, 0, 0},													0, NULL, NULL, (void*)&collision_20_32_4, false}, // floor below spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Back5Collisions1[] =
{
	{&CollisionCl, 						{  -6, -123, 0, 0},													0, NULL, NULL, (void*)&collision_44_3_4, false},
	{&CollisionCl, 						{ -68,  -94, 0, 0},													0, NULL, NULL, (void*)&collision_45_5_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Back5Collisions2[] =
{
	{&CollisionCl, 						{  -3,   28, 0, 0},													0, NULL, NULL, (void*)&collision_62_25_4, false},
	{&CollisionTopCl, 					{ 179, -112, 0, 0},													0, NULL, NULL, (void*)&collision_6_2_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main5Collisions[] =
{
	{&CollisionCl, 						{ -29,  -84, 0, 0},													0, NULL, NULL, (void*)&collision_8_3_4, false}, // left floating block
	{&CollisionCl, 						{  81,  -84, 0, 0},													0, NULL, NULL, (void*)&collision_8_3_4, false}, // middle floating block
	{&CollisionCl, 						{ 195,  -84, 0, 0},													0, NULL, NULL, (void*)&collision_8_3_4, false}, // right floating block

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main6Children[] =
{
	{&Level1Main1Main6Entity, 			{   0, 	  0, 0, 0},													0, NULL, NULL, NULL, false},
	{&HideLayer10x7Entity,				{ -64,  -76, -SORT_INCREMENT * 2, 0}, 								0, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main6Collisions[] =
{
	{&CollisionCl, 						{ -57,	 64, 0, 0},													0, NULL, NULL, (void*)&collision_48_28_4, false},
	{&CollisionTopCl, 					{-131, -104, 0, 0},													0, NULL, NULL, (void*)&collision_6_2_4, false},
	{&CollisionCl,						{ -57, -112, 0, 0},													0, NULL, NULL, (void*)&collision_12_4_4, false},
	{&CollisionCl, 						{ 167,	-16, 0, 0},													0, NULL, NULL, (void*)&collision_48_28_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1Main1Main1Children[] =
{
	{&RunSignEntity,					{ -24,	-148, LAYER_0_BACKGROUND - LAYER_0_FOREGROUND, 0},			0, NULL, NULL, NULL, false},
	{&CoinEntity,						{   0,	-163, LAYER_0_ITEMS - LAYER_0_FOREGROUND, 0},				1, NULL, NULL, NULL, false},
	{&CoinEntity,						{-116,	-163, LAYER_0_ITEMS - LAYER_0_FOREGROUND, 0},				2, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec Level1MainStageChildren[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this spec
	{&MoundBgBackEntity,				{   0,  120, LAYER_5 + LAYER_INCREMENT*3, 0},						0, NULL, NULL, NULL, true},
	{&CloudsEntity,						{   0,  194, LAYER_5 + LAYER_INCREMENT*2, 0},						0, NULL, NULL, NULL, true},
	{&MoundBgFrontEntity,				{   0,  212, LAYER_5 + LAYER_INCREMENT*0, 0},						0, NULL, NULL, NULL, true},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	// left border
	{&CollisionCl,						{  -8,  128, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, (void*)&collision_2_28_4, false},

	// part 1
	{&Level1Main1Main1Entity,			{ 256,  360, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&SmokeParticleSystem,				{  88,  150, 40, LAYER_0_BACKGROUND_DISPLACEMENT},					0, NULL, NULL, NULL, false},
	{&Level1HouseEntity,				{  88,  192, LAYER_0_DECORATIONS, LAYER_0_DOORS_DISPLACEMENT}, 		0, "House", NULL, NULL, false},
	{&KeyDoorEntity,					{  44,  220, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "HouseEnt", NULL, (void*)&Level1HouseStageMainEntryPoint, false},
	{&ManagedEntity,					{ 256,  368, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main1Collisions, NULL, false},

	{&RunSignEntity,					{ 232,  220, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},0, NULL, NULL, NULL, false},
	{&CoinEntity,						{ 184,  225, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			0, "1", NULL, NULL, false},
	{&CoinEntity,						{ 200,  225, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			0, "2", NULL, NULL, false},

	{&Level1Main1Back1Entity,			{ 360,  248, LAYER_3, 0},											0, NULL, NULL, NULL, false},

	{&StarEntity,						{ 240,	 96, LAYER_5 + LAYER_INCREMENT*3, 0},						0, NULL, NULL, NULL, false},

	{&CoinEntity,						{ 320,	248, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			0, "3", NULL, NULL, false},
	{&CoinEntity,						{ 336,	248, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			0, "4", NULL, NULL, false},
	{&SawBladeH8Entity,					{ 352,	259, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&JumpSignEntity,					{ 472,	244, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},0, NULL, NULL, NULL, false},

	// part 2
	{&Level1Main1Main2Entity,			{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&ManagedEntity,					{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main2Collisions1, NULL, false},
	{&ManagedEntity,					{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main2Collisions2, NULL, false},
	{&ManagedEntity,					{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main2Collisions3, NULL, false},
	{&ManagedEntity,					{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main2Collisions4, NULL, false},

	{&WaterfallTopEntity,				{ 596, 266, LAYER_0_FOREGROUND, - SORT_INCREMENT*2},				0, NULL, NULL, NULL, false},
	{&WaterfallStream2x28Entity,		{ 596, 378, LAYER_0_FOREGROUND, - SORT_INCREMENT*2}, 				0, NULL, NULL, NULL, false},

	{&CoinEntity,						{ 528, 228, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "5", NULL, NULL, false},
	{&CoinEntity,						{ 544, 228, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "6", NULL, NULL, false},
	{&CoinEntity,						{ 732, 196, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "7", NULL, NULL, false},
	{&BandanaEntity,					{ 756, 196, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "1", NULL, NULL, false},
	{&CoinEntity,						{ 780, 196, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "8", NULL, NULL, false},

	{&BushEntity,						{ 600, 412, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},

	// part 3
	{&HideLayer10x7Entity,				{1068, 196,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 	0, NULL, NULL, NULL, false},
	{&Level1Main1Main3AEntity, 			{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&Level1Main1Main3BEntity, 			{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&DoorEntity,						{ 798, 401, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},				0, "CoinEntr", NULL, (void*)&Level1CoinRoomStageMainEntryPoint, false},
	{&HideLayer10x7Entity,				{1372, 260,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 	0, NULL, NULL, NULL, false},

	{&ManagedEntity,					{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main3Collisions1, NULL, false},
	{&ManagedEntity,					{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main3Collisions2, NULL, false},
	{&ManagedEntity,					{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main3Collisions3, NULL, false},
	{&ManagedEntity,					{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main3Collisions4, NULL, false},

	{&CoinEntity,						{ 988, 260, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "9", NULL, NULL, false},
	{&CoinEntity,						{ 988, 308, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "10", NULL, NULL, false},
	{&CoinEntity,						{ 988, 356, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "11", NULL, NULL, false},
	{&GrassEntity,						{1052, 408, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&DoorEntity,						{1086, 208, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},				0, "IntEntrD", NULL, (void*)&Level1IntersectionStageUpperEntryPoint, false},

	{&WaterfallTopEntity,				{1156, 346, LAYER_0_FOREGROUND, -(SORT_INCREMENT*2)},				0, NULL, NULL, NULL, false},
	{&WaterfallStream2x16Entity,		{1156, 408, LAYER_0_FOREGROUND, -(SORT_INCREMENT*2)}, 				0, NULL, NULL, NULL, false},
	{&WaterPondEntity,					{1173, 465, LAYER_0_FOREGROUND, 0},									0, NULL, NULL, NULL, false},

	{&SawBladeV3Entity,					{1197, 472, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&DoubleJumpSignEntity,				{1244, 432, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&GrassEntity,						{1280, 440, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&CoinEntity,						{1340, 432, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "12", NULL, NULL, false},
	{&CoinEntity,						{1356, 432, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "13", NULL, NULL, false},
	{&DoorEntity,						{1373, 272, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},				0, "IntExitD", NULL, (void*)&Level1IntersectionStageExitEntryPoint, false},
	{&KeyEntity,						{1348, 276, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "2", NULL, NULL, false},
	{&BushEntity,						{1430, 412, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&Snail3Entity,						{1496, 377, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&Snail3Entity,						{1576, 345, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&Mound1Entity,						{1668, 300, LAYER_0_BACKGROUND + 16, LAYER_0_BACKGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&CoinEntity,						{1724, 304, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "14", NULL, NULL, false},
	{&CoinEntity,						{1740, 304, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "15", NULL, NULL, false},

	// part 4
	{&Level1Main1Main4Entity, 			{1732, 400, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&ManagedEntity,					{1732, 400,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main4Collisions1, NULL, false},
	{&ManagedEntity,					{1732, 400,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main4Collisions2, NULL, false},
	{&ManagedEntity,					{1732, 400,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main4Collisions3, NULL, false},

	{&SawBladeH3Entity,					{1861, 303, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},				0, NULL, NULL, NULL, false},
	{&Mound2Entity,						{2024, 301, LAYER_0_BACKGROUND + 16, LAYER_0_BACKGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},

	// part 5 (back)
	{&Level1Main1Back5Entity,			{2336,  328, LAYER_2, 0}, 											0, NULL, NULL, NULL, false},
	{&LayerSwitchDoorBackEntity, 		{2481,  299, LAYER_2, 0}, 											0, "DoorBk1", NULL, (void*)&Level1MainLsFrontEntryPoint, false},
	{&ManagedEntity,					{2336,  388, LAYER_2, 0}, 											0, NULL, (struct PositionedEntity*)Level1Main1Back5Collisions1, NULL, false},
	{&ManagedEntity,					{2328,  384, LAYER_2, 0}, 											0, NULL, (struct PositionedEntity*)Level1Main1Back5Collisions2, NULL, false},
	{&CannonEntity,						{2180,  286, LAYER_2, 0},											0, NULL, NULL, NULL, false},
	{&CannonEntity,						{2404,  286, LAYER_2, 0},											0, NULL, NULL, NULL, false},
	{&CoinBackEntity,					{2093,  264, LAYER_2_ITEMS, 0},										0, "16", NULL, NULL, false},
	{&CoinBackEntity,					{2105,  264, LAYER_2_ITEMS, 0},										0, "17", NULL, NULL, false},
	{&CoinBackEntity,					{2263,  244, LAYER_2_ITEMS, 0},										0, "18", NULL, NULL, false},
	{&CoinBackEntity,					{2275,  244, LAYER_2_ITEMS, 0},										0, "19", NULL, NULL, false},

	// part 5
	{&Level1Main1Main5Entity, 			{2208, 392, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&ManagedEntity,					{2208, 400,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main5Collisions, NULL, false},
	{&CoinEntity,						{2172, 292, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "20", NULL, NULL, false},
	{&CoinEntity,						{2188, 292, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "21", NULL, NULL, false},
	{&CoinEntity,						{2396, 292, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "22", NULL, NULL, false},
	{&CoinEntity,						{2412, 292, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "23", NULL, NULL, false},

	// part 6
	{&Level1Main1Main6Entity, 			{2732, 364, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&HideLayer10x7Entity,				{2668, 296, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&ManagedEntity,					{2732, 372, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)Level1Main1Main6Collisions, NULL, false},
	{&StarEntity,						{2588, 112, LAYER_5 + LAYER_INCREMENT*3, 0},						0, NULL, NULL, NULL, false},
	{&LayerSwitchDoorEntity,			{2669, 308, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "DoorFt1", NULL, (void*)&Level1MainLsBackEntryPoint, false},
	{&CoinEntity,						{2732, 232, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "24", NULL, NULL, false},
	{&CoinEntity,						{2748, 232, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "25", NULL, NULL, false},
	{&Level1TowerEntity,				{2894, 132, 32, LAYER_0_BACKGROUND_DISPLACEMENT},					0, NULL, NULL, NULL, false},
	{&CloudAEntity,						{2796, 104, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&CloudAEntity,						{2868, 120, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&CloudAEntity,						{2972, 112, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&KeyDoorEntity,					{2891, 228, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "TowrEnt", NULL, (void*)&Level1TowerStageMainEntryPoint, false},
	{&GrassEntity,						{2960, 237, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},

	// right border
	{&CollisionCl,						{2995, 132, LAYER_0, 0},											0, NULL, NULL, (void*)&collision_2_28_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec Level1MainStageUiChildren[] =
{
	{&LowPowerIndicatorEntitySpec, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GuiEntity, {192, 215, 0, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const Level1MainStageFonts[] =
{
	&PlatformerFontSpec,
	&AstonishSFontSpec,
	&PlatformerGuiFontSpec,

	NULL
};

CharSetROMSpec* const Level1MainStageCharsets[] =
{
	&Level1Main1MainCharset,
	&Level1Main1MainFrontCharset,
	&Level1Main1MainBackCharset,
//	&DoorCharset,
//	&DoorBackCharset,
//	&CoinCharset,
//	&CoinBackCharset,
//	&CoinSilhouetteCharset,
//	&CoinBackSilhouetteCharset,
//	&LowPowerIndicatorCharset,
	&MoundBgBackCharset,
	&MoundBgMiddleCharset,
	&MoundBgFrontCharset,
//	&SnailCharset,
//	&GrassCharset,
//	&BushCharset,
//	&Level1HouseCharset,
//	&SawBladeCharset,
//	&KeyCharset,
//	&HeroBandanaCharset,
//	&CannonCharset,
//	&CannonBallCharset,
	&SmokeParticleSmallCharset,
//	&RunSignCharset,
//	&JumpSignCharset,
//	&DoubleJumpSignCharset,
//	&WaterfallStream2x28Charset,
//	&WaterfallTopCharset,

	NULL
};

TextureSpec* const Level1MainStageTextures[] =
{
	&Level1Main1Main3Texture,
	&Level1Main1MainFront3aTexture,
	&Level1Main1MainFront3bTexture,
	&Level1Main1MainBack3aTexture,
	&Level1Main1MainBack3bTexture,
	&Level1Main1MainBack3cTexture,
	&Level1Main1Main1Texture,
	&Level1Main1Back1Texture,
	&Level1Main1Main2Texture,
	&Level1Main1MainFront1Texture,
	&Level1Main1MainFront2aTexture,
	&Level1Main1MainFront2bTexture,
	&LowPowerIndicatorTextureSpec,
	&MoundBgBackTexture,
	&MoundBgMiddleTexture,
	&MoundBgFrontTexture,
	&DustParticleSmallTexture,
	&SawBladeTexture,
	&DoorTexture,
	&DoorBackTexture,
	&Level1HouseTexture,
	&CoinTexture,
	&CoinBackTexture,
	&CoinSilhouetteTexture,
	&CoinBackSilhouetteTexture,
	&HeroBandanaTexture,
	&CannonTexture,
	&CannonBallTexture,
	&KeyTexture,
	&WaterfallStream2x28Texture,
	&WaterfallTopTexture,

	NULL
};

const PostProcessingEffect Level1MainStage_POST_PROCESSING_EFFECTS[] =
{
	PostProcessingRain_rain,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec Level1MainStage =
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
			2988,
			// y
			512,
			// z
			2988,
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
		80,
		// unload padding
		48,
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
		12,

		// maximum number of rows to compute on each call to the affine functions
		48,

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
		// Note that each SPT's z coordinate must be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
		{
			// __spt0
			LAYER_0_PARTICLES + 2,
			// __spt1
			LAYER_0_PARTICLES + 2,
			// __spt2
			LAYER_0_PARTICLES + 2,
			// __spt3
			15,
		},

		// optical configuration values
		{
			// maximum x view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE,
			// maximum y view distance's power into the horizon
			__MAXIMUM_Y_VIEW_DISTANCE,
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
		(FontSpec**)Level1MainStageFonts,

		// char sets to preload
		(CharSetSpec**)Level1MainStageCharsets,

		// textures to preload
		(TextureSpec**)Level1MainStageTextures,

		// background sounds
		(SoundSpec**)Level1Sounds,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)Level1MainStageUiChildren,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)Level1MainStageChildren,
	},

	// post processing effects
	(PostProcessingEffect*)Level1MainStage_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec Level1MainMainEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1MainStage,

	// name of the entity to start at
	"HouseEnt",

	// offset from entry point (x, y, z)
	{
		19,
		-10,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMSpec Level1MainHouseEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1MainStage,

	// name of the entity to start at
	"HouseEnt",

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

StageEntryPointROMSpec Level1MainCoinRoomEntryDoorEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1MainStage,

	// name of the entity to start at
	"CoinEntr",

	// offset from entry point (x, y, z)
	{
		-19,
		4,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__LEFT,

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMSpec Level1MainIntersectionEntryDoorEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1MainStage,

	// name of the entity to start at
	"IntEntrD",

	// offset from entry point (x, y, z)
	{
		-19,
		5,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__LEFT,

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMSpec Level1MainIntersectionExitDoorEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1MainStage,

	// name of the entity to start at
	"IntExitD",

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

StageEntryPointROMSpec Level1MainLsFrontEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1MainStage,

	// name of the entity to start at
	"DoorFt1",

	// offset from entry point (x, y, z)
	{
		0,
		-2,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMSpec Level1MainLsBackEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1MainStage,

	// name of the entity to start at
	"DoorBk1",

	// offset from entry point (x, y, z)
	{
		0,
		-8,
		-1,
		-1
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMSpec Level1MainTowerEntryPoint =
{
	// the stage to load
	(StageSpec*)&Level1MainStage,

	// name of the entity to start at
	"TowrEnt",

	// offset from entry point (x, y, z)
	{
		-19,
		5,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__LEFT,

	// whether this entry point acts as a checkpoint
	false,
};
