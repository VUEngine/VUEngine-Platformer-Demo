/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <VUEngine.h>
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

extern EntitySpec CannonBallEntity;
extern EntitySpec CoinEntity;
extern EntitySpec DoorEntity;
extern EntitySpec HeroEntity;
extern EntitySpec HERO_EN;
extern EntitySpec KeyEntity;
extern EntitySpec LavaTopEntity;
extern EntitySpec LayerSwitchDoorBackEntity;
extern EntitySpec Level1HouseEntity;
extern EntitySpec SawBladeH3Entity;
extern EntitySpec SawBladeV3Entity;
extern EntitySpec Snail3Entity;


//---------------------------------------------------------------------------------------------------------
//										DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// only need to define one for all managed entities
EntityROMSpec ManagedEntity =
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
			
	/// meshes
	(WireframeSpec**)NULL,

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
	{&Level1HouseEntity,		"House"},
	{&CannonBallEntity,		"CannonBall"},
	{&CoinEntity,				"Coin"},
	{&DoorEntity,				"Door"},
	{&HeroEntity,				"Hero"},
	{&KeyEntity,				"Key"},
	{&SawBladeV3Entity,		"SawBlade V3"},
	{&SawBladeH3Entity,		"SawBlade H3"},
	{NULL, ""},
};

const UserAnimatedEntity _userAnimatedEntities[] =
{
	{(AnimatedEntitySpec*)&CoinEntity,						"Coin"},
	{(AnimatedEntitySpec*)&DoorEntity,						"Door"},
	{(AnimatedEntitySpec*)&LayerSwitchDoorBackEntity,	"Back Door"},
	{(AnimatedEntitySpec*)&HeroEntity,						"Hero"},
	{(AnimatedEntitySpec*)&KeyEntity,						"Key"},
	{(AnimatedEntitySpec*)&SawBladeV3Entity,				"SawBlade"},
	{(AnimatedEntitySpec*)&Snail3Entity,					"Snail"},
	{(AnimatedEntitySpec*)&LavaTopEntity,					"Lava top"},
	{NULL, ""},
};

const SoundROMSpec* _userSounds[] =
{
	NULL
};

const ToolState _userToolStates[] =
{
	NULL
};