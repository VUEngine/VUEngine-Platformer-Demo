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

extern Size collision_2_28_1;
extern Size collision_3_2_1;
extern Size collision_7_2_1;
extern Size collision_8_3_1;
extern Size collision_12_4_1;
extern Size collision_14_6_1;
extern Size collision_14_18_1;
extern Size collision_18_6_1;
extern Size collision_20_2_1;
extern Size collision_20_6_1;
extern Size collision_20_32_1;
extern Size collision_28_16_1;
extern Size collision_32_14_1;
extern Size collision_34_30_1;
extern Size collision_38_10_1;
extern Size collision_47_3_1;
extern Size collision_48_10_1;
extern Size collision_48_18_1;
extern Size collision_48_28_1;
extern Size collision_49_5_1;
extern Size collision_67_25_1;


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_COLLISIONS[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(-136), __F_TO_FIX19_13(-12), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_34_30_1, false}, // left floor
	{&COLLISION_CL,					{__F_TO_FIX19_13(112),	__F_TO_FIX19_13(13), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_34_30_1, false}, // right floor

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_TOP_CL,				{__F_TO_FIX19_13(-226), __F_TO_FIX19_13(-104),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // left top one-way
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-145), __F_TO_FIX19_13(-56),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_18_1, false}, // floor left to spikes
	{&COLLISION_CL, 				{__F_TO_FIX19_13(127),	__F_TO_FIX19_13(-56),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_18_1, false}, // floor right to spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-8),	__F_TO_FIX19_13(-132),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // floating block over spikes
	{&COLLISION_HIT_CL,				{__F_TO_FIX19_13(-8),	__F_TO_FIX19_13(-94),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_2_1, false}, // spikes hit collision
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-8),	__F_TO_FIX19_13(-40),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_32_14_1, false}, // floor below spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_3[] =
{
	{&COLLISION_TOP_CL,				{__F_TO_FIX19_13(-226), __F_TO_FIX19_13(72),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // left bottom one-way
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-10),	__F_TO_FIX19_13(136),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_18_1, false}, // secret bottom floor
	{&COLLISION_TOP_CL,				{__F_TO_FIX19_13(210),	__F_TO_FIX19_13(-72),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // right top one-way

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_4[] =
{
	{&COLLISION_TOP_CL,				{__F_TO_FIX19_13(210),	__F_TO_FIX19_13(24),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // right bottom one-way
	{&COLLISION_CL,					{__F_TO_FIX19_13(127),	__F_TO_FIX19_13(38),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // wall right to the secret door
	{&COLLISION_CL,					{__F_TO_FIX19_13(239),	__F_TO_FIX19_13(88),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_18_6_1, false}, // floor under the one-way passage

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1[] =
{
	{&COLLISION_TOP_CL, 			{__F_TO_FIX19_13(-226), __F_TO_FIX19_13(-8),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // top one-way
	{&COLLISION_TOP_CL, 			{__F_TO_FIX19_13(-226), __F_TO_FIX19_13(88),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false}, // bottom one-way
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-8),	__F_TO_FIX19_13(-138),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_18_1, false}, // above hidden area

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-48),	__F_TO_FIX19_13(25),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_38_10_1, false},
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-8),	__F_TO_FIX19_13(-13),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_28_16_1, false},
	{&COLLISION_CL, 				{__F_TO_FIX19_13(32),	__F_TO_FIX19_13(-41),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_38_10_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_3[] =
{
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-8),	__F_TO_FIX19_13(88),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_10_1, false}, // ceiling above steps area
	{&COLLISION_CL,					{__F_TO_FIX19_13(-161), __F_TO_FIX19_13(232),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // 2nd lowest left step
	{&COLLISION_CL,					{__F_TO_FIX19_13(-112), __F_TO_FIX19_13(256),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // lowest left step

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_4[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(104),	__F_TO_FIX19_13(272),	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_28_16_1, false}, // lowest right step

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(-296), __F_TO_FIX19_13(40), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // lowest step after ceiling
	{&COLLISION_CL,					{__F_TO_FIX19_13(-216), __F_TO_FIX19_13(8), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // middle step after ceiling
	{&COLLISION_CL,					{__F_TO_FIX19_13(-136), __F_TO_FIX19_13(-24), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_14_6_1, false}, // highest step after ceiling

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(-32),	__F_TO_FIX19_13(-56), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_6_1, false}, // floor left to spikes
	{&COLLISION_CL, 				{__F_TO_FIX19_13(128),	__F_TO_FIX19_13(-84), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // floating block over spikes
	{&COLLISION_CL,					{__F_TO_FIX19_13(124),	__F_TO_FIX19_13(-24), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_6_1, false}, // floor right to spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_3[] =
{
	{&COLLISION_HIT_CL, 			{__F_TO_FIX19_13(128),	__F_TO_FIX19_13(-46), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_2_1, false}, // spikes hit collision
	{&COLLISION_CL, 				{__F_TO_FIX19_13(288),	__F_TO_FIX19_13(49), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_20_32_1, false}, // floor below spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_COLLISIONS_1[] =
{
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-5),	__F_TO_FIX19_13(-120), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_47_3_1, false},
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-76),	__F_TO_FIX19_13(-90), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_49_5_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{__F_TO_FIX19_13(0),	__F_TO_FIX19_13(32), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_67_25_1, false},
	{&COLLISION_TOP_CL, 			{__F_TO_FIX19_13(190), 	__F_TO_FIX19_13(-112), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_5_COLLISIONS[] =
{
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-28),	__F_TO_FIX19_13(-84), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // left floating block
	{&COLLISION_CL, 				{__F_TO_FIX19_13(82),	__F_TO_FIX19_13(-84), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // middle floating block
	{&COLLISION_CL, 				{__F_TO_FIX19_13(196),	__F_TO_FIX19_13(-84), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_8_3_1, false}, // right floating block

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_CHILDREN[] =
{
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	{__F_TO_FIX19_13(0), 	__F_TO_FIX19_13(0), 	__F_TO_FIX19_13(0)},		0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{__F_TO_FIX19_13(-64), 	__F_TO_FIX19_13(-76), 	__F_TO_FIX19_13(-SORT_INCREMENT * 2)}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_COLLISIONS[] =
{
	{&COLLISION_CL, 				{__F_TO_FIX19_13(-56),	__F_TO_FIX19_13(65), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_28_1, false},
	{&COLLISION_TOP_CL, 			{__F_TO_FIX19_13(-130), __F_TO_FIX19_13(-104), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_7_2_1, false},
	{&COLLISION_CL,					{__F_TO_FIX19_13(-56),	__F_TO_FIX19_13(-112), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_12_4_1, false},
	{&COLLISION_CL, 				{__F_TO_FIX19_13(168),	__F_TO_FIX19_13(-16), 	__F_TO_FIX19_13(0)},	0, NULL, NULL, (void*)&collision_48_28_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_IM_CHILDREN[] =
{
	{&RUN_SIGN_IM,					{__F_TO_FIX19_13(232 - 256),	__F_TO_FIX19_13(220 - 368), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND - LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(0),	__F_TO_FIX19_13(225 - 368 - 20), 	__F_TO_FIX19_13(LAYER_0_ITEMS - LAYER_0_FOREGROUND)},			1, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(200 - 256 - 60),	__F_TO_FIX19_13(225 - 368 - 20), 	__F_TO_FIX19_13(LAYER_0_ITEMS - LAYER_0_FOREGROUND)},			2, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,				{__F_TO_FIX19_13(0),	__F_TO_FIX19_13(112), 	__F_TO_FIX19_13(LAYER_5)},					0, NULL, NULL, NULL, true},
	{&CLOUDS_IM,					{__F_TO_FIX19_13(0),	__F_TO_FIX19_13(198), 	__F_TO_FIX19_13(LAYER_4)},					0, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM,			{__F_TO_FIX19_13(0),	__F_TO_FIX19_13(212), 	__F_TO_FIX19_13(LAYER_3)},					0, NULL, NULL, NULL, true},

	{&HERO_AC,						{__F_TO_FIX19_13(56),	__F_TO_FIX19_13(288), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, HERO_NAME, NULL, NULL, false},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	// left border
	{&COLLISION_CL,					{__F_TO_FIX19_13(-8),	__F_TO_FIX19_13(128), 	__F_TO_FIX19_13(LAYER_0)},					0, NULL, NULL, (void*)&collision_2_28_1, false},

	// part 1
	{&SMOKE_PS,						{__F_TO_FIX19_13(88),	__F_TO_FIX19_13(150), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND + 16)},	0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_1_IM,		{__F_TO_FIX19_13(256), 	__F_TO_FIX19_13(368), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_HOUSE_IM,				{__F_TO_FIX19_13(88),	__F_TO_FIX19_13(192), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, "House", NULL, NULL, false},
	{&KEY_DOOR_AG,					{__F_TO_FIX19_13(44), 	__F_TO_FIX19_13(220), 	__F_TO_FIX19_13(LAYER_0_DOORS)}, 			0, "HouseEnt", NULL, (void*)&LEVEL1_HOUSE_STAGE_MAIN_EP, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(256),	__F_TO_FIX19_13(368),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_1_COLLISIONS, NULL, false},

	{&RUN_SIGN_IM,					{__F_TO_FIX19_13(232),	__F_TO_FIX19_13(220), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(184),	__F_TO_FIX19_13(225), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			1, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(200),	__F_TO_FIX19_13(225), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			2, NULL, NULL, NULL, false},

	{&LEVEL_1_MAIN_1_BACK_1_IM,		{__F_TO_FIX19_13(360),	__F_TO_FIX19_13(256), 	__F_TO_FIX19_13(LAYER_2)},					0, NULL, NULL, NULL, false},

	{&STAR_AG,						{__F_TO_FIX19_13(240),	__F_TO_FIX19_13(96), 	__F_TO_FIX19_13(LAYER_5)},					0, NULL, NULL, NULL, false},

	{&COIN_AG,						{__F_TO_FIX19_13(320),	__F_TO_FIX19_13(248), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			3, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(336),	__F_TO_FIX19_13(248), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			4, NULL, NULL, NULL, false},
	{&SAW_BLADE_H8_AC,				{__F_TO_FIX19_13(352),	__F_TO_FIX19_13(259), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&JUMP_SIGN_IM,					{__F_TO_FIX19_13(472),	__F_TO_FIX19_13(244), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},

	// part 2
	{&LEVEL_1_MAIN_1_MAIN_2_IM,		{__F_TO_FIX19_13(764), 	__F_TO_FIX19_13(352), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(764),	__F_TO_FIX19_13(352),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(764),	__F_TO_FIX19_13(352),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(764),	__F_TO_FIX19_13(352),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_3, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(764),	__F_TO_FIX19_13(352),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_4, NULL, false},

	{&WATERFALL_TOP_AG,				{__F_TO_FIX19_13(596),	__F_TO_FIX19_13(266), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&WATERFALL_STREAM_2x28_AG,		{__F_TO_FIX19_13(596),	__F_TO_FIX19_13(378), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND - SORT_INCREMENT)}, 0, NULL, NULL, NULL, false},

	{&COIN_AG,						{__F_TO_FIX19_13(528),	__F_TO_FIX19_13(228), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			5, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(544),	__F_TO_FIX19_13(228), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			6, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(732),	__F_TO_FIX19_13(196), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			7, NULL, NULL, NULL, false},
	{&BANDANA_AG,					{__F_TO_FIX19_13(756),	__F_TO_FIX19_13(196), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			1, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(780),	__F_TO_FIX19_13(196), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			8, NULL, NULL, NULL, false},

	{&BUSH_AG,						{__F_TO_FIX19_13(600),	__F_TO_FIX19_13(412), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},

	// part 3
	{&HIDE_LAYER_10x7_AG,			{__F_TO_FIX19_13(1228 - 160), __F_TO_FIX19_13(240 - 44),	__F_TO_FIX19_13(LAYER_0_FOREGROUND + -SORT_INCREMENT * 2)}, 0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_3_A_IM, 	{__F_TO_FIX19_13(1228), __F_TO_FIX19_13(240),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_3_B_IM, 	{__F_TO_FIX19_13(1228), __F_TO_FIX19_13(240),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{__F_TO_FIX19_13(798),	__F_TO_FIX19_13(401), 	__F_TO_FIX19_13(LAYER_0_DOORS)},			0, "CoinEntr", NULL, (void*)&LEVEL1_COIN_ROOM_STAGE_MAIN_EP, false},
	{&HIDE_LAYER_10x7_AG,			{__F_TO_FIX19_13(1228 + 144), 	__F_TO_FIX19_13(240 + 20),	__F_TO_FIX19_13(LAYER_0_FOREGROUND + -SORT_INCREMENT * 2)}, 0, NULL, NULL, NULL, false},

	{&MANAGED_ENTITY,				{__F_TO_FIX19_13(1228), __F_TO_FIX19_13(240),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{__F_TO_FIX19_13(1228), __F_TO_FIX19_13(240),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,				{__F_TO_FIX19_13(1228), __F_TO_FIX19_13(240),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_3, NULL, false},
	{&MANAGED_ENTITY,				{__F_TO_FIX19_13(1228), __F_TO_FIX19_13(240),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_4, NULL, false},

	{&COIN_AG,						{__F_TO_FIX19_13(988),	__F_TO_FIX19_13(260), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			9, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(988),	__F_TO_FIX19_13(308), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			10, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(988),	__F_TO_FIX19_13(356), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			11, NULL, NULL, NULL, false},
	{&GRASS_AG,						{__F_TO_FIX19_13(1052), __F_TO_FIX19_13(408), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{__F_TO_FIX19_13(1086), __F_TO_FIX19_13(208), 	__F_TO_FIX19_13(LAYER_0_DOORS)},			0, "IntEntrD", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_UPPER_EP, false},

	{&WATERFALL_TOP_AG,				{__F_TO_FIX19_13(1156),	__F_TO_FIX19_13(346), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&WATERFALL_STREAM_2x16_AG,		{__F_TO_FIX19_13(1156),	__F_TO_FIX19_13(408), 	__F_TO_FIX19_13(0)}, 						0, NULL, NULL, NULL, false},
	{&WATER_POND_EN,				{__F_TO_FIX19_13(1173),	__F_TO_FIX19_13(465), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND + 1)},	0, NULL, NULL, NULL, false},

	{&SAW_BLADE_V3_AC,				{__F_TO_FIX19_13(1197), __F_TO_FIX19_13(472), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&DOUBLE_JUMP_SIGN_IM,			{__F_TO_FIX19_13(1244), __F_TO_FIX19_13(432), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&GRASS_AG,						{__F_TO_FIX19_13(1280), __F_TO_FIX19_13(440), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(1340), __F_TO_FIX19_13(432), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			12, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(1356), __F_TO_FIX19_13(432), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			13, NULL, NULL, NULL, false},
	{&DOOR_AG,						{__F_TO_FIX19_13(1373), __F_TO_FIX19_13(272), 	__F_TO_FIX19_13(LAYER_0_DOORS)},			0, "IntExitD", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_EXIT_EP, false},
	{&KEY_AG,						{__F_TO_FIX19_13(1348), __F_TO_FIX19_13(276), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			2, NULL, NULL, NULL, false},
	{&BUSH_AG,						{__F_TO_FIX19_13(1430), __F_TO_FIX19_13(412), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&SNAIL_3_AC,					{__F_TO_FIX19_13(1496), __F_TO_FIX19_13(377), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&SNAIL_3_AC,					{__F_TO_FIX19_13(1576), __F_TO_FIX19_13(345), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&MOUND_1_IM,					{__F_TO_FIX19_13(1668), __F_TO_FIX19_13(300), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(1724), __F_TO_FIX19_13(304), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			14, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(1740), __F_TO_FIX19_13(304), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			15, NULL, NULL, NULL, false},

	// part 4
	{&LEVEL_1_MAIN_1_MAIN_4_IM, 	{__F_TO_FIX19_13(1732), __F_TO_FIX19_13(400), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(1732), __F_TO_FIX19_13(400),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(1732), __F_TO_FIX19_13(400),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(1732), __F_TO_FIX19_13(400),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_3, NULL, false},

	{&SAW_BLADE_H3_AC,				{__F_TO_FIX19_13(1861), __F_TO_FIX19_13(303), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)},			0, NULL, NULL, NULL, false},
	{&MOUND_2_IM,					{__F_TO_FIX19_13(2024), __F_TO_FIX19_13(300), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},

	// part 5 (back)
	{&LEVEL_1_MAIN_1_BACK_5_IM,		{__F_TO_FIX19_13(2336), 	__F_TO_FIX19_13(381 + -50), 	__F_TO_FIX19_13(LAYER_2)}, 0, NULL, NULL, NULL, false},
	{&LAYER_SWITCH_DOOR_BACK_AG, 	{__F_TO_FIX19_13(2336 + 145), 	__F_TO_FIX19_13(381 + -82), 	__F_TO_FIX19_13(LAYER_2 + -SORT_INCREMENT)}, 0, "DoorBk1", NULL, (void*)&LEVEL_1_MAIN_LS_FRONT_EP, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(2336), __F_TO_FIX19_13(381),	__F_TO_FIX19_13(LAYER_2)},					0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(2336), __F_TO_FIX19_13(381),	__F_TO_FIX19_13(LAYER_2)},					0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS_2, NULL, false},
	{&CANNON_AC,					{__F_TO_FIX19_13(2180), __F_TO_FIX19_13(282), 	__F_TO_FIX19_13(LAYER_2_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&CANNON_AC,					{__F_TO_FIX19_13(2404), __F_TO_FIX19_13(282), 	__F_TO_FIX19_13(LAYER_2_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{__F_TO_FIX19_13(2093), __F_TO_FIX19_13(259), 	__F_TO_FIX19_13(LAYER_2_ITEMS)},			16, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{__F_TO_FIX19_13(2105), __F_TO_FIX19_13(259), 	__F_TO_FIX19_13(LAYER_2_ITEMS)},			17, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{__F_TO_FIX19_13(2263), __F_TO_FIX19_13(236), 	__F_TO_FIX19_13(LAYER_2_ITEMS)},			18, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{__F_TO_FIX19_13(2275), __F_TO_FIX19_13(236), 	__F_TO_FIX19_13(LAYER_2_ITEMS)},			19, NULL, NULL, NULL, false},

	// part 5
	{&LEVEL_1_MAIN_1_MAIN_5_IM, 	{__F_TO_FIX19_13(2208), __F_TO_FIX19_13(400), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(2208), __F_TO_FIX19_13(400),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_5_COLLISIONS, NULL, false},

	{&COIN_AG,						{__F_TO_FIX19_13(2172), __F_TO_FIX19_13(292), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			20, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(2188), __F_TO_FIX19_13(292), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			21, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(2396), __F_TO_FIX19_13(292), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			22, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(2412), __F_TO_FIX19_13(292), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			23, NULL, NULL, NULL, false},

	// part 6
//	{&MANAGED_ENTITY,				{__F_TO_FIX19_13(2732), __F_TO_FIX19_13(372),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_CHILDREN, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	{__F_TO_FIX19_13(2732), 	__F_TO_FIX19_13(372), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{__F_TO_FIX19_13(2732-64), 	__F_TO_FIX19_13(372-76), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND - SORT_INCREMENT * 2)}, 0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(2732), __F_TO_FIX19_13(372),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_COLLISIONS, NULL, false},

	{&STAR_AG,						{__F_TO_FIX19_13(2556), __F_TO_FIX19_13(80), 	__F_TO_FIX19_13(LAYER_5)},					0, NULL, NULL, NULL, false},

	{&LAYER_SWITCH_DOOR_AG,			{__F_TO_FIX19_13(2669), __F_TO_FIX19_13(308), 	__F_TO_FIX19_13(LAYER_0_DOORS)}, 			0, "DoorFt1", NULL, (void*)&LEVEL_1_MAIN_LS_BACK_EP, false},
	{&COIN_AG,						{__F_TO_FIX19_13(2732), __F_TO_FIX19_13(232), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			24, NULL, NULL, NULL, false},
	{&COIN_AG,						{__F_TO_FIX19_13(2748), __F_TO_FIX19_13(232), 	__F_TO_FIX19_13(LAYER_0_ITEMS)},			25, NULL, NULL, NULL, false},

	{&LEVEL_1_TOWER_IM,				{__F_TO_FIX19_13(2893), __F_TO_FIX19_13(144), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{__F_TO_FIX19_13(2796), __F_TO_FIX19_13(104), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{__F_TO_FIX19_13(2868), __F_TO_FIX19_13(120), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{__F_TO_FIX19_13(2972), __F_TO_FIX19_13(112), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)},		0, NULL, NULL, NULL, false},
	{&KEY_DOOR_AG,					{__F_TO_FIX19_13(2893), __F_TO_FIX19_13(228), 	__F_TO_FIX19_13(LAYER_0_DOORS)}, 			0, "TowrEnt", NULL, (void*)&LEVEL1_TOWER_STAGE_MAIN_EP, false},
	{&GRASS_AG,						{__F_TO_FIX19_13(2960), __F_TO_FIX19_13(237), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)},		0, NULL, NULL, NULL, false},

	// right border
	{&COLLISION_CL,					{__F_TO_FIX19_13(2996), __F_TO_FIX19_13(116), 	__F_TO_FIX19_13(LAYER_0)},					0, NULL, NULL, (void*)&collision_2_28_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN[] =
{
	{&GUI_AG, {__F_TO_FIX19_13(192), __F_TO_FIX19_13(215), __F_TO_FIX19_13(-4)}, 0, NULL, NULL, NULL, true},

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
			__SCREEN_DEPTH,
		},

		// screen's initial position inside the game world
		{
			// x
			__I_TO_FIX19_13(0),
			// y
			__I_TO_FIX19_13(0),
			// z
			__I_TO_FIX19_13(0)
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
		0,

		// maximum number of texture's rows to write each time the texture writing is active
		5,

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

		// OBJECT segments z coordinates
		// Note that each SPT's z coordinate must be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
		{
			// __spt0
			__F_TO_FIX19_13(LAYER_0_PARTICLES),
			// __spt1
			__F_TO_FIX19_13(LAYER_0_PARTICLES),
			// __spt2
			__F_TO_FIX19_13(LAYER_0_PARTICLES),
			// __spt3
			__F_TO_FIX19_13(24),
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			__I_TO_FIX19_13(__DISTANCE_EYE_SCREEN),
			// distance from left to right eye (depth sensation)
			__I_TO_FIX19_13(__BASE_FACTOR),
			// horizontal view point center
			__I_TO_FIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
			// vertical view point center
			__I_TO_FIX19_13(__VERTICAL_VIEW_POINT_CENTER),
		},
	},

	// physics
	{
		// gravity
		{
			__I_TO_FIX19_13(0),
			__I_TO_FIX19_13(__GRAVITY),
			__I_TO_FIX19_13(0)
		},

		// friction
		__F_TO_FIX19_13(0.1f),
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
		__F_TO_FIX19_13(19),
		__F_TO_FIX19_13(-20),
		__F_TO_FIX19_13(SORT_INCREMENT * 0),
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
		__F_TO_FIX19_13(19),
		__F_TO_FIX19_13(0),
		__F_TO_FIX19_13(SORT_INCREMENT * 3),
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
		__F_TO_FIX19_13(-19),
		__F_TO_FIX19_13(0),
		__F_TO_FIX19_13(SORT_INCREMENT * 3),
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
		__F_TO_FIX19_13(-19),
		__F_TO_FIX19_13(-5),
		__F_TO_FIX19_13(SORT_INCREMENT * 3),
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
		__F_TO_FIX19_13(19),
		__F_TO_FIX19_13(0),
		__F_TO_FIX19_13(SORT_INCREMENT * 3),
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
		__F_TO_FIX19_13(0),
		__I_TO_FIX19_13(-1),
		__F_TO_FIX19_13(SORT_INCREMENT * 3),
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
		__F_TO_FIX19_13(0),
		__F_TO_FIX19_13(-0.5f),
		__F_TO_FIX19_13(-SORT_INCREMENT),
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
		__F_TO_FIX19_13(-19),
		__F_TO_FIX19_13(0),
		__F_TO_FIX19_13(SORT_INCREMENT * 3),
	},

	// whether this entry point acts as a checkpoint
	false,
};
