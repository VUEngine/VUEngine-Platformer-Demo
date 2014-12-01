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

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


// include VBJaEngine's Game class
#include <Game.h>
#include <Debug.h>
#include <LevelEditor.h>
#include <I18n.h>
#include <AnimationEditor.h>

// include the Game's objects
#include <objects.h>

// include the Game's localization files
#include <../assets/text/text.h>

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 										DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// register languages
// I18n_register(I18n_getInstance(), "en", lang_en);
 
 
#ifdef __DEBUG_TOOLS
const ClassSizeData _userClassesSizeData[] = {
		
	{"Hero", &Hero_getObjectSize},
	{"PiranhaPlant", &PiranhaPlant_getObjectSize},
	{"", NULL},
};
#endif

#ifdef __LEVEL_EDITOR
const UserObject _userObjects[] = {
	{"Coin", &COIN_MC},
	{"Saw blade", &SAW_BLADE_MC},
	{"SawBlade Lane V6", &SAW_BLADE_LANE_V_6_IM},
	{"Japan. door", &JAPANARC_IM},
	{"Wall", &WALL0_BG},
	{"Floor 0", &FLOOR0_BG},
	{"Floor 1", &FLOOR1_BG},
	{"Floor 2", &FLOOR2_BG},
	{"Hor. pipe", &PIPE1_BG},
	{"Ver. pipe", &PIPE0_BG},
	{"Small mount", &MOUNTS0_IM},
	{"Large mount", &MOUNTS1_IM},
	{"Pole", &POLE0_BG},
	{"Goal", &GOAL0_IM},
	{"", NULL},
};
#endif

#ifdef __ANIMATION_EDITOR
const UserActor _userActors[] = {
		
	{"Hero", (ActorDefinition*)&HERO_MC},
	{"Coin", (ActorDefinition*)&COIN_MC},
	{"Ver. Piranha plant", (ActorDefinition*)&PIRANHA_PLANT_V_MC},
	{"SawBlade", (ActorDefinition*)&SAW_BLADE_MC},
	{"", NULL},
};
#endif