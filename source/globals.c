/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <SoundTest.h>
#include <Entity.h>
#include <Bandana.h>
#include <Cannon.h>
#include <CannonBall.h>
#include <CogWheel.h>
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

extern EntitySpec CANNON_BALL_AC;
extern EntitySpec COIN_EN;
extern EntitySpec DOOR_EN;
extern EntitySpec HERO_AC;
extern EntitySpec HERO_EN;
extern EntitySpec KEY_EN;
extern EntitySpec LAVA_TOP_EN;
extern EntitySpec LAYER_SWITCH_DOOR_BACK_EN;
extern EntitySpec LEVEL_1_HOUSE_IM;
extern EntitySpec SAW_BLADE_H3_AC;
extern EntitySpec SAW_BLADE_V3_AC;
extern EntitySpec SNAIL_3_AC;


//---------------------------------------------------------------------------------------------------------
//										DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// only need to define one for all managed entities
EntityROMSpec MANAGED_ENTITY =
{
	// class allocator
	__TYPE(Entity),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	NULL,

	// use z displacement in projection
	false,

	// collision shapes
	NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	NULL,
};

#ifdef __DEBUG_TOOLS
const ClassSizeData _userClassesSizeData[] =
{
	{&Bandana::getObjectSize,		"Bandana"},
	{&Cannon::getObjectSize,		"Cannon"},
	{&CannonBall::getObjectSize,	"CannonBall"},
	{&CogWheel::getObjectSize,		"CogWheel"},
	{&Coin::getObjectSize,			"Coin"},
	{&Door::getObjectSize,			"Door"},
	{&Gui::getObjectSize,			"GUI"},
	{&Hero::getObjectSize,			"Hero"},
	{&HideLayer::getObjectSize,		"HideLayer"},
	{&HideLayer::getObjectSize,		"Hint"},
	{&Key::getObjectSize,			"Key"},
	{&MovingEntity::getObjectSize,	"MovingEntity"},
	{NULL, ""},
};
#endif

const UserObject _userObjects[] =
{
	{&LEVEL_1_HOUSE_IM,		"House"},
	{&CANNON_BALL_AC,		"CannonBall"},
	{&COIN_EN,				"Coin"},
	{&DOOR_EN,				"Door"},
	{&HERO_AC,				"Hero"},
	{&KEY_EN,				"Key"},
	{&SAW_BLADE_V3_AC,		"SawBlade V3"},
	{&SAW_BLADE_H3_AC,		"SawBlade H3"},
	{NULL, ""},
};

const UserAnimatedEntity _userAnimatedEntities[] =
{
	{(AnimatedEntitySpec*)&COIN_EN,						"Coin"},
	{(AnimatedEntitySpec*)&DOOR_EN,						"Door"},
	{(AnimatedEntitySpec*)&LAYER_SWITCH_DOOR_BACK_EN,	"Back Door"},
	{(AnimatedEntitySpec*)&HERO_AC,						"Hero"},
	{(AnimatedEntitySpec*)&KEY_EN,						"Key"},
	{(AnimatedEntitySpec*)&SAW_BLADE_V3_AC,				"SawBlade"},
	{(AnimatedEntitySpec*)&SNAIL_3_AC,					"Snail"},
	{(AnimatedEntitySpec*)&LAVA_TOP_EN,					"Lava top"},
	{NULL, ""},
};

const SoundROM* _userSounds[] =
{
	NULL
};

const ToolState _userToolStates[] =
{
	NULL
};