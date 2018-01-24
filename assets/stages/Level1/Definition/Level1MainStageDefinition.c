/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
#include <PostProcessingEffects.h>



//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL1_HOUSE_STAGE_MAIN_EP;
extern StageEntryPointROMDef LEVEL1_COIN_ROOM_STAGE_MAIN_EP;
extern StageEntryPointROMDef LEVEL1_INTERSECTION_STAGE_UPPER_EP;
extern StageEntryPointROMDef LEVEL1_INTERSECTION_STAGE_EXIT_EP;
extern StageEntryPointROMDef LEVEL1_TOWER_STAGE_MAIN_EP;
extern u16 WORLD_0_0_0_BGM[][2];

StageEntryPointROMDef LEVEL_1_MAIN_LS_BACK_EP;
StageEntryPointROMDef LEVEL_1_MAIN_LS_FRONT_EP;

extern EntityDefinition BANDANA_AG;
extern EntityDefinition BUSH_AG;
extern EntityDefinition CANNON_AC;
extern EntityDefinition CLOUD_A_IM;
extern EntityDefinition CLOUDS_IM;
extern EntityDefinition COIN_AG;
extern EntityDefinition COIN_BACK_AG;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition COLLISION_HIT_CL;
extern EntityDefinition COLLISION_TOP_CL;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition DOOR_AG;
extern EntityDefinition DOUBLE_JUMP_SIGN_IM;
extern EntityDefinition GRASS_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition HIDE_LAYER_10x7_AG;
extern EntityDefinition JUMP_SIGN_IM;
extern EntityDefinition KEY_AG;
extern EntityDefinition KEY_DOOR_AG;
extern EntityDefinition LAYER_SWITCH_DOOR_AG;
extern EntityDefinition LAYER_SWITCH_DOOR_BACK_AG;
extern EntityDefinition LEVEL_1_HOUSE_IM;
extern EntityDefinition LEVEL_1_MAIN_1_BACK_1_IM;
extern EntityDefinition LEVEL_1_MAIN_1_BACK_5_IM;
extern EntityDefinition LEVEL_1_MAIN_1_MAIN_1_IM;
extern EntityDefinition LEVEL_1_MAIN_1_MAIN_2_IM;
extern EntityDefinition LEVEL_1_MAIN_1_MAIN_3_A_IM;
extern EntityDefinition LEVEL_1_MAIN_1_MAIN_3_B_IM;
extern EntityDefinition LEVEL_1_MAIN_1_MAIN_4_IM;
extern EntityDefinition LEVEL_1_MAIN_1_MAIN_5_IM;
extern EntityDefinition LEVEL_1_MAIN_1_MAIN_6_IM;
extern EntityDefinition LEVEL_1_TOWER_IM;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition MOUND_1_IM;
extern EntityDefinition MOUND_2_IM;
extern EntityDefinition MOUND_BG_BACK_IM;
extern EntityDefinition MOUND_BG_FRONT_IM;
extern EntityDefinition RUN_SIGN_IM;
extern EntityDefinition SAW_BLADE_H3_AC;
extern EntityDefinition SAW_BLADE_H8_AC;
extern EntityDefinition SAW_BLADE_V3_AC;
extern EntityDefinition SMOKE_PS;
extern EntityDefinition SNAIL_3_AC;
extern EntityDefinition STAR_AG;
extern EntityDefinition WATER_SPLASH_PS;
extern EntityDefinition WATERFALL_STREAM_2x16_AG;
extern EntityDefinition WATERFALL_STREAM_2x28_AG;
extern EntityDefinition WATERFALL_TOP_AG;
extern EntityDefinition WATER_POND_EN;

extern CharSetDefinition RUN_SIGN_CH;
extern CharSetDefinition JUMP_SIGN_CH;
extern CharSetDefinition DOUBLE_JUMP_SIGN_CH;
extern CharSetDefinition WATERFALL_STREAM_2x16_CH;
extern CharSetDefinition WATERFALL_STREAM_2x28_CH;
extern CharSetDefinition WATERFALL_TOP_CH;
extern CharSetDefinition BUSH_CH;
extern CharSetDefinition CANNON_BALL_CH;
extern CharSetDefinition SMOKE_PARTICLE_SMALL_CH;
extern CharSetDefinition CANNON_CH;
extern CharSetDefinition COIN_BACK_CH;
extern CharSetDefinition COIN_BACK_SILHOUETTE_CH;
extern CharSetDefinition COIN_CH;
extern CharSetDefinition COIN_SILHOUETTE_CH;
extern CharSetDefinition DOOR_BACK_CH;
extern CharSetDefinition DOOR_CH;
extern CharSetDefinition GRASS_CH;
extern CharSetDefinition HERO_BANDANA_CH;
extern CharSetDefinition KEY_CH;
extern CharSetDefinition LEVEL_1_HOUSE_CH;
extern CharSetDefinition LEVEL_1_MAIN_1_MAIN_BACK_CH;
extern CharSetDefinition LEVEL_1_MAIN_1_MAIN_CH;
extern CharSetDefinition LEVEL_1_MAIN_1_MAIN_FRONT_CH;
extern CharSetDefinition MOUND_BG_BACK_CH;
extern CharSetDefinition MOUND_BG_FRONT_CH;
extern CharSetDefinition MOUND_BG_MIDDLE_CH;
extern CharSetDefinition SAW_BLADE_CH;
extern CharSetDefinition SNAIL_CH;

extern TextureDefinition WATERFALL_STREAM_2x16_TX;
extern TextureDefinition WATERFALL_STREAM_2x28_TX;
extern TextureDefinition WATERFALL_TOP_TX;
extern TextureDefinition CANNON_BALL_TX;
extern TextureDefinition CANNON_TX;
extern TextureDefinition COIN_BACK_SILHOUETTE_TX;
extern TextureDefinition COIN_BACK_TX;
extern TextureDefinition COIN_SILHOUETTE_TX;
extern TextureDefinition COIN_TX;
extern TextureDefinition DOOR_BACK_TX;
extern TextureDefinition DOOR_TX;
extern TextureDefinition DUST_PARTICLE_SMALL_TX;
extern TextureDefinition HERO_BANDANA_TX;
extern TextureDefinition KEY_TX;
extern TextureDefinition LEVEL_1_HOUSE_TX;
extern TextureDefinition LEVEL_1_MAIN_1_BACK_1_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_1_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_2_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_3_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_BACK_3A_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_BACK_3B_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_BACK_3C_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_FRONT_1_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_FRONT_2A_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_FRONT_2B_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_FRONT_3A_TX;
extern TextureDefinition LEVEL_1_MAIN_1_MAIN_FRONT_3B_TX;
extern TextureDefinition MOUND_BG_BACK_TX;
extern TextureDefinition MOUND_BG_FRONT_TX;
extern TextureDefinition MOUND_BG_MIDDLE_TX;
extern TextureDefinition SAW_BLADE_TX;

extern Size collision_2_28_4;
extern Size collision_3_2_4;
extern Size collision_7_2_4;
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
extern Size collision_47_3_4;
extern Size collision_48_10_4;
extern Size collision_48_18_4;
extern Size collision_48_28_4;
extern Size collision_49_5_4;
extern Size collision_67_25_4;


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_COLLISIONS[] =
{
	{&COLLISION_CL,					{(-136), (-12), 	(0), 0},	0, NULL, NULL, (void*)&collision_34_30_4, false}, // left floor
	{&COLLISION_CL,					{(112),	(12), 	(0), 0},	0, NULL, NULL, (void*)&collision_34_30_4, false}, // right floor

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_TOP_CL,				{(-226), (-104),	(0), 0},	0, NULL, NULL, (void*)&collision_7_2_4, false}, // left top one-way
	{&COLLISION_CL, 				{(-145), (-56),	(0), 0},	0, NULL, NULL, (void*)&collision_14_18_4, false}, // floor left to spikes
	{&COLLISION_CL, 				{(127),	(-56),	(0), 0},	0, NULL, NULL, (void*)&collision_14_18_4, false}, // floor right to spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{(-8),	(-132),	(0), 0},	0, NULL, NULL, (void*)&collision_8_3_4, false}, // floating block over spikes
	{&COLLISION_HIT_CL,				{(-8),	(-94),	(0), 0},	0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes hit collision
	{&COLLISION_CL, 				{(-8),	(-40),	(0), 0},	0, NULL, NULL, (void*)&collision_32_14_4, false}, // floor below spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_3[] =
{
	{&COLLISION_TOP_CL,				{(-226), (72),	(0), 0},	0, NULL, NULL, (void*)&collision_7_2_4, false}, // left bottom one-way
	{&COLLISION_CL, 				{(-10),	(136),	(0), 0},	0, NULL, NULL, (void*)&collision_48_18_4, false}, // secret bottom floor
	{&COLLISION_TOP_CL,				{(210),	(-72),	(0), 0},	0, NULL, NULL, (void*)&collision_7_2_4, false}, // right top one-way

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_4[] =
{
	{&COLLISION_TOP_CL,				{(210),	(24),	(0), 0},	0, NULL, NULL, (void*)&collision_7_2_4, false}, // right bottom one-way
	{&COLLISION_CL,					{(127),	(38),	(0), 0},	0, NULL, NULL, (void*)&collision_14_6_4, false}, // wall right to the secret door
	{&COLLISION_CL,					{(239),	(88),	(0), 0},	0, NULL, NULL, (void*)&collision_18_6_4, false}, // floor under the one-way passage

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1[] =
{
	{&COLLISION_TOP_CL, 			{(-226), (-8),	(0), 0},	0, NULL, NULL, (void*)&collision_7_2_4, false}, // top one-way
	{&COLLISION_TOP_CL, 			{(-226), (88),	(0), 0},	0, NULL, NULL, (void*)&collision_7_2_4, false}, // bottom one-way
	{&COLLISION_CL, 				{(-8),	(-138),	(0), 0},	0, NULL, NULL, (void*)&collision_48_18_4, false}, // above hidden area

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{(-48),	(24),	(0), 0},	0, NULL, NULL, (void*)&collision_38_10_4, false},
	{&COLLISION_CL, 				{(-8),	(-13),	(0), 0},	0, NULL, NULL, (void*)&collision_28_16_4, false},
	{&COLLISION_CL, 				{(32),	(-41),	(0), 0},	0, NULL, NULL, (void*)&collision_38_10_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_3[] =
{
	{&COLLISION_CL, 				{(-8),	(88),	(0), 0},	0, NULL, NULL, (void*)&collision_48_10_4, false}, // ceiling above steps area
	{&COLLISION_CL,					{(-161), (232),	(0), 0},	0, NULL, NULL, (void*)&collision_14_6_4, false}, // 2nd lowest left step
	{&COLLISION_CL,					{(-112), (256),	(0), 0},	0, NULL, NULL, (void*)&collision_14_6_4, false}, // lowest left step

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_4[] =
{
	{&COLLISION_CL,					{(104),	(272),	(0), 0},	0, NULL, NULL, (void*)&collision_28_16_4, false}, // lowest right step

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1[] =
{
	{&COLLISION_CL,					{(-296), (40), 	(0), 0},	0, NULL, NULL, (void*)&collision_14_6_4, false}, // lowest step after ceiling
	{&COLLISION_CL,					{(-216), (8), 	(0), 0},	0, NULL, NULL, (void*)&collision_14_6_4, false}, // middle step after ceiling
	{&COLLISION_CL,					{(-136), (-24), 	(0), 0},	0, NULL, NULL, (void*)&collision_14_6_4, false}, // highest step after ceiling

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2[] =
{
	{&COLLISION_CL,					{(-32),	(-56), 	(0), 0},	0, NULL, NULL, (void*)&collision_20_6_4, false}, // floor left to spikes
	{&COLLISION_CL, 				{(128),	(-84), 	(0), 0},	0, NULL, NULL, (void*)&collision_8_3_4, false}, // floating block over spikes
	{&COLLISION_CL,					{(124),	(-24), 	(0), 0},	0, NULL, NULL, (void*)&collision_20_6_4, false}, // floor right to spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_3[] =
{
	{&COLLISION_HIT_CL, 			{(128),	(-46), 	(0), 0},	0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes hit collision
	{&COLLISION_CL, 				{(288),	(48), 	(0), 0},	0, NULL, NULL, (void*)&collision_20_32_4, false}, // floor below spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_COLLISIONS_1[] =
{
	{&COLLISION_CL, 				{(-5),	(-119), (0), 0},	0, NULL, NULL, (void*)&collision_47_3_4, false},
	{&COLLISION_CL, 				{(-76),	(-91), 	(0), 0},	0, NULL, NULL, (void*)&collision_49_5_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{(0),	(32), 	(0), 0},	0, NULL, NULL, (void*)&collision_67_25_4, false},
	{&COLLISION_TOP_CL, 			{(182), (-107), (0), 0},	0, NULL, NULL, (void*)&collision_7_2_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_5_COLLISIONS[] =
{
	{&COLLISION_CL, 				{(-28),	(-84), 	(0), 0},	0, NULL, NULL, (void*)&collision_8_3_4, false}, // left floating block
	{&COLLISION_CL, 				{(82),	(-84), 	(0), 0},	0, NULL, NULL, (void*)&collision_8_3_4, false}, // middle floating block
	{&COLLISION_CL, 				{(196),	(-84), 	(0), 0},	0, NULL, NULL, (void*)&collision_8_3_4, false}, // right floating block

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_CHILDREN[] =
{
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	{(0), 	(0), 	(0), 0},		0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{(-64), 	(-76), 	(-SORT_INCREMENT * 2), 0}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_COLLISIONS[] =
{
	{&COLLISION_CL, 				{(-56),	(64), 	(0), 0},	0, NULL, NULL, (void*)&collision_48_28_4, false},
	{&COLLISION_TOP_CL, 			{(-130), (-104), 	(0), 0},	0, NULL, NULL, (void*)&collision_7_2_4, false},
	{&COLLISION_CL,					{(-56),	(-112), 	(0), 0},	0, NULL, NULL, (void*)&collision_12_4_4, false},
	{&COLLISION_CL, 				{(168),	(-16), 	(0), 0},	0, NULL, NULL, (void*)&collision_48_28_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_IM_CHILDREN[] =
{
	{&RUN_SIGN_IM,					{(232 - 256),	(220 - 368), 	(LAYER_0_BACKGROUND - LAYER_0_FOREGROUND), 0},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{(0),	(225 - 368 - 20), 	(LAYER_0_ITEMS - LAYER_0_FOREGROUND), 0},			1, NULL, NULL, NULL, false},
	{&COIN_AG,						{(200 - 256 - 60),	(225 - 368 - 20), 	(LAYER_0_ITEMS - LAYER_0_FOREGROUND), 0},			2, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,				{(0),	(140), 	(LAYER_5 + LAYER_INCREMENT*3), 0},					0, NULL, NULL, NULL, true},
	{&CLOUDS_IM,					{(0),	(198), 	(LAYER_5 + LAYER_INCREMENT*2), 0},					0, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM,			{(0),	(212), 	(LAYER_5 + LAYER_INCREMENT*0), 0},					0, NULL, NULL, NULL, true},

	{&HERO_AC,						{(56),	(288), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, HERO_NAME, NULL, NULL, false},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	// left border
	{&COLLISION_CL,					{(-8),	(128), 	(LAYER_0), 0},					0, NULL, NULL, (void*)&collision_2_28_4, false},

	// part 1
	{&SMOKE_PS,						{(84),	(150), 	LAYER_0_BACKGROUND, LAYER_0_BACKGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_1_IM,		{(256), (368), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_HOUSE_IM,				{(88),	(192), 	LAYER_0_BACKGROUND, LAYER_0_BACKGROUND_DISPLACEMENT},		0, "House", NULL, NULL, false},
	{&KEY_DOOR_AG,					{(43), 	(220), 	LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "HouseEnt", NULL, (void*)&LEVEL1_HOUSE_STAGE_MAIN_EP, false},
	{&MANAGED_ENTITY,				{(256),	(368),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_1_COLLISIONS, NULL, false},

	{&RUN_SIGN_IM,					{(232),	(220), 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{(184),	(225), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			1, NULL, NULL, NULL, false},
	{&COIN_AG,						{(200),	(225), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			2, NULL, NULL, NULL, false},

	{&LEVEL_1_MAIN_1_BACK_1_IM,		{(360),	(256), 	(LAYER_2), 0},					0, NULL, NULL, NULL, false},

	{&STAR_AG,						{(240),	(96), 	(LAYER_5 + LAYER_INCREMENT*3), 0},					0, NULL, NULL, NULL, false},

	{&COIN_AG,						{(320),	(248), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			3, NULL, NULL, NULL, false},
	{&COIN_AG,						{(336),	(248), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			4, NULL, NULL, NULL, false},
	{&SAW_BLADE_H8_AC,				{(352),	(259), 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&JUMP_SIGN_IM,					{(472),	(245), 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},		0, NULL, NULL, NULL, false},

	// part 2
	{&LEVEL_1_MAIN_1_MAIN_2_IM,		{(764), (352), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,				{(764),	(352),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{(764),	(352),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,				{(764),	(352),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_3, NULL, false},
	{&MANAGED_ENTITY,				{(764),	(352),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_4, NULL, false},

	{&WATERFALL_TOP_AG,				{(596),	(266), 	LAYER_0_FOREGROUND, -SORT_INCREMENT},		0, NULL, NULL, NULL, false},
	{&WATERFALL_STREAM_2x28_AG,		{(596),	(378), 	LAYER_0_FOREGROUND, -SORT_INCREMENT}, 0, NULL, NULL, NULL, false},

	{&COIN_AG,						{(528),	(228), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			5, NULL, NULL, NULL, false},
	{&COIN_AG,						{(544),	(228), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			6, NULL, NULL, NULL, false},
	{&COIN_AG,						{(732),	(196), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			7, NULL, NULL, NULL, false},
	{&BANDANA_AG,					{(756),	(196), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			1, NULL, NULL, NULL, false},
	{&COIN_AG,						{(780),	(196), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			8, NULL, NULL, NULL, false},

	{&BUSH_AG,						{(600),	(412), 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},		0, NULL, NULL, NULL, false},

	// part 3
	{&HIDE_LAYER_10x7_AG,			{(1228 - 160), (240 - 44),	(LAYER_0_FOREGROUND), -SORT_INCREMENT}, 0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_3_A_IM, 	{(1228), (240),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_3_B_IM, 	{(1228), (240),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{(798),	(401), 	LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},			0, "CoinEntr", NULL, (void*)&LEVEL1_COIN_ROOM_STAGE_MAIN_EP, false},
	{&HIDE_LAYER_10x7_AG,			{(1228 + 144), 	(240 + 20),	(LAYER_0_FOREGROUND), -SORT_INCREMENT}, 0, NULL, NULL, NULL, false},

	{&MANAGED_ENTITY,				{(1228), (240),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{(1228), (240),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,				{(1228), (240),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_3, NULL, false},
	{&MANAGED_ENTITY,				{(1228), (240),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_4, NULL, false},

	{&COIN_AG,						{(988),	(260), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			9, NULL, NULL, NULL, false},
	{&COIN_AG,						{(988),	(308), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			10, NULL, NULL, NULL, false},
	{&COIN_AG,						{(988),	(356), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			11, NULL, NULL, NULL, false},
	{&GRASS_AG,						{(1052), (408), LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{(1086), (208), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},			0, "IntEntrD", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_UPPER_EP, false},

	{&WATERFALL_TOP_AG,				{(1156), (346), 	LAYER_0_FOREGROUND, -SORT_INCREMENT},		0, NULL, NULL, NULL, false},
	{&WATERFALL_STREAM_2x16_AG,		{(1156), (408), 	LAYER_0_FOREGROUND, -SORT_INCREMENT}, 						0, NULL, NULL, NULL, false},
	{&WATER_POND_EN,				{(1173), (465), 	LAYER_0_FOREGROUND, 0},	0, NULL, NULL, NULL, false},

	{&SAW_BLADE_V3_AC,				{(1197), (472), 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&DOUBLE_JUMP_SIGN_IM,			{(1244), (432), 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&GRASS_AG,						{(1280), (440), 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{(1340), (432), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			12, NULL, NULL, NULL, false},
	{&COIN_AG,						{(1356), (432), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			13, NULL, NULL, NULL, false},
	{&DOOR_AG,						{(1373), (272), 	LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},			0, "IntExitD", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_EXIT_EP, false},
	{&KEY_AG,						{(1348), (276), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			2, NULL, NULL, NULL, false},
	{&BUSH_AG,						{(1430), (412), 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&SNAIL_3_AC,					{(1496), (377), 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&SNAIL_3_AC,					{(1576), (345), 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&MOUND_1_IM,					{(1668), (300), 	LAYER_0_BACKGROUND, LAYER_0_BACKGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{(1724), (304), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			14, NULL, NULL, NULL, false},
	{&COIN_AG,						{(1740), (304), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			15, NULL, NULL, NULL, false},

	// part 4
	{&LEVEL_1_MAIN_1_MAIN_4_IM, 	{(1732), (400), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,	{(1732), (400),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,	{(1732), (400),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,	{(1732), (400),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_3, NULL, false},

	{&SAW_BLADE_H3_AC,	{(1861), (303), 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&MOUND_2_IM,		{(2024), (300), 	LAYER_0_BACKGROUND, LAYER_0_BACKGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},

	// part 5 (back)
	{&LEVEL_1_MAIN_1_BACK_5_IM,		{(2336), (381 + -58), 	(LAYER_2), LAYER_2_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
	{&LAYER_SWITCH_DOOR_BACK_AG, 	{(2336 + 145), 	(381 + -86), (LAYER_2), LAYER_2_DOORS_DISPLACEMENT}, 0, "DoorBk1", NULL, (void*)&LEVEL_1_MAIN_LS_FRONT_EP, false},
	{&MANAGED_ENTITY,				{(2336), (382),	(LAYER_2), LAYER_2_DOORS_DISPLACEMENT * 2}, 0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{(2336), (381 - 5),	(LAYER_2), LAYER_2_DOORS_DISPLACEMENT * 2}, 0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS_2, NULL, false},
	{&CANNON_AC,					{(2180), (282), 	LAYER_2_FOREGROUND, LAYER_2_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&CANNON_AC,					{(2404), (282), 	LAYER_2_FOREGROUND, LAYER_2_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{(2093), (259), 	LAYER_2_ITEMS, LAYER_2_ITEMS_DISPLACEMENT},			16, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{(2105), (259), 	LAYER_2_ITEMS, LAYER_2_ITEMS_DISPLACEMENT},			17, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{(2263), (236), 	LAYER_2_ITEMS, LAYER_2_ITEMS_DISPLACEMENT},			18, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{(2275), (236), 	LAYER_2_ITEMS, LAYER_2_ITEMS_DISPLACEMENT},			19, NULL, NULL, NULL, false},

	// part 5
	{&LEVEL_1_MAIN_1_MAIN_5_IM, 	{(2208), (400), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,	{(2208), (400),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_5_COLLISIONS, NULL, false},

	{&COIN_AG,						{(2172), (292), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			20, NULL, NULL, NULL, false},
	{&COIN_AG,						{(2188), (292), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			21, NULL, NULL, NULL, false},
	{&COIN_AG,						{(2396), (292), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			22, NULL, NULL, NULL, false},
	{&COIN_AG,						{(2412), (292), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			23, NULL, NULL, NULL, false},

	// part 6
//	{&MANAGED_ENTITY,				{(2732), (372),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_CHILDREN, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	{(2732), 	(372), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{(2732-64), 	(372-76), 	(LAYER_0_FOREGROUND), -SORT_INCREMENT}, 0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,	{(2732), (372),	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_COLLISIONS, NULL, false},

	{&STAR_AG,						{(2556), (80), 	(LAYER_5), 0},					0, NULL, NULL, NULL, false},

	{&LAYER_SWITCH_DOOR_AG,			{(2669), (308), 	LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "DoorFt1", NULL, (void*)&LEVEL_1_MAIN_LS_BACK_EP, false},
	{&COIN_AG,						{(2732), (232), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			24, NULL, NULL, NULL, false},
	{&COIN_AG,						{(2748), (232), 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			25, NULL, NULL, NULL, false},

	{&LEVEL_1_TOWER_IM,				{(2893), (144), 	LAYER_0_BACKGROUND, LAYER_0_BACKGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{(2796), (104), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{(2868), (120), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{(2972), (112), 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&KEY_DOOR_AG,					{(2893), (228), 	LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "TowrEnt", NULL, (void*)&LEVEL1_TOWER_STAGE_MAIN_EP, false},
	{&GRASS_AG,						{(2960), (237), 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},		0, NULL, NULL, NULL, false},

	// right border
	{&COLLISION_CL,					{(2996), (116), 	(LAYER_0), 0},					0, NULL, NULL, (void*)&collision_2_28_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN[] =
{
	{&GUI_AG, {(192), (215), (-0), 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const LEVEL_1_MAIN_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMDef* const LEVEL_1_MAIN_STAGE_ST_CHARSETS[] =
{
	&LEVEL_1_MAIN_1_MAIN_CH,
	&LEVEL_1_MAIN_1_MAIN_FRONT_CH,
	&LEVEL_1_MAIN_1_MAIN_BACK_CH,
	&DOOR_CH,
	&DOOR_BACK_CH,
	&COIN_CH,
	&COIN_BACK_CH,
	&COIN_SILHOUETTE_CH,
	&COIN_BACK_SILHOUETTE_CH,
	&MOUND_BG_BACK_CH,
	&MOUND_BG_MIDDLE_CH,
	&MOUND_BG_FRONT_CH,
	&SNAIL_CH,
	&GRASS_CH,
	&BUSH_CH,
	&LEVEL_1_HOUSE_CH,
	&SAW_BLADE_CH,
	&KEY_CH,
	&HERO_BANDANA_CH,
	&CANNON_CH,
	&CANNON_BALL_CH,
	&SMOKE_PARTICLE_SMALL_CH,
	&RUN_SIGN_CH,
	&JUMP_SIGN_CH,
	&DOUBLE_JUMP_SIGN_CH,
	&WATERFALL_STREAM_2x28_CH,
	&WATERFALL_TOP_CH,

	NULL
};

TextureDefinition* const LEVEL_1_MAIN_STAGE_ST_TEXTURES[] =
{
	&LEVEL_1_MAIN_1_MAIN_3_TX,
	&LEVEL_1_MAIN_1_MAIN_FRONT_3A_TX,
	&LEVEL_1_MAIN_1_MAIN_FRONT_3B_TX,
	&LEVEL_1_MAIN_1_MAIN_BACK_3A_TX,
	&LEVEL_1_MAIN_1_MAIN_BACK_3B_TX,
	&LEVEL_1_MAIN_1_MAIN_BACK_3C_TX,
	&LEVEL_1_MAIN_1_MAIN_1_TX,
	&LEVEL_1_MAIN_1_BACK_1_TX,
	&LEVEL_1_MAIN_1_MAIN_2_TX,
	&LEVEL_1_MAIN_1_MAIN_FRONT_1_TX,
	&LEVEL_1_MAIN_1_MAIN_FRONT_2A_TX,
	&LEVEL_1_MAIN_1_MAIN_FRONT_2B_TX,
	&MOUND_BG_BACK_TX,
	&MOUND_BG_MIDDLE_TX,
	&MOUND_BG_FRONT_TX,
	&DUST_PARTICLE_SMALL_TX,
	&SAW_BLADE_TX,
	&DOOR_TX,
	&DOOR_BACK_TX,
	&LEVEL_1_HOUSE_TX,
	&COIN_TX,
	&COIN_BACK_TX,
	&COIN_SILHOUETTE_TX,
	&COIN_BACK_SILHOUETTE_TX,
	&HERO_BANDANA_TX,
	&CANNON_TX,
	&CANNON_BALL_TX,
	&KEY_TX,
	&WATERFALL_STREAM_2x28_TX,
	&WATERFALL_TOP_TX,
	NULL
};

const PostProcessingEffect LEVEL_1_MAIN_STAGE_ST_POST_PROCESSING_EFFECTS[] =
{
	PostProcessingEffects_rain,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_MAIN_STAGE_ST =
{
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
			0,
			// p
			0
		},
	},

	// streaming
	{
		// load padding
		96,
		// unload padding
		24,
		// streaming amplitude
		14,
		// particle removal delay cycles
		4,
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		1,

		// maximum number of texture's rows to write each time the texture writing is active
		8,

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
			(BrightnessRepeatDefinition*)NULL,
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

		// obj segments sizes (must total 1024)
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

		// OBJECT segments z coordinates
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
			20,
		},

		// optical configuration values
		{
			// maximum x view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE_POWER,
			// maximum y view distance's power into the horizon
			__MAXIMUM_Y_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			__DISTANCE_EYE_SCREEN,
			// distance from left to right eye (depth sensation)
			__BASE_FACTOR,
			// horizontal view point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// vertical view point center
			__VERTICAL_VIEW_POINT_CENTER,
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
		(FontDefinition**)LEVEL_1_MAIN_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)LEVEL_1_MAIN_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureDefinition**)LEVEL_1_MAIN_STAGE_ST_TEXTURES,

		// background music
		(const u16 (*)[])WORLD_0_0_0_BGM,
	},

	// entities
	{
		// ui
		{
			LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN,
			__TYPE(UiContainer),
		},

		// children
		LEVEL_1_MAIN_STAGE_ST_CHILDREN,
	},

	// post processing effects
	(PostProcessingEffect*)LEVEL_1_MAIN_STAGE_ST_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL_1_MAIN_MAIN_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"HouseEnt",

	// offset from entry point (x, y, z)
	{
		19,
		-0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMDef LEVEL_1_MAIN_HOUSE_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"HouseEnt",

	// offset from entry point (x, y, z)
	{
		19,
		0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMDef LEVEL_1_MAIN_COIN_ROOM_ENTRY_DOOR_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"CoinEntr",

	// offset from entry point (x, y, z)
	{
		-19,
		0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMDef LEVEL_1_MAIN_INTERSECTION_ENTRY_DOOR_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"IntEntrD",

	// offset from entry point (x, y, z)
	{
		-19,
		-5,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMDef LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"IntExitD",

	// offset from entry point (x, y, z)
	{
		19,
		0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMDef LEVEL_1_MAIN_LS_FRONT_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"DoorFt1",

	// offset from entry point (x, y, z)
	{
		0,
		-2,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMDef LEVEL_1_MAIN_LS_BACK_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"DoorBk1",

	// offset from entry point (x, y, z)
	{
		0,
		0,
		0,
		-1
	},

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMDef LEVEL_1_MAIN_TOWER_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"TowrEnt",

	// offset from entry point (x, y, z)
	{
		-19,
		0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};
