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
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LAYER_0_FLOOR	196
#define LAYER_1_FLOOR	196 - 16
#define LAYER_2_FLOOR	196 - 32
#define LAYER_3_FLOOR	196 - 64

#define LEVEL_X_SIZE 	384
#define LEVEL_Y_SIZE 	5000
#define LEVEL_Z_SIZE 	64

#define SCREEN_X_POSITION 	0
#define SCREEN_Y_POSITION 	LEVEL_Y_SIZE - __SCREEN_HEIGHT
#define SCREEN_Z_POSITION 	0


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures and entities.
 */

PositionedEntityROMDef LAVA_CHILD_ENTITIES2[] =
{
	{&LAVA_TOP_AG, {FTOFIX19_13(0), FTOFIX19_13(-114), FTOFIX19_13(-1)}, NULL, NULL, NULL, false},
    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LAVA_CHILD_ENTITIES[] =
{
	{&LAVA_IG,		{FTOFIX19_13(0), FTOFIX19_13(224 - 32), FTOFIX19_13(-2)}, "Lava", (struct PositionedEntity*)LAVA_CHILD_ENTITIES2, NULL, false},
    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_3_PART_1_CHILD_ENTITIES[] =
{
	{&COLLISION_2x28x48,	{FTOFIX19_13(-182), FTOFIX19_13(64), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // outer left wall
	{&COLLISION_48x28x2,	{FTOFIX19_13(304), FTOFIX19_13(254), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // bottom right floor
	{&COLLISION_2x28x48,	{FTOFIX19_13(192), FTOFIX19_13(64), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // outer right wall
	{&COLLISION_48x28x2,	{FTOFIX19_13(-120), FTOFIX19_13(286), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // bottom left floor
	{&COLLISION_3x2x2,		{FTOFIX19_13(96), FTOFIX19_13(74), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // floating stone bottom right
	{&COLLISION_3x2x2,		{FTOFIX19_13(180), FTOFIX19_13(100), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // step stone bottom right
	{&COLLISION_48x3x2,		{FTOFIX19_13(-168), FTOFIX19_13(54), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // 2nd level floor left
	{&DOOR_AG,	            {FTOFIX19_13(-144), FTOFIX19_13(154), FTOFIX19_13(1)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_3_ROOM_1_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&HERO_AC, 				{FTOFIX19_13(72), FTOFIX19_13(LEVEL_Y_SIZE - __SCREEN_HEIGHT + 104), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&PLATE_BG_IM,	        {FTOFIX19_13(256), FTOFIX19_13(LEVEL_Y_SIZE - __SCREEN_HEIGHT + 112), FTOFIX19_13(55)}, NULL, NULL, NULL, true},
	{(ManagedEntityDefinition*)&MANAGED_ENTITY,		{FTOFIX19_13(192), FTOFIX19_13(LEVEL_Y_SIZE - __SCREEN_HEIGHT / 2), FTOFIX19_13(LAYER_0)}, NULL, (struct PositionedEntity*)LAVA_CHILD_ENTITIES, NULL, true},
	
	{&COIN_AG, 				{FTOFIX19_13(132), FTOFIX19_13(-48 + SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},
	{&COIN_AG, 				{FTOFIX19_13(148), FTOFIX19_13(-48 + SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},
	{&COIN_AG, 				{FTOFIX19_13(132), FTOFIX19_13(-64 + SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},
	{&COIN_AG, 				{FTOFIX19_13(148), FTOFIX19_13(-64 + SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},

	{&COIN_AG, 				{FTOFIX19_13(132 + 32), FTOFIX19_13(-48 + SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},
	{&COIN_AG, 				{FTOFIX19_13(148 + 32), FTOFIX19_13(-48 + SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},
	{&COIN_AG, 				{FTOFIX19_13(132 + 32), FTOFIX19_13(-64 + SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},
	{&COIN_AG, 				{FTOFIX19_13(148 + 32), FTOFIX19_13(-64 + SCREEN_Y_POSITION + LAYER_0_FLOOR - 40), FTOFIX19_13(LAYER_0 + 1)}, NULL, NULL, NULL, true},

	// the following entities must be placed in logical (spatial) order,
	// according to the level's disposition, for the streaming to work properly
	// beware of edge case scenarios!
	{&LEVEL1_3_PART1_IM,    {FTOFIX19_13(192), FTOFIX19_13(LEVEL_Y_SIZE - __SCREEN_HEIGHT -48), FTOFIX19_13(LAYER_0 + 2)}, NULL, (struct PositionedEntity*)LEVEL_1_3_PART_1_CHILD_ENTITIES, NULL, true},
	{&LAVA_TRIGGER_IG,  	{FTOFIX19_13(174), FTOFIX19_13(LEVEL_Y_SIZE - __SCREEN_HEIGHT + 80), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&COG_WHEEL_IG,	        {FTOFIX19_13(384), FTOFIX19_13(LEVEL_Y_SIZE - __SCREEN_HEIGHT), FTOFIX19_13(50)}, NULL, NULL, NULL, true},
	//{&LEVEL1_3_PART2_IM,    {192), FTOFIX19_13(LEVEL_Y_SIZE - __SCREEN_HEIGHT -48 - 512, LAYER_0 + 2}, NULL, LEVEL_1_3_PART_1_CHILD_ENTITIES, NULL},
	//{&LEVEL1_3_PART3_IM,    {192 + 48*8), FTOFIX19_13(LEVEL_Y_SIZE - __SCREEN_HEIGHT -48 - 512, LAYER_0 + 2}, NULL, LEVEL_1_3_PART_1_CHILD_ENTITIES, NULL},
	//{&COIN_MC,    {312, 4856, LAYER_0 + 2}, NULL, LEVEL_1_3_PART_1_CHILD_ENTITIES, NULL},
	//{&COIN_MC,    {328, 4856, LAYER_0 + 2}, NULL, LEVEL_1_3_PART_1_CHILD_ENTITIES, NULL},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_3_ROOM_1_ST_UI_ENTITIES[] =
{
	{&GUI_IM, {FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(__SCREEN_HEIGHT - 8), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

TextureROMDef* LEVEL_1_3_ROOM_1_ST_TEXTURES[] =
{
	//&COIN_TX,
	&DOOR_TX,
	&GUI_TX,
	&LAVA_TX,
	&LAVA_TOP_TX,
	&LEVEL1_3_PART1_TX,
	//&LEVEL1_3_PART2_TX,
	&COG_WHEEL_TX,
	&PLATE_BG_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerStageROMDef LEVEL_1_3_ROOM_1_ST =
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
            ITOFIX19_13(20),
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
    		// maximum view distance's power into the horizon
    		__MAXIMUM_VIEW_DISTANCE_POWER,
            // distance of the eyes to the screen
            ITOFIX19_13(__DISTANCE_EYE_SCREEN),
            // distance from left to right eye (depth sensation)
            ITOFIX19_13(__BASE_FACTOR),
            // horizontal View point center
            ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
            // vertical View point center
            ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER + __VERTICAL_VIEW_POINT_CENTER/2),
        },

        // textures to preload
        (TextureDefinition**)LEVEL_1_3_ROOM_1_ST_TEXTURES,

        // UI
        {
            LEVEL_1_3_ROOM_1_ST_UI_ENTITIES,
            __TYPE(UI),
        },

        // entities
        LEVEL_1_3_ROOM_1_ST_ENTITIES,

        // background music
        NULL,
    },

    // identifier
    "1-3",

    // name
    (void*)STR_LEVEL_1_3_NAME,
};