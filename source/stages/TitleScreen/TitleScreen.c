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
#include <objects.h>
#include <macros.h>
#include <TitleScreenState.h>
#include "stages/textures.h"


//---------------------------------------------------------------------------------------------------------
// 											    PROTOTYPES
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_1_ROOM_1_ST;
StageROMDef LEVEL_1_3_ROOM_1_ST;


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
 * know that it must stop reading the stage's/ui's textures ante enties.
 */

extern AnimatedInGameEntityROMDef HERO_DUMMY_AC;

PositionedEntityROMDef TITLE_SCREEN_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
//	{&CLOUDS_SB, 			{FTOFIX19_13(-32), FTOFIX19_13(-112), FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL},
    {&MOUND_BG_BACK_IM,	 	{FTOFIX19_13(-32), FTOFIX19_13(0), FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL},
	{&MOUND_BG_MIDDLE_IM, 	{FTOFIX19_13(-32), FTOFIX19_13(110), FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL},
	{&MOUND_BG_FRONT_IM, 	{FTOFIX19_13(-32), FTOFIX19_13(154), FTOFIX19_13(LAYER_3 + 1)}, NULL, NULL, NULL},

	{&DUMMY_HERO_AC, 		{FTOFIX19_13(16), FTOFIX19_13(148), FTOFIX19_13(0)}, "DummyHero", NULL, NULL},
	{&DUMMY_HERO_AC, 		{FTOFIX19_13(352), FTOFIX19_13(140), FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&DUMMY_HERO_AC, 		{FTOFIX19_13(352 + 18), FTOFIX19_13(140), FTOFIX19_13(0)}, NULL, NULL, NULL},

	{&HERO_AC, 				{FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(148), FTOFIX19_13(0)}, HERO_NAME, NULL, NULL},
	{&TEST_PS, 				{FTOFIX19_13(__SCREEN_WIDTH - 30), FTOFIX19_13(10), FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL},
	
	{&COLLISION_48x2x48, 	{FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(177), FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&COLLISION_2x28x48, 	{FTOFIX19_13(90), FTOFIX19_13(__SCREEN_HEIGHT >> 1), FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&COLLISION_2x28x48, 	{FTOFIX19_13(__SCREEN_WIDTH - 92), FTOFIX19_13(__SCREEN_HEIGHT >> 1), FTOFIX19_13(0)}, NULL, NULL, NULL},

	// ignore samples
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(57), FTOFIX19_13(138), FTOFIX19_13(0)}, "IgnoreMeCoin", NULL, NULL},
	{&DOOR_AG,				{FTOFIX19_13((__SCREEN_WIDTH >> 1)), FTOFIX19_13(152), FTOFIX19_13(1)}, "IgnoreMeDoor", NULL, NULL},
	{&DOOR_AG,				{FTOFIX19_13((__SCREEN_WIDTH >> 1) - 40), FTOFIX19_13(152), FTOFIX19_13(1)}, NULL, NULL, (void*)&LEVEL_1_1_ROOM_1_ST},
	{&DOOR_AG,				{FTOFIX19_13((__SCREEN_WIDTH >> 1) + 40), FTOFIX19_13(152), FTOFIX19_13(1)}, NULL, NULL, (void*)&LEVEL_1_3_ROOM_1_ST},

	/*
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(57), FTOFIX19_13(138), FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&OBJECT_COIN_AG, 		{FTOFIX19_13(71), FTOFIX19_13(138), FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&BGMAP_COIN_AG, 		{FTOFIX19_13(316), FTOFIX19_13(146), FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&BGMAP_COIN_AG, 		{FTOFIX19_13(330), FTOFIX19_13(146), FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&AFFINE_COIN_AG, 		{FTOFIX19_13(299), FTOFIX19_13(98), FTOFIX19_13(LAYER_3)}, NULL, NULL, NULL},
	{&AFFINE_COIN_AG,		{FTOFIX19_13(313), FTOFIX19_13(98), FTOFIX19_13(LAYER_3)}, NULL, NULL, NULL},
*/
	{&LOGO_IM, 			    {FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(72), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL},

    {&TITLESCREEN_MIDDLE_IM,{FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(184), FTOFIX19_13(0)}, NULL, NULL, NULL},
    {&TITLESCREEN_FRONT_IM, {FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(165), FTOFIX19_13(-10)}, NULL, NULL, NULL},
	{&SUPER_AWESOME_IM,     {FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(48), FTOFIX19_13(LAYER_0 - 16)}, NULL, NULL, NULL},

	{NULL, {0,0,0}, NULL, NULL, NULL},
};

PositionedEntityROMDef TITLE_SCREEN_ST_UI_ENTITIES[] =
{
	{&GUI_BLANK_IM,			{FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(__SCREEN_HEIGHT - 8), FTOFIX19_13(0)}, NULL, NULL, NULL},
	{NULL, {0,0,0}, NULL, NULL, NULL},
};

TextureROMDef* TITLE_SCREEN_ST_TEXTURES[] =
{
	&CLOUDS_A_TX,
	&CLOUDS_B_TX,
	&MOUND_BG_BACK_TX,
	&MOUND_BG_MIDDLE_TX,
	&MOUND_BG_FRONT_TX,
	&SUPER_AWESOME_TX,
	&LOGO_L_TX,
	&LOGO_R_TX,
	&LOGO_OUTLINE_L_TX,
	&LOGO_OUTLINE_R_TX,
	&GUI_BLANK_TX,
	&DOOR_TX,
	&BGMAP_COIN_TX,
	&TITLESCREEN_MIDDLE_TX,
	&TITLESCREEN_FRONT_TX,
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

	// OBJs segments z coordinates (SPT0 to SPT3)
    {
    	ITOFIX19_13(0), 
		ITOFIX19_13(0), 
		ITOFIX19_13(0), 
		ITOFIX19_13(0)
    },

    //initial screen position
    {
        // x
        ITOFIX19_13(SCREEN_X_POSITION),
        // y
        ITOFIX19_13(SCREEN_Y_POSITION),
        // z
        ITOFIX19_13(SCREEN_Z_POSITION)
    },

    //textures to preload
    (TextureDefinition**)TITLE_SCREEN_ST_TEXTURES,

    //UI
    {
        TITLE_SCREEN_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    //entities
    TITLE_SCREEN_ST_ENTITIES,

    //background music
    (const u16 (*)[])WORLD_0_0_0_BGM,

    //identifier
    "",

    //name
    "",
};