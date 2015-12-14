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

extern StageROMDef LEVEL_1_COIN_ROOM_ST;
extern StageROMDef LEVEL_1_SMALL_ROOM_ST;
extern StageROMDef LEVEL_1_TOWER_ST;


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures and entities.
 */

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_2_IM_COLLISIONS[] =
{
	{&COLLISION_ONEWAY_7x1x1, 	{FTOFIX19_13(-226), FTOFIX19_13(-108),  FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x18x1, 	    {FTOFIX19_13(-145), FTOFIX19_13(-56),   FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x18x1, 	    {FTOFIX19_13(127),  FTOFIX19_13(-56),   FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	        {FTOFIX19_13(-8),   FTOFIX19_13(-132),  FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&HIT_COLLISION_20x1x1, 	{FTOFIX19_13(-8),   FTOFIX19_13(-100),  FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_32x14x1, 	    {FTOFIX19_13(-8),   FTOFIX19_13(-40),   FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x1, 	{FTOFIX19_13(-226), FTOFIX19_13(69),    FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_48x18x1, 	    {FTOFIX19_13(-10),  FTOFIX19_13(137),   FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x1, 	{FTOFIX19_13(210),  FTOFIX19_13(-76),   FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x1, 	{FTOFIX19_13(210),  FTOFIX19_13(21),    FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		    {FTOFIX19_13(127),  FTOFIX19_13(39),    FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&COLLISION_18x6x1,		    {FTOFIX19_13(238),  FTOFIX19_13(89),    FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_3_MANAGED[] =
{
	{&LEVEL_1_MAIN_1_MAIN_3_IM, 	    {FTOFIX19_13(0),    FTOFIX19_13(0),     FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_FRONT_3_IM, 	    {FTOFIX19_13(-32),  FTOFIX19_13(120),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_BACK_3_IM, 	{FTOFIX19_13(-7),   FTOFIX19_13(92),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
 //   {&HIDE_LAYER_10x7_AG,               {FTOFIX19_13(-162), FTOFIX19_13(-44),   FTOFIX19_13(-0.000001f)},   NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x1, 	        {FTOFIX19_13(-226), FTOFIX19_13(-12),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x1, 	        {FTOFIX19_13(-226), FTOFIX19_13(84),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_48x18x1, 	            {FTOFIX19_13(-8),   FTOFIX19_13(-122),  FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_28x16x1, 	            {FTOFIX19_13(-8),   FTOFIX19_13(-12),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_48x18x1, 	            {FTOFIX19_13(-8),   FTOFIX19_13(56),    FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(-162), FTOFIX19_13(232),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(-112), FTOFIX19_13(264),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(48),   FTOFIX19_13(264),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(128),  FTOFIX19_13(232),   FTOFIX19_13(0)},    NULL, NULL, NULL, false},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition

//	{&MOUND_BG_BACK_IM,	 	            {FTOFIX19_13(0),    FTOFIX19_13(168), FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, true},
//	{&MOUND_BG_MIDDLE_IM, 	            {FTOFIX19_13(0),    FTOFIX19_13(198), FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM, 	            {FTOFIX19_13(0),    FTOFIX19_13(224), FTOFIX19_13(LAYER_3 + 0.000001f)}, NULL, NULL, NULL, true},
	{&CLOUDS_SB, 			            {FTOFIX19_13(0),    FTOFIX19_13(24),  FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},

	{&HERO_AC, 				            {FTOFIX19_13(56),   FTOFIX19_13(288), FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, true},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	{&COLLISION_2x28x1,                {FTOFIX19_13(-12),  FTOFIX19_13(116), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

	{&LEVEL_1_MAIN_1_MAIN_1_IM, 	    {FTOFIX19_13(256),  FTOFIX19_13(360), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_FRONT_1_IM, 	{FTOFIX19_13(256),  FTOFIX19_13(256), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
    {&LEVEL_1_HOUSE_IM,                 {FTOFIX19_13(104),  FTOFIX19_13(192), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
    {&SMOKE_PS,                         {FTOFIX19_13(101),  FTOFIX19_13(152), FTOFIX19_13(LAYER_0_BACK)}, NULL, NULL, NULL, false},
	{&COLLISION_30x33x1,                {FTOFIX19_13(118),  FTOFIX19_13(369), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_34x30x1,                {FTOFIX19_13(366),  FTOFIX19_13(381), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(216),  FTOFIX19_13(225), FTOFIX19_13(LAYER_0)}, "Coin 001", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(232),  FTOFIX19_13(225), FTOFIX19_13(LAYER_0)}, "Coin 002", NULL, NULL, false},
	{&LEVEL_1_MAIN_1_BACK_1_IM,         {FTOFIX19_13(360),  FTOFIX19_13(250), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(304),  FTOFIX19_13(248), FTOFIX19_13(LAYER_0)}, "Coin 003", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(320),  FTOFIX19_13(248), FTOFIX19_13(LAYER_0)}, "Coin 004", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(336),  FTOFIX19_13(248), FTOFIX19_13(LAYER_0)}, "Coin 005", NULL, NULL, false},
	{&SAW_BLADE_H8_AC,                  {FTOFIX19_13(338),  FTOFIX19_13(260), FTOFIX19_13(LAYER_0_BACK)}, NULL, NULL, NULL, false},
	{&BUSH_AG,                          {FTOFIX19_13(472),  FTOFIX19_13(256), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

	{&LEVEL_1_MAIN_1_MAIN_2_IM, 	    {FTOFIX19_13(768),  FTOFIX19_13(352), FTOFIX19_13(LAYER_0)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_2_IM_COLLISIONS, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(532),  FTOFIX19_13(228), FTOFIX19_13(LAYER_0)}, "Coin 006", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(548),  FTOFIX19_13(228), FTOFIX19_13(LAYER_0)}, "Coin 007", NULL, NULL, false},
	{&LEVEL_1_MAIN_1_FRONT_2_IM, 	    {FTOFIX19_13(760),  FTOFIX19_13(320), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_BACK_2_IM, 	{FTOFIX19_13(717),  FTOFIX19_13(392), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	//{&COIN_AG,                          {FTOFIX19_13(736),  FTOFIX19_13(196), FTOFIX19_13(LAYER_0)}, "Coin 008", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(752),  FTOFIX19_13(196), FTOFIX19_13(LAYER_0)}, "Coin 009", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(768),  FTOFIX19_13(196), FTOFIX19_13(LAYER_0)}, "Coin 010", NULL, NULL, false},
	//{&COIN_AG,                          {FTOFIX19_13(784),  FTOFIX19_13(196), FTOFIX19_13(LAYER_0)}, "Coin 011", NULL, NULL, false},
	{&DOOR_AG,				            {FTOFIX19_13(802),  FTOFIX19_13(400), FTOFIX19_13(LAYER_0)}, NULL, NULL, (void*)&LEVEL_1_COIN_ROOM_ST, false},

	{&HIDE_LAYER_10x7_AG,               {FTOFIX19_13(1072), FTOFIX19_13(196),   FTOFIX19_13(LAYER_0_FRONT)},   NULL, NULL, NULL, false},
    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(1232), FTOFIX19_13(240), FTOFIX19_13(0)}, NULL, (struct PositionedEntity*)LEVEL_1_MAIN_1_MAIN_3_MANAGED, NULL, true},
//	{&COIN_AG,                          {FTOFIX19_13(992),  FTOFIX19_13(212), FTOFIX19_13(LAYER_0)}, "Coin 011", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(992),  FTOFIX19_13(260), FTOFIX19_13(LAYER_0)}, "Coin 012", NULL, NULL, false},
//	{&COIN_AG,                          {FTOFIX19_13(992),  FTOFIX19_13(308), FTOFIX19_13(LAYER_0)}, "Coin 013", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(992),  FTOFIX19_13(356), FTOFIX19_13(LAYER_0)}, "Coin 014", NULL, NULL, false},
//	{&COIN_AG,                          {FTOFIX19_13(992),  FTOFIX19_13(404), FTOFIX19_13(LAYER_0)}, "Coin 015", NULL, NULL, false},
	{&GRASS_AG,                         {FTOFIX19_13(1056), FTOFIX19_13(408), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&DOOR_AG,				            {FTOFIX19_13(1090), FTOFIX19_13(208), FTOFIX19_13(LAYER_0)}, NULL, NULL, (void*)&LEVEL_1_SMALL_ROOM_ST, false},
	{&DOOR_AG,				            {FTOFIX19_13(1361), FTOFIX19_13(208), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&KEY_AG,				            {FTOFIX19_13(1392), FTOFIX19_13(212), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_LANE_V_6_IM,            {FTOFIX19_13(1199), FTOFIX19_13(472), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_V3_AC,                  {FTOFIX19_13(1200), FTOFIX19_13(472), FTOFIX19_13(LAYER_0_FRONT)}, NULL, NULL, NULL, false},

	{&LEVEL_1_MAIN_1_MAIN_4_IM, 	    {FTOFIX19_13(1736), FTOFIX19_13(400), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_FRONT_4_IM, 	    {FTOFIX19_13(1700), FTOFIX19_13(368), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_H3_AC,                  {FTOFIX19_13(1865), FTOFIX19_13(302), FTOFIX19_13(LAYER_0_BACK)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(1440), FTOFIX19_13(441), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(1520), FTOFIX19_13(409), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_14x6x1,		            {FTOFIX19_13(1600), FTOFIX19_13(377), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_20x6x1,		            {FTOFIX19_13(1704), FTOFIX19_13(345), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_20x6x1,		            {FTOFIX19_13(1860), FTOFIX19_13(375), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	                {FTOFIX19_13(1864), FTOFIX19_13(317), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_20x32x1, 	            {FTOFIX19_13(2024), FTOFIX19_13(449), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&HIT_COLLISION_20x1x1, 	        {FTOFIX19_13(1864), FTOFIX19_13(348), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

	{&LEVEL_1_MAIN_1_MAIN_5_IM, 	    {FTOFIX19_13(2212), FTOFIX19_13(392), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_FRONT_5_IM, 	    {FTOFIX19_13(2192), FTOFIX19_13(320), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_BACK_5_IM,         {FTOFIX19_13(2340), FTOFIX19_13(384), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&COLLISION_41x2x1, 	            {FTOFIX19_13(2360), FTOFIX19_13(248), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&COLLISION_43x5x1, 	            {FTOFIX19_13(2288), FTOFIX19_13(281), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&COLLISION_59x25x1, 	            {FTOFIX19_13(2372), FTOFIX19_13(413), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x1, 	        {FTOFIX19_13(2530), FTOFIX19_13(256), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&DOOR_BACK_AG, 	                {FTOFIX19_13(2482), FTOFIX19_13(288), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(2176), FTOFIX19_13(292), FTOFIX19_13(LAYER_0)}, "Coin 006", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(2192), FTOFIX19_13(292), FTOFIX19_13(LAYER_0)}, "Coin 006", NULL, NULL, false},
//	{&CANNON_AC,                        {FTOFIX19_13(2184), FTOFIX19_13(290), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	                {FTOFIX19_13(2184), FTOFIX19_13(317), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	                {FTOFIX19_13(2296), FTOFIX19_13(317), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(2400), FTOFIX19_13(292), FTOFIX19_13(LAYER_0)}, "Coin 006", NULL, NULL, false},
	{&COIN_AG,                          {FTOFIX19_13(2416), FTOFIX19_13(292), FTOFIX19_13(LAYER_0)}, "Coin 006", NULL, NULL, false},
//	{&CANNON_AC,                        {FTOFIX19_13(2408), FTOFIX19_13(290), FTOFIX19_13(LAYER_2)}, NULL, NULL, NULL, false},
	{&COLLISION_8x3x1, 	                {FTOFIX19_13(2408), FTOFIX19_13(317), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

///	{&HERO_AC, 				            {FTOFIX19_13(2509), FTOFIX19_13(305), FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, false},

	{&LEVEL_1_MAIN_1_MAIN_6_IM, 	    {FTOFIX19_13(2736), FTOFIX19_13(356), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_FRONT_6_IM, 	    {FTOFIX19_13(2736), FTOFIX19_13(284), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&LEVEL_1_MAIN_1_MAIN_BACK_6_IM, 	{FTOFIX19_13(2821), FTOFIX19_13(164), FTOFIX19_13(LAYER_0_BACK)}, NULL, NULL, NULL, false},
	{&COLLISION_48x28x1, 	            {FTOFIX19_13(2680), FTOFIX19_13(429), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_ONEWAY_7x1x1, 	        {FTOFIX19_13(2606), FTOFIX19_13(257), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_12x4x1,                 {FTOFIX19_13(2680), FTOFIX19_13(253), FTOFIX19_13(LAYER_0_FRONT)}, NULL, NULL, NULL, false},
	{&HIDE_LAYER_10x7_AG,               {FTOFIX19_13(2672), FTOFIX19_13(288), FTOFIX19_13(LAYER_0_FRONT)}, NULL, NULL, NULL, false},
	{&DOOR_AG,				            {FTOFIX19_13(2673), FTOFIX19_13(300), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COLLISION_48x28x1, 	            {FTOFIX19_13(2904), FTOFIX19_13(349), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&DOOR_AG,				            {FTOFIX19_13(2904), FTOFIX19_13(220), FTOFIX19_13(LAYER_0)}, NULL, NULL, (void*)&LEVEL_1_TOWER_ST, false},

	{&COLLISION_2x28x1,                {FTOFIX19_13(3000), FTOFIX19_13(116), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_MAIN_1_MAIN_1_ST_UI_ENTITIES[] =
{
	{&GUI_IM, {FTOFIX19_13(192), FTOFIX19_13(213), FTOFIX19_13(-8)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

TextureROMDef* LEVEL_1_MAIN_1_MAIN_1_ST_TEXTURES[] =
{
	&LEVEL_1_MAIN_1_MAIN_1_TX,
	&LEVEL_1_MAIN_1_MAIN_2_TX,
	&LEVEL_1_MAIN_1_FRONT_2_TX,
	&LEVEL_1_MAIN_1_MAIN_FRONT_1_TX,
	&CLOUDS_A_TX,
	&CLOUDS_B_TX,
//	&LEVEL_1_MAIN_1_BACK_1_TX,
//	&MOUND_BG_BACK_TX,
//	&MOUND_BG_MIDDLE_TX,
	&MOUND_BG_FRONT_TX,
	&LEVEL_1_HOUSE_TX,
	&SMOKE_PARTICLE_SMALL_TX,
	&COIN_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerStageROMDef LEVEL_1_MAIN_1_MAIN_1_ST =
{
    {
        // size
        {
            // x
            2992,
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
            //ITOFIX19_13(2509),
            ITOFIX19_13(56),
            // y
            ITOFIX19_13(200),
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

        // textures to preload
        (TextureDefinition**)LEVEL_1_MAIN_1_MAIN_1_ST_TEXTURES,

        // UI
        {
            LEVEL_1_MAIN_1_MAIN_1_ST_UI_ENTITIES,
            __TYPE(UI),
        },

        // entities
        LEVEL_1_MAIN_1_MAIN_1_ST_ENTITIES,

        // background music
        (const u16 (*)[])KRISSE_BGM,
    },

    // identifier
    "1-1",

    // name
    (void*)STR_LEVEL_1_NAME,
};