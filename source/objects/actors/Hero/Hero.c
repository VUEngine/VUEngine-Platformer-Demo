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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Screen.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <KeypadManager.h>
#include "Hero.h"
#include "states/HeroIdle.h"
#include "states/HeroMoving.h"
#include <CustomScreenMovementManager.h>
#include <CustomScreenEffectManager.h>
#include <CameraTriggerEntity.h>
#include <EventManager.h>
#include <Hint.h>
#include <SoundManager.h>
#include <debugUtilities.h>
#include <gameDebugConfig.h>
#include <HideLayer.h>


#define HERO_MASS							2
#define HERO_ELASTICITY						0.0f
#define HERO_FRICTION						0

#define HERO_FLASH_PALETTE					3
#define HERO_FLASH_DURATION					2000
#define HERO_FLASH_INTERVAL					100

#define HERO_INPUT_FORCE 					__I_TO_FIX19_13(5050)
#define HERO_X_INPUT_FORCE_WHILE_JUMPING	__I_TO_FIX19_13(3050)

#define HERO_MAX_VELOCITY_X					__I_TO_FIX19_13(75)
#define HERO_MAX_VELOCITY_Y					__I_TO_FIX19_13(305)
#define HERO_MAX_VELOCITY_Z					__I_TO_FIX19_13(40)
#define HERO_BOOST_VELOCITY_X				__F_TO_FIX19_13(100)
#define HERO_NORMAL_JUMP_INPUT_FORCE		__I_TO_FIX19_13(-21000)
#define HERO_BOOST_JUMP_INPUT_FORCE			__I_TO_FIX19_13(-28000)

#define CAMERA_BOUNDING_BOX_DISPLACEMENT	{__I_TO_FIX19_13(0), __I_TO_FIX19_13(-24), 0}

#define HERO_CHECK_Y_VELOCITY				20


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Hero, Actor);


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern double fabs (double);

extern const u16 COLLECT_SND[];
extern const u16 FIRE_SND[];
extern const u16 JUMP_SND[];
extern CharSetDefinition HERO_CH;
extern CharSetDefinition HERO_BANDANA_CH;

extern EntityDefinition DUST_PS;
extern EntityDefinition HINT_MC;
extern CameraTriggerEntityROMDef CAMERA_BOUNDING_BOX_IG;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void Hero_onUserInput(Hero this, Object eventFirer);
void Hero_enterDoor(Hero this);
void Hero_hideHint(Hero this);
void Hero_updateSprite(Hero this);
static void Hero_addHint(Hero this);
static void Hero_addFeetDust(Hero this);
static void Hero_slide(Hero this);
static void Hero_showDust(Hero this, bool autoHideDust);
static void Hero_hideDust(Hero this);
void Hero_losePowerUp(Hero this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// Only one instance
Hero hero = NULL;

// there can only be one hero instantiated
Hero Hero_getInstance()
{
	return hero;
}

void Hero_setInstance(Hero instance)
{
	ASSERT(!hero, "Hero::setInstance: already instantiated");

	hero = instance;
}

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Hero, HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Hero, heroDefinition, id, internalId, name);

// class's constructor
void Hero_constructor(Hero this, HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Hero::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Actor, (ActorDefinition*)heroDefinition, id, internalId, name);

	// construct the game state machine
	this->stateMachine = __NEW(StateMachine, this);

	// init class variables
	this->coins = 0;
	this->hasKey = false;
	this->hint = NULL;
	this->feetDust = NULL;
	this->cameraBoundingBox = NULL;
	this->energy = HERO_INITIAL_ENERGY;
	this->powerUp = kPowerUpNone;
	this->invincible = false;
	this->currentlyOverlappedDoor = NULL;
	this->boost = false;
	this->jumps = 0;
	this->keepAddingForce = false;

	// register a body for physics
	this->body = PhysicalWorld_createBody(Game_getPhysicalWorld(Game_getInstance()), (BodyAllocator)__TYPE(Body), __SAFE_CAST(SpatialObject, this), heroDefinition->animatedEntityDefinition.entityDefinition.physicalSpecification);
	Body_setAxisSubjectToGravity(this->body, __Y_AXIS);
	Body_stopMovement(this->body, (__X_AXIS | __Y_AXIS | __Z_AXIS));
	this->collisionSolver = __NEW(CollisionSolver, __SAFE_CAST(SpatialObject, this));

	Hero_setInstance(this);

	Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getInstance()), __SAFE_CAST(Object, this), (EventListener)Hero_onUserInput, kEventUserInput);

	this->inputDirection = Entity_getDirection(__SAFE_CAST(Entity, this));
}

// class's destructor
void Hero_destructor(Hero this)
{
	ASSERT(this, "Hero::destructor: null this");
	ASSERT(hero, "Hero::destructor: already deleted");
	ASSERT(hero == this, "Hero::destructor: more than one instance");

	// remove event listeners
	Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getInstance()), __SAFE_CAST(Object, this), (EventListener)Hero_onUserInput, kEventUserInput);

	// announce my dead
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventHeroDied);

	// discard pending delayed messages
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroFlash);

	// free the instance pointers
	this->feetDust = NULL;
	this->hint = NULL;
	this->cameraBoundingBox = NULL;
	hero = NULL;

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Hero_ready(Hero this, bool recursive)
{
	ASSERT(this, "Hero::ready: null this");

	Entity_informShapesThatStartedMoving(__SAFE_CAST(Entity, this));

	// call base
	__CALL_BASE_METHOD(Actor, ready, this, recursive);

	// override with progress from progress manager
	ProgressManager progressManager = ProgressManager_getInstance();
	if(progressManager)
	{
		this->energy = ProgressManager_getHeroCurrentEnergy(progressManager);

		u8 currentPowerUp = ProgressManager_getHeroCurrentPowerUp(progressManager);
		if(currentPowerUp != this->powerUp)
		{
			this->powerUp = currentPowerUp;
			Hero_updateSprite(this);
		}

		this->hasKey = ProgressManager_heroHasKey(ProgressManager_getInstance());
	}

	// initialize me as idle
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));

	Hero_addHint(this);
	Hero_addFeetDust(this);
}

void Hero_locateOverNextFloor(Hero this __attribute__ ((unused)))
{
/*	VBVec3D direction = {0, 1, 0};

	SpatialObject collidingSpatialObject = CollisionManager_searchNextObjectOfCollision(Game_getCollisionManager(Game_getInstance()), this->shape, direction);
	ASSERT(collidingSpatialObject, "Hero::locateOverNextFloor: null collidingSpatialObject");

	if(collidingSpatialObject && this->collisionSolver)
	{
		VBVec3D displacement =
		{
			__I_TO_FIX19_13(0),
			__1I_FIX19_13,
			__I_TO_FIX19_13(0),
		};

		CollisionSolver_resolveCollision(this->collisionSolver, VirtualList_front(this->shapes), collidingShapesToRemove, displacement, true);
	}
	*/
}

// make him jump
void Hero_jump(Hero this, bool checkIfYMovement)
{
	ASSERT(this, "Hero::jump: null this");

	if(this->body)
	{
		// get the hero's body velocity
		Velocity velocity = Body_getVelocity(this->body);

		// determine the maximum number of possible jumps before reaching ground again
		s8 allowedNumberOfJumps = (this->powerUp == kPowerUpBandana) ? 2 : 1;

		this->jumps = 0;

#ifdef GOD_MODE
	allowedNumberOfJumps = 127;
#endif

		// check if more jumps are allowed
		if(this->jumps < allowedNumberOfJumps)
		{
			// init a force to add to the hero's momentum
			Force force = {0, 0, 0};

			// is this the first jump from ground or a double jump from mid-air?
			if(this->jumps == 0)
			{
				// don't allow a first jump from mid-air without bandana
				if(checkIfYMovement && 0 <= Body_getNormal(this->body).y && (allowedNumberOfJumps == 1))
				{
					return;
				}

				// set first jump performed
				this->jumps = 1;

				// we're leaving ground with this jump
				Hero_startedMovingOnAxis(this, __Y_AXIS);

				// add more force when running, normal force otherwise
				force.y = this->boost ? HERO_BOOST_JUMP_INPUT_FORCE : HERO_NORMAL_JUMP_INPUT_FORCE;

				// add the force to actually make the hero jump
				Actor_addForce(__SAFE_CAST(Actor, this), &force);
			}
			else
			{
				// hack to avoid the processing of kBodyStopped message triggered by the call to Actor_stopMovement
				this->jumps = -1;

				// stop movement to gain full momentum of the jump force that will be added
				Actor_stopMovement(__SAFE_CAST(Actor, this), __Y_AXIS);

				// set second jump performed
				this->jumps = 2;

				// double jumps can never have boost
				force.y = HERO_NORMAL_JUMP_INPUT_FORCE;

				// add the force to actually make the hero jump
				Actor_addForce(__SAFE_CAST(Actor, this), &force);

				// show dust
				Hero_showDust(this, true);
			}

			// play jump animation
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Jump");

			// play jump sound
			SoundManager_playFxSound(SoundManager_getInstance(), JUMP_SND, this->transform.globalPosition);
		}
	}
}

// keep movement
void Hero_addForce(Hero this, u16 axis, bool enableAddingForce)
{
	ASSERT(this, "Hero::addForce: null this");

	if(enableAddingForce)
	{
		this->keepAddingForce = true;
	}

	if(!this->keepAddingForce)
	{
		return;
	}

	static int movementType = 0;

	fix19_13 maxVelocity = this->boost ? HERO_BOOST_VELOCITY_X : HERO_MAX_VELOCITY_X;

	Velocity velocity = Body_getVelocity(this->body);

	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, this));

	if(direction.x != this->inputDirection.x ||
		((__X_AXIS & axis) && maxVelocity > abs(velocity.x)) ||
		((__Z_AXIS & axis) && maxVelocity > abs(velocity.z)) ||
		Actor_changedDirection(__SAFE_CAST(Actor, this), __X_AXIS) ||
		Actor_changedDirection(__SAFE_CAST(Actor, this), __Z_AXIS))
	{
		fix19_13 inputForce = __Y_AXIS & Body_getMovementOnAllAxes(this->body) ? HERO_X_INPUT_FORCE_WHILE_JUMPING : HERO_INPUT_FORCE;
		fix19_13 xForce = (__X_AXIS & axis) ? __RIGHT == this->inputDirection.x ? inputForce : -inputForce : 0;
		fix19_13 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		Actor_addForce(__SAFE_CAST(Actor, this), &force);
		movementType = __ACCELERATED_MOVEMENT;
	}
	else
	{
		if(__UNIFORM_MOVEMENT != movementType || (abs(velocity.x) > maxVelocity && !(__Y_AXIS & Body_getMovementOnAllAxes(this->body))))
		{
			Velocity newVelocity =
			{
				(__X_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.x) : 0,
				0,
				(__Z_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.z) : 0,
			};

			movementType = __UNIFORM_MOVEMENT;
			Body_moveUniformly(this->body, newVelocity);
		}
	}
}

static void Hero_slide(Hero this)
{
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Slide");

	Hero_showDust(this, false);
}

static void Hero_showDust(Hero this, bool autoHideDust)
{
	ParticleSystem_start(this->feetDust);

	if(autoHideDust)
	{
		// stop the dust after some time
		MessageDispatcher_dispatchMessage(200, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroStopFeetDust, NULL);
	}
}

static void Hero_hideDust(Hero this)
{
	ParticleSystem_pause(this->feetDust);
}

// start movement
void Hero_stopAddingForce(Hero this)
{
	ASSERT(this, "Hero::stopMovement: null this");

	Velocity velocity = Body_getVelocity(this->body);

	this->keepAddingForce = false;

	// no input
//	this->inputDirection.x = 0;
//	this->inputDirection.y = 0;
//	this->inputDirection.z = 0;

	if(!(__Y_AXIS & Body_getMovementOnAllAxes(this->body)))
	{
		Hero_slide(this);
	}
	else if(!AnimatedEntity_isAnimationLoaded(__SAFE_CAST(AnimatedEntity, this), "Fall"))
	{
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Fall");
	}

	// begin to decelerate
	u16 axisOfDeacceleration = 0;
	axisOfDeacceleration |= velocity.x? __X_AXIS: 0;
	axisOfDeacceleration |= velocity.z? __Z_AXIS: 0;

	if(axisOfDeacceleration)
	{
		fix19_13 inputForce = HERO_INPUT_FORCE;
		fix19_13 xForce = __RIGHT == this->inputDirection.x ? inputForce : -inputForce;
		fix19_13 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		//Body_moveAccelerated(this->body, axisOfDeacceleration);
		Actor_addForce(__SAFE_CAST(Actor, this), &force);
	}
	else
	{
		Hero_stopMovingOnAxis(this, __X_AXIS | __Z_AXIS);
	}
}

// started moving over axis
void Hero_startedMovingOnAxis(Hero this, u16 axis)
{
	if(__Y_AXIS & axis)
	{
		Hero_hideDust(this);
		Hero_capVelocity(this, true);
	}

	// start movement
	if(__SAFE_CAST(State, HeroMoving_getInstance()) != StateMachine_getCurrentState(this->stateMachine))
	{
		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
		}
		else if(__Y_AXIS & axis)
		{
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Fall");
			Container_addChild(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), __SAFE_CAST(Container, this));
		}

		StateMachine_swapState(this->stateMachine, __SAFE_CAST(State,  HeroMoving_getInstance()));
	}
	else
	{
		bool movementState = Body_getMovementOnAllAxes(this->body);

		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;

			if(!(__Y_AXIS & movementState))
			{
				this->keepAddingForce = true;

				AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
			}
		}

		if(__Y_AXIS & axis)
		{
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Fall");
			Container_addChild(__SAFE_CAST(Container, Game_getStage(Game_getInstance())), __SAFE_CAST(Container, this));
		}

		if(__Z_AXIS & axis)
		{
			AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
		}
	}
}

// stop moving over axis
bool Hero_stopMovingOnAxis(Hero this, u16 axis)
{
	ASSERT(this, "Hero::stopMovingOnAxis: null this");


	// if being hit do nothing
	if(!Body_isActive(this->body))
	{
		return false;
	}

	bool movementState = Body_getMovementOnAllAxes(this->body);

	if((__X_AXIS & axis) && !(__Y_AXIS & movementState))
	{
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");

		Hero_hideDust(this);
	}

	if(__Y_AXIS & axis)
	{
		MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);

		Hero_lockCameraTriggerMovement(this, __Y_AXIS, true);

		this->jumps = 0;

		if(__X_AXIS & Body_getMovementOnAllAxes(this->body))
		{
			if(this->inputDirection.x)
			{
				AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");

				Hero_showDust(this, true);
			}
			else
			{
				Hero_slide(this);
			}
		}
	}

	if(__Z_AXIS & axis)
	{
		this->keepAddingForce = false;
		this->jumps = 0;
		StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));
		return true;
	}

	if(!movementState && __SAFE_CAST(State, HeroIdle_getInstance()) != StateMachine_getCurrentState(this->stateMachine))
	{
		this->keepAddingForce = false;
		this->jumps = 0;
		StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));
		return true;
	}

	return false;
}

// check direction
void Hero_checkDirection(Hero this, u32 pressedKey, char* animation)
{
	ASSERT(this, "Hero::checkDirection: null this");

	bool movementState = Body_getMovementOnAllAxes(this->body);
	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, this));

	Hero_hideDust(this);

	if(K_LR & pressedKey)
	{
		this->inputDirection.x = __RIGHT;

		VBVec3D position = *Container_getLocalPosition(__SAFE_CAST(Container, this->feetDust));
		position.x = abs(position.x) * -1;
		Container_setLocalPosition(__SAFE_CAST(Container, this->feetDust), &position);
	}
	else if(K_LL & pressedKey)
	{
		this->inputDirection.x = __LEFT;

		VBVec3D position = *Container_getLocalPosition(__SAFE_CAST(Container, this->feetDust));
		position.x = abs(position.x);
		Container_setLocalPosition(__SAFE_CAST(Container, this->feetDust), &position);
	}
	else if(K_LU & pressedKey)
	{
		this->inputDirection.z = __FAR;
	}
	else if(K_LD & pressedKey)
	{
		this->inputDirection.z = __NEAR;
	}

	if(direction.x != this->inputDirection.x)
	{
		Hero_lockCameraTriggerMovement(this, __X_AXIS, true);
	}

	if(animation && !(__Y_AXIS & movementState))
	{
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), animation);
	}
}

void Hero_lockCameraTriggerMovement(Hero this, u8 axisToLockUp, bool locked)
{
	if(this->cameraBoundingBox)
	{
		VBVec3DFlag overridePositionFlag = CameraTriggerEntity_getOverridePositionFlag(__SAFE_CAST(CameraTriggerEntity, this->cameraBoundingBox));

		VBVec3DFlag positionFlag = CustomScreenMovementManager_getPositionFlag(CustomScreenMovementManager_getInstance());

		if(__X_AXIS & axisToLockUp)
		{
			overridePositionFlag.x = locked;

			positionFlag.x = !locked;
		}

		CameraTriggerEntity_setOverridePositionFlag(__SAFE_CAST(CameraTriggerEntity, this->cameraBoundingBox), overridePositionFlag);
		CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager_getInstance(), positionFlag);
	}
}

void Hero_takeHitFrom(Hero this, Entity collidingEntity, Shape collidingShape, int energyToReduce, bool pause, bool invincibleWins, bool alignToEnemy)
{
#ifdef GOD_MODE
	return;
#endif

	if(!Hero_isInvincible(this) || !invincibleWins)
	{
		if(invincibleWins && ((this->energy - energyToReduce >= 0) || (this->powerUp != kPowerUpNone)))
		{
			Hero_setInvincible(this, true);

			// reset invincible a bit later
			MessageDispatcher_dispatchMessage(HERO_FLASH_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroStopInvincibility, NULL);

			// start flashing of hero
			MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroFlash);
			MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroFlash, NULL);

			// lose power-up or reduce energy
			if(this->powerUp != kPowerUpNone)
			{
				Hero_losePowerUp(this);
			}
			else
			{
				this->energy -= energyToReduce;
			}

			if(pause)
			{
				Actor_stopAllMovement(__SAFE_CAST(Actor, this));
				Game_disableKeypad(Game_getInstance());
				GameState_pausePhysics(Game_getCurrentState(Game_getInstance()), true);
				Body_setActive(this->body, false);
				GameState_pauseAnimations(Game_getCurrentState(Game_getInstance()), true);
				MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroResumePhysics, collidingEntity);
			}
		}
		else
		{
			Hero_setInvincible(this, true);
			this->energy = 0;
			Hero_flash(this);
			GameState_pausePhysics(Game_getCurrentState(Game_getInstance()), true);
			GameState_pauseAnimations(Game_getCurrentState(Game_getInstance()), true);
			Body_setActive(this->body, false);
			Entity_activateShapes(__SAFE_CAST(Entity, this), false);
			MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroDied, NULL);
		}

		// start short screen shake
		Screen_startEffect(Screen_getInstance(), kShake, 200);

		// play hit sound
		SoundManager_playFxSound(SoundManager_getInstance(), FIRE_SND, this->transform.globalPosition);

		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Hit");

		// inform others to update ui etc
		Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventHitTaken);
	}
}

// flash after being hit
void Hero_flash(Hero this)
{
	ASSERT(this, "Hero::flash: null this");

	// only flash as long as hero is invincible
	if(Hero_isInvincible(this))
	{
		// toggle between original and flash palette
		Hero_toggleFlashPalette(this);

		// next flash state change after HERO_FLASH_INTERVAL milliseconds
		MessageDispatcher_dispatchMessage(HERO_FLASH_INTERVAL, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroFlash, NULL);
	}
	else
	{
		// set palette back to original
		Hero_resetPalette(this);
	}
}

void Hero_toggleFlashPalette(Hero this)
{
	// get all of the hero's sprites and loop through them
	VirtualList sprites = Entity_getSprites(__SAFE_CAST(Entity, this));
	VirtualNode node = VirtualList_begin(sprites);
	for(; node; node = VirtualNode_getNext(node))
	{
		// get sprite's texture
		Sprite sprite = __SAFE_CAST(Sprite, VirtualNode_getData(node));
		Texture texture = Sprite_getTexture(sprite);

		// get original palette
		TextureDefinition* textureDefinition = Texture_getDefinition(texture);

		// set new palette
		if(Texture_getPalette(texture) == textureDefinition->palette)
		{
			Texture_setPalette(texture, HERO_FLASH_PALETTE);
		}
		else
		{
			Texture_setPalette(texture, textureDefinition->palette);
		}

		// rewrite sprite to bgmap to apply changed palette
		Sprite_rewrite(sprite);
	}
}

void Hero_resetPalette(Hero this)
{
	// get all of hero's sprites and loop through them
	VirtualList sprites = Entity_getSprites(__SAFE_CAST(Entity, this));
	VirtualNode node = VirtualList_begin(sprites);
	for(; node; node = VirtualNode_getNext(node))
	{
		// get sprite's texture
		Sprite sprite = __SAFE_CAST(Sprite, VirtualNode_getData(node));
		Texture texture = Sprite_getTexture(sprite);

		// get original palette and set it
		TextureDefinition* textureDefinition = Texture_getDefinition(texture);
		Texture_setPalette(texture, textureDefinition->palette);

		// rewrite sprite to bgmap to apply changed palette
		Sprite_rewrite(sprite);
	}
}

// set animation delta
void Hero_setAnimationDelta(Hero this, int delta __attribute__ ((unused)))
{
	ASSERT(this, "Hero::setAnimationDelta: null this");

	ASSERT(this->sprites, "Hero::setAnimationDelta: null sprites");

	VirtualNode node = VirtualList_begin(this->sprites);

	for(; node; node = VirtualNode_getNext(node))
	{
		Sprite_setFrameCycleDecrement(__SAFE_CAST(Sprite, VirtualNode_getData(node)), this->boost ? 2 : 1);
	}
}

// disable boost
void Hero_disableBoost(Hero this)
{
	ASSERT(this, "Hero::disableBoost: null this");

	if(this->boost)
	{
		this->boost = false;
		Hero_setAnimationDelta(this, -1);
	}
}

// enable boost
void Hero_enableBoost(Hero this)
{
	if(!this->boost)
	{
		this->boost = true;

		Hero_setAnimationDelta(this, -2);
	}
}

// get the door overlapped by the hero
Door Hero_getOverlappedDoor(Hero this)
{
	ASSERT(this, "Hero::getOverlappedDoor: null this");

	return this->currentlyOverlappedDoor;
}

void Hero_enterDoor(Hero this)
{
	ASSERT(this, "Hero::enterDoor: null this");

	if((__Y_AXIS | __Z_AXIS) & Body_getMovementOnAllAxes(this->body))
	{
		return;
	}

	// play animation
	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "WalkingBack");

	// move towards door
	/*
	Body_setAxisSubjectToGravity(this->body, 0);
	Velocity velocity = {0, 0, __I_TO_FIX19_13(8)};
	Body_moveUniformly(this->body, velocity);
	*/

	// inform the door entity
	if(this->currentlyOverlappedDoor != NULL)
	{
		MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this->currentlyOverlappedDoor), kHeroEnterDoor, NULL);
	}

	// hide hint immediately
	if(this->hint != NULL)
	{
		Entity_hide(__SAFE_CAST(Entity, this->hint));
	}

	// play door sound
	SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, this->transform.globalPosition);
}

static void Hero_addHint(Hero this)
{
	ASSERT(this, "Hero::addHints: null this");

	VBVec3D position = {0, 0, __F_TO_FIX19_13(-1)};

	// save the hint entity, so we can remove it later
	this->hint = Entity_addChildEntity(__SAFE_CAST(Entity, this), &HINT_MC, -1, "hint", &position, NULL);

	Hero_hideHint(this);
}

static void Hero_addFeetDust(Hero this)
{
	ASSERT(this, "Hero::addFeetDust: null this");

	VBVec3D position = {__F_TO_FIX19_13(-6), __F_TO_FIX19_13(10), __F_TO_FIX19_13(-2)};

	this->feetDust = __SAFE_CAST(ParticleSystem, Entity_addChildEntity(__SAFE_CAST(Entity, this), &DUST_PS, -1, "feetDust", &position, NULL));
	ASSERT(this->feetDust, "Hero::addFeetDust: null feetDust");

	ParticleSystem_spawnAllParticles(this->feetDust);
}

void Hero_showHint(Hero this, u32 hintType)
{
	ASSERT(this, "Hero::showHint: null this");
	ASSERT(this->hint, "Hero::showHint: null hint");

	Hint_open((Hint)this->hint, hintType);
}

void Hero_hideHint(Hero this)
{
	// check if a hint is being shown at the moment
	if(this->hint)
	{
		// play the closing animation
		Hint_close(__SAFE_CAST(Hint, this->hint));
	}
}

// make hero to look to the player
void Hero_lookFront(Hero this)
{
	// if not already playing
	if(!AnimatedEntity_isAnimationLoaded(__SAFE_CAST(AnimatedEntity, this), "Front"))
	{
		// play animation
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Front");
	}
}

// make hero to look away from the player
void Hero_lookBack(Hero this)
{
	// if not already playing
	if(!AnimatedEntity_isAnimationLoaded(__SAFE_CAST(AnimatedEntity, this), "Back"))
	{
		// play animation
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Back");
	}
}

// die hero
void Hero_die(Hero this)
{
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroFlash);

	Container_deleteMyself(__SAFE_CAST(Container, this));

	/*
	// go to dead state
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroDead_getInstance()));

	// must unregister the shape for collision detections
	Entity_activateShapes(__SAFE_CAST(Entity, this), false);

	// change in game state
	this->inGameState = kDead;
	*/
}

// process user input
static void Hero_onUserInput(Hero this, Object eventFirer __attribute__ ((unused)))
{
	UserInput userInput = PlatformerLevelState_getUserInput(PlatformerLevelState_getInstance());

	if(userInput.pressedKey)
	{
		__VIRTUAL_CALL(HeroState, onKeyPressed, StateMachine_getCurrentState(this->stateMachine), this, &userInput);
	}

	if(userInput.releasedKey)
	{
		__VIRTUAL_CALL(HeroState, onKeyReleased, StateMachine_getCurrentState(this->stateMachine), this, &userInput);
	}

	if(userInput.holdKey)
	{
		__VIRTUAL_CALL(HeroState, onKeyHold, StateMachine_getCurrentState(this->stateMachine), this, &userInput);
	}
}

// does the hero have a key?
bool Hero_hasKey(Hero this)
{
	return this->hasKey;
}

// collect a power-up
void Hero_collectPowerUp(Hero this, u8 powerUp)
{
	this->powerUp = powerUp;
	Hero_updateSprite(this);

	Actor_stopAllMovement(__SAFE_CAST(Actor, this));
	Game_disableKeypad(Game_getInstance());
	GameState_pausePhysics(Game_getCurrentState(Game_getInstance()), true);
	Body_setActive(this->body, false);

	AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Transition");
}

// lose a power-up
void Hero_losePowerUp(Hero this)
{
	this->powerUp = kPowerUpNone;
	Hero_updateSprite(this);
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventPowerUp);
}

// update sprite, e.g. after collecting a power-up
void Hero_updateSprite(Hero this)
{
	CharSet charSet = Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites))), true);

	CharSetDefinition* charSetDefinition = NULL;

	switch(this->powerUp)
	{
		case kPowerUpBandana:

			charSetDefinition = &HERO_BANDANA_CH;
			break;

		default:
		case kPowerUpNone:

			charSetDefinition = &HERO_CH;
			break;
	}

	CharSet_setCharSetDefinition(charSet, charSetDefinition);
	CharSet_rewrite(charSet);
}

// get current power-up
u8 Hero_getPowerUp(Hero this)
{
	return this->powerUp;
}

// get energy
u8 Hero_getEnergy(Hero this)
{
	return this->energy;
}

// set invincibility
void Hero_setInvincible(Hero this, bool invincible)
{
	this->invincible = invincible;
}

// get invincibility
bool Hero_isInvincible(Hero this)
{
	return this->invincible;
}

// process collisions
bool Hero_processCollision(Hero this, CollisionInformation collisionInformation)
{
	ASSERT(this, "Hero::processCollision: null this");
	ASSERT(collisionInformation.collidingShape, "Hero::processCollision: null collidingObjects");

	Shape collidingShape = collisionInformation.collidingShape;
	Entity collidingEntity = __SAFE_CAST(Entity, Shape_getOwner(collidingShape));

	switch(Entity_getInGameType(collidingEntity))
	{
		case kShape:
			break;

		case kCameraTarget:
			{
/*				if(collisionInformation.translationVector.y)
				{
					Hero_lockCameraTriggerMovement(this, __Y_AXIS, false);
				}

				if(collisionInformation.translationVector.x)
				{
					Hero_lockCameraTriggerMovement(this, __X_AXIS, false);
				}
				else
				{
					Hero_lockCameraTriggerMovement(this, __Y_AXIS, false);
				}
*/
				VBVec3D position = CAMERA_BOUNDING_BOX_DISPLACEMENT;

				__VIRTUAL_CALL(Container, setLocalPosition, this->cameraBoundingBox, &position);
			}
			break;

		case kCoin:

			MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingEntity), kItemTaken, NULL);
			break;

		case kKey:

			this->hasKey = true;
			MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingEntity), kItemTaken, NULL);
			break;

		case kBandana:

			Hero_collectPowerUp(this, kPowerUpBandana);
			MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingEntity), kItemTaken, NULL);
			break;

		case kHideLayer:

			// first contact with hide layer?
			if(!HideLayer_isOverlapping((HideLayer)collidingEntity))
			{
				HideLayer_setOverlapping((HideLayer)collidingEntity);
			}
			break;

		case kDoor:

			Door_onOverlapping((Door)collidingEntity);
			break;

		case kWaterPond:

			if(Body_getMovementOnAllAxes(this->body))
			{
				MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingEntity), kReactToCollision, NULL);
			}
			break;

		case kLava:

			Hero_takeHitFrom(this, NULL, NULL, this->energy, true, false, true);
			break;

		case kSawBlade:
		case kSnail:

			Hero_takeHitFrom(this, collidingEntity, collidingShape, 1, true, true, false);
			break;

		case kCannonBall:

			Hero_takeHitFrom(this, collidingEntity, collidingShape, 2, true, true, false);
			break;

		case kHit:

			Hero_takeHitFrom(this, collidingEntity, collidingShape, 1, true, true, false);
			break;

		case kLavaTrigger:

			MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingEntity), kLavaTriggerStart, NULL);
			Hero_stopAddingForce(this);
			//Hero_stopMovingOnAxis(this, __X_AXIS);
			break;

		case kMovingPlatform:
		case kTopShape:
			{
				// if hero's moving over the y axis or is above colliding entity
//				if((collisionInformation.translationVector.x) || (0 >= Body_getVelocity(this->body).y) || Hero_isBelow(this, collisionInformation.shape, collisionInformation.collidingShape))
				{
					// don't further process collision
					return true;
				}
			}
			break;
	}

	return Actor_processCollision(__SAFE_CAST(Actor, this), collisionInformation);
}

void Hero_capVelocity(Hero this, bool discardPreviousMessages)
{
	ASSERT(this, "Hero::checkCapVelocity: null this");

	if(discardPreviousMessages)
	{
		MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);
	}

	if(Body_isActive(this->body))
	{
		Velocity velocity = Body_getVelocity(this->body);

		if(velocity.y)
		{
			if(HERO_MAX_VELOCITY_Y < velocity.y && __UNIFORM_MOVEMENT != Body_getMovementType(this->body).y)
			{
				velocity.x = 0;
				velocity.y = HERO_MAX_VELOCITY_Y;
				velocity.z = 0;

				//Body_moveUniformly(this->body, velocity);
			}
			else if(0 < velocity.y)
			{
				MessageDispatcher_dispatchMessage(HERO_CHECK_Y_VELOCITY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckVelocity, NULL);
			}
		}
		else
		{
			MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckVelocity, NULL);
		}
	}
}

bool Hero_handleMessage(Hero this, Telegram telegram)
{
	ASSERT(this, "Hero::handleMessage: null this");

	// handle messages that any state would handle here
	switch(Telegram_getMessage(telegram))
	{
		case kHeroCheckVelocity:

			Hero_capVelocity(this, false);
			return true;
			break;

		case kHeroStartOverlapping:
		{
			Door door = __SAFE_CAST(Door, Telegram_getSender(telegram));

			this->currentlyOverlappedDoor = door;
			Hero_showHint(this, __VIRTUAL_CALL(Door, getHintType, door));
			return true;
			break;
		}
		case kHeroEndOverlapping:

			this->currentlyOverlappedDoor = NULL;
			Hero_hideHint(this);
			return true;
			break;

		case kHeroStopFeetDust:

			Hero_hideDust(this);
			return true;
			break;

		case kHeroStopInvincibility:

			Hero_setInvincible(this, false);
			return true;
			break;

		case kHeroFlash:

			Hero_flash(this);
			return true;
			break;

		case kHeroResumePhysics:

			Game_enableKeypad(Game_getInstance());
			GameState_pausePhysics(Game_getCurrentState(Game_getInstance()), false);
			GameState_pauseAnimations(Game_getCurrentState(Game_getInstance()), false);
			Body_setActive(this->body, true);

			Velocity velocity = Body_getVelocity(this->body);

			if(!velocity.y)
			{
				if(velocity.x)
				{
					AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
				}
				else
				{
					AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");
				}
			}
			else if(velocity.x)
			{
				AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
			}
			else
			{
				AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");
			}

			break;

		case kHeroDied:

			Hero_die(this);
			break;

		case kBodyStopped:

			if(-1 == this->jumps)
			{
				return true;
			}
			break;
	}

	return Actor_handleMessage(__SAFE_CAST(Actor, this), telegram);
}

// process message
bool Hero_handlePropagatedMessage(Hero this, int message)
{
	ASSERT(this, "Hero::handlePropagatedMessage: null this");

	switch(message)
	{
		case kLevelSetUp:
			{
				// set camera
				VBVec3D cameraBoundingBoxPosition = CAMERA_BOUNDING_BOX_DISPLACEMENT;
				this->cameraBoundingBox = Entity_addChildEntity(__SAFE_CAST(Entity, this), (EntityDefinition*)&CAMERA_BOUNDING_BOX_IG, 0, NULL, &cameraBoundingBoxPosition, NULL);
				//CollisionManager_shapeStartedMoving(Game_getCollisionManager(Game_getInstance()), Entity_getShape(__SAFE_CAST(Entity, this->cameraBoundingBox)));

				Hero_lockCameraTriggerMovement(this, __X_AXIS | __Y_AXIS, true);
			}

			//Hero_locateOverNextFloor(this);

			break;

		case kLevelStarted:
			{
				VBVec3DFlag positionFlag = {true, true, true};
				CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager_getInstance(), positionFlag);
			}
			break;

	}

	return false;
}

void Hero_getOutOfDoor(Hero this, VBVec3D* outOfDoorPosition)
{
	ASSERT(this, "Hero::setPosition: null this");

	// stop all movement
	Actor_stopAllMovement(__SAFE_CAST(Actor, this));

	// set new position
	Actor_setPosition(__SAFE_CAST(Actor, this), outOfDoorPosition);

	// must make sure that collision detection is reset
//	Actor_resetCollisionStatus(__SAFE_CAST(Actor, this));

	// make the camera active for collision detection
	Hero_lockCameraTriggerMovement(this, __X_AXIS | __Y_AXIS, false);

	Entity_informShapesThatStartedMoving(__SAFE_CAST(Entity, this));

	Container_invalidateGlobalTransformation(__SAFE_CAST(Container, this));

	Body_setAxisSubjectToGravity(this->body, __Y_AXIS);

}

void Hero_suspend(Hero this)
{
	ASSERT(this, "Hero::suspend: null this");

	__CALL_BASE_METHOD(Actor, suspend, this);

	ParticleSystem_pause(this->feetDust);
}

void Hero_resume(Hero this)
{
	ASSERT(this, "Hero::resume: null this");

	__CALL_BASE_METHOD(Actor, resume, this);

	Screen_focus(Screen_getInstance(), false);

	Hero_lockCameraTriggerMovement(this, __X_AXIS | __Y_AXIS, true);

	VBVec3DFlag positionFlag = {true, true, true};
	CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager_getInstance(), positionFlag);

	Hero_updateSprite(this);
}

u16 Hero_getAxesForBouncing(Hero this __attribute__ ((unused)))
{
	ASSERT(this, "Hero::getAxesForBouncing: null this");

	return __Y_AXIS;
}

bool Hero_isBelow(Hero this, Shape shape, Shape collidingShape)
{
	ASSERT(this, "Hero::isAboveEntity: null this");

	RightBox shapeRightBox = __VIRTUAL_CALL(Shape, getSurroundingRightBox, shape);
	RightBox collidingShapeRightBox = __VIRTUAL_CALL(Shape, getSurroundingRightBox, collidingShape);

	VBVec3D shapePosition = __VIRTUAL_CALL(Shape, getPosition, shape);

	fix19_13 heroBottomPosition = shapePosition.y + ((shapeRightBox.x1 - shapeRightBox.x0) >> 1) - Body_getLastDisplacement(this->body).y;

	return heroBottomPosition > collidingShapeRightBox.y0;
}

void Hero_collisionsProcessingDone(Hero this, const CollisionInformation* collisionInformation)
{
	ASSERT(this, "Hero::collisionsProcessingDone: null this");

	if(collisionInformation->collidingShape)
	{
		Shape collidingShape = collisionInformation->collidingShape;
		Entity collidingEntity = __SAFE_CAST(Entity, Shape_getOwner(collidingShape));

		switch(Entity_getInGameType(collidingEntity))
		{
			case kMovingPlatform:

				Container_addChild(__SAFE_CAST(Container, collidingEntity), __SAFE_CAST(Container, this));
				break;
		}
	}
}

u16 Hero_getAxisForFlipping(Hero this __attribute__ ((unused)))
{
	return __X_AXIS;
}

void Hero_onPowerUpTransitionComplete(Hero this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Hero::onPowerUpTransitionComplete: null this");

	MessageDispatcher_dispatchMessage(300, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroResumePhysics, NULL);
}

bool Hero_isAffectedByRelativity(Hero this __attribute__ ((unused)))
{
	ASSERT(this, "Hero::isAffectedByRelativity: null this");

	return true;
}

void Hero_syncRotationWithBody(Hero this)
{
	ASSERT(this, "Hero::syncRotationWithBody: null this");

	if(__X_AXIS & Body_getMovementOnAllAxes(this->body))
	{
		Velocity velocity = Body_getVelocity(this->body);

		Direction direction =
		{
			__RIGHT, __DOWN, __FAR
		};

		if(0 > velocity.x)
		{
			direction.x = __LEFT;
		}

		Entity_setDirection(__SAFE_CAST(Entity, this), direction);
	}
}
