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
//                                                 INCLUDES
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
//                                                 PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern StageROMDef LEVEL_1_MAIN_1_MAIN_1_ST;


//---------------------------------------------------------------------------------------------------------
//                                                 ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures and entities.
 */

PositionedEntityROMDef LEVEL_1_SMALL_ROOM_ST_ENTITIES[] =
{
    // since these are always visible it doesn't matter that they are not logically placed in this definition

    {&LEVEL_1_SMALL_ROOM_FRONT_IM,          {FTOFIX19_13(192),  FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
    {&LEVEL_1_SMALL_ROOM_PLATFORMS_IM,      {FTOFIX19_13(188),  FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
    {&COLLISION_48x2x48,                    {FTOFIX19_13(192),  FTOFIX19_13(168), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
    {&COLLISION_48x2x48,                    {FTOFIX19_13(192),  FTOFIX19_13(48),  FTOFIX19_13(0)}, NULL, NULL, NULL, true},
    {&COLLISION_48x2x48,                    {FTOFIX19_13(-56),  FTOFIX19_13(120), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
    {&COLLISION_18x6x8,                     {FTOFIX19_13(240),  FTOFIX19_13(136), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
    {&COLLISION_ONEWAY_7x1x8,               {FTOFIX19_13(156),  FTOFIX19_13(116), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
    {&COLLISION_2x28x48,                    {FTOFIX19_13(96),   FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
    {&COLLISION_2x28x48,                    {FTOFIX19_13(280),  FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},

    {&HERO_AC,                              {FTOFIX19_13(122),  FTOFIX19_13(96),  FTOFIX19_13(0)}, HERO_NAME, NULL, NULL, true},

    {&DOOR_AG,                              {FTOFIX19_13(122),  FTOFIX19_13(96),  FTOFIX19_13(1)}, NULL, NULL, NULL, true},
    {&DOOR_AG,                              {FTOFIX19_13(122),  FTOFIX19_13(145), FTOFIX19_13(1)}, NULL, NULL, NULL, true},

    {&COIN_AG,                              {FTOFIX19_13(208),  FTOFIX19_13(96),  FTOFIX19_13(LAYER_0 + 2)}, "Coin 099", NULL, NULL, true},
    {&COIN_AG,                              {FTOFIX19_13(224),  FTOFIX19_13(96),  FTOFIX19_13(LAYER_0 + 2)}, "Coin 100", NULL, NULL, true},

    {&EXIT_ROOM_DOOR_AG,                    {FTOFIX19_13(257),  FTOFIX19_13(96),  FTOFIX19_13(1)}, NULL, NULL, (void*)&LEVEL_1_MAIN_1_MAIN_1_ST, true},

    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_SMALL_ROOM_ST_UI_ENTITIES[] =
{
    {&GUI_IM,                 {FTOFIX19_13(__SCREEN_WIDTH / 2), FTOFIX19_13(__SCREEN_HEIGHT - 8), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};

TextureROMDef* LEVEL_1_SMALL_ROOM_ST_TEXTURES[] =
{
    &LEVEL_1_SMALL_ROOM_FRONT_TX,
    &LEVEL_1_SMALL_ROOM_PLATFORMS_TX,
    &DOOR_TX,
    &COIN_TX,
    NULL
};


//---------------------------------------------------------------------------------------------------------
//                                             STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerStageROMDef LEVEL_1_SMALL_ROOM_ST =
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
        (TextureDefinition**)LEVEL_1_SMALL_ROOM_ST_TEXTURES,

        // UI
        {
            LEVEL_1_SMALL_ROOM_ST_UI_ENTITIES,
            __TYPE(UI),
        },

        // entities
        LEVEL_1_SMALL_ROOM_ST_ENTITIES,

        // background music
        (const u16 (*)[])KRISSE_BGM,
    },

    // identifier
    "1-1",

    // name
    NULL,
};