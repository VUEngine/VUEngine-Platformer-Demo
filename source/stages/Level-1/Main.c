/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Stage.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <VPUManager.h>

#include <objects.h>
#include <sound.h>


//---------------------------------------------------------------------------------------------------------
// 											    DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL_1_COIN_ROOM_MAIN_EP;
extern StageEntryPointROMDef LEVEL_1_SMALL_ROOM_MAIN_EP;
extern StageEntryPointROMDef LEVEL_1_TOWER_MAIN_EP;

StageEntryPointROMDef LEVEL_1_MAIN_LS_FRONT_EP[];
StageEntryPointROMDef LEVEL_1_MAIN_LS_BACK_EP[];

extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition COLLISIONS_CONTAINER_ENTITY;


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_1_IM,     {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
    {&LEVEL_1_HOUSE_IM,             {FTOFIX19_13(-140), FTOFIX19_13(-176), 	FTOFIX19_13(0)},    "House", NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_COLLISIONS[] =
{
	{&COLLISION_34x30x1,            {FTOFIX19_13(-136), FTOFIX19_13(-12), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // left floor
	{&COLLISION_34x30x1,            {FTOFIX19_13(112),  FTOFIX19_13(12), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // right floor

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_2_IM,     {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_ONEWAY_7x7x1,       {FTOFIX19_13(-226), FTOFIX19_13(-84),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // left top one-way
	{&COLLISION_14x18x1, 	        {FTOFIX19_13(-145), FTOFIX19_13(-56),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floor left to spikes
	{&COLLISION_14x18x1, 	        {FTOFIX19_13(127),  FTOFIX19_13(-56),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floor right to spikes
	{&COLLISION_8x3x1, 	            {FTOFIX19_13(-8),   FTOFIX19_13(-132),  FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floating block over spikes
	{&HIT_COLLISION_20x2x1,         {FTOFIX19_13(-8),   FTOFIX19_13(-92),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // spikes hit collision
	{&COLLISION_32x14x1, 	        {FTOFIX19_13(-8),   FTOFIX19_13(-40),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floor below spikes

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_ONEWAY_7x7x1,       {FTOFIX19_13(-226), FTOFIX19_13(92),    FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // left bottom one-way
	{&COLLISION_48x18x1, 	        {FTOFIX19_13(-10),  FTOFIX19_13(136),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // secret bottom floor
	{&COLLISION_ONEWAY_7x7x1,       {FTOFIX19_13(210),  FTOFIX19_13(-52),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // right top one-way
	{&COLLISION_ONEWAY_7x7x1,       {FTOFIX19_13(210),  FTOFIX19_13(44),    FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // right bottom one-way
	{&COLLISION_14x6x1,		        {FTOFIX19_13(127),  FTOFIX19_13(38),    FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // wall right to the secret door
	{&COLLISION_18x6x1,		        {FTOFIX19_13(238),  FTOFIX19_13(88),    FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floor under the one-way passage

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_3_IM, 	{FTOFIX19_13(0),    FTOFIX19_13(0),     FTOFIX19_13(0)},    NULL, NULL, NULL, false},
    {&HIDE_LAYER_10x7_AG,           {FTOFIX19_13(-160), FTOFIX19_13(-43),   FTOFIX19_13(-SORT_INCREMENT * 4)},    NULL, NULL, NULL, false},
	{&LANE_V_6_IM,                  {FTOFIX19_13(-31),  FTOFIX19_13(232), 	FTOFIX19_13(-SORT_INCREMENT)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1[] =
{
	{&COLLISION_ONEWAY_7x7x1, 	    {FTOFIX19_13(-226), FTOFIX19_13(12),    FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // top one-way
	{&COLLISION_ONEWAY_7x7x1, 	    {FTOFIX19_13(-226), FTOFIX19_13(108),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // bottom one-way
	{&COLLISION_48x18x1, 	        {FTOFIX19_13(-8),   FTOFIX19_13(-138),  FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // above hidden area
	{&COLLISION_38x10x1, 	        {FTOFIX19_13(-48),  FTOFIX19_13(24),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_28x16x1, 	        {FTOFIX19_13(-8),   FTOFIX19_13(-13),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_38x10x1, 	        {FTOFIX19_13(32),   FTOFIX19_13(-41),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2[] =
{
	{&COLLISION_48x10x1, 	        {FTOFIX19_13(-8),   FTOFIX19_13(88),    FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // ceiling above steps area
	{&COLLISION_14x6x1,		        {FTOFIX19_13(-162), FTOFIX19_13(232),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // 2nd lowest left step
	{&COLLISION_14x6x1,		        {FTOFIX19_13(-112), FTOFIX19_13(264),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // lowest left step
	{&COLLISION_14x6x1,		        {FTOFIX19_13(48),   FTOFIX19_13(264),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // lowest right step
	{&COLLISION_14x6x1,		        {FTOFIX19_13(128),  FTOFIX19_13(232),   FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // 2nd lowest right step

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_4_IM, 	{FTOFIX19_13(0),    FTOFIX19_13(0), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1[] =
{
	{&COLLISION_14x6x1,		        {FTOFIX19_13(-296), FTOFIX19_13(40), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // lowest step after ceiling
	{&COLLISION_14x6x1,		        {FTOFIX19_13(-216), FTOFIX19_13(8), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // middle step after ceiling
	{&COLLISION_14x6x1,		        {FTOFIX19_13(-136), FTOFIX19_13(-24), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // highest step after ceiling
	{&COLLISION_20x6x1,		        {FTOFIX19_13(-32),  FTOFIX19_13(-56), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floor left to spikes

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2[] =
{
	{&COLLISION_8x3x1, 	            {FTOFIX19_13(128),  FTOFIX19_13(-84), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floating block over spikes
	{&COLLISION_20x6x1,		        {FTOFIX19_13(124),  FTOFIX19_13(-24), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floor right to spikes
	{&HIT_COLLISION_20x2x1, 	    {FTOFIX19_13(128),  FTOFIX19_13(-44), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // spikes hit collision
	{&COLLISION_20x32x1, 	        {FTOFIX19_13(288),  FTOFIX19_13(48), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // floor below spikes

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_BACK_5_IM,     {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(4 * SORT_INCREMENT)}, NULL, NULL, NULL, false},
	{&LAYER_SWITCH_DOOR_BACK_AG, 	{FTOFIX19_13(145), 	FTOFIX19_13(-82), 	FTOFIX19_13(3 * SORT_INCREMENT)}, "Door Back 1", NULL, (void*)&LEVEL_1_MAIN_LS_FRONT_EP, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_COLLISIONS[] =
{
	{&COLLISION_47x3x1, 	        {FTOFIX19_13(-8),   FTOFIX19_13(-120), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_49x5x1, 	        {FTOFIX19_13(-72),  FTOFIX19_13(-88), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_67x25x1, 	        {FTOFIX19_13(0),    FTOFIX19_13(32), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x7x1, 	    {FTOFIX19_13(190), 	FTOFIX19_13(-91), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_5_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_5_IM, 	{FTOFIX19_13(0),    FTOFIX19_13(0), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_5_COLLISIONS[] =
{
	{&COLLISION_8x3x1, 	            {FTOFIX19_13(-28),  FTOFIX19_13(-84), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // left floating block
	{&COLLISION_8x3x1, 	            {FTOFIX19_13(74),   FTOFIX19_13(-84), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // middle floating block
	{&COLLISION_8x3x1, 	            {FTOFIX19_13(196),  FTOFIX19_13(-84), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false}, // right floating block

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	{FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(-SORT_INCREMENT * 2)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_COLLISIONS[] =
{
	{&COLLISION_48x28x1, 	        {FTOFIX19_13(-56),  FTOFIX19_13(63), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x7x1, 	    {FTOFIX19_13(-130), FTOFIX19_13(-85), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_12x4x1,             {FTOFIX19_13(-56),  FTOFIX19_13(-113), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_48x28x1, 	        {FTOFIX19_13(168),  FTOFIX19_13(-17), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_MAIN_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,				{FTOFIX19_13(0),    FTOFIX19_13(32), 	FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, true},
	{&CLOUDS_IM,					{FTOFIX19_13(0),    FTOFIX19_13(170), 	FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM,			{FTOFIX19_13(0),    FTOFIX19_13(208), 	FTOFIX19_13(LAYER_3)}, NULL, NULL, NULL, true},

	{&HERO_AC,						{FTOFIX19_13(56),   FTOFIX19_13(288), 	FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, true},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

    // left border
	{&COLLISION_2x28x1,				{FTOFIX19_13(-8),  FTOFIX19_13(128), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

    // part 1
    {&SMOKE_PS,						{FTOFIX19_13(94),   FTOFIX19_13(140), 	FTOFIX19_13(LAYER_0_FOREGROUND + 32)},   NULL, NULL, NULL, false},
    {&MANAGED_ENTITY,				{FTOFIX19_13(256),  FTOFIX19_13(368),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_1_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(256),  FTOFIX19_13(368),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_1_COLLISIONS, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(232),  FTOFIX19_13(225), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 01", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(248),  FTOFIX19_13(225), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 02", NULL, NULL, false},

	{&LEVEL_1_MAIN_1_BACK_1_IM,		{FTOFIX19_13(360),  FTOFIX19_13(240), 	FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},

    {&STAR_AG,						{FTOFIX19_13(344),  FTOFIX19_13(16), 	FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(320),  FTOFIX19_13(248), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 03", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(336),  FTOFIX19_13(248), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 04", NULL, NULL, false},
	{&SAW_BLADE_H8_AC,				{FTOFIX19_13(338),  FTOFIX19_13(259), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},
	{&BUSH_AG,						{FTOFIX19_13(472),  FTOFIX19_13(256), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

    // part 2
    {&MANAGED_ENTITY,				{FTOFIX19_13(764), FTOFIX19_13(352),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(764), FTOFIX19_13(352),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(764), FTOFIX19_13(352),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(528),  FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 05", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(544),  FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 06", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(732),  FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 07", NULL, NULL, false},
	{&BANDANA_AG,					{FTOFIX19_13(756),  FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},
    {&COIN_AG,						{FTOFIX19_13(780),  FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 08", NULL, NULL, false},
	{&DOOR_AG,						{FTOFIX19_13(798),  FTOFIX19_13(401), 	FTOFIX19_13(LAYER_0_DOORS)}, NULL, NULL, (void*)&LEVEL_1_COIN_ROOM_MAIN_EP, false},

    // part 3
    {&MANAGED_ENTITY,				{FTOFIX19_13(1228), FTOFIX19_13(240),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1228), FTOFIX19_13(240),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1228), FTOFIX19_13(240),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(988),  FTOFIX19_13(260), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 09", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(988),  FTOFIX19_13(308), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 10", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(988),  FTOFIX19_13(356), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 11", NULL, NULL, false},
	{&GRASS_AG,						{FTOFIX19_13(1052), FTOFIX19_13(408), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},
	{&DOOR_AG,						{FTOFIX19_13(1086), FTOFIX19_13(208), 	FTOFIX19_13(LAYER_0_DOORS)}, NULL, NULL, (void*)&LEVEL_1_SMALL_ROOM_MAIN_EP, false},
	{&DOOR_AG,						{FTOFIX19_13(1357), FTOFIX19_13(272), 	FTOFIX19_13(LAYER_0_DOORS)}, "SmallRoomExitDoor", NULL, NULL, false},
	{&KEY_AG,						{FTOFIX19_13(1388), FTOFIX19_13(276), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_V3_AC,				{FTOFIX19_13(1196), FTOFIX19_13(472), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(1340), FTOFIX19_13(432), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 12", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(1356), FTOFIX19_13(432), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 13", NULL, NULL, false},
	{&GRASS_AG,						{FTOFIX19_13(1288), FTOFIX19_13(472), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},
	{&SNAIL_4_AC,					{FTOFIX19_13(1416), FTOFIX19_13(409), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},
	{&BUSH_AG,						{FTOFIX19_13(1484), FTOFIX19_13(380), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},
	//{&SNAIL_4_AC,					{FTOFIX19_13(1576), FTOFIX19_13(345), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(1692), FTOFIX19_13(304), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 14", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(1708), FTOFIX19_13(304), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 15", NULL, NULL, false},

    // part 4
    {&MANAGED_ENTITY,				{FTOFIX19_13(1732), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1732), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(1732), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2, NULL, false},

	{&SAW_BLADE_H3_AC,				{FTOFIX19_13(1861), FTOFIX19_13(303), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    // part 5 (back)
    {&MANAGED_ENTITY,				{FTOFIX19_13(2336), FTOFIX19_13(368),   FTOFIX19_13(LAYER_2)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(2336), FTOFIX19_13(368),   FTOFIX19_13(LAYER_2)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS, NULL, false},
	{&CANNON_AC,					{FTOFIX19_13(2180), FTOFIX19_13(266), 	FTOFIX19_13(LAYER_2_FOREGROUND)},    NULL, NULL, NULL, false},
	{&CANNON_AC,					{FTOFIX19_13(2404), FTOFIX19_13(266), 	FTOFIX19_13(LAYER_2_FOREGROUND)},    NULL, NULL, NULL, false},
	{&COIN_BACK_AG,					{FTOFIX19_13(2093), FTOFIX19_13(249), 	FTOFIX19_13(LAYER_2_ITEMS)}, "Coin 16", NULL, NULL, false},
	{&COIN_BACK_AG,					{FTOFIX19_13(2105), FTOFIX19_13(249), 	FTOFIX19_13(LAYER_2_ITEMS)}, "Coin 17", NULL, NULL, false},
	{&COIN_BACK_AG,					{FTOFIX19_13(2263), FTOFIX19_13(226), 	FTOFIX19_13(LAYER_2_ITEMS)}, "Coin 18", NULL, NULL, false},
	{&COIN_BACK_AG,					{FTOFIX19_13(2275), FTOFIX19_13(226), 	FTOFIX19_13(LAYER_2_ITEMS)}, "Coin 19", NULL, NULL, false},

    // part 5
    {&MANAGED_ENTITY,				{FTOFIX19_13(2208), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_5_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(2208), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_5_COLLISIONS, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(2172), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 20", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2188), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 21", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2396), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 22", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2412), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 23", NULL, NULL, false},

    // part 6
    {&MANAGED_ENTITY,				{FTOFIX19_13(2732), FTOFIX19_13(372),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(2732), FTOFIX19_13(372),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_COLLISIONS, NULL, false},

	{&STAR_AG,						{FTOFIX19_13(2544), FTOFIX19_13(16), 	FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, false},

	{&HIDE_LAYER_10x7_AG,           {FTOFIX19_13(2668), FTOFIX19_13(296), 	FTOFIX19_13(LAYER_0_FOREGROUND - 4 * SORT_INCREMENT)}, NULL, NULL, NULL, false},
	{&LAYER_SWITCH_DOOR_AG,			{FTOFIX19_13(2669), FTOFIX19_13(308), 	FTOFIX19_13(LAYER_0_DOORS - 2 * SORT_INCREMENT)}, "Door Front 1", NULL, (void*)&LEVEL_1_MAIN_LS_BACK_EP, false},
	{&COIN_AG,						{FTOFIX19_13(2732), FTOFIX19_13(232), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 24", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2748), FTOFIX19_13(232), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 25", NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(2764), FTOFIX19_13(232), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 26", NULL, NULL, false},
	{&KEY_DOOR_AG,					{FTOFIX19_13(2893), FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_DOORS - 2 * SORT_INCREMENT)}, "TowerEntrance", NULL, (void*)&LEVEL_1_TOWER_MAIN_EP, false},
	{&GRASS_AG,						{FTOFIX19_13(2960), FTOFIX19_13(237), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

    // right border
	{&COLLISION_2x28x1,				{FTOFIX19_13(2996), FTOFIX19_13(116), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_ST_UI_CHILDREN[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(217), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef* LEVEL_1_MAIN_ST_CHARSETS[] =
{
	&LEVEL_1_MAIN_1_MAIN_CH,
	&LEVEL_1_MAIN_1_MAIN_FRONT_CH,
	&LEVEL_1_MAIN_1_MAIN_BACK_CH,
	&DOOR_CH,
	&COIN_CH,
	&COIN_BACK_CH,
	&COIN_SILHOUETTE_CH,
	&COIN_BACK_SILHOUETTE_CH,
	&MOUND_BG_BACK_CH,
	&MOUND_BG_MIDDLE_CH,
	&MOUND_BG_FRONT_CH,
	&HIDE_LAYER_10x7_CH,
	&SNAIL_CH,
	&GRASS_CH,
	&BUSH_CH,
	&LEVEL_1_HOUSE_CH,
	&SAW_BLADE_CH,
	&KEY_CH,
	NULL,
};

StageTextureEntryROMDef LEVEL_1_MAIN_ST_TEXTURES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_3_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_3_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_BACK_3_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_1_TX, true},
	{&LEVEL_1_MAIN_1_BACK_1_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_2_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_1_TX, true},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_2_TX, true},
	{&MOUND_BG_BACK_TX, false},
	{&MOUND_BG_MIDDLE_TX, false},
	{&MOUND_BG_FRONT_TX, false},
	{&DUST_PARTICLE_SMALL_TX, false},
	{&SAW_BLADE_TX, false},
	{&DOOR_TX, false},
	{&LEVEL_1_HOUSE_TX, false},
	{&HIDE_LAYER_10x7_TX, false},

	{NULL, false}
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_MAIN_ST =
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
        // delay per cycle
        14,
        // load padding
        74,
        // unload padding
        16,
        // streaming amplitude
        38,
    },

    // rendering
    {
        // number of cycles the texture writing is idle
        4,

        // maximum number of texture's rows to write each time the texture writing is active
        8,

        // maximum number of rows to compute on each call to the affine functions
        12,

        // column table
		NULL,

        // palette's config
        {
            // background color
            __COLOR_BLACK,

            {
                __BGMAP_PALETTE_0,
                __BGMAP_PALETTE_1,
                __BGMAP_PALETTE_2,
                __BGMAP_PALETTE_3,
            },
            {
                __OBJECT_PALETTE_0,
                __OBJECT_PALETTE_1,
                __OBJECT_PALETTE_2,
                __OBJECT_PALETTE_3,
            }
        },

        // BGMAP segments configuration
        // number of segments reserved for dynamically allocated textures when preloading
        5,

        // OBJs segments sizes (must total 1024)
        {
            // SPT0
            __AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
            // SPT1
            __AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
            // SPT2
            __AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
            // SPT3
            __AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
        },

        // OBJs segments z coordinates
        // Note that each SPT's z coordinate much be larger than or equal to the previous one's,
        // since the VIP renders OBJ Worlds in reverse order (SPT3 to SPT0)
        {
            // SPT0
            FTOFIX19_13(LAYER_0_PARTICLES),
            // SPT1
            FTOFIX19_13(LAYER_0_PARTICLES),
            // SPT2
            FTOFIX19_13(LAYER_0_PARTICLES),
            // SPT3
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
        // char sets to preload
        (CharSetDefinition**)LEVEL_1_MAIN_ST_CHARSETS,

        // textures to preload
        (StageTextureEntryDefinition*)LEVEL_1_MAIN_ST_TEXTURES,

        // background music
        (const u16 (*)[])WORLD_0_0_0_BGM,
    },

    // entities
    {
        // UI
        {
            LEVEL_1_MAIN_ST_UI_CHILDREN,
            __TYPE(UI),
        },

        // children
        LEVEL_1_MAIN_ST_CHILDREN,
    },
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL_1_MAIN_MAIN_EP[] =
{{
	// the stage to load
    (StageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "House",

    // offset from entry point (x, y, z)
    {FTOFIX19_13(-64), FTOFIX19_13(-200), FTOFIX19_13(-SORT_INCREMENT)},
}};

StageEntryPointROMDef LEVEL_1_MAIN_SMALL_ROOM_EXIT_DOOR_EP[] =
{{
	// the stage to load
    (StageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "SmallRoomExitDoor",

    // offset from entry point (x, y, z)
    {0, FTOFIX19_13(-5), FTOFIX19_13(-SORT_INCREMENT)},
}};

StageEntryPointROMDef LEVEL_1_MAIN_LS_FRONT_EP[] =
{{
	// the stage to load
    (StageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "Door Front 1",

    // offset from entry point (x, y, z)
    {0, ITOFIX19_13(-1), FTOFIX19_13(-SORT_INCREMENT)},
}};

StageEntryPointROMDef LEVEL_1_MAIN_LS_BACK_EP[] =
{{
	// the stage to load
    (StageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "Door Back 1",

    // offset from entry point (x, y, z)
    {0, FTOFIX19_13(-0.5f), FTOFIX19_13(-SORT_INCREMENT)},
}};

StageEntryPointROMDef LEVEL_1_MAIN_TOWER_EP[] =
{{
	// the stage to load
    (StageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "TowerEntrance",

    // offset from entry point (x, y, z)
    {0, FTOFIX19_13(-5), FTOFIX19_13(-SORT_INCREMENT)},
}};
