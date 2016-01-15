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
#include "stages/textures.h"


//---------------------------------------------------------------------------------------------------------
// 											    PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern PlatformerStageEntryPointROMDef LEVEL_1_COIN_ROOM_MAIN_EP;
extern PlatformerStageEntryPointROMDef LEVEL_1_SMALL_ROOM_MAIN_EP;
extern PlatformerStageEntryPointROMDef LEVEL_1_TOWER_MAIN_EP;

PlatformerStageEntryPointROMDef LEVEL_1_MAIN_LS_FRONT_EP[];
PlatformerStageEntryPointROMDef LEVEL_1_MAIN_LS_BACK_EP[];


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_1_IM,         {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
    {&LEVEL_1_HOUSE_IM,                 {FTOFIX19_13(-140), FTOFIX19_13(-176), 	FTOFIX19_13(0)},    "House", NULL, NULL, false},
    {&SMOKE_PS,                         {FTOFIX19_13(-164), FTOFIX19_13(-218), 	FTOFIX19_13(32)},   NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_COLLISIONS[] =
{
	{&COLLISION_30x33x1,                {FTOFIX19_13(-130), FTOFIX19_13(1), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_34x30x1,                {FTOFIX19_13(110),  FTOFIX19_13(13), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_2_IM,         {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_ONEWAY_7x7x1, 			{FTOFIX19_13(-226), FTOFIX19_13(-83),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x18x1, 	    		{FTOFIX19_13(-145), FTOFIX19_13(-55),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x18x1, 	    		{FTOFIX19_13(127),  FTOFIX19_13(-55),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	        		{FTOFIX19_13(-8),   FTOFIX19_13(-131),  FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&HIT_COLLISION_20x1x1, 			{FTOFIX19_13(-8),   FTOFIX19_13(-100),  FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_32x14x1, 	    		{FTOFIX19_13(-8),   FTOFIX19_13(-40),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_ONEWAY_7x7x1, 			{FTOFIX19_13(-226), FTOFIX19_13(93),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_48x18x1, 	    		{FTOFIX19_13(-10),  FTOFIX19_13(137),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x7x1, 			{FTOFIX19_13(210),  FTOFIX19_13(-51),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x7x1, 			{FTOFIX19_13(210),  FTOFIX19_13(45),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		    		{FTOFIX19_13(127),  FTOFIX19_13(39),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_18x6x1,		    		{FTOFIX19_13(238),  FTOFIX19_13(89),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_3_IM, 	    {FTOFIX19_13(0),    FTOFIX19_13(0),     FTOFIX19_13(0)},    NULL, NULL, NULL, false},
    {&HIDE_LAYER_10x7_AG,               {FTOFIX19_13(-160), FTOFIX19_13(-44),   FTOFIX19_13(-SORT_INCREMENT * 4)},    NULL, NULL, NULL, false},
	{&LANE_V_6_IM,            {FTOFIX19_13(-32), FTOFIX19_13(232), 	FTOFIX19_13(-SORT_INCREMENT)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1[] =
{
	{&COLLISION_ONEWAY_7x7x1, 	        {FTOFIX19_13(-226), FTOFIX19_13(-11 + 24),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x7x1, 	        {FTOFIX19_13(-226), FTOFIX19_13(84 + 24),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_48x18x1, 	            {FTOFIX19_13(-8),   FTOFIX19_13(-138),  FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_38x10x1, 	            {FTOFIX19_13(-48),  FTOFIX19_13(25),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_28x16x1, 	            {FTOFIX19_13(-8),   FTOFIX19_13(-12),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_38x10x1, 	            {FTOFIX19_13(32),   FTOFIX19_13(-40),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2[] =
{
	{&COLLISION_48x10x1, 	            {FTOFIX19_13(-8),   FTOFIX19_13(89),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(-162), FTOFIX19_13(233),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(-112), FTOFIX19_13(265),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(48),   FTOFIX19_13(265),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(128),  FTOFIX19_13(233),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_4_IM, 	    {FTOFIX19_13(0),    FTOFIX19_13(0), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1[] =
{
	{&COLLISION_14x6x1,		            {FTOFIX19_13(-296), FTOFIX19_13(41), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(-216), FTOFIX19_13(9), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(-136), FTOFIX19_13(-23), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_20x6x1,		            {FTOFIX19_13(-32),  FTOFIX19_13(-55), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2[] =
{
	{&COLLISION_20x6x1,		            {FTOFIX19_13(124),  FTOFIX19_13(-27), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	                {FTOFIX19_13(128),  FTOFIX19_13(-84), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_20x32x1, 	            {FTOFIX19_13(288),  FTOFIX19_13(53), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&HIT_COLLISION_20x1x1, 	        {FTOFIX19_13(128),  FTOFIX19_13(-51), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_BACK_5_IM,         {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(4 * SORT_INCREMENT)}, NULL, NULL, NULL, false},
	{&CANNON_AC,                        {FTOFIX19_13(-156), FTOFIX19_13(-102), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&CANNON_AC,                        {FTOFIX19_13(68),   FTOFIX19_13(-102), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_BACK_5_COLLISIONS[] =
{
	{&COLLISION_46x2x1, 	            {FTOFIX19_13(-4),   FTOFIX19_13(-124), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_48x5x1, 	            {FTOFIX19_13(-76),  FTOFIX19_13(-88), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_67x25x1, 	            {FTOFIX19_13(0),    FTOFIX19_13(32), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x7x1, 	        {FTOFIX19_13(190), 	FTOFIX19_13(-115 + 24), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_5_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_5_IM, 	    {FTOFIX19_13(0),    FTOFIX19_13(0), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_5_COLLISIONS[] =
{
	{&COLLISION_8x3x1, 	                {FTOFIX19_13(-28),  FTOFIX19_13(-83), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	                {FTOFIX19_13(74),   FTOFIX19_13(-83), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	                {FTOFIX19_13(196),  FTOFIX19_13(-83), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_ENTITIES[] =
{
	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	    {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(-SORT_INCREMENT * 2)}, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,               {FTOFIX19_13(-64), 	FTOFIX19_13(-76), 	FTOFIX19_13(-SORT_INCREMENT * 4)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_6_COLLISIONS[] =
{
	{&COLLISION_48x28x1, 	            {FTOFIX19_13(-56),  FTOFIX19_13(65), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x7x1, 	        {FTOFIX19_13(-130), FTOFIX19_13(-107 + 24), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_12x4x1,                 {FTOFIX19_13(-56),  FTOFIX19_13(-111), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_48x28x1, 	            {FTOFIX19_13(168),  FTOFIX19_13(-15), 	FTOFIX19_13(0)},    NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,	 	                    {FTOFIX19_13(0),    FTOFIX19_13(120), 	FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, true},
	{&CLOUDS_IM, 	  			                {FTOFIX19_13(0),    FTOFIX19_13(232), 	FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM, 	                    {FTOFIX19_13(0),    FTOFIX19_13(256), 	FTOFIX19_13(LAYER_3)}, NULL, NULL, NULL, true},

	{&HERO_AC, 				                    {FTOFIX19_13(56),   FTOFIX19_13(288), 	FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, true},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	{&COLLISION_2x28x1,                         {FTOFIX19_13(-12),  FTOFIX19_13(116), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(256),  FTOFIX19_13(368),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_1_ENTITIES, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(256),  FTOFIX19_13(368),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_1_COLLISIONS, NULL, false},

	{&COIN_AG,                                  {FTOFIX19_13(232),  FTOFIX19_13(225), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 001", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(248),  FTOFIX19_13(225), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 002", NULL, NULL, false},
	{&LEVEL_1_MAIN_1_BACK_1_IM,                 {FTOFIX19_13(360),  FTOFIX19_13(256), 	FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
    {&STAR_AG,                                  {FTOFIX19_13(344),  FTOFIX19_13(92),  	FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(304),  FTOFIX19_13(248), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 003", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(320),  FTOFIX19_13(248), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 004", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(336),  FTOFIX19_13(248), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 005", NULL, NULL, false},
	{&SAW_BLADE_H8_AC,                          {FTOFIX19_13(338),  FTOFIX19_13(260), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},
	{&BUSH_AG,                                  {FTOFIX19_13(472),  FTOFIX19_13(256), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(764), FTOFIX19_13(352),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_ENTITIES, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(764), FTOFIX19_13(352),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_1, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(764), FTOFIX19_13(352),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_COLLISIONS_2, NULL, false},

	{&COIN_AG,                                  {FTOFIX19_13(528),  FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 006", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(544),  FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 007", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(732),  FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 009", NULL, NULL, false},
    {&BANDANA_AG,                               {FTOFIX19_13(756),  FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},
//	{&COIN_AG,                                  {FTOFIX19_13(764),  FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 010", NULL, NULL, false},
    {&COIN_AG,                                  {FTOFIX19_13(780),  FTOFIX19_13(196), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 011", NULL, NULL, false},
	{&DOOR_AG,				                    {FTOFIX19_13(798),  FTOFIX19_13(400), 	FTOFIX19_13(LAYER_0_DOORS)}, NULL, NULL, (void*)&LEVEL_1_COIN_ROOM_MAIN_EP, false},

    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(1227), FTOFIX19_13(240),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_ENTITIES, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(1227), FTOFIX19_13(240),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_1, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(1227), FTOFIX19_13(240),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_COLLISIONS_2, NULL, false},

//	{&COIN_AG,                                  {FTOFIX19_13(988),  FTOFIX19_13(212), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 011", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(988),  FTOFIX19_13(260), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 012", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(988),  FTOFIX19_13(308), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 013", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(988),  FTOFIX19_13(356), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 014", NULL, NULL, false},
//	{&COIN_AG,                                  {FTOFIX19_13(988),  FTOFIX19_13(404), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 015", NULL, NULL, false},
	{&GRASS_AG,                                 {FTOFIX19_13(1052), FTOFIX19_13(408), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},
	{&DOOR_AG,				                    {FTOFIX19_13(1086), FTOFIX19_13(208), 	FTOFIX19_13(LAYER_0_DOORS)}, NULL, NULL, (void*)&LEVEL_1_SMALL_ROOM_MAIN_EP, false},
	{&DOOR_AG,				                    {FTOFIX19_13(1357), FTOFIX19_13(272), 	FTOFIX19_13(LAYER_0_DOORS)}, "SmallRoomExitDoor", NULL, NULL, false},
	{&KEY_AG,				                    {FTOFIX19_13(1388), FTOFIX19_13(276), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_V3_AC,                          {FTOFIX19_13(1196), FTOFIX19_13(472), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(1340), FTOFIX19_13(432), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 016", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(1356), FTOFIX19_13(432), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 017", NULL, NULL, false},
	{&GRASS_AG,                                 {FTOFIX19_13(1288), FTOFIX19_13(472), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(1732), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_ENTITIES, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(1732), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_1, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(1732), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_4_COLLISIONS_2, NULL, false},

	{&SAW_BLADE_H3_AC,                          {FTOFIX19_13(1861), FTOFIX19_13(302), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(2336), FTOFIX19_13(384),   FTOFIX19_13(LAYER_2)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_ENTITIES, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(2336), FTOFIX19_13(384),   FTOFIX19_13(LAYER_2)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_BACK_5_COLLISIONS, NULL, false},

    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(2208), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_5_ENTITIES, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(2208), FTOFIX19_13(400),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_5_COLLISIONS, NULL, false},

	{&COIN_AG,                                  {FTOFIX19_13(2172), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 019", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(2188), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 020", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(2396), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 021", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(2412), FTOFIX19_13(292), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 022", NULL, NULL, false},

    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(2732), FTOFIX19_13(364),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_ENTITIES, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(2732), FTOFIX19_13(364),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_6_COLLISIONS, NULL, false},

	{&STAR_AG,  	        			        {FTOFIX19_13(2544), FTOFIX19_13(108), 	FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, false},
	{&LAYER_SWITCH_DOOR_AG,				        {FTOFIX19_13(2669), FTOFIX19_13(300), 	FTOFIX19_13(LAYER_0_DOORS - 2 * SORT_INCREMENT)}, "Door Front 1", NULL, (void*)&LEVEL_1_MAIN_LS_BACK_EP, false},
	{&COIN_AG,                                  {FTOFIX19_13(2732), FTOFIX19_13(224), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 023", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(2748), FTOFIX19_13(224), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 024", NULL, NULL, false},
	{&COIN_AG,                                  {FTOFIX19_13(2764), FTOFIX19_13(224), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 025", NULL, NULL, false},
	{&DOOR_AG,				                    {FTOFIX19_13(2900), FTOFIX19_13(220), 	FTOFIX19_13(LAYER_0_DOORS - 2 * SORT_INCREMENT)}, "TowerEntrance", NULL, (void*)&LEVEL_1_TOWER_MAIN_EP, false},
	{&GRASS_AG,				                    {FTOFIX19_13(2960), FTOFIX19_13(228), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

	{&COLLISION_2x28x1,                         {FTOFIX19_13(2996), FTOFIX19_13(116), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_ST_UI_ENTITIES[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(215), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

CharSetROMDef* LEVEL_1_MAIN_ST_CHARSETS[] =
{
	&LEVEL_1_MAIN_1_MAIN_CH,
	&LEVEL_1_MAIN_1_MAIN_FRONT_CH,
	NULL,
};

TextureROMDef* LEVEL_1_MAIN_ST_TEXTURES[] =
{
	&LEVEL_1_MAIN_1_MAIN_1_TX,
	&LEVEL_1_MAIN_1_MAIN_2_TX,
	&LEVEL_1_MAIN_1_MAIN_FRONT_1_TX,
	&LEVEL_1_MAIN_1_MAIN_FRONT_2_TX,
	&LEVEL_1_MAIN_1_BACK_1_TX,
	&MOUND_BG_BACK_TX,
	&MOUND_BG_MIDDLE_TX,
	&MOUND_BG_FRONT_TX,
	&HERO_TX,
	&DUST_PARTICLE_SMALL_TX,
	&COIN_TX,
	&DOOR_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerStageROMDef LEVEL_1_MAIN_ST =
{
    {
        // size
        {
            // x
            2988,
            // y
            512,
            // z
            256,
        },

        // streaming
    	{
    		// delay per cycle
    		8,
    		// load padding
    		80,
    		// unload padding
    		16,
    		// streaming amplitude
    		28,
    	},

        // gravity
        {
            ITOFIX19_13(0),
            ITOFIX19_13(__GRAVITY),
            ITOFIX19_13(0)
        },

        // friction
        FTOFIX19_13(0.1f),
        
        // Palette's config
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
        6,

    	// OBJs segments sizes (must total 1024)
        {
            // SPT0
        	__AVAILABLE_CHAR_OBJECTS / 4,
            // SPT1
        	__AVAILABLE_CHAR_OBJECTS / 4,
            // SPT2
        	__AVAILABLE_CHAR_OBJECTS / 4,
            // SPT3
        	__AVAILABLE_CHAR_OBJECTS / 4,
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

        // initial screen position
        {
            // x
            ITOFIX19_13(0),
            // y
            ITOFIX19_13(0),
            // z
            ITOFIX19_13(0)
        },

        // optical configuration values
        {
    		// maximum view distance's power into the horizon
    		__MAXIMUM_VIEW_DISTANCE_POWER + 1,
            // distance of the eyes to the screen
            ITOFIX19_13(__DISTANCE_EYE_SCREEN),
            // distance from left to right eye (depth sensation)
            ITOFIX19_13(__BASE_FACTOR),
            // horizontal View point center
            ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
            // vertical View point center
            ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER),
        },

        // char sets to preload
        (CharSetDefinition**)LEVEL_1_MAIN_ST_CHARSETS,

        // textures to preload
        (TextureDefinition**)LEVEL_1_MAIN_ST_TEXTURES,

        // UI
        {
            LEVEL_1_MAIN_ST_UI_ENTITIES,
            __TYPE(UI),
        },

        // entities
        LEVEL_1_MAIN_ST_ENTITIES,

        // background music
        (const u16 (*)[])KRISSE_BGM,
    },

    // identifier
    "1-1",

    // name
    (void*)STR_LEVEL_1_NAME,
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
// ---------------------------------------------------------------------------------------------------------

PlatformerStageEntryPointROMDef LEVEL_1_MAIN_MAIN_EP[] =
{{
	// the stage to load
    (PlatformerStageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "House",

    // offset from entry point (x, y, z)
    {FTOFIX19_13(-64), FTOFIX19_13(-256), FTOFIX19_13(-SORT_INCREMENT)},

	// does a level start at this entry point?
	true,
}};

PlatformerStageEntryPointROMDef LEVEL_1_MAIN_SMALL_ROOM_EXIT_DOOR_EP[] =
{{
	// the stage to load
    (PlatformerStageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "SmallRoomExitDoor",

    // offset from entry point (x, y, z)
    {0, 0, FTOFIX19_13(-SORT_INCREMENT)},

	// does a level start at this entry point?
	false,
}};

PlatformerStageEntryPointROMDef LEVEL_1_MAIN_LS_FRONT_EP[] =
{{
	// the stage to load
    (PlatformerStageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "Door Front 1",

    // offset from entry point (x, y, z)
    {0, 0, FTOFIX19_13(-SORT_INCREMENT)},

	// does a level start at this entry point?
	false,
}};

PlatformerStageEntryPointROMDef LEVEL_1_MAIN_LS_BACK_EP[] =
{{
	// the stage to load
    (PlatformerStageDefinition*)&LEVEL_1_MAIN_ST,

	// name of the entity to start at
    "Door Back 1",

    // offset from entry point (x, y, z)
    {0, 0, FTOFIX19_13(-SORT_INCREMENT)},

	// does a level start at this entry point?
	false,
}};