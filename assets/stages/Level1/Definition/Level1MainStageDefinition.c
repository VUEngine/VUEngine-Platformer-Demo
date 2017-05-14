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
extern EntityDefinition COLLISIONS_CONTAINER_ENTITY;
extern EntityDefinition DOOR_AG;
extern EntityDefinition DOUBLE_JUMP_SIGN_IM;
extern EntityDefinition GRASS_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
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
extern EntityDefinition LEVEL_1_MAIN_1_MAIN_3_IM;
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

extern VBVec3D collision_2_28_1;
extern VBVec3D collision_3_2_1;
extern VBVec3D collision_7_2_1;
extern VBVec3D collision_8_3_1;
extern VBVec3D collision_12_4_1;
extern VBVec3D collision_14_6_1;
extern VBVec3D collision_14_18_1;
extern VBVec3D collision_18_6_1;
extern VBVec3D collision_20_2_1;
extern VBVec3D collision_20_6_1;
extern VBVec3D collision_20_32_1;
extern VBVec3D collision_28_16_1;
extern VBVec3D collision_32_14_1;
extern VBVec3D collision_34_30_1;
extern VBVec3D collision_38_10_1;
extern VBVec3D collision_47_3_1;
extern VBVec3D collision_48_10_1;
extern VBVec3D collision_48_18_1;
extern VBVec3D collision_48_28_1;
extern VBVec3D collision_49_5_1;
extern VBVec3D collision_67_25_1;


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_COLLISIONS[] =
{
	{&COLLISION_CL,					{FTOFIX19_13(-136), FTOFIX19_13(-12), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_34_30_1, false}, // left floor
	{&COLLISION_CL,					{FTOFIX19_13(112),	FTOFIX19_13(12), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_34_30_1, false}, // right floor

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_TOP_CL,				{FTOFIX19_13(-226), FTOFIX19_13(-104),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // left top one-way
	{&COLLISION_CL, 				{FTOFIX19_13(-145), FTOFIX19_13(-56),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_18_1, false}, // floor left to spikes
	{&COLLISION_CL, 				{FTOFIX19_13(127),	FTOFIX19_13(-56),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_18_1, false}, // floor right to spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{FTOFIX19_13(-8),	FTOFIX19_13(-132),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // floating block over spikes
	{&COLLISION_HIT_CL,				{FTOFIX19_13(-8),	FTOFIX19_13(-94),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_2_1, false}, // spikes hit collision
	{&COLLISION_CL, 				{FTOFIX19_13(-8),	FTOFIX19_13(-40),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_32_14_1, false}, // floor below spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_3[] =
{
	{&COLLISION_TOP_CL,				{FTOFIX19_13(-226), FTOFIX19_13(72),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // left bottom one-way
	{&COLLISION_CL, 				{FTOFIX19_13(-10),	FTOFIX19_13(136),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_18_1, false}, // secret bottom floor
	{&COLLISION_TOP_CL,				{FTOFIX19_13(210),	FTOFIX19_13(-72),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // right top one-way

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_4[] =
{
	{&COLLISION_TOP_CL,				{FTOFIX19_13(210),	FTOFIX19_13(24),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // right bottom one-way
	{&COLLISION_CL,					{FTOFIX19_13(127),	FTOFIX19_13(38),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // wall right to the secret door
	{&COLLISION_CL,					{FTOFIX19_13(239),	FTOFIX19_13(88),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_18_6_1, false}, // floor under the one-way passage

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_CHILDREN[] =
{
	{&LEVEL_1_MAIN_1_MAIN_3_IM, 	{FTOFIX19_13(0), 	FTOFIX19_13(0),		FTOFIX19_13(0)},		0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{FTOFIX19_13(144), 	FTOFIX19_13(20),	FTOFIX19_13(-SORT_INCREMENT * 2)}, 0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{FTOFIX19_13(-160), FTOFIX19_13(-44),	FTOFIX19_13(-SORT_INCREMENT * 2)}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1[] =
{
	{&COLLISION_TOP_CL, 			{FTOFIX19_13(-226), FTOFIX19_13(-8),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // top one-way
	{&COLLISION_TOP_CL, 			{FTOFIX19_13(-226), FTOFIX19_13(88),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // bottom one-way
	{&COLLISION_CL, 				{FTOFIX19_13(-8),	FTOFIX19_13(-138),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_18_1, false}, // above hidden area

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{FTOFIX19_13(-48),	FTOFIX19_13(24),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_38_10_1, false},
	{&COLLISION_CL, 				{FTOFIX19_13(-8),	FTOFIX19_13(-13),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_28_16_1, false},
	{&COLLISION_CL, 				{FTOFIX19_13(32),	FTOFIX19_13(-41),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_38_10_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_3[] =
{
	{&COLLISION_CL, 				{FTOFIX19_13(-8),	FTOFIX19_13(88),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_10_1, false}, // ceiling above steps area
	{&COLLISION_CL,					{FTOFIX19_13(-161), FTOFIX19_13(232),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // 2nd lowest left step
	{&COLLISION_CL,					{FTOFIX19_13(-112), FTOFIX19_13(256),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // lowest left step

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_4[] =
{
	{&COLLISION_CL,					{FTOFIX19_13(104),	FTOFIX19_13(272),	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_28_16_1, false}, // lowest right step

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1[] =
{
	{&COLLISION_CL,					{FTOFIX19_13(-296), FTOFIX19_13(40), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // lowest step after ceiling
	{&COLLISION_CL,					{FTOFIX19_13(-216), FTOFIX19_13(8), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // middle step after ceiling
	{&COLLISION_CL,					{FTOFIX19_13(-136), FTOFIX19_13(-24), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // highest step after ceiling

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2[] =
{
	{&COLLISION_CL,					{FTOFIX19_13(-32),	FTOFIX19_13(-56), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_6_1, false}, // floor left to spikes
	{&COLLISION_CL, 				{FTOFIX19_13(128),	FTOFIX19_13(-84), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // floating block over spikes
	{&COLLISION_CL,					{FTOFIX19_13(124),	FTOFIX19_13(-24), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_6_1, false}, // floor right to spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_3[] =
{
	{&COLLISION_HIT_CL, 			{FTOFIX19_13(128),	FTOFIX19_13(-46), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_2_1, false}, // spikes hit collision
	{&COLLISION_CL, 				{FTOFIX19_13(288),	FTOFIX19_13(48), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_32_1, false}, // floor below spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_BACK_5_IM,		{FTOFIX19_13(0), 	FTOFIX19_13(-50), 	FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false},
	{&LAYER_SWITCH_DOOR_BACK_AG, 	{FTOFIX19_13(145), 	FTOFIX19_13(-82), 	FTOFIX19_13(-SORT_INCREMENT)}, 0, "DoorBk1", NULL, (void*)&LEVEL_1_MAIN_LS_FRONT_EP, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_COLLISIONS_1[] =
{
	{&COLLISION_CL, 				{FTOFIX19_13(-5),	FTOFIX19_13(-120), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_47_3_1, false},
	{&COLLISION_CL, 				{FTOFIX19_13(-76),	FTOFIX19_13(-89), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_49_5_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{FTOFIX19_13(0),	FTOFIX19_13(32), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_67_25_1, false},
	{&COLLISION_TOP_CL, 			{FTOFIX19_13(190), 	FTOFIX19_13(-112), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_5_COLLISIONS[] =
{
	{&COLLISION_CL, 				{FTOFIX19_13(-28),	FTOFIX19_13(-84), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // left floating block
	{&COLLISION_CL, 				{FTOFIX19_13(82),	FTOFIX19_13(-84), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // middle floating block
	{&COLLISION_CL, 				{FTOFIX19_13(196),	FTOFIX19_13(-84), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // right floating block

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_CHILDREN[] =
{
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	{FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(0)},		0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{FTOFIX19_13(-64), 	FTOFIX19_13(-76), 	FTOFIX19_13(-SORT_INCREMENT * 2)}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_COLLISIONS[] =
{
	{&COLLISION_CL, 				{FTOFIX19_13(-56),	FTOFIX19_13(64), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_28_1, false},
	{&COLLISION_TOP_CL, 			{FTOFIX19_13(-130), FTOFIX19_13(-104), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false},
	{&COLLISION_CL,					{FTOFIX19_13(-56),	FTOFIX19_13(-112), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_12_4_1, false},
	{&COLLISION_CL, 				{FTOFIX19_13(168),	FTOFIX19_13(-16), 	FTOFIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_28_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition

	{&MOUND_BG_BACK_IM,				{FTOFIX19_13(0),	FTOFIX19_13(112), 	FTOFIX19_13(LAYER_5)},					0, NULL, NULL, NULL, true},
	{&CLOUDS_IM,					{FTOFIX19_13(0),	FTOFIX19_13(198), 	FTOFIX19_13(LAYER_4)},					0, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM,			{FTOFIX19_13(0),	FTOFIX19_13(212), 	FTOFIX19_13(LAYER_3)},					0, NULL, NULL, NULL, true},

	{&HERO_AC,						{FTOFIX19_13(56),	FTOFIX19_13(288), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, HERO_NAME, NULL, NULL, true},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	// left border
	{&COLLISION_CL,					{FTOFIX19_13(-8),	FTOFIX19_13(128), 	FTOFIX19_13(LAYER_0)},					0, NULL, NULL, (void*)&collision_2_28_1, false},

	// part 1
	{&SMOKE_PS,						{FTOFIX19_13(88),	FTOFIX19_13(150), 	FTOFIX19_13(LAYER_0_FOREGROUND + 16)},	0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_1_IM,		{FTOFIX19_13(256), 	FTOFIX19_13(368), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_HOUSE_IM,				{FTOFIX19_13(88),	FTOFIX19_13(192), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, "House", NULL, NULL, false},
	{&KEY_DOOR_AG,					{FTOFIX19_13(44), 	FTOFIX19_13(220), 	FTOFIX19_13(LAYER_0_DOORS)}, 			0, "HouseEnt", NULL, (void*)&LEVEL1_HOUSE_STAGE_MAIN_EP, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(256),	FTOFIX19_13(368),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_1_COLLISIONS, NULL, false},

	{&RUN_SIGN_IM,					{FTOFIX19_13(232),	FTOFIX19_13(220), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(184),	FTOFIX19_13(225), 	FTOFIX19_13(LAYER_0_ITEMS)},			1, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(200),	FTOFIX19_13(225), 	FTOFIX19_13(LAYER_0_ITEMS)},			2, NULL, NULL, NULL, false},

	{&LEVEL_1_MAIN_1_BACK_1_IM,		{FTOFIX19_13(360),	FTOFIX19_13(256), 	FTOFIX19_13(LAYER_2)},					0, NULL, NULL, NULL, false},

	{&STAR_AG,						{FTOFIX19_13(240),	FTOFIX19_13(96), 	FTOFIX19_13(LAYER_5)},					0, NULL, NULL, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(320),	FTOFIX19_13(248), 	FTOFIX19_13(LAYER_0_ITEMS)},			3, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(336),	FTOFIX19_13(248), 	FTOFIX19_13(LAYER_0_ITEMS)},			4, NULL, NULL, NULL, false},
	{&SAW_BLADE_H8_AC,				{FTOFIX19_13(352),	FTOFIX19_13(259), 	FTOFIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&JUMP_SIGN_IM,					{FTOFIX19_13(472),	FTOFIX19_13(244), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},

	// part 2
	{&LEVEL_1_MAIN_1_MAIN_2_IM,		{FTOFIX19_13(764), 	FTOFIX19_13(352), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(764),	FTOFIX19_13(352),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(764),	FTOFIX19_13(352),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(764),	FTOFIX19_13(352),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_3, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(764),	FTOFIX19_13(352),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_4, NULL, false},

	{&WATERFALL_TOP_AG,				{FTOFIX19_13(596),	FTOFIX19_13(266), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&WATERFALL_STREAM_2x28_AG,		{FTOFIX19_13(596),	FTOFIX19_13(378), 	FTOFIX19_13(LAYER_0_FOREGROUND - SORT_INCREMENT)}, 0, NULL, NULL, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(528),	FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_ITEMS)},			5, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(544),	FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_ITEMS)},			6, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(732),	FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)},			7, NULL, NULL, NULL, false},
	{&BANDANA_AG,					{FTOFIX19_13(756),	FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)},			1, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(780),	FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)},			8, NULL, NULL, NULL, false},

	{&BUSH_AG,						{FTOFIX19_13(600),	FTOFIX19_13(412), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{FTOFIX19_13(798),	FTOFIX19_13(401), 	FTOFIX19_13(LAYER_0_DOORS)},			0, "CoinEntr", NULL, (void*)&LEVEL1_COIN_ROOM_STAGE_MAIN_EP, false},

	// part 3
	{&MANAGED_ENTITY,				{FTOFIX19_13(1228), FTOFIX19_13(240),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_CHILDREN, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1228), FTOFIX19_13(240),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1228), FTOFIX19_13(240),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1228), FTOFIX19_13(240),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_3, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1228), FTOFIX19_13(240),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_4, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(988),	FTOFIX19_13(260), 	FTOFIX19_13(LAYER_0_ITEMS)},			9, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(988),	FTOFIX19_13(308), 	FTOFIX19_13(LAYER_0_ITEMS)},			10, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(988),	FTOFIX19_13(356), 	FTOFIX19_13(LAYER_0_ITEMS)},			11, NULL, NULL, NULL, false},
	//{&GRASS_AG,						{FTOFIX19_13(1052), FTOFIX19_13(408), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{FTOFIX19_13(1086), FTOFIX19_13(208), 	FTOFIX19_13(LAYER_0_DOORS)},			0, "IntEntrD", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_UPPER_EP, false},

	{&WATERFALL_TOP_AG,				{FTOFIX19_13(1156),	FTOFIX19_13(346), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&WATERFALL_STREAM_2x16_AG,		{FTOFIX19_13(1156),	FTOFIX19_13(408), 	FTOFIX19_13(0)}, 						0, NULL, NULL, NULL, false},
	{&WATER_POND_EN,				{FTOFIX19_13(1174),	FTOFIX19_13(465), 	FTOFIX19_13(LAYER_0_FOREGROUND + 1)},	0, NULL, NULL, NULL, false},

	{&SAW_BLADE_V3_AC,				{FTOFIX19_13(1197), FTOFIX19_13(472), 	FTOFIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&DOUBLE_JUMP_SIGN_IM,			{FTOFIX19_13(1244), FTOFIX19_13(432), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&GRASS_AG,						{FTOFIX19_13(1280), FTOFIX19_13(440), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(1340), FTOFIX19_13(432), 	FTOFIX19_13(LAYER_0_ITEMS)},			12, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(1356), FTOFIX19_13(432), 	FTOFIX19_13(LAYER_0_ITEMS)},			13, NULL, NULL, NULL, false},
	{&DOOR_AG,						{FTOFIX19_13(1373), FTOFIX19_13(272), 	FTOFIX19_13(LAYER_0_DOORS)},			0, "IntExitD", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_EXIT_EP, false},
	{&KEY_AG,						{FTOFIX19_13(1348), FTOFIX19_13(276), 	FTOFIX19_13(LAYER_0_ITEMS)},			2, NULL, NULL, NULL, false},
//	{&BUSH_AG,						{FTOFIX19_13(1430), FTOFIX19_13(412), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&SNAIL_3_AC,					{FTOFIX19_13(1496), FTOFIX19_13(377), 	FTOFIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&SNAIL_3_AC,					{FTOFIX19_13(1576), FTOFIX19_13(345), 	FTOFIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&MOUND_1_IM,					{FTOFIX19_13(1668), FTOFIX19_13(300), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(1724), FTOFIX19_13(304), 	FTOFIX19_13(LAYER_0_ITEMS)},			14, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(1740), FTOFIX19_13(304), 	FTOFIX19_13(LAYER_0_ITEMS)},			15, NULL, NULL, NULL, false},

	// part 4
	{&LEVEL_1_MAIN_1_MAIN_4_IM, 	{FTOFIX19_13(1732), FTOFIX19_13(400), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1732), FTOFIX19_13(400),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1732), FTOFIX19_13(400),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1732), FTOFIX19_13(400),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_3, NULL, false},

	{&SAW_BLADE_H3_AC,				{FTOFIX19_13(1861), FTOFIX19_13(303), 	FTOFIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&MOUND_2_IM,					{FTOFIX19_13(2024), FTOFIX19_13(300), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},

	// part 5 (back)
	{&MANAGED_ENTITY,				{FTOFIX19_13(2336), FTOFIX19_13(381),	FTOFIX19_13(LAYER_2)},					0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_ENTITIES, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(2336), FTOFIX19_13(381),	FTOFIX19_13(LAYER_2)},					0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS_1, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(2336), FTOFIX19_13(381),	FTOFIX19_13(LAYER_2)},					0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS_2, NULL, false},
	{&CANNON_AC,					{FTOFIX19_13(2180), FTOFIX19_13(282), 	FTOFIX19_13(LAYER_2_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&CANNON_AC,					{FTOFIX19_13(2404), FTOFIX19_13(282), 	FTOFIX19_13(LAYER_2_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{FTOFIX19_13(2093), FTOFIX19_13(259), 	FTOFIX19_13(LAYER_2_ITEMS)},			16, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{FTOFIX19_13(2105), FTOFIX19_13(259), 	FTOFIX19_13(LAYER_2_ITEMS)},			17, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{FTOFIX19_13(2263), FTOFIX19_13(236), 	FTOFIX19_13(LAYER_2_ITEMS)},			18, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{FTOFIX19_13(2275), FTOFIX19_13(236), 	FTOFIX19_13(LAYER_2_ITEMS)},			19, NULL, NULL, NULL, false},

	// part 5
	{&LEVEL_1_MAIN_1_MAIN_5_IM, 	{FTOFIX19_13(2208), FTOFIX19_13(400), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(2208), FTOFIX19_13(400),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_5_COLLISIONS, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(2172), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)},			20, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2188), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)},			21, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2396), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)},			22, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2412), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)},			23, NULL, NULL, NULL, false},

	// part 6
	{&MANAGED_ENTITY,				{FTOFIX19_13(2732), FTOFIX19_13(372),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_CHILDREN, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(2732), FTOFIX19_13(372),	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_COLLISIONS, NULL, false},

	{&STAR_AG,						{FTOFIX19_13(2556), FTOFIX19_13(80), 	FTOFIX19_13(LAYER_5)},					0, NULL, NULL, NULL, false},

	{&LAYER_SWITCH_DOOR_AG,			{FTOFIX19_13(2669), FTOFIX19_13(308), 	FTOFIX19_13(LAYER_0_DOORS)}, 			0, "DoorFt1", NULL, (void*)&LEVEL_1_MAIN_LS_BACK_EP, false},
	{&COIN_AG,						{FTOFIX19_13(2732), FTOFIX19_13(232), 	FTOFIX19_13(LAYER_0_ITEMS)},			24, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2748), FTOFIX19_13(232), 	FTOFIX19_13(LAYER_0_ITEMS)},			25, NULL, NULL, NULL, false},

	{&LEVEL_1_TOWER_IM,				{FTOFIX19_13(2893), FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{FTOFIX19_13(2796), FTOFIX19_13(104), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{FTOFIX19_13(2868), FTOFIX19_13(120), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{FTOFIX19_13(2972), FTOFIX19_13(112), 	FTOFIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&KEY_DOOR_AG,					{FTOFIX19_13(2893), FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_DOORS)}, 			0, "TowrEnt", NULL, (void*)&LEVEL1_TOWER_STAGE_MAIN_EP, false},
	{&GRASS_AG,						{FTOFIX19_13(2960), FTOFIX19_13(237), 	FTOFIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},

	// right border
	{&COLLISION_CL,					{FTOFIX19_13(2996), FTOFIX19_13(116), 	FTOFIX19_13(LAYER_0)},					0, NULL, NULL, (void*)&collision_2_28_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(215), FTOFIX19_13(-4)}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
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

StageTextureEntryROMDef LEVEL_1_MAIN_STAGE_ST_TEXTURES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_3_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_3A_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_3B_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_BACK_3A_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_BACK_3B_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_BACK_3C_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_1_TX, true},
	{&LEVEL_1_MAIN_1_BACK_1_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_2_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_1_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_2A_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_2B_TX, true},
	{&MOUND_BG_BACK_TX, false},
	{&MOUND_BG_MIDDLE_TX, false},
	{&MOUND_BG_FRONT_TX, false},
	{&DUST_PARTICLE_SMALL_TX, false},
	{&SAW_BLADE_TX, false},
	{&DOOR_TX, false},
	{&DOOR_BACK_TX, false},
	{&LEVEL_1_HOUSE_TX, false},
	{&COIN_TX, false},
	{&COIN_BACK_TX, false},
	{&COIN_SILHOUETTE_TX, false},
	{&COIN_BACK_SILHOUETTE_TX, false},
	{&HERO_BANDANA_TX, false},
	{&CANNON_TX, false},
	{&CANNON_BALL_TX, false},
	{&KEY_TX, false},
	{&WATERFALL_STREAM_2x28_TX, false},
	{&WATERFALL_TOP_TX, false},

	{NULL, false}
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
			__SCREEN_DEPTH,
		},

		// screen's initial position inside the game world
		{
			// x
			ITOFIX19_13(0),
			// y
			ITOFIX19_13(0),
			// z
			ITOFIX19_13(0)
		},
	},

	// streaming
	{
		// minimum free ms in the current game frame to allow streaming to quick in
		4,
		// load padding
		120,
		// unload padding
		24,
		// streaming amplitude
		16,
		// particle removal delay cycles
		4,
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		1,

		// maximum number of texture's rows to write each time the texture writing is active
		10,

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

		// obj segments z coordinates
		// Note that each SPT's z coordinate much be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
		{
			// __spt0
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt1
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt2
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt3
			FTOFIX19_13(24),
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			ITOFIX19_13(__DISTANCE_EYE_SCREEN),
			// distance from left to right eye (depth sensation)
			ITOFIX19_13(__BASE_FACTOR),
			// horizontal view point center
			ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
			// vertical view point center
			ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER),
		},
	},

	// physics
	{
		// gravity
		{
			ITOFIX19_13(0),
			ITOFIX19_13(__GRAVITY),
			ITOFIX19_13(0)
		},

		// friction
		FTOFIX19_13(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)LEVEL_1_MAIN_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)LEVEL_1_MAIN_STAGE_ST_CHARSETS,

		// textures to preload
		(StageTextureEntryDefinition*)LEVEL_1_MAIN_STAGE_ST_TEXTURES,

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
	(PostProcessingEffect*)LEVEL_1_MAIN_STAGE_ST_POST_PROCESSING_EFFECTS
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
		FTOFIX19_13(22),
		FTOFIX19_13(-20),
		FTOFIX19_13(SORT_INCREMENT * 3),
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
		FTOFIX19_13(16),
		FTOFIX19_13(0),
		FTOFIX19_13(SORT_INCREMENT * 3),
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
		FTOFIX19_13(-16),
		FTOFIX19_13(0),
		FTOFIX19_13(SORT_INCREMENT * 3),
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
		FTOFIX19_13(-16),
		FTOFIX19_13(-5),
		FTOFIX19_13(SORT_INCREMENT * 3),
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
		FTOFIX19_13(16),
		FTOFIX19_13(0),
		FTOFIX19_13(SORT_INCREMENT * 3),
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
		FTOFIX19_13(0),
		ITOFIX19_13(-1),
		FTOFIX19_13(SORT_INCREMENT * 3),
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
		FTOFIX19_13(0),
		FTOFIX19_13(-0.5f),
		FTOFIX19_13(-SORT_INCREMENT),
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
		FTOFIX19_13(-16),
		FTOFIX19_13(0),
		FTOFIX19_13(SORT_INCREMENT * 3),
	},

	// whether this entry point acts as a checkpoint
	false,
};
