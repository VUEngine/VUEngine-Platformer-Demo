/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
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

extern StageROMDef LEVEL_1_1_COIN_ROOM_ST;


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LAYER_0_FLOOR	196
#define LAYER_1_FLOOR	196 - 16
#define LAYER_2_FLOOR	196 - 32
#define LAYER_3_FLOOR	196 - 64

#define LEVEL_X_SIZE 	3000
#define LEVEL_Y_SIZE 	1000
#define LEVEL_Z_SIZE 	300

#define SCREEN_X_POSITION 	0
#define SCREEN_Y_POSITION 	LEVEL_Y_SIZE - __SCREEN_HEIGHT
#define SCREEN_Z_POSITION 	LAYER_0


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures and entities.
 */

PositionedEntityROMDef MANAGED_FLOOR_1_ENTITIES[] =
{
	{&FLOOR_16x8_IG,		{FTOFIX19_13(-32), FTOFIX19_13(9), FTOFIX19_13(0.01f)}, NULL, NULL, NULL, false},
	{&FLOOR_4x10_IG,		{FTOFIX19_13(48), FTOFIX19_13(0), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef CASTLE_CHILD_ENTITIES[] =
{
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(-34), FTOFIX19_13(-26), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(6), FTOFIX19_13(-13), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(45), FTOFIX19_13(-26), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_1_ROOM_1_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,	 	{FTOFIX19_13(SCREEN_X_POSITION), FTOFIX19_13(SCREEN_Y_POSITION + 88), FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, true},
	{&MOUND_BG_MIDDLE_IM, 	{FTOFIX19_13(SCREEN_X_POSITION), FTOFIX19_13(SCREEN_Y_POSITION + 120), FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM, 	{FTOFIX19_13(SCREEN_X_POSITION), FTOFIX19_13(SCREEN_Y_POSITION + 152), FTOFIX19_13(LAYER_3 + 0.1f)}, NULL, NULL, NULL, true},
	{&MOUND_BG_CASTLE_IM, 	{FTOFIX19_13(SCREEN_X_POSITION + 396), FTOFIX19_13(851), FTOFIX19_13(LAYER_3 - 0.1f)}, NULL, (struct PositionedEntity*)CASTLE_CHILD_ENTITIES, NULL, false},
	{&CLOUDS_SB, 			{FTOFIX19_13(SCREEN_X_POSITION), FTOFIX19_13(SCREEN_Y_POSITION - 64), FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&HERO_AC, 				{FTOFIX19_13(SCREEN_X_POSITION + 32), FTOFIX19_13(SCREEN_Y_POSITION + 110), FTOFIX19_13(LAYER_0 - 2)}, HERO_NAME, NULL, NULL, false},
	
	// the following entities must be placed in logical (spatial) order,
	// according to the level's disposition, for the streaming to work properly
	// beware of edge case scenarios!
	{&COLLISION_2x28x48, 	{FTOFIX19_13(-12), FTOFIX19_13(SCREEN_Y_POSITION + 116), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{(ManagedEntityDefinition*)&MANAGED_ENTITY,		{FTOFIX19_13(96), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR + 8), FTOFIX19_13(LAYER_0 + 2 + 0.01f)}, NULL, (struct PositionedEntity*)MANAGED_FLOOR_1_ENTITIES, NULL, false},
	{&MOUND_1_IM,			{FTOFIX19_13(84), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 16), FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(132), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, "Coin 001", NULL, NULL, false},
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(148), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, "Coin 002", NULL, NULL, false},
	{&ONE_WAY_PLATFORM_4_IG,{FTOFIX19_13(140), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 80), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&SAW_BLADE_LANE_V_6_IM,{FTOFIX19_13(198), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 36), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_VERTICAL_AC,{FTOFIX19_13(198), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 36), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&FLOOR_4x3_FLOAT_IG,	{FTOFIX19_13(236), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&ENTER_ROOM_DOOR_AG,	{FTOFIX19_13(238), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 70), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, (void*)&LEVEL_1_1_COIN_ROOM_ST, false},
	{&FLOOR_22x8_IG,		{FTOFIX19_13(384), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR + 8), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&MOUND_2_IM,			{FTOFIX19_13(392), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 16), FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL, false},

	{&CANNON_AC,		    {FTOFIX19_13(344), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 64), FTOFIX19_13(LAYER_2 + 2)}, NULL, NULL, NULL, false},

//	{&FLOOR_4x10_IG,		{FTOFIX19_13(10), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 16), FTOFIX19_13(LAYER_2 + 2 - 0.01f)}, NULL, NULL, NULL, false},
//	{&FLOOR_22x8_IG,		{FTOFIX19_13(382), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 28), FTOFIX19_13(LAYER_2 + 2)}, NULL, NULL, NULL, false},
//	{&DOOR_AG,				{FTOFIX19_13(314), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 78), FTOFIX19_13(LAYER_2 + 1)}, NULL, NULL, NULL, false},
//	{&FLOOR_4x3_FLOAT_IG,	{FTOFIX19_13(520), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 56), FTOFIX19_13(LAYER_2 + 2)}, NULL, NULL, NULL, false},

	{&FLOOR_2x2_BLOCK_IG,	{FTOFIX19_13(512), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 60), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG,		{FTOFIX19_13(508), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 72), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},

	
	{&FLOOR_2x2_BLOCK_IG,	{FTOFIX19_13(576), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 98), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG,		{FTOFIX19_13(572), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 110), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(626), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 28), FTOFIX19_13(LAYER_2 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_4x3_FLOAT_IG,	{FTOFIX19_13(648), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 130), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&KEY_AG,	            {FTOFIX19_13(648), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 152), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},

	{&FLOOR_16x8_IG,		{FTOFIX19_13(770), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 126), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(880), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 90), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(1000), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 50), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},

	{&FLOOR_16x8_IG,		{FTOFIX19_13(1072), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&MOUND_1_IM,			{FTOFIX19_13(1096), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 32), FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL, false},
	{&FLOOR_4x10_IG,		{FTOFIX19_13(1155), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 8), FTOFIX19_13(LAYER_0 + 2 - 0.01f)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(1146), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 56), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(1162), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 56), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_LANE_V_6_IM,{FTOFIX19_13(1198), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 62), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_VERTICAL_AC,{FTOFIX19_13(1198), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&FLOOR_4x3_FLOAT_IG,	{FTOFIX19_13(1236), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 56), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&ENTER_ROOM_DOOR_AG,	{FTOFIX19_13(1238), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 86), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, (void*)&LEVEL_1_1_COIN_ROOM_ST, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(1368), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 8), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&MOUND_2_IM,			{FTOFIX19_13(1376), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 32), FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL, false},
	{&FLOOR_2x2_BLOCK_IG,	{FTOFIX19_13(1496), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 76), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG,		{FTOFIX19_13(1492), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 88), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&FLOOR_2x2_BLOCK_IG,	{FTOFIX19_13(1560), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 114), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG,		{FTOFIX19_13(1556), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 126), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&FLOOR_4x3_FLOAT_IG,	{FTOFIX19_13(1632), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 146), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_4x10_IG,		{FTOFIX19_13(1698), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 146), FTOFIX19_13(LAYER_0 + 1 + 0.5f)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(1800), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 126), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(1900), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 90), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(2000), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 50), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},

	{&FLOOR_16x8_IG,		{FTOFIX19_13(2072), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&MOUND_1_IM,			{FTOFIX19_13(2096), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 32), FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL, false},
	{&FLOOR_4x10_IG,		{FTOFIX19_13(2155), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 8), FTOFIX19_13(LAYER_0 + 2 - 0.01f)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(2146), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 56), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(2162), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 56), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_LANE_V_6_IM,{FTOFIX19_13(2198), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 62), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_VERTICAL_AC,{FTOFIX19_13(2198), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&FLOOR_4x3_FLOAT_IG,	{FTOFIX19_13(2236), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 56), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&DOOR_AG,				{FTOFIX19_13(2238), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 86), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(2368), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 8), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&MOUND_2_IM,			{FTOFIX19_13(2376), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 32), FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL, false},
	{&FLOOR_2x2_BLOCK_IG,	{FTOFIX19_13(2496), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 76), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG,		{FTOFIX19_13(2492), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 88), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&FLOOR_2x2_BLOCK_IG,	{FTOFIX19_13(2560), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 114), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&OBJECT_COIN_AG,		{FTOFIX19_13(2556), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 126), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, false},
	{&FLOOR_4x3_FLOAT_IG,	{FTOFIX19_13(2632), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 146), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_4x10_IG,		{FTOFIX19_13(2698), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 146), FTOFIX19_13(LAYER_0 + 1 + 0.5f)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(2800), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 126), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(2900), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 90), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},
	{&FLOOR_16x8_IG,		{FTOFIX19_13(3000), FTOFIX19_13(SCREEN_Y_POSITION + LAYER_0_FLOOR - 50), FTOFIX19_13(LAYER_0 + 2)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_1_ROOM_1_ST_UI_ENTITIES[] =
{
	{&GUI_IM, 				{FTOFIX19_13(__SCREEN_WIDTH / 2), FTOFIX19_13(__SCREEN_HEIGHT - 8), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

TextureROMDef* LEVEL_1_1_ROOM_1_ST_TEXTURES[] =
{
//	&OBJECT_COIN_TX,
//	&DUST_PARTICLE_SMALL_TX,
	&CLOUDS_A_TX,
	&CANNON_TX,
	&CANNON_BALL_TX,
	&CLOUDS_B_TX,
	&MOUND_BG_BACK_TX,
	&MOUND_BG_MIDDLE_TX,
	&MOUND_BG_FRONT_TX,
	&MOUND_BG_CASTLE_TX,
	&MOUND_BG_CASTLE_FLAG_TX,
	&BGMAP_COIN_TX,
	&SAW_BLADE_TX,
	&SAW_BLADE_LANE_V_6_TX,
	&GUI_TX,
	&FLOOR_4x10_L_TX,
	&FLOOR_4x10_R_TX,
	&FLOOR_16x8_L_TX,
	&FLOOR_16x8_R_TX,
	&FLOOR_2x2_BLOCK_L_TX,
	&FLOOR_4x3_FLOAT_L_TX,
	&FLOOR_4x3_FLOAT_R_TX,
	&DOOR_TX,
	&MOUND_1_TX,
	&MOUND_2_TX,
	&KEY_TX,
	&HINT_ENTER_TX,
	&ONE_WAY_PLATFORM_4_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerStageROMDef LEVEL_1_1_ROOM_1_ST =
{
    {
        // size
        {
            // x
            LEVEL_X_SIZE,
            // y
            LEVEL_Y_SIZE,
            // z
            LEVEL_Z_SIZE
        },

        // gravity
        {
            ITOFIX19_13(0),
            ITOFIX19_13(__GRAVITY / 2),
            ITOFIX19_13(0)
        },

        // friction
        FTOFIX19_13(0.1f),

        // OBJs segments z coordinates
        // Note that each SPT's z coordinate much be larger than or equal to the previous one's,
        // since the VIP renders OBJ Worlds in reverse order (SPT3 to SPT0)
        {
            // SPT0
            ITOFIX19_13(LAYER_0),
            // SPT1
            ITOFIX19_13(LAYER_0),
            // SPT2
            ITOFIX19_13(LAYER_1),
            // SPT3
            ITOFIX19_13(LAYER_3),
        },

        // initial screen position
        {
            // x
            ITOFIX19_13(SCREEN_X_POSITION),
            // y
            ITOFIX19_13(SCREEN_Y_POSITION),
            // z
            ITOFIX19_13(SCREEN_Z_POSITION)
        },

        // optical configuration values
        {
            // distance of the eyes to the screen
            ITOFIX19_13(__DISTANCE_EYE_SCREEN),
            // maximum view distance into the horizont
            ITOFIX19_13(__MAXIMUM_VIEW_DISTANCE),
            // distance from left to right eye (depth sensation)
            ITOFIX19_13(__BASE_FACTOR),
            // horizontal View point center
            ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
            // vertical View point center
            ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER),
        },

        // textures to preload
        (TextureDefinition**)LEVEL_1_1_ROOM_1_ST_TEXTURES,

        // UI
        {
            LEVEL_1_1_ROOM_1_ST_UI_ENTITIES,
            __TYPE(UI),
        },

        // entities
        LEVEL_1_1_ROOM_1_ST_ENTITIES,

        // background music
        (const u16 (*)[])KRISSE_BGM,

        // background color
        __COLOR_BLACK,
    },

    // identifier
    "1-1",

    // name
    (void*)STR_LEVEL_1_1_NAME,
};