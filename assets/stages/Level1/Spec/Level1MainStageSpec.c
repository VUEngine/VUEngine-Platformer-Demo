/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <PostProcessingRain.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMSpec LEVEL1_HOUSE_STAGE_MAIN_EP;
extern StageEntryPointROMSpec LEVEL1_COIN_ROOM_STAGE_MAIN_EP;
extern StageEntryPointROMSpec LEVEL1_INTERSECTION_STAGE_UPPER_EP;
extern StageEntryPointROMSpec LEVEL1_INTERSECTION_STAGE_EXIT_EP;
extern StageEntryPointROMSpec LEVEL1_TOWER_STAGE_MAIN_EP;

StageEntryPointROMSpec LEVEL_1_MAIN_LS_BACK_EP;
StageEntryPointROMSpec LEVEL_1_MAIN_LS_FRONT_EP;

extern EntitySpec BANDANA_AG;
extern EntitySpec BUSH_AG;
extern EntitySpec CANNON_AC;
extern EntitySpec CLOUD_A_IM;
extern EntitySpec CLOUDS_IM;
extern EntitySpec COIN_AG;
extern EntitySpec COIN_BACK_AG;
extern EntitySpec COLLISION_CL;
extern EntitySpec COLLISION_HIT_CL;
extern EntitySpec COLLISION_TOP_CL;
extern EntitySpec MANAGED_ENTITY;
extern EntitySpec DOOR_AG;
extern EntitySpec DOUBLE_JUMP_SIGN_IM;
extern EntitySpec GRASS_AG;
extern EntitySpec GUI_AG;
extern EntitySpec HERO_AC;
extern EntitySpec HIDE_LAYER_10x7_AG;
extern EntitySpec JUMP_SIGN_IM;
extern EntitySpec KEY_AG;
extern EntitySpec KEY_DOOR_AG;
extern EntitySpec LAYER_SWITCH_DOOR_AG;
extern EntitySpec LAYER_SWITCH_DOOR_BACK_AG;
extern EntitySpec LEVEL_1_HOUSE_IM;
extern EntitySpec LEVEL_1_MAIN_1_BACK_1_IM;
extern EntitySpec LEVEL_1_MAIN_1_BACK_5_IM;
extern EntitySpec LEVEL_1_MAIN_1_MAIN_1_IM;
extern EntitySpec LEVEL_1_MAIN_1_MAIN_2_IM;
extern EntitySpec LEVEL_1_MAIN_1_MAIN_3_A_IM;
extern EntitySpec LEVEL_1_MAIN_1_MAIN_3_B_IM;
extern EntitySpec LEVEL_1_MAIN_1_MAIN_4_IM;
extern EntitySpec LEVEL_1_MAIN_1_MAIN_5_IM;
extern EntitySpec LEVEL_1_MAIN_1_MAIN_6_IM;
extern EntitySpec LEVEL_1_TOWER_IM;
extern EntitySpec LOW_POWER_INDICATOR_LB;
extern EntitySpec MANAGED_ENTITY;
extern EntitySpec MOUND_1_IM;
extern EntitySpec MOUND_2_IM;
extern EntitySpec MOUND_BG_BACK_IM;
extern EntitySpec MOUND_BG_FRONT_IM;
extern EntitySpec RUN_SIGN_IM;
extern EntitySpec SAW_BLADE_H3_AC;
extern EntitySpec SAW_BLADE_H8_AC;
extern EntitySpec SAW_BLADE_V3_AC;
extern EntitySpec SMOKE_PS;
extern EntitySpec SNAIL_3_AC;
extern EntitySpec STAR_AG;
extern EntitySpec WATER_SPLASH_PS;
extern EntitySpec WATERFALL_STREAM_2x16_AG;
extern EntitySpec WATERFALL_STREAM_2x28_AG;
extern EntitySpec WATERFALL_TOP_AG;
extern EntitySpec WATER_POND_EN;

extern CharSetSpec RUN_SIGN_CH;
extern CharSetSpec JUMP_SIGN_CH;
extern CharSetSpec DOUBLE_JUMP_SIGN_CH;
extern CharSetSpec WATERFALL_STREAM_2x16_CH;
extern CharSetSpec WATERFALL_STREAM_2x28_CH;
extern CharSetSpec WATERFALL_TOP_CH;
extern CharSetSpec BUSH_CH;
extern CharSetSpec CANNON_BALL_CH;
extern CharSetSpec SMOKE_PARTICLE_SMALL_CH;
extern CharSetSpec CANNON_CH;
extern CharSetSpec COIN_BACK_CH;
extern CharSetSpec COIN_BACK_SILHOUETTE_CH;
extern CharSetSpec COIN_CH;
extern CharSetSpec COIN_SILHOUETTE_CH;
extern CharSetSpec DOOR_BACK_CH;
extern CharSetSpec DOOR_CH;
extern CharSetSpec GRASS_CH;
extern CharSetSpec HERO_BANDANA_CH;
extern CharSetSpec KEY_CH;
extern CharSetSpec LEVEL_1_HOUSE_CH;
extern CharSetSpec LEVEL_1_MAIN_1_MAIN_BACK_CH;
extern CharSetSpec LEVEL_1_MAIN_1_MAIN_CH;
extern CharSetSpec LEVEL_1_MAIN_1_MAIN_FRONT_CH;
extern CharSetSpec LOW_POWER_INDICATOR_CH;
extern CharSetSpec MOUND_BG_BACK_CH;
extern CharSetSpec MOUND_BG_FRONT_CH;
extern CharSetSpec MOUND_BG_MIDDLE_CH;
extern CharSetSpec SAW_BLADE_CH;
extern CharSetSpec SNAIL_CH;

extern TextureSpec WATERFALL_STREAM_2x16_TX;
extern TextureSpec WATERFALL_STREAM_2x28_TX;
extern TextureSpec WATERFALL_TOP_TX;
extern TextureSpec CANNON_BALL_TX;
extern TextureSpec CANNON_TX;
extern TextureSpec COIN_BACK_SILHOUETTE_TX;
extern TextureSpec COIN_BACK_TX;
extern TextureSpec COIN_SILHOUETTE_TX;
extern TextureSpec COIN_TX;
extern TextureSpec DOOR_BACK_TX;
extern TextureSpec DOOR_TX;
extern TextureSpec DUST_PARTICLE_SMALL_TX;
extern TextureSpec HERO_BANDANA_TX;
extern TextureSpec KEY_TX;
extern TextureSpec LEVEL_1_HOUSE_TX;
extern TextureSpec LEVEL_1_MAIN_1_BACK_1_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_1_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_2_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_3_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_BACK_3A_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_BACK_3B_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_BACK_3C_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_FRONT_1_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_FRONT_2A_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_FRONT_2B_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_FRONT_3A_TX;
extern TextureSpec LEVEL_1_MAIN_1_MAIN_FRONT_3B_TX;
extern TextureSpec LOW_POWER_INDICATOR_TX;
extern TextureSpec MOUND_BG_BACK_TX;
extern TextureSpec MOUND_BG_FRONT_TX;
extern TextureSpec MOUND_BG_MIDDLE_TX;
extern TextureSpec SAW_BLADE_TX;
extern TextureROMSpec GUI_TX;

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

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_1_COLLISIONS[] =
{
	{&COLLISION_CL,					{-136, -12, 0, 0},											0, NULL, NULL, (void*)&collision_34_30_4, false}, // left floor
	{&COLLISION_CL,					{ 112,  12, 0, 0},											0, NULL, NULL, (void*)&collision_34_30_4, false}, // right floor

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_TOP_CL,				{-226, -104, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // left top one-way
	{&COLLISION_CL, 				{-145,  -56, 0, 0},											0, NULL, NULL, (void*)&collision_14_18_4, false}, // floor left to spikes
	{&COLLISION_CL, 				{ 127,  -56, 0, 0},											0, NULL, NULL, (void*)&collision_14_18_4, false}, // floor right to spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{  -8, -132, 0, 0},											0, NULL, NULL, (void*)&collision_8_3_4, false}, // floating block over spikes
	{&COLLISION_HIT_CL,				{  -8,  -94, 0, 0},											0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes hit collision
	{&COLLISION_CL, 				{  -8,  -40, 0, 0},											0, NULL, NULL, (void*)&collision_32_14_4, false}, // floor below spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_3[] =
{
	{&COLLISION_TOP_CL,				{-226,   72, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // left bottom one-way
	{&COLLISION_CL, 				{ -10,  136, 0, 0},											0, NULL, NULL, (void*)&collision_48_18_4, false}, // secret bottom floor
	{&COLLISION_TOP_CL,				{ 210,  -72, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // right top one-way

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_4[] =
{
	{&COLLISION_TOP_CL,				{ 210,  24, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // right bottom one-way
	{&COLLISION_CL,					{ 127,  38, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // wall right to the secret door
	{&COLLISION_CL,					{ 239,  88, 0, 0},											0, NULL, NULL, (void*)&collision_18_6_4, false}, // floor under the one-way passage

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1[] =
{
	{&COLLISION_TOP_CL, 			{-226,   -8, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // top one-way
	{&COLLISION_TOP_CL, 			{-226,   88, 0, 0},											0, NULL, NULL, (void*)&collision_6_2_4, false}, // bottom one-way
	{&COLLISION_CL, 				{  -8, -138, 0, 0},											0, NULL, NULL, (void*)&collision_48_18_4, false}, // above hidden area

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{ -48,  24,	0, 0},											0, NULL, NULL, (void*)&collision_38_10_4, false},
	{&COLLISION_CL, 				{  -8, -13,	0, 0},											0, NULL, NULL, (void*)&collision_28_16_4, false},
	{&COLLISION_CL, 				{  32, -41,	0, 0},											0, NULL, NULL, (void*)&collision_38_10_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_3[] =
{
	{&COLLISION_CL, 				{  -8,	88, 0, 0},											0, NULL, NULL, (void*)&collision_48_10_4, false}, // ceiling above steps area
	{&COLLISION_CL,					{-161, 232, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // 2nd lowest left step
	{&COLLISION_CL,					{-112, 256, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // lowest left step

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_4[] =
{
	{&COLLISION_CL,					{ 104, 272, 0, 0},											0, NULL, NULL, (void*)&collision_28_16_4, false}, // lowest right step

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1[] =
{
	{&COLLISION_CL,					{-296,  40, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // lowest step after ceiling
	{&COLLISION_CL,					{-216,   8, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // middle step after ceiling
	{&COLLISION_CL,					{-136, -24, 0, 0},											0, NULL, NULL, (void*)&collision_14_6_4, false}, // highest step after ceiling

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2[] =
{
	{&COLLISION_CL,					{ -32,  -56, 0, 0},											0, NULL, NULL, (void*)&collision_20_6_4, false}, // floor left to spikes
	{&COLLISION_CL, 				{ 128,  -84, 0, 0},											0, NULL, NULL, (void*)&collision_8_3_4, false}, // floating block over spikes
	{&COLLISION_CL,					{ 124,  -24, 0, 0},											0, NULL, NULL, (void*)&collision_20_6_4, false}, // floor right to spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_3[] =
{
	{&COLLISION_HIT_CL, 			{ 128,	-46, 0, 0},													0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes hit collision
	{&COLLISION_CL, 				{ 288,	 48, 0, 0},													0, NULL, NULL, (void*)&collision_20_32_4, false}, // floor below spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_BACK_5_COLLISIONS_1[] =
{
	{&COLLISION_CL, 				{  -8, -122, 0, 0},													0, NULL, NULL, (void*)&collision_44_3_4, false},
	{&COLLISION_CL, 				{ -71,  -95, 0, 0},													0, NULL, NULL, (void*)&collision_45_5_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_BACK_5_COLLISIONS_2[] =
{
	{&COLLISION_CL, 				{  -3,   29, 0, 0},													0, NULL, NULL, (void*)&collision_62_25_4, false},
	{&COLLISION_TOP_CL, 			{ 179, -110, 0, 0},													0, NULL, NULL, (void*)&collision_6_2_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_5_COLLISIONS[] =
{
	{&COLLISION_CL, 				{ -28,  -84, 0, 0},													0, NULL, NULL, (void*)&collision_8_3_4, false}, // left floating block
	{&COLLISION_CL, 				{  82,  -84, 0, 0},													0, NULL, NULL, (void*)&collision_8_3_4, false}, // middle floating block
	{&COLLISION_CL, 				{ 196,  -84, 0, 0},													0, NULL, NULL, (void*)&collision_8_3_4, false}, // right floating block

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_6_CHILDREN[] =
{
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	{   0, 	  0, 0, 0},													0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{ -64,  -76, -SORT_INCREMENT * 2, 0}, 								0, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_6_COLLISIONS[] =
{
	{&COLLISION_CL, 				{ -56,	 64, 0, 0},													0, NULL, NULL, (void*)&collision_48_28_4, false},
	{&COLLISION_TOP_CL, 			{-130, -104, 0, 0},													0, NULL, NULL, (void*)&collision_6_2_4, false},
	{&COLLISION_CL,					{ -56, -112, 0, 0},													0, NULL, NULL, (void*)&collision_12_4_4, false},
	{&COLLISION_CL, 				{ 168,	-16, 0, 0},													0, NULL, NULL, (void*)&collision_48_28_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_1_MAIN_1_IM_CHILDREN[] =
{
	{&RUN_SIGN_IM,					{ -24,	-148, LAYER_0_BACKGROUND - LAYER_0_FOREGROUND, 0},			0, NULL, NULL, NULL, false},
	{&COIN_AG,						{   0,	-163, LAYER_0_ITEMS - LAYER_0_FOREGROUND, 0},				1, NULL, NULL, NULL, false},
	{&COIN_AG,						{-116,	-163, LAYER_0_ITEMS - LAYER_0_FOREGROUND, 0},				2, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec LEVEL_1_MAIN_STAGE_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this spec
	{&MOUND_BG_BACK_IM,				{   0,  132, LAYER_5 + LAYER_INCREMENT*3, 0},						0, NULL, NULL, NULL, true},
	{&CLOUDS_IM,					{   0,  204, LAYER_5 + LAYER_INCREMENT*2, 0},						0, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM,			{   0,  212, LAYER_5 + LAYER_INCREMENT*0, 0},						0, NULL, NULL, NULL, true},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	// left border
	{&COLLISION_CL,					{  -8,  128, LAYER_0, 0},											0, NULL, NULL, (void*)&collision_2_28_4, false},

	// part 1
	{&LEVEL_1_MAIN_1_MAIN_1_IM,		{ 256,  360, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&SMOKE_PS,						{  88,  150, 40, LAYER_0_BACKGROUND_DISPLACEMENT},					0, NULL, NULL, NULL, false},
	{&LEVEL_1_HOUSE_IM,				{  88,  192, LAYER_0_DECORATIONS, LAYER_0_DOORS_DISPLACEMENT}, 		0, "House", NULL, NULL, false},
	{&KEY_DOOR_AG,					{  44,  220, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "HouseEnt", NULL, (void*)&LEVEL1_HOUSE_STAGE_MAIN_EP, false},
	{&MANAGED_ENTITY,				{ 256,  368, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_1_COLLISIONS, NULL, false},

	{&RUN_SIGN_IM,					{ 232,  220, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},0, NULL, NULL, NULL, false},
	{&COIN_AG,						{ 184,  225, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			0, "1", NULL, NULL, false},
	{&COIN_AG,						{ 200,  225, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			0, "2", NULL, NULL, false},

	{&LEVEL_1_MAIN_1_BACK_1_IM,		{ 360,  248, LAYER_3, 0},											0, NULL, NULL, NULL, false},

	{&STAR_AG,						{ 240,	 96, LAYER_5 + LAYER_INCREMENT*3, 0},						0, NULL, NULL, NULL, false},

	{&COIN_AG,						{ 320,	248, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			0, "3", NULL, NULL, false},
	{&COIN_AG,						{ 336,	248, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},			0, "4", NULL, NULL, false},
	{&SAW_BLADE_H8_AC,				{ 352,	259, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&JUMP_SIGN_IM,					{ 472,	244, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},0, NULL, NULL, NULL, false},

	// part 2
	{&LEVEL_1_MAIN_1_MAIN_2_IM,		{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,				{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,				{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_3, NULL, false},
	{&MANAGED_ENTITY,				{ 764, 352, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_4, NULL, false},

	{&WATERFALL_TOP_AG,				{ 596, 266, LAYER_0_FOREGROUND, - SORT_INCREMENT*2},				0, NULL, NULL, NULL, false},
	{&WATERFALL_STREAM_2x28_AG,		{ 596, 378, LAYER_0_FOREGROUND, - SORT_INCREMENT*2}, 				0, NULL, NULL, NULL, false},

	{&COIN_AG,						{ 528, 228, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "5", NULL, NULL, false},
	{&COIN_AG,						{ 544, 228, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "6", NULL, NULL, false},
	{&COIN_AG,						{ 732, 196, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "7", NULL, NULL, false},
	{&BANDANA_AG,					{ 756, 196, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "1", NULL, NULL, false},
	{&COIN_AG,						{ 780, 196, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "8", NULL, NULL, false},

	{&BUSH_AG,						{ 600, 412, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},

	// part 3
	{&HIDE_LAYER_10x7_AG,			{1068, 196,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 	0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_3_A_IM, 	{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_3_B_IM, 	{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{ 798, 401, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},				0, "CoinEntr", NULL, (void*)&LEVEL1_COIN_ROOM_STAGE_MAIN_EP, false},
	{&HIDE_LAYER_10x7_AG,			{1372, 260,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 	0, NULL, NULL, NULL, false},

	{&MANAGED_ENTITY,				{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,				{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_3, NULL, false},
	{&MANAGED_ENTITY,				{1228, 240,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_4, NULL, false},

	{&COIN_AG,						{ 988, 260, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "9", NULL, NULL, false},
	{&COIN_AG,						{ 988, 308, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "10", NULL, NULL, false},
	{&COIN_AG,						{ 988, 356, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "11", NULL, NULL, false},
	{&GRASS_AG,						{1052, 408, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{1086, 208, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},				0, "IntEntrD", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_UPPER_EP, false},

	{&WATERFALL_TOP_AG,				{1156, 346, LAYER_0_FOREGROUND, -(SORT_INCREMENT*2)},				0, NULL, NULL, NULL, false},
	{&WATERFALL_STREAM_2x16_AG,		{1156, 408, LAYER_0_FOREGROUND, -(SORT_INCREMENT*2)}, 				0, NULL, NULL, NULL, false},
	{&WATER_POND_EN,				{1173, 465, LAYER_0_FOREGROUND, 0},									0, NULL, NULL, NULL, false},

	{&SAW_BLADE_V3_AC,				{1197, 472, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&DOUBLE_JUMP_SIGN_IM,			{1244, 432, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&GRASS_AG,						{1280, 440, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&COIN_AG,						{1340, 432, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "12", NULL, NULL, false},
	{&COIN_AG,						{1356, 432, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "13", NULL, NULL, false},
	{&DOOR_AG,						{1373, 272, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT},				0, "IntExitD", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_EXIT_EP, false},
	{&KEY_AG,						{1348, 276, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "2", NULL, NULL, false},
	{&BUSH_AG,						{1430, 412, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&SNAIL_3_AC,					{1496, 377, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&SNAIL_3_AC,					{1576, 345, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&MOUND_1_IM,					{1668, 300, LAYER_0_BACKGROUND + 16, LAYER_0_BACKGROUND_DISPLACEMENT},		0, NULL, NULL, NULL, false},
	{&COIN_AG,						{1724, 304, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "14", NULL, NULL, false},
	{&COIN_AG,						{1740, 304, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "15", NULL, NULL, false},

	// part 4
	{&LEVEL_1_MAIN_1_MAIN_4_IM, 	{1732, 400, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,				{1732, 400,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{1732, 400,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2, NULL, false},
	{&MANAGED_ENTITY,				{1732, 400,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_3, NULL, false},

	{&SAW_BLADE_H3_AC,				{1861, 303, LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},				0, NULL, NULL, NULL, false},
	{&MOUND_2_IM,					{2024, 301, LAYER_0_BACKGROUND + 16, LAYER_0_BACKGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},

	// part 5 (back)
	{&LEVEL_1_MAIN_1_BACK_5_IM,		{2336,  328, LAYER_2, LAYER_2_FOREGROUND_DISPLACEMENT}, 			0, NULL, NULL, NULL, false},
	{&LAYER_SWITCH_DOOR_BACK_AG, 	{2481,  300, LAYER_2 + 16, -16}, 									0, "DoorBk1", NULL, (void*)&LEVEL_1_MAIN_LS_FRONT_EP, false},
	{&MANAGED_ENTITY,				{2336,  389, LAYER_2, LAYER_2_DOORS_DISPLACEMENT * 2}, 				0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{2328,  383, LAYER_2, LAYER_2_DOORS_DISPLACEMENT * 2}, 				0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS_2, NULL, false},
	{&CANNON_AC,					{2180,  286, LAYER_2_FOREGROUND, LAYER_2_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&CANNON_AC,					{2404,  286, LAYER_2_FOREGROUND, LAYER_2_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{2093,  264, LAYER_2_ITEMS, LAYER_2_ITEMS_DISPLACEMENT},			0, "16", NULL, NULL, false},
	{&COIN_BACK_AG,					{2105,  264, LAYER_2_ITEMS, LAYER_2_ITEMS_DISPLACEMENT},			0, "17", NULL, NULL, false},
	{&COIN_BACK_AG,					{2263,  244, LAYER_2_ITEMS, LAYER_2_ITEMS_DISPLACEMENT},			0, "18", NULL, NULL, false},
	{&COIN_BACK_AG,					{2275,  244, LAYER_2_ITEMS, LAYER_2_ITEMS_DISPLACEMENT},			0, "19", NULL, NULL, false},

	// part 5
	{&LEVEL_1_MAIN_1_MAIN_5_IM, 	{2208, 392, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,				{2208, 400,	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_5_COLLISIONS, NULL, false},
	{&COIN_AG,						{2172, 292, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "20", NULL, NULL, false},
	{&COIN_AG,						{2188, 292, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "21", NULL, NULL, false},
	{&COIN_AG,						{2396, 292, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "22", NULL, NULL, false},
	{&COIN_AG,						{2412, 292, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "23", NULL, NULL, false},

	// part 6
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	{2732, 364, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,			{2668, 296, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&MANAGED_ENTITY,				{2732, 372, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_COLLISIONS, NULL, false},
	{&STAR_AG,						{2588, 112, LAYER_5 + LAYER_INCREMENT*3, 0},						0, NULL, NULL, NULL, false},
	{&LAYER_SWITCH_DOOR_AG,			{2669, 308, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "DoorFt1", NULL, (void*)&LEVEL_1_MAIN_LS_BACK_EP, false},
	{&COIN_AG,						{2732, 232, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "24", NULL, NULL, false},
	{&COIN_AG,						{2748, 232, LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT},				0, "25", NULL, NULL, false},
	{&LEVEL_1_TOWER_IM,				{2894, 132, 32, LAYER_0_BACKGROUND_DISPLACEMENT},					0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{2796, 104, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{2868, 120, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&CLOUD_A_IM,					{2972, 112, LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&KEY_DOOR_AG,					{2891, 228, LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "TowrEnt", NULL, (void*)&LEVEL1_TOWER_STAGE_MAIN_EP, false},
	{&GRASS_AG,						{2960, 237, LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT},	0, NULL, NULL, NULL, false},

	// right border
	{&COLLISION_CL,					{2996, 132, LAYER_0, 0},											0, NULL, NULL, (void*)&collision_2_28_4, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN[] =
{
	{&LOW_POWER_INDICATOR_LB, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GUI_AG, {192, 216, 0, -2}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const LEVEL_1_MAIN_STAGE_ST_FONTS[] =
{
	&PLATFORMER_FONT,
	&ASTONISH_S_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMSpec* const LEVEL_1_MAIN_STAGE_ST_CHARSETS[] =
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
	&LOW_POWER_INDICATOR_CH,
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

TextureSpec* const LEVEL_1_MAIN_STAGE_ST_TEXTURES[] =
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
	&LOW_POWER_INDICATOR_TX,
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
	PostProcessingRain_rain,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec LEVEL_1_MAIN_STAGE_ST =
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
		// number of cycles the texture writing is idle
		1,

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
			// maximum x view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE,
			// maximum y view distance's power into the horizon
			__MAXIMUM_Y_VIEW_DISTANCE,
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
		(FontSpec**)LEVEL_1_MAIN_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetSpec**)LEVEL_1_MAIN_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureSpec**)LEVEL_1_MAIN_STAGE_ST_TEXTURES,

		// background sounds
		(Sound**)NULL,
	},

	// entities
	{
		// ui
		{
			LEVEL_1_MAIN_STAGE_ST_UI_CHILDREN,
			__TYPE(UIContainer),
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

StageEntryPointROMSpec LEVEL_1_MAIN_MAIN_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"HouseEnt",

	// offset from entry point (x, y, z)
	{
		19,
		-30,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMSpec LEVEL_1_MAIN_HOUSE_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_MAIN_STAGE_ST,

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

StageEntryPointROMSpec LEVEL_1_MAIN_COIN_ROOM_ENTRY_DOOR_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_MAIN_STAGE_ST,

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

StageEntryPointROMSpec LEVEL_1_MAIN_INTERSECTION_ENTRY_DOOR_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_MAIN_STAGE_ST,

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

StageEntryPointROMSpec LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_MAIN_STAGE_ST,

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

StageEntryPointROMSpec LEVEL_1_MAIN_LS_FRONT_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_MAIN_STAGE_ST,

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

StageEntryPointROMSpec LEVEL_1_MAIN_LS_BACK_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_MAIN_STAGE_ST,

	// name of the entity to start at
	"DoorBk1",

	// offset from entry point (x, y, z)
	{
		0,
		0,
		0,
		-1
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMSpec LEVEL_1_MAIN_TOWER_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_MAIN_STAGE_ST,

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
