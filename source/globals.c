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
#include <ManagedEntity.h>
#include <CollisionsContainerEntity.h>

#include <objects.h>
#include <screens.h>
#include <sound.h>


//---------------------------------------------------------------------------------------------------------
// 										DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// only need to define one for all containers
EntityROMDef SIMPLE_CONTAINER =
{
    __TYPE(Entity),
    NULL
};


// only need to define one for all managed entities
ManagedEntityROMDef MANAGED_ENTITY =
{
    __TYPE(ManagedEntity),
    NULL
};

// only need to define one for all entities
CollisionsContainerEntityROMDef COLLISIONS_CONTAINER_ENTITY =
{
    __TYPE(CollisionsContainerEntity),
    NULL
};


#ifdef __DEBUG_TOOLS
const ClassSizeData _userClassesSizeData[] =
{
	{&Bandana_getObjectSize,        "Bandana"},
	{&Cannon_getObjectSize,         "Cannon"},
	{&CannonBall_getObjectSize,     "CannonBall"},
	{&Coin_getObjectSize,           "Coin"},
	{&Door_getObjectSize,           "Door"},
	{&GUI_getObjectSize,            "GUI"},
	{&Hero_getObjectSize,           "Hero"},
	{&HideLayer_getObjectSize,      "HideLayer"},
	{&HideLayer_getObjectSize,      "Hint"},
	{&Key_getObjectSize,            "Key"},
	{&MovingEntity_getObjectSize,   "MovingEntity"},
	{NULL, ""},
};
#endif

#ifdef __STAGE_EDITOR
const UserObject _userObjects[] =
{
	{&LEVEL_1_HOUSE_IM,     "House"},
	{&CANNON_BALL_AC,       "CannonBall"},
	{&COIN_AG,              "Coin"},
	{&DOOR_AG,              "Door"},
	{&HERO_AC,              "Hero"},
	{&KEY_AG,               "Key"},
	{&SAW_BLADE_V3_AC,      "SawBlade V3"},
	{&SAW_BLADE_H3_AC,      "SawBlade H3"},
	{&LANE_V_6_IM,          "SawBlade Lane V6"},
	{NULL, ""},
};
#endif

#ifdef __ANIMATION_EDITOR
const UserAnimatedInGameEntity _userAnimatedInGameEntities[] =
{
	{(AnimatedInGameEntityDefinition*)&COIN_AG,                     "Coin"},
	{(AnimatedInGameEntityDefinition*)&DOOR_AG,                     "Door"},
	{(AnimatedInGameEntityDefinition*)&LAYER_SWITCH_DOOR_BACK_AG,   "Back Door"},
	{(AnimatedInGameEntityDefinition*)&HERO_AC,                     "Hero"},
	{(AnimatedInGameEntityDefinition*)&KEY_AG,                      "Key"},
	{(AnimatedInGameEntityDefinition*)&SAW_BLADE_V3_AC,             "SawBlade"},
	{(AnimatedInGameEntityDefinition*)&LAVA_TOP_AG,                 "Lava top"},
	{NULL, ""},
};
#endif
