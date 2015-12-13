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
#include <TitleScreenState.h>
#include <VPUManager.h>

#include <objects.h>
#include <screens.h>
#include <sound.h>


//---------------------------------------------------------------------------------------------------------
// 											    PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern StageROMDef LEVEL_1_MAIN_1_MAIN_1_ST;


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LEVEL_X_SIZE 	    __SCREEN_WIDTH
#define LEVEL_Y_SIZE 	    __SCREEN_HEIGHT
#define LEVEL_Z_SIZE 	    __SCREEN_WIDTH

#define SCREEN_X_POSITION 	0
#define SCREEN_Y_POSITION 	(LEVEL_Y_SIZE - __SCREEN_HEIGHT)
#define SCREEN_Z_POSITION 	0


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures and entities.
 */

extern AnimatedInGameEntityROMDef HERO_DUMMY_AC;

PositionedEntityROMDef CASTLE_CHILD_ENTITIES[] =
{
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(-34),  FTOFIX19_13(-26), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(6),    FTOFIX19_13(-13), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(45),   FTOFIX19_13(-26), FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TITLE_SCREEN_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
    {&MOUND_BG_BACK_IM,	 	{FTOFIX19_13(-32),  FTOFIX19_13(88), FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, true},
	{&MOUND_BG_MIDDLE_IM, 	{FTOFIX19_13(-32),  FTOFIX19_13(120), FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM, 	{FTOFIX19_13(-32),  FTOFIX19_13(154), FTOFIX19_13(LAYER_3 + 1)}, NULL, NULL, NULL, true},

	{&MOUND_BG_CASTLE_IM, 	{FTOFIX19_13(360),  FTOFIX19_13(77), FTOFIX19_13(LAYER_3 - 0.1f)}, NULL, (struct PositionedEntity*)CASTLE_CHILD_ENTITIES, NULL, false},

	{&FLOOR_16x12_IG,		{FTOFIX19_13(-16),  FTOFIX19_13(208), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&FLOOR_4x12_IG,		{FTOFIX19_13(64),   FTOFIX19_13(192), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&FLOOR_22x5_IG,		{FTOFIX19_13(192),  FTOFIX19_13(188), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&FLOOR_16x12_IG,		{FTOFIX19_13(360),  FTOFIX19_13(200), FTOFIX19_13(0)}, NULL, NULL, NULL, true},

	{&COLLISION_2x28x1, 	{FTOFIX19_13(92),   FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COLLISION_2x28x1, 	{FTOFIX19_13(292),  FTOFIX19_13(112), FTOFIX19_13(0)}, NULL, NULL, NULL, true},

	{&HERO_AC, 				{FTOFIX19_13(144),  FTOFIX19_13(148), FTOFIX19_13(0)}, HERO_NAME, NULL, NULL, true},
	{&DOOR_AG,				{FTOFIX19_13(192),  FTOFIX19_13(152), FTOFIX19_13(1)}, NULL, NULL, (void*)&LEVEL_1_MAIN_1_MAIN_1_ST, true},

	{&GRASS_AG,      	    {FTOFIX19_13(34),   FTOFIX19_13(153), FTOFIX19_13(1)}, NULL, NULL, NULL, true},
	{&BUSH_AG,      	    {FTOFIX19_13(366),  FTOFIX19_13(148), FTOFIX19_13(1)}, NULL, NULL, NULL, true},
	{&FENCE_IM,      	    {FTOFIX19_13(322),  FTOFIX19_13(145), FTOFIX19_13(-1)}, NULL, NULL, NULL, true},
	{&FENCE_IM,      	    {FTOFIX19_13(339),  FTOFIX19_13(145), FTOFIX19_13(-1)}, NULL, NULL, NULL, true},

	{&COIN_AG, 		        {FTOFIX19_13(57),   FTOFIX19_13(138), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&COIN_AG, 		        {FTOFIX19_13(71),   FTOFIX19_13(138), FTOFIX19_13(0)}, NULL, NULL, NULL, true},

	{&VBJAENGINE_IM,        {FTOFIX19_13(192),  FTOFIX19_13(10), FTOFIX19_13(LAYER_0 + 32)}, NULL, NULL, NULL, true},
	{&LOGO_IM, 			    {FTOFIX19_13(192),  FTOFIX19_13(64), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},

	// samples of ignored entities
	{&COIN_AG, 		        {FTOFIX19_13(57), FTOFIX19_13(108), FTOFIX19_13(0)}, "IgnoreMeCoin", NULL, NULL, true},
	{&DOOR_AG,				{FTOFIX19_13((__SCREEN_WIDTH >> 1)), FTOFIX19_13(152), FTOFIX19_13(0)}, "IgnoreMeDoor", NULL, NULL, true},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TITLE_SCREEN_ST_UI_ENTITIES[] =
{
	{&GUI_BLANK_IM,			{FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(__SCREEN_HEIGHT - 8), FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

TextureROMDef* TITLE_SCREEN_ST_TEXTURES[] =
{
	&COIN_TX,
	&DUST_PARTICLE_SMALL_TX,
	&DUST_PARTICLE_LARGE_TX,
	&CLOUDS_A_TX,
	&CLOUDS_B_TX,
	&MOUND_BG_BACK_TX,
	&MOUND_BG_MIDDLE_TX,
	&MOUND_BG_FRONT_TX,
	&MOUND_BG_CASTLE_TX,
	&BUSH_TX,
	&GRASS_TX,
	&FENCE_TX,
	&VBJAENGINE_TX,
	&LOGO_L_TX,
	&LOGO_R_TX,
	&LOGO_OUTLINE_L_TX,
	&LOGO_OUTLINE_R_TX,
	&GUI_BLANK_TX,
	&DOOR_TX,
	&COIN_TX,
	&FLOOR_22x12_TX,
	&FLOOR_22_TOP_TX,
	&FLOOR_16x12_TX,
	&FLOOR_16_TOP_TX,
	&FLOOR_4x12_TX,
	&FLOOR_4_TOP_TX,
	NULL
};



//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef TITLE_SCREEN_ST =
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

    // streaming
	{
		// delay per cycle
		8,
		// load padding
		64,
		// unload padding
		16,
		// streaming amplitude
		16,
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
    1,

	// OBJs segments sizes (must total 1024)
    {
        // SPT0
    	__AVAILABLE_CHAR_OBJECTS,
        // SPT1
    	0,
        // SPT2
    	0,
        // SPT3
    	0,
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
    (TextureDefinition**)TITLE_SCREEN_ST_TEXTURES,

    // UI
    {
        TITLE_SCREEN_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    // entities
    TITLE_SCREEN_ST_ENTITIES,

    // background music
    (const u16 (*)[])WORLD_0_0_0_BGM,
};