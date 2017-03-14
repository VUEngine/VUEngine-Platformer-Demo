/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <Debug.h>
#include <StageEditor.h>
#include <AnimationInspector.h>
#include <ManagedEntity.h>
#include <CollisionsContainerEntity.h>
#include <Bandana.h>
#include <Cannon.h>
#include <CannonBall.h>
#include <Coin.h>
#include <Door.h>
#include <Gui.h>
#include <Hero.h>
#include <HideLayer.h>
#include <Key.h>
#include <MovingEntity.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition LEVEL_1_HOUSE_IM;
extern EntityDefinition CANNON_BALL_AC;
extern EntityDefinition COIN_AG;
extern EntityDefinition DOOR_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition HERO_AG;
extern EntityDefinition KEY_AG;
extern EntityDefinition SAW_BLADE_V3_AC;
extern EntityDefinition SAW_BLADE_H3_AC;
extern EntityDefinition LAVA_TOP_AG;
extern EntityDefinition LANE_V_6_IM;
extern EntityDefinition LAYER_SWITCH_DOOR_BACK_AG;


//---------------------------------------------------------------------------------------------------------
//										DEFINITIONS
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
	{&Bandana_getObjectSize,		"Bandana"},
	{&Cannon_getObjectSize,			"Cannon"},
	{&CannonBall_getObjectSize,		"CannonBall"},
	{&Coin_getObjectSize,			"Coin"},
	{&Door_getObjectSize,			"Door"},
	{&Gui_getObjectSize,			"GUI"},
	{&Hero_getObjectSize,			"Hero"},
	{&HideLayer_getObjectSize,		"HideLayer"},
	{&HideLayer_getObjectSize,		"Hint"},
	{&Key_getObjectSize,			"Key"},
	{&MovingEntity_getObjectSize,	"MovingEntity"},
	{NULL, ""},
};
#endif

const UserObject _userObjects[] =
{
	{&LEVEL_1_HOUSE_IM,		"House"},
	{&CANNON_BALL_AC,		"CannonBall"},
	{&COIN_AG,				"Coin"},
	{&DOOR_AG,				"Door"},
	{&HERO_AC,				"Hero"},
	{&KEY_AG,				"Key"},
	{&SAW_BLADE_V3_AC,		"SawBlade V3"},
	{&SAW_BLADE_H3_AC,		"SawBlade H3"},
	{&LANE_V_6_IM,			"SawBlade Lane V6"},
	{NULL, ""},
};

const UserAnimatedInGameEntity _userAnimatedInGameEntities[] =
{
	{(AnimatedInGameEntityDefinition*)&COIN_AG,						"Coin"},
	{(AnimatedInGameEntityDefinition*)&DOOR_AG,						"Door"},
	{(AnimatedInGameEntityDefinition*)&LAYER_SWITCH_DOOR_BACK_AG,	"Back Door"},
	{(AnimatedInGameEntityDefinition*)&HERO_AC,						"Hero"},
	{(AnimatedInGameEntityDefinition*)&KEY_AG,						"Key"},
	{(AnimatedInGameEntityDefinition*)&SAW_BLADE_V3_AC,				"SawBlade"},
	{(AnimatedInGameEntityDefinition*)&LAVA_TOP_AG,					"Lava top"},
	{NULL, ""},
};
