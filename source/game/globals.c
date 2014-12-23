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

// include VBJaEngine's Game class
#include <Game.h>
#include <Debug.h>
#include <StageEditor.h>
#include <AnimationEditor.h>

// include the Game's objects
#include <objects.h>


//---------------------------------------------------------------------------------------------------------
// 										DEFINITIONS
//---------------------------------------------------------------------------------------------------------

#ifdef __DEBUG_TOOLS
const ClassSizeData _userClassesSizeData[] =
{
		
	{&Hero_getObjectSize, "Hero"},
	{&Coin_getObjectSize, "Coin"},
	{&SawBlade_getObjectSize, "SawBlade"},
	{NULL, ""},
};
#endif

#ifdef __STAGE_EDITOR
const UserObject _userObjects[] =
{

	{&COIN_MC, "Coin"},
	{&DOOR_MC, "Door"},
	{&HERO_MC, "Hero"},
	{&KEY_MC, "Key"},
	{&SAW_BLADE_MC, "SawBlade"},
	{&SAW_BLADE_LANE_V_6_IM, "SawBlade Lane V6"},
	{NULL, ""},
};
#endif

#ifdef __ANIMATION_EDITOR
const UserActor _userActors[] =
{
		
	{(ActorDefinition*)&COIN_MC, "Coin"},
	{(ActorDefinition*)&DOOR_MC, "Door"},
	{(ActorDefinition*)&HERO_MC, "Hero"},
	{(ActorDefinition*)&KEY_MC, "Key"},
	{(ActorDefinition*)&SAW_BLADE_MC, "SawBlade"},
	{NULL, ""},
};
#endif