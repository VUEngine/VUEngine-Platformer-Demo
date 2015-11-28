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

#include <Game.h>
#include <Debug.h>
#include <StageEditor.h>
#include <AnimationEditor.h>

#include <objects.h>
#include <screens.h>
#include <sound.h>


//---------------------------------------------------------------------------------------------------------
// 										DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// only need to define one for all managed entities
const ManagedEntityROMDef MANAGED_ENTITY =
{
    __TYPE(ManagedEntity),
    NULL
};


#ifdef __DEBUG_TOOLS
const ClassSizeData _userClassesSizeData[] =
{
	{&Hero_getObjectSize, "Hero"},
	{&Coin_getObjectSize, "Coin"},
	{&SawBlade_getObjectSize, "SawBlade"},
	{&Door_getObjectSize, "Door"},
	{&Key_getObjectSize, "Key"},
	{NULL, ""},
};
#endif

#ifdef __STAGE_EDITOR
const UserObject _userObjects[] =
{
	{&LEVEL_1_HOUSE_IM, "House"},
	{&CANNON_BALL_IG, "CannonBall"},
	{&COIN_AG, "Coin"},
	{&DOOR_AG, "Door"},
	{&HERO_AC, "Hero"},
	{&KEY_AG, "Key"},
	{&SAW_BLADE_V3_AC, "SawBlade V3"},
	{&SAW_BLADE_H3_AC, "SawBlade H3"},
	{&SAW_BLADE_LANE_V_6_IM, "SawBlade Lane V6"},
	{NULL, ""},
};
#endif

#ifdef __ANIMATION_EDITOR
const UserAnimatedInGameEntity _userAnimatedInGameEntities[] =
{
	{(AnimatedInGameEntityDefinition*)&COIN_AG, "Coin"},
	{(AnimatedInGameEntityDefinition*)&DOOR_AG, "Door"},
	{(AnimatedInGameEntityDefinition*)&HERO_AC, "Hero"},
	{(AnimatedInGameEntityDefinition*)&HINT_ENTER_MC, "Hint enter"},
	{(AnimatedInGameEntityDefinition*)&KEY_AG, "Key"},
	{(AnimatedInGameEntityDefinition*)&SAW_BLADE_V3_AC, "SawBlade"},
	{(AnimatedInGameEntityDefinition*)&LAVA_TOP_AG, "Lava top"},
	{NULL, ""},
};
#endif