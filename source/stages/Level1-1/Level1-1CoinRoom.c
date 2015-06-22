/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
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

extern StageROMDef LEVEL_1_1_ROOM_1_ST;


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures and entities.
 */

PositionedEntityROMDef LEVEL_1_1_COIN_ROOM_COLLISIONS[] =
{
    {&COLLISION_48x2x48,                	{FTOFIX19_13(192), FTOFIX19_13(200), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COLLISION_48x2x48,                	{FTOFIX19_13(192), FTOFIX19_13(2), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COLLISION_2x28x48,                	{FTOFIX19_13(10), FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COLLISION_2x28x48,                	{FTOFIX19_13(__SCREEN_WIDTH - 10), FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COLLISION_12x12x2,                	{FTOFIX19_13(-16), FTOFIX19_13(8), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COLLISION_12x12x2,                	{FTOFIX19_13(__SCREEN_WIDTH + 16), FTOFIX19_13(8), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COLLISION_12x12x2,                	{FTOFIX19_13(40), FTOFIX19_13(208), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COLLISION_12x12x2,                	{FTOFIX19_13(__SCREEN_WIDTH - 40), FTOFIX19_13(208), FTOFIX19_13(0)}, NULL, NULL, NULL, true},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_1_COIN_ROOM_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition

	{&LEVEL1_1_COIN_ROOM_FRONT_IM,	        {FTOFIX19_13(192), FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&LEVEL1_1_COIN_ROOM_FRONT_PLATFORMS_IM,{FTOFIX19_13(193), FTOFIX19_13(105), FTOFIX19_13(-2)}, NULL, NULL, NULL, true},
	{&LEVEL1_1_COIN_ROOM_FRONT_SHADOWS_IM,	{FTOFIX19_13(193), FTOFIX19_13(180), FTOFIX19_13(-1)}, NULL, NULL, NULL, true},
	{&LEVEL1_1_COIN_ROOM_MIDDLE_IM,	        {FTOFIX19_13(32), FTOFIX19_13(112), FTOFIX19_13(2)}, NULL, NULL, NULL, true},
	{&LEVEL1_1_COIN_ROOM_MIDDLE_IM,	        {FTOFIX19_13(__SCREEN_WIDTH - 32), FTOFIX19_13(112), FTOFIX19_13(2)}, NULL, NULL, NULL, true},

	{&HERO_AC, 				                {FTOFIX19_13(44), FTOFIX19_13(144), FTOFIX19_13(0)}, HERO_NAME, NULL, NULL, true},

	{&EXIT_ROOM_DOOR_AG,	                {FTOFIX19_13(44), FTOFIX19_13(144), FTOFIX19_13(1)}, NULL, NULL, NULL, true},
	{&EXIT_ROOM_DOOR_AG,	                {FTOFIX19_13(__SCREEN_WIDTH - 44), FTOFIX19_13(144), FTOFIX19_13(1)}, NULL, NULL, (void*)&LEVEL_1_1_ROOM_1_ST, true},

	{&TORCH_AG,	                            {FTOFIX19_13(44), FTOFIX19_13(104), FTOFIX19_13(1)}, NULL, NULL, (void*)&LEVEL_1_1_ROOM_1_ST, true},
	{&TORCH_AG,	                            {FTOFIX19_13(__SCREEN_WIDTH - 44), FTOFIX19_13(104), FTOFIX19_13(1)}, NULL, NULL, (void*)&LEVEL_1_1_ROOM_1_ST, true},

    {(ManagedEntityDefinition*)&MANAGED_ENTITY,	{FTOFIX19_13(0), FTOFIX19_13(0), FTOFIX19_13(0)}, NULL, (struct PositionedEntity*)LEVEL_1_1_COIN_ROOM_COLLISIONS, NULL, true},
	{&OBJECT_COIN_AG, 	        			{FTOFIX19_13(144 + 0), FTOFIX19_13(104 + 0), FTOFIX19_13(LAYER_0 + 2)}, "Coin 050", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 0), FTOFIX19_13(104 + 16), FTOFIX19_13(LAYER_0 + 2)}, "Coin 051", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 0), FTOFIX19_13(104 + 32), FTOFIX19_13(LAYER_0 + 2)}, "Coin 052", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 0), FTOFIX19_13(104 + 48), FTOFIX19_13(LAYER_0 + 2)}, "Coin 053", NULL, NULL, true},
	{&OBJECT_COIN_AG, 	        			{FTOFIX19_13(144 + 32), FTOFIX19_13(104 + 0), FTOFIX19_13(LAYER_0 + 2)}, "Coin 054", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 32), FTOFIX19_13(104 + 16), FTOFIX19_13(LAYER_0 + 2)}, "Coin 055", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 32), FTOFIX19_13(104 + 32), FTOFIX19_13(LAYER_0 + 2)}, "Coin 056", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 32), FTOFIX19_13(104 + 48), FTOFIX19_13(LAYER_0 + 2)}, "Coin 057", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 16), FTOFIX19_13(104 + 64), FTOFIX19_13(LAYER_0 + 2)}, "Coin 058", NULL, NULL, true},

	{&OBJECT_COIN_AG, 	        			{FTOFIX19_13(144 + 64), FTOFIX19_13(104 + 0), FTOFIX19_13(LAYER_0 + 2)}, "Coin 059", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 64), FTOFIX19_13(104 + 16), FTOFIX19_13(LAYER_0 + 2)}, "Coin 060", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 64), FTOFIX19_13(104 + 32), FTOFIX19_13(LAYER_0 + 2)}, "Coin 061", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 64), FTOFIX19_13(104 + 48), FTOFIX19_13(LAYER_0 + 2)}, "Coin 062", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 64), FTOFIX19_13(104 + 64), FTOFIX19_13(LAYER_0 + 2)}, "Coin 063", NULL, NULL, true},
	{&OBJECT_COIN_AG, 	        			{FTOFIX19_13(144 + 80), FTOFIX19_13(104 + 0), FTOFIX19_13(LAYER_0 + 2)}, "Coin 064", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 80), FTOFIX19_13(104 + 32), FTOFIX19_13(LAYER_0 + 2)}, "Coin 065", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 80), FTOFIX19_13(104 + 64), FTOFIX19_13(LAYER_0 + 2)}, "Coin 066", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 96), FTOFIX19_13(104 + 16), FTOFIX19_13(LAYER_0 + 2)}, "Coin 067", NULL, NULL, true},
	{&OBJECT_COIN_AG, 		        		{FTOFIX19_13(144 + 96), FTOFIX19_13(104 + 48), FTOFIX19_13(LAYER_0 + 2)}, "Coin 068", NULL, NULL, true},

	{&SAW_BLADE_HORIZONTAL_AC,              {FTOFIX19_13(216), FTOFIX19_13(193), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_1_COIN_ROOM_ST_UI_ENTITIES[] =
{
	{&GUI_IM, 				{FTOFIX19_13(__SCREEN_WIDTH / 2), FTOFIX19_13(__SCREEN_HEIGHT - 8), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

TextureROMDef* LEVEL_1_1_COIN_ROOM_ST_TEXTURES[] =
{
    &DOOR_TX,
    &LEVEL1_1_COIN_ROOM_FRONT_TX,
    &LEVEL1_1_COIN_ROOM_FRONT_SHADOWS_TX,
    &LEVEL1_1_COIN_ROOM_FRONT_PLATFORMS_TX,
    &LEVEL1_1_COIN_ROOM_MIDDLE_TX,
    &SAW_BLADE_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerStageROMDef LEVEL_1_1_COIN_ROOM_ST =
{
    {
        // size
        {
            // x
            __SCREEN_WIDTH,
            // y
            __SCREEN_HEIGHT,
            // z
            128
        },

        // gravity
        {
            ITOFIX19_13(0),
            ITOFIX19_13(__GRAVITY >> 1),
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
            ITOFIX19_13(0),
            // SPT1
            ITOFIX19_13(0),
            // SPT2
            ITOFIX19_13(0),
            // SPT3
            ITOFIX19_13(0),
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
            // distance of the eyes to the screen
            ITOFIX19_13(__DISTANCE_EYE_SCREEN),
            // maximum view distance into the horizont
            ITOFIX19_13(__MAXIMUM_VIEW_DISTANCE),
            // distance from left to right eye (depth sensation)
            ITOFIX19_13(__BASE_FACTOR),
            // horizontal View point center
            ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
            // vertical View point center
            ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER + __VERTICAL_VIEW_POINT_CENTER/2),
        },

        // textures to preload
        (TextureDefinition**)LEVEL_1_1_COIN_ROOM_ST_TEXTURES,

        // UI
        {
            LEVEL_1_1_COIN_ROOM_ST_UI_ENTITIES,
            __TYPE(UI),
        },

        // entities
        LEVEL_1_1_COIN_ROOM_ST_ENTITIES,

        // background music
        (const u16 (*)[])KRISSE_BGM,
    },

    // identifier
    "1-1",

    // name
    NULL,
};