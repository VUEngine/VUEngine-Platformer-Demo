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

extern StageROMDef LEVEL_1_1_COIN_ROOM_ST;


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures and entities.
 */

PositionedEntityROMDef LEVEL1_1_MAIN_2_IM_COLLISIONS[] =
{
	{&COLLISION_ONEWAY_7x1x8, 	{FTOFIX19_13(-226), FTOFIX19_13(-12), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_48x18x8, 	    {FTOFIX19_13(-10),  FTOFIX19_13(57),  FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x8, 	{FTOFIX19_13(-226), FTOFIX19_13(181), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_48x18x8, 	    {FTOFIX19_13(-10),  FTOFIX19_13(249), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x8, 	{FTOFIX19_13(210),  FTOFIX19_13(37),  FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x8, 	{FTOFIX19_13(210),  FTOFIX19_13(134), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x8,		    {FTOFIX19_13(127),  FTOFIX19_13(152), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_18x6x8,		    {FTOFIX19_13(238),  FTOFIX19_13(201), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL1_1_MAIN_3_IM_COLLISIONS[] =
{
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef CASTLE_CHILD_ENTITIES[] =
{
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(-34),  FTOFIX19_13(-26), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(6),    FTOFIX19_13(-13), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(45),   FTOFIX19_13(-26), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_1_ROOM_1_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,	 	{FTOFIX19_13(0),    FTOFIX19_13(144), FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, true},
	{&MOUND_BG_MIDDLE_IM, 	{FTOFIX19_13(0),    FTOFIX19_13(178), FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM, 	{FTOFIX19_13(0),    FTOFIX19_13(216), FTOFIX19_13(LAYER_3 + 0.1f)}, NULL, NULL, NULL, true},
	{&MOUND_BG_CASTLE_IM, 	{FTOFIX19_13(704),  FTOFIX19_13(139), FTOFIX19_13(LAYER_3 - 0.1f)}, NULL, (struct PositionedEntity*)CASTLE_CHILD_ENTITIES, NULL, false},
	{&CLOUDS_SB, 			{FTOFIX19_13(0),    FTOFIX19_13(24), FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&HERO_AC, 				{FTOFIX19_13(56),   FTOFIX19_13(288), FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, false},
	
	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!
	{&COLLISION_2x28x48,        {FTOFIX19_13(-12),  FTOFIX19_13(116), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

	{&LEVEL1_1_MAIN_1_IM, 	    {FTOFIX19_13(256),  FTOFIX19_13(360), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL1_1_TOP_1_IM, 	    {FTOFIX19_13(256),  FTOFIX19_13(256), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL1_1_ROOM_1_HOUSE_IM, {FTOFIX19_13(104),  FTOFIX19_13(192), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_30x33x8,        {FTOFIX19_13(118),  FTOFIX19_13(369), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_34x30x8,        {FTOFIX19_13(366),  FTOFIX19_13(381), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COIN_AG,                  {FTOFIX19_13(216),  FTOFIX19_13(225), FTOFIX19_13(LAYER_0)}, "Coin 001", NULL, NULL, false},
	{&COIN_AG,                  {FTOFIX19_13(232),  FTOFIX19_13(225), FTOFIX19_13(LAYER_0)}, "Coin 002 ", NULL, NULL, false},
	{&LEVEL1_1_BACK_1_IM,       {FTOFIX19_13(360),  FTOFIX19_13(240), FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL, false},
	{&BUSH_AG,                  {FTOFIX19_13(472),  FTOFIX19_13(256), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

	{&LEVEL1_1_MAIN_2_IM, 	    {FTOFIX19_13(768),  FTOFIX19_13(240), FTOFIX19_13(LAYER_0)}, NULL, (struct PositionedEntity*)LEVEL1_1_MAIN_2_IM_COLLISIONS, NULL, false},
	{&LEVEL1_1_TOP_2_IM, 	    {FTOFIX19_13(760),  FTOFIX19_13(328), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL1_1_BACK_2_IM, 	    {FTOFIX19_13(717),  FTOFIX19_13(392), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&DOOR_AG,				    {FTOFIX19_13(818),  FTOFIX19_13(400), FTOFIX19_13(LAYER_0)}, NULL, NULL, (void*)&LEVEL_1_1_COIN_ROOM_ST, true},

	{&LEVEL1_1_MAIN_3_IM, 	    {FTOFIX19_13(1232), FTOFIX19_13(240), FTOFIX19_13(LAYER_0)}, NULL, (struct PositionedEntity*)LEVEL1_1_MAIN_3_IM_COLLISIONS, NULL, false},
	{&LEVEL1_1_TOP_3_IM, 	    {FTOFIX19_13(1200), FTOFIX19_13(360), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL1_1_BACK_3_IM, 	    {FTOFIX19_13(1225), FTOFIX19_13(332), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x8, 	{FTOFIX19_13(1006), FTOFIX19_13(229), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x8, 	{FTOFIX19_13(1006), FTOFIX19_13(325), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_48x18x8, 	    {FTOFIX19_13(1224), FTOFIX19_13(104), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_28x16x8, 	    {FTOFIX19_13(1224), FTOFIX19_13(268), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_48x18x8, 	    {FTOFIX19_13(1224), FTOFIX19_13(297), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x8,		    {FTOFIX19_13(1070), FTOFIX19_13(472), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x8,		    {FTOFIX19_13(1120), FTOFIX19_13(505), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x8,		    {FTOFIX19_13(1280), FTOFIX19_13(505), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x8,		    {FTOFIX19_13(1360), FTOFIX19_13(473), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_LANE_V_6_IM,    {FTOFIX19_13(1199), FTOFIX19_13(472), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_V3_AC,          {FTOFIX19_13(1200), FTOFIX19_13(472), FTOFIX19_13(LAYER_0 - 1)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_1_ROOM_1_ST_UI_ENTITIES[] =
{
	{&GUI_IM,   {FTOFIX19_13(__SCREEN_WIDTH / 2), FTOFIX19_13(__SCREEN_HEIGHT - 8), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

TextureROMDef* LEVEL_1_1_ROOM_1_ST_TEXTURES[] =
{
	&HERO_TX,
	&LEVEL1_1_ROOM_1_HOUSE_TX,
	&COIN_TX,
	&CLOUDS_A_TX,
	&CLOUDS_B_TX,
	&MOUND_BG_BACK_TX,
	&MOUND_BG_MIDDLE_TX,
	&MOUND_BG_FRONT_TX,
	&LEVEL1_1_BACK_1_TX,
	&LEVEL1_1_MAIN_1_TX,
	&LEVEL1_1_MAIN_2_TX,
	&LEVEL1_1_TOP_1_TX,
	&LEVEL1_1_TOP_2_TX,
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
            2048,
            // y
            512,
            // z
            256,
        },

        // gravity
        {
            ITOFIX19_13(0),
            ITOFIX19_13(__GRAVITY / 2),
            ITOFIX19_13(0)
        },

        // friction
        FTOFIX19_13(0.1f),

        // Palette's config
        {
        	// background color
        	__COLOR_BLACK,
        	
        	{
        		0xE4,
        		0xE0,
        		0xD0,
        		0xE0,
        	},
        	{
        		0xE4,
        		0xE0,
        		0xD0,
        		0xE0,
        	} 
        },

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
            ITOFIX19_13(LAYER_0),
            // SPT1
            ITOFIX19_13(LAYER_0),
            // SPT2
            ITOFIX19_13(LAYER_0),
            // SPT3
            ITOFIX19_13(LAYER_0),
        },

        // initial screen position
        {
            // x
            ITOFIX19_13(0),
            // y
            ITOFIX19_13(113),
            // z
            ITOFIX19_13(0)
        },

        // optical configuration values
        {
    		// maximum view distance's power into the horizon
    		__MAXIMUM_VIEW_DISTANCE_POWER,
            // distance of the eyes to the screen
            ITOFIX19_13(__DISTANCE_EYE_SCREEN),
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
    },

    // identifier
    "1-1",

    // name
    (void*)STR_LEVEL_1_1_NAME,
};