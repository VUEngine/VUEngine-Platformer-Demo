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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Camera.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <KeypadManager.h>
#include "Hero.h"
#include "states/HeroIdle.h"
#include "states/HeroMoving.h"
#include <CustomCameraMovementManager.h>
#include <CustomCameraEffectManager.h>
#include <CameraTriggerEntity.h>
#include <EventManager.h>
#include <Hint.h>
#include <SoundManager.h>
#include <debugConfig.h>
#include <gameDebugConfig.h>
#include <HideLayer.h>


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

static void Hero::onUserInput(Hero this, Object eventFirer);
void Hero::enterDoor(Hero this);
void Hero::hideHint(Hero this);
void Hero::updateSprite(Hero this);
static void Hero::addHint(Hero this);
static void Hero::addFeetDust(Hero this);
static void Hero::slide(Hero this);
static void Hero::showDust(Hero this, bool autoHideDust);
static void Hero::hideDust(Hero this);
void Hero::losePowerUp(Hero this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// Only one instance
Hero hero = NULL;

// there can only be one hero instantiated
Hero Hero::getInstance()
{
	return hero;
}

void Hero::setInstance(Hero instance)
{
	ASSERT(!hero, "Hero::setInstance: already instantiated");

	hero = instance;
}

// class's constructor
void Hero::constructor(Hero this, HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Hero::constructor: null this");

	// construct base
	Base::constructor((ActorDefinition*)heroDefinition, id, internalId, name);

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
	this->underWater = false;

	Hero::setInstance(this);

	Object::addEventListener(__SAFE_CAST(Object, PlatformerLevelState::getInstance()), __SAFE_CAST(Object, this), (EventListener)Hero::onUserInput, kEventUserInput);

	this->inputDirection = Entity::getDirection(__SAFE_CAST(Entity, this));
}

// class's destructor
void Hero::destructor(Hero this)
{
	ASSERT(this, "Hero::destructor: null this");
	ASSERT(hero, "Hero::destructor: already deleted");
	ASSERT(hero == this, "Hero::destructor: more than one instance");

	// remove event listeners
	Object::removeEventListener(__SAFE_CAST(Object, PlatformerLevelState::getInstance()), __SAFE_CAST(Object, this), (EventListener)Hero::onUserInput, kEventUserInput);

	// announce my dead
	Object::fireEvent(__SAFE_CAST(Object, EventManager::getInstance()), kEventHeroDied);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kHeroFlash);

	// free the instance pointers
	this->feetDust = NULL;
	this->hint = NULL;
	this->cameraBoundingBox = NULL;
	hero = NULL;

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Hero::ready(Hero this, bool recursive)
{
	ASSERT(this, "Hero::ready: null this");

	Entity::informShapesThatStartedMoving(__SAFE_CAST(Entity, this));

	// call base
	Base::ready(this, recursive);

	// override with progress from progress manager
	ProgressManager progressManager = ProgressManager::getInstance();
	if(progressManager)
	{
		this->energy = ProgressManager::getHeroCurrentEnergy(progressManager);

		u8 currentPowerUp = ProgressManager::getHeroCurrentPowerUp(progressManager);
		if(currentPowerUp != this->powerUp)
		{
			this->powerUp = currentPowerUp;
			Hero::updateSprite(this);
		}

		this->hasKey = ProgressManager::heroHasKey(ProgressManager::getInstance());
	}

	// initialize me as idle
	StateMachine::swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle::getInstance()));

	Hero::addHint(this);
	Hero::addFeetDust(this);
}

void Hero::locateOverNextFloor(Hero this __attribute__ ((unused)))
{
/*	Vector3D direction = {0, 1, 0};

	SpatialObject collidingSpatialObject = CollisionManager::searchNextObjectOfCollision(Game::getCollisionManager(Game::getInstance()), this->shape, direction);
	ASSERT(collidingSpatialObject, "Hero::locateOverNextFloor: null collidingSpatialObject");

	if(collidingSpatialObject)
	{
		Vector3D displacement =
		{
			__I_TO_FIX10_6(0),
			__1I_FIX10_6,
			__I_TO_FIX10_6(0),
		};

		Shape::resolveCollision(this->shape, VirtualList::front(this->shapes), collidingShapesToRemove, displacement, true);
	}
	*/
}

// make him jump
void Hero::jump(Hero this, bool checkIfYMovement)
{
	ASSERT(this, "Hero::jump: null this");

	if(this->body)
	{
		// determine the maximum number of possible jumps before reaching ground again
		s8 allowedNumberOfJumps = this->underWater ? 127 : (this->powerUp == kPowerUpBandana) ? 2 : 1;

#ifdef GOD_MODE
	allowedNumberOfJumps = 127;
#endif

		// check if more jumps are allowed
		if(this->jumps < allowedNumberOfJumps)
		{
			// init a force to add to the hero's momentum
			Force force = {0, 0, 0};

			fix10_6 yBouncingPlaneNormal = Body::getLastNormalDirection(this->body).y;

			yBouncingPlaneNormal = yBouncingPlaneNormal ? yBouncingPlaneNormal : -__1I_FIX10_6;

			// is this the first jump from ground or a double jump from mid-air?
			if(this->jumps == 0)
			{
				// don't allow a first jump from mid-air without bandana
				if(checkIfYMovement && 0 < yBouncingPlaneNormal && (allowedNumberOfJumps == 1))
				{
					return;
				}

				// set first jump performed
				this->jumps = 1;

				// we're leaving ground with this jump
				//Hero::startedMovingOnAxis(this, __Y_AXIS);

				// add more force when running, normal force otherwise
				force.y = __FIX10_6_MULT(__ABS(yBouncingPlaneNormal), this->boost ? HERO_BOOST_JUMP_INPUT_FORCE : HERO_NORMAL_JUMP_INPUT_FORCE);

				// add the force to actually make the hero jump
				Actor::addForce(__SAFE_CAST(Actor, this), &force);
			}
			else
			{
				// hack to avoid the processing of kBodyStopped message triggered by the call to Actor::stopMovement
				this->jumps = -1;

				// stop movement to gain full momentum of the jump force that will be added
				Actor::stopMovement(__SAFE_CAST(Actor, this), __Y_AXIS);

				// set second jump performed
				this->jumps = 2;

				// double jumps can never have boost
				force.y = HERO_NORMAL_JUMP_INPUT_FORCE;

				// add the force to actually make the hero jump
				Actor::addForce(__SAFE_CAST(Actor, this), &force);

				// show dust
				Hero::showDust(this, true);
			}

			// play jump animation
			AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Jump");

			// play jump sound
			SoundManager::playFxSound(SoundManager::getInstance(), JUMP_SND, this->transformation.globalPosition);
		}
	}
}

// keep movement
void Hero::addForce(Hero this, u16 axis, bool enableAddingForce)
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

	fix10_6 maxVelocity = this->boost ? HERO_BOOST_VELOCITY_X : HERO_MAX_VELOCITY_X;

	maxVelocity = this->underWater ? maxVelocity >> 1: maxVelocity;

	Velocity velocity = Body::getVelocity(this->body);

	Direction direction = Entity::getDirection(__SAFE_CAST(Entity, this));

	if(direction.x != this->inputDirection.x ||
		((__X_AXIS & axis) && maxVelocity > __ABS(velocity.x)) ||
		((__Z_AXIS & axis) && maxVelocity > __ABS(velocity.z)) ||
		Actor::hasChangedDirection(__SAFE_CAST(Actor, this), __X_AXIS) ||
		Actor::hasChangedDirection(__SAFE_CAST(Actor, this), __Z_AXIS))
	{
		fix10_6 inputForce = !Body::getNormal(this->body).y ? HERO_X_INPUT_FORCE_WHILE_JUMPING : HERO_INPUT_FORCE;
		fix10_6 xForce = (__X_AXIS & axis) ? __RIGHT == this->inputDirection.x ? inputForce : -inputForce : 0;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		Actor::addForce(__SAFE_CAST(Actor, this), &force);
	}
	else
	{
		if(__UNIFORM_MOVEMENT != Body::getMovementType(this->body).x || (__ABS(velocity.x) > maxVelocity && !(__Y_AXIS & Body::getMovementOnAllAxes(this->body))))
		{
			Velocity newVelocity =
			{
				(__X_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.x) : 0,
				0,
				(__Z_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.z) : 0,
			};

			Body::moveUniformly(this->body, newVelocity);
		}
	}
}

static void Hero::slide(Hero this)
{
	AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Slide");

	Hero::showDust(this, false);
}

static void Hero::showDust(Hero this, bool autoHideDust)
{
	if(this->feetDust)
	{
		ParticleSystem::start(this->feetDust);
	}

	if(autoHideDust)
	{
		// stop the dust after some time
		MessageDispatcher::dispatchMessage(200, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroStopFeetDust, NULL);
	}
}

static void Hero::hideDust(Hero this)
{
	if(this->feetDust)
	{
		ParticleSystem::pause(this->feetDust);
	}
}

// start movement
void Hero::stopAddingForce(Hero this)
{
	ASSERT(this, "Hero::stopMovement: null this");

	Velocity velocity = Body::getVelocity(this->body);

	this->keepAddingForce = false;

	// no input
//	this->inputDirection.x = 0;
//	this->inputDirection.y = 0;
//	this->inputDirection.z = 0;

	// if walking over something
	if(0 > Body::getNormal(this->body).y)
	{
		Hero::slide(this);
	}

	// begin to decelerate
	u16 axisOfDeacceleration = 0;
	axisOfDeacceleration |= velocity.x? __X_AXIS: 0;
	axisOfDeacceleration |= velocity.z? __Z_AXIS: 0;

	if(axisOfDeacceleration)
	{
		fix10_6 inputForce = HERO_FORCE_FOR_STOPPING;
		fix10_6 xForce = __RIGHT == this->inputDirection.x ? inputForce : -inputForce;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		Force force =
		{
			xForce,
			0,
			zForce
		};

		Actor::addForce(__SAFE_CAST(Actor, this), &force);
	}
	else
	{
		Hero::stopMovingOnAxis(this, __X_AXIS | __Z_AXIS);
	}
}

// started moving over axis
void Hero::startedMovingOnAxis(Hero this, u16 axis)
{
	if(__Y_AXIS & axis)
	{
		Hero::hideDust(this);
		Hero::capVelocity(this, true);
	}

	// start movement
	if(__SAFE_CAST(State, HeroMoving::getInstance()) != StateMachine::getCurrentState(this->stateMachine))
	{
		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;
			AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
		}

		StateMachine::swapState(this->stateMachine, __SAFE_CAST(State,  HeroMoving::getInstance()));
	}
	else
	{
		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;
		}
	}
}

// stop moving over axis
bool Hero::stopMovingOnAxis(Hero this, u16 axis)
{
	ASSERT(this, "Hero::stopMovingOnAxis: null this");

	// if being hit do nothing
	if(!Body::isActive(this->body))
	{
		return false;
	}

	bool movementState = Body::getMovementOnAllAxes(this->body);

	if((__X_AXIS & axis) && !(__Y_AXIS & movementState))
	{
		AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");

		Hero::hideDust(this);
	}

	// if there is something below
	if(0 > Body::getNormal(this->body).y)
	{
		if(__Y_AXIS & axis)
		{
			MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);

			Hero::lockCameraTriggerMovement(this, __Y_AXIS, true);

			this->jumps = 0;

			if(Body::getVelocity(this->body).x)
			{
				if(this->inputDirection.x)
				{
					AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");

					Hero::showDust(this, true);
				}
				else
				{
					Hero::slide(this);
				}
			}
		}

		if(__Z_AXIS & axis)
		{
			this->keepAddingForce = false;
			this->jumps = 0;
			StateMachine::swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle::getInstance()));
			return true;
		}

		if(!movementState && __SAFE_CAST(State, HeroIdle::getInstance()) != StateMachine::getCurrentState(this->stateMachine))
		{
			this->keepAddingForce = false;
			this->jumps = 0;
			StateMachine::swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle::getInstance()));
			return true;
		}
		else
		{
			// make sure that hitting the floor doesn't slow me down because of the friction
			if(__UNIFORM_MOVEMENT == Body::getMovementType(this->body).x)
			{
				fix10_6 maxVelocity = HERO_BOOST_VELOCITY_X;

				Velocity newVelocity =
				{
					(int)maxVelocity * this->inputDirection.x,
					0,
					0,
				};

				Body::moveUniformly(this->body, newVelocity);
			}

			AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
		}
	}
	else
	{
		AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Fall");
	}

	return false;
}

// check direction
void Hero::checkDirection(Hero this, u32 pressedKey, char* animation)
{
	ASSERT(this, "Hero::checkDirection: null this");

	bool movementState = Body::getMovementOnAllAxes(this->body);
	Direction direction = Entity::getDirection(__SAFE_CAST(Entity, this));

	Hero::hideDust(this);

	if(K_LR & pressedKey)
	{
		this->inputDirection.x = __RIGHT;

		if(this->feetDust)
		{
			Vector3D position = *Container::getLocalPosition(__SAFE_CAST(Container, this->feetDust));
			position.x = __ABS(position.x) * -1;
			Container::setLocalPosition(__SAFE_CAST(Container, this->feetDust), &position);
		}
	}
	else if(K_LL & pressedKey)
	{
		this->inputDirection.x = __LEFT;

		if(this->feetDust)
		{
			Vector3D position = *Container::getLocalPosition(__SAFE_CAST(Container, this->feetDust));
			position.x = __ABS(position.x);
			Container::setLocalPosition(__SAFE_CAST(Container, this->feetDust), &position);
		}
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
		Hero::lockCameraTriggerMovement(this, __X_AXIS, true);
	}

	if(animation && !(__Y_AXIS & movementState))
	{
		AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), animation);
	}
}

void Hero::lockCameraTriggerMovement(Hero this, u8 axisToLockUp, bool locked)
{
	if(this->cameraBoundingBox)
	{
		Vector3DFlag overridePositionFlag = CameraTriggerEntity::getOverridePositionFlag(__SAFE_CAST(CameraTriggerEntity, this->cameraBoundingBox));

		Vector3DFlag positionFlag = CustomCameraMovementManager::getPositionFlag(CustomCameraMovementManager::getInstance());

		if(__X_AXIS & axisToLockUp)
		{
			overridePositionFlag.x = locked;

			positionFlag.x = !locked;
		}

		if(__Y_AXIS & axisToLockUp)
		{
			overridePositionFlag.y = locked;
		}

		CameraTriggerEntity::setOverridePositionFlag(__SAFE_CAST(CameraTriggerEntity, this->cameraBoundingBox), overridePositionFlag);
		CustomCameraMovementManager::setPositionFlag(CustomCameraMovementManager::getInstance(), positionFlag);
	}
}

void Hero::takeHitFrom(Hero this, SpatialObject collidingObject, int energyToReduce, bool pause, bool invincibleWins)
{
#ifdef GOD_MODE
	return;
#endif

	if(!Hero::isInvincible(this) || !invincibleWins)
	{
		if(invincibleWins && ((this->energy - energyToReduce >= 0) || (this->powerUp != kPowerUpNone)))
		{
			Hero::setInvincible(this, true);

			// reset invincible a bit later
			MessageDispatcher::dispatchMessage(HERO_FLASH_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroStopInvincibility, NULL);

			// start flashing of hero
			MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kHeroFlash);
			MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroFlash, NULL);

			// lose power-up or reduce energy
			if(this->powerUp != kPowerUpNone)
			{
				Hero::losePowerUp(this);
			}
			else
			{
				this->energy -= energyToReduce;
			}

			if(pause)
			{
				Actor::stopAllMovement(__SAFE_CAST(Actor, this));
				Game::disableKeypad(Game::getInstance());
				GameState::pausePhysics(Game::getCurrentState(Game::getInstance()), true);
				//GameState::pauseAnimations(Game::getCurrentState(Game::getInstance()), true);
				MessageDispatcher::dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroResumePhysics, collidingObject);
			}
		}
		else
		{
			Game::disableKeypad(Game::getInstance());
			Hero::setInvincible(this, true);
			this->energy = 0;
			Hero::flash(this);
			GameState::pausePhysics(Game::getCurrentState(Game::getInstance()), true);
			GameState::pauseAnimations(Game::getCurrentState(Game::getInstance()), true);
			Entity::activateShapes(__SAFE_CAST(Entity, this), false);
			MessageDispatcher::dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroDied, NULL);
		}

		// start short screen shake
		Camera::startEffect(Camera::getInstance(), kShake, 200);

		// play hit sound
		SoundManager::playFxSound(SoundManager::getInstance(), FIRE_SND, this->transformation.globalPosition);

		AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Hit");

		// inform others to update ui etc
		Object::fireEvent(__SAFE_CAST(Object, EventManager::getInstance()), kEventHitTaken);
	}
}

// flash after being hit
void Hero::flash(Hero this)
{
	ASSERT(this, "Hero::flash: null this");

	// only flash as long as hero is invincible
	if(Hero::isInvincible(this))
	{
		// toggle between original and flash palette
		Hero::toggleFlashPalette(this);

		// next flash state change after HERO_FLASH_INTERVAL milliseconds
		MessageDispatcher::dispatchMessage(HERO_FLASH_INTERVAL, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroFlash, NULL);
	}
	else
	{
		// set palette back to original
		Hero::resetPalette(this);
	}
}

void Hero::toggleFlashPalette(Hero this)
{
	// get all of the hero's sprites and loop through them
	VirtualList sprites = Entity::getSprites(__SAFE_CAST(Entity, this));
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		// get sprite's texture
		Sprite sprite = __SAFE_CAST(Sprite, VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		// get original palette
		TextureDefinition* textureDefinition = Texture::getDefinition(texture);

		// set new palette
		if(Texture::getPalette(texture) == textureDefinition->palette)
		{
			Texture::setPalette(texture, HERO_FLASH_PALETTE);
		}
		else
		{
			Texture::setPalette(texture, textureDefinition->palette);
		}

		// rewrite sprite to bgmap to apply changed palette
		Sprite::rewrite(sprite);
	}
}

void Hero::resetPalette(Hero this)
{
	// get all of hero's sprites and loop through them
	VirtualList sprites = Entity::getSprites(__SAFE_CAST(Entity, this));
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		// get sprite's texture
		Sprite sprite = __SAFE_CAST(Sprite, VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		// get original palette and set it
		TextureDefinition* textureDefinition = Texture::getDefinition(texture);
		Texture::setPalette(texture, textureDefinition->palette);

		// rewrite sprite to bgmap to apply changed palette
		Sprite::rewrite(sprite);
	}
}

// set animation delta
void Hero::setAnimationDelta(Hero this, int delta __attribute__ ((unused)))
{
	ASSERT(this, "Hero::setAnimationDelta: null this");

	ASSERT(this->sprites, "Hero::setAnimationDelta: null sprites");

	VirtualNode node = VirtualList::begin(this->sprites);

	for(; node; node = VirtualNode::getNext(node))
	{
		Sprite::setFrameCycleDecrement(__SAFE_CAST(Sprite, VirtualNode::getData(node)), this->boost ? 2 : 1);
	}
}

// disable boost
void Hero::disableBoost(Hero this)
{
	ASSERT(this, "Hero::disableBoost: null this");

	if(this->boost)
	{
		this->boost = false;
		Hero::setAnimationDelta(this, -1);
	}
}

// enable boost
void Hero::enableBoost(Hero this)
{
	if(!this->boost)
	{
		this->boost = true;

		Hero::setAnimationDelta(this, -2);
	}
}

// get the door overlapped by the hero
Door Hero::getOverlappedDoor(Hero this)
{
	ASSERT(this, "Hero::getOverlappedDoor: null this");

	return this->currentlyOverlappedDoor;
}

void Hero::enterDoor(Hero this)
{
	ASSERT(this, "Hero::enterDoor: null this");

	if((__Y_AXIS | __Z_AXIS) & Body::getMovementOnAllAxes(this->body))
	{
		return;
	}

	// play animation
	AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "WalkingBack");

	// move towards door
	/*
	Body::setAxesSubjectToGravity(this->body, 0);
	Velocity velocity = {0, 0, __I_TO_FIX10_6(8)};
	Body::moveUniformly(this->body, velocity);
	*/

	// inform the door entity
	if(this->currentlyOverlappedDoor)
	{
		MessageDispatcher::dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this->currentlyOverlappedDoor), kHeroEnterDoor, NULL);
	}

	// hide hint immediately
	if(this->hint != NULL)
	{
		Entity::hide(__SAFE_CAST(Entity, this->hint));
	}

	// play door sound
	SoundManager::playFxSound(SoundManager::getInstance(), COLLECT_SND, this->transformation.globalPosition);
}

static void Hero::addHint(Hero this)
{
	ASSERT(this, "Hero::addHints: null this");

	Vector3D position = {0, 0, __PIXELS_TO_METERS(-1)};

	// save the hint entity, so we can remove it later
	this->hint = Entity::addChildEntity(__SAFE_CAST(Entity, this), &HINT_MC, -1, "hint", &position, NULL);

	Hero::hideHint(this);
}

static void Hero::addFeetDust(Hero this)
{
	ASSERT(this, "Hero::addFeetDust: null this");

	Vector3D position = {__PIXELS_TO_METERS(-8), __PIXELS_TO_METERS(10), __PIXELS_TO_METERS(12)};

	this->feetDust = __SAFE_CAST(ParticleSystem, Entity::addChildEntity(__SAFE_CAST(Entity, this), &DUST_PS, -1, "feetDust", &position, NULL));
	ASSERT(this->feetDust, "Hero::addFeetDust: null feetDust");

	ParticleSystem::spawnAllParticles(this->feetDust);
}

void Hero::showHint(Hero this, u32 hintType)
{
	ASSERT(this, "Hero::showHint: null this");
	ASSERT(this->hint, "Hero::showHint: null hint");

	Hint::open((Hint)this->hint, hintType);
}

void Hero::hideHint(Hero this)
{
	// check if a hint is being shown at the moment
	if(this->hint)
	{
		// play the closing animation
		Hint::close(__SAFE_CAST(Hint, this->hint));
	}
}

// make hero to look to the player
void Hero::lookFront(Hero this)
{
	// if not already playing
	if(!AnimatedEntity::isAnimationLoaded(__SAFE_CAST(AnimatedEntity, this), "Front"))
	{
		// play animation
		AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Front");
	}
}

// make hero to look away from the player
void Hero::lookBack(Hero this)
{
	// if not already playing
	if(!AnimatedEntity::isAnimationLoaded(__SAFE_CAST(AnimatedEntity, this), "Back"))
	{
		// play animation
		AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Back");
	}
}

// die hero
void Hero::die(Hero this)
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kHeroFlash);

	Container::deleteMyself(__SAFE_CAST(Container, this));

	/*
	// go to dead state
	StateMachine::swapState(this->stateMachine, __SAFE_CAST(State, HeroDead::getInstance()));

	// must unregister the shape for collision detections
	Entity::activateShapes(__SAFE_CAST(Entity, this), false);

	// change in game state
	this->inGameState = kDead;
	*/
}

// process user input
static void Hero::onUserInput(Hero this, Object eventFirer __attribute__ ((unused)))
{
	UserInput userInput = PlatformerLevelState::getUserInput(PlatformerLevelState::getInstance());

	HeroState currentState = __SAFE_CAST(HeroState, StateMachine::getCurrentState(this->stateMachine));

	if(userInput.pressedKey)
	{
		HeroState::onKeyPressed(currentState, this, &userInput);
	}

	if(userInput.releasedKey)
	{
		HeroState::onKeyReleased(currentState, this, &userInput);
	}

	if(userInput.holdKey)
	{
		HeroState::onKeyHold(currentState, this, &userInput);
	}
}

// does the hero have a key?
bool Hero::hasKey(Hero this)
{
	return this->hasKey;
}

// collect a power-up
void Hero::collectPowerUp(Hero this, u8 powerUp)
{
	this->powerUp = powerUp;
	this->keepAddingForce = false;

	Hero::updateSprite(this);

	Actor::stopAllMovement(__SAFE_CAST(Actor, this));
	Game::disableKeypad(Game::getInstance());
	GameState::pausePhysics(Game::getCurrentState(Game::getInstance()), true);

	AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Transition");
}

// lose a power-up
void Hero::losePowerUp(Hero this)
{
	this->powerUp = kPowerUpNone;
	Hero::updateSprite(this);
	Object::fireEvent(__SAFE_CAST(Object, EventManager::getInstance()), kEventPowerUp);
}

// update sprite, e.g. after collecting a power-up
void Hero::updateSprite(Hero this)
{
	CharSet charSet = Texture::getCharSet(Sprite::getTexture(__SAFE_CAST(Sprite, VirtualList::front(this->sprites))), true);

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

	CharSet::setCharSetDefinition(charSet, charSetDefinition);
	CharSet::rewrite(charSet);
}

// get current power-up
u8 Hero::getPowerUp(Hero this)
{
	return this->powerUp;
}

// get energy
u8 Hero::getEnergy(Hero this)
{
	return this->energy;
}

// set invincibility
void Hero::setInvincible(Hero this, bool invincible)
{
	this->invincible = invincible;
}

// get invincibility
bool Hero::isInvincible(Hero this)
{
	return this->invincible;
}

fix10_6 Hero::getFrictionOnCollision(Hero this, SpatialObject collidingObject, const Vector3D* collidingObjectNormal)
{
	// ignore friction on y axis
	if(collidingObjectNormal->x && !collidingObjectNormal->y)
	{
		return 0;
	}

	return Base::getFrictionOnCollision(__SAFE_CAST(Actor, this), collidingObject, collidingObjectNormal);
}

// process collisions
bool Hero::enterCollision(Hero this, const CollisionInformation* collisionInformation)
{
	ASSERT(this, "Hero::enterCollision: null this");
	ASSERT(collisionInformation->collidingShape, "Hero::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		// speed things up by breaking early
		case kShape:
			break;

		case kCameraTarget:
			{
				if(collisionInformation->solutionVector.direction.y)
				{
					Hero::lockCameraTriggerMovement(this, __Y_AXIS, false);
				}

				if(collisionInformation->solutionVector.direction.x)
				{
					Hero::lockCameraTriggerMovement(this, __X_AXIS, false);
				}
				else
				{
					Hero::lockCameraTriggerMovement(this, __Y_AXIS, false);
				}

				Vector3D position = CAMERA_BOUNDING_BOX_DISPLACEMENT;

				Container::setLocalPosition(this->cameraBoundingBox, &position);
			}
			return false;
			break;

		case kCoin:

			MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingObject), kItemTaken, NULL);
			return false;
			break;

		case kKey:

			this->hasKey = true;
			MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingObject), kItemTaken, NULL);
			return false;
			break;

		case kBandana:

			Hero::collectPowerUp(this, kPowerUpBandana);
			MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingObject), kItemTaken, NULL);
			return false;
			break;

		case kHideLayer:

			// first contact with hide layer?
			HideLayer::setOverlapping((HideLayer)collidingObject);
			return false;
			break;

		case kDoor:
			{
				Door door = __SAFE_CAST(Door, collidingObject);
				Hero::showHint(this, Door::getHintType(door));
				Door::setOverlapping(door);
				this->currentlyOverlappedDoor = door;
			}
			return false;
			break;

		case kWaterPond:

			if(Body::getMovementOnAllAxes(this->body))
			{
				this->underWater = true;

				MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingObject), kReactToCollision, NULL);

				Body::setSurroundingFrictionCoefficient(this->body, Actor::getSurroundingFrictionCoefficient(__SAFE_CAST(Actor, this)) + SpatialObject::getFrictionCoefficient(collidingObject));
			}
			return true;
			break;

		case kLava:

			Hero::takeHitFrom(this, NULL, this->energy, true, false);
			return false;
			break;

		case kSawBlade:
		case kSnail:

			Hero::takeHitFrom(this, collidingObject, 1, true, true);
			return false;
			break;

		case kCannonBall:

			Hero::takeHitFrom(this, collidingObject, 2, true, true);
			return false;
			break;

		case kHit:

			Hero::takeHitFrom(this, collidingObject, 1, true, true);
			return false;
			break;

		case kLavaTrigger:

			MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingObject), kLavaTriggerStart, NULL);
			Hero::stopAddingForce(this);
			return false;
			break;

		case kMovingPlatform:
		case kTopShape:
			{
				if((0 > Body::getVelocity(this->body).y) || Hero::isBelow(this, collisionInformation->shape, collisionInformation))
				{
					// don't further process collision
					return false;
				}
			}
			break;
	}

	return Base::enterCollision(__SAFE_CAST(Actor, this), collisionInformation) && (__ABS(collisionInformation->solutionVector.direction.y) > __ABS(collisionInformation->solutionVector.direction.x));
}

// process collisions
bool Hero::updateCollision(Hero this, const CollisionInformation* collisionInformation)
{
	ASSERT(this, "Hero::enterCollision: null this");
	ASSERT(collisionInformation->collidingShape, "Hero::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		case kHit:

			Hero::takeHitFrom(this, collidingObject, 1, true, true);
			return false;
			break;

		case kWaterPond:

			if(Body::getMovementOnAllAxes(this->body))
			{
				MessageDispatcher::dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, collidingObject), kReactToCollision, NULL);
			}
			return false;
	}

	return false;
}

void Hero::capVelocity(Hero this, bool discardPreviousMessages)
{
	ASSERT(this, "Hero::checkCapVelocity: null this");

	if(discardPreviousMessages)
	{
		MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kHeroCheckVelocity);
	}

	if(Body::isActive(this->body))
	{
		Velocity velocity = Body::getVelocity(this->body);

		if(velocity.y)
		{
			if(HERO_MAX_VELOCITY_Y < velocity.y && __UNIFORM_MOVEMENT != Body::getMovementType(this->body).y)
			{
				velocity.x = 0;
				velocity.y = HERO_MAX_VELOCITY_Y;
				velocity.z = 0;

				//Body::moveUniformly(this->body, velocity);
			}
			else if(0 < velocity.y)
			{
				MessageDispatcher::dispatchMessage(HERO_CHECK_Y_VELOCITY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckVelocity, NULL);
			}
		}
		else
		{
			MessageDispatcher::dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckVelocity, NULL);
		}
	}
}

bool Hero::handleMessage(Hero this, Telegram telegram)
{
	ASSERT(this, "Hero::handleMessage: null this");

	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
		case kHeroCheckVelocity:

			Hero::capVelocity(this, false);
			return true;
			break;

		case kHeroStopFeetDust:

			Hero::hideDust(this);
			return true;
			break;

		case kHeroStopInvincibility:

			Hero::setInvincible(this, false);
			return true;
			break;

		case kHeroFlash:

			Hero::flash(this);
			return true;
			break;

		case kHeroResumePhysics:

			Game::enableKeypad(Game::getInstance());
			GameState::pausePhysics(Game::getCurrentState(Game::getInstance()), false);
			GameState::pauseAnimations(Game::getCurrentState(Game::getInstance()), false);

			Velocity velocity = Body::getVelocity(this->body);

			if(!velocity.y)
			{
				if(velocity.x)
				{
					AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
				}
				else
				{
					AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");
				}
			}
			else if(velocity.x)
			{
				AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Walk");
			}
			else
			{
				AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Idle");
			}

			break;

		case kHeroDied:

			Hero::die(this);
			break;

		case kBodyStopped:

			if(-1 == this->jumps)
			{
				return true;
			}
			break;
	}

	return Base::handleMessage(__SAFE_CAST(Actor, this), telegram);
}

// process message
bool Hero::handlePropagatedMessage(Hero this, int message)
{
	ASSERT(this, "Hero::handlePropagatedMessage: null this");

	switch(message)
	{
		case kLevelSetUp:
			{
				// set camera
				Vector3D cameraBoundingBoxPosition = CAMERA_BOUNDING_BOX_DISPLACEMENT;
				this->cameraBoundingBox = Entity::addChildEntity(__SAFE_CAST(Entity, this), (EntityDefinition*)&CAMERA_BOUNDING_BOX_IG, 0, NULL, &cameraBoundingBoxPosition, NULL);
				Hero::lockCameraTriggerMovement(this, __X_AXIS | __Y_AXIS, true);
			}

			//Hero::locateOverNextFloor(this);

			break;

		case kLevelStarted:
			{
				Vector3DFlag positionFlag = {true, true, true};
				CustomCameraMovementManager::setPositionFlag(CustomCameraMovementManager::getInstance(), positionFlag);
			}
			break;

	}

	return false;
}

void Hero::getOutOfDoor(Hero this, Vector3D* outOfDoorPosition)
{
	ASSERT(this, "Hero::setPosition: null this");

	// stop all movement
	Actor::stopAllMovement(__SAFE_CAST(Actor, this));

	// set new position
	Actor::setPosition(__SAFE_CAST(Actor, this), outOfDoorPosition);

	// must make sure that collision detection is reset
//	Actor::resetCollisionStatus(__SAFE_CAST(Actor, this));

	// make the camera active for collision detection
	Hero::lockCameraTriggerMovement(this, __X_AXIS | __Y_AXIS, false);

	Entity::informShapesThatStartedMoving(__SAFE_CAST(Entity, this));

	Container::invalidateGlobalTransformation(__SAFE_CAST(Container, this));

	Body::setAxesSubjectToGravity(this->body, __Y_AXIS);

	this->currentlyOverlappedDoor = NULL;
}

void Hero::suspend(Hero this)
{
	ASSERT(this, "Hero::suspend: null this");

	Base::suspend(this);

	if(this->feetDust)
	{
		ParticleSystem::pause(this->feetDust);
	}
}

void Hero::resume(Hero this)
{
	ASSERT(this, "Hero::resume: null this");

	Base::resume(this);

	Camera::focus(Camera::getInstance(), false);

	Hero::lockCameraTriggerMovement(this, __X_AXIS | __Y_AXIS, true);

	Vector3DFlag positionFlag = {true, true, true};
	CustomCameraMovementManager::setPositionFlag(CustomCameraMovementManager::getInstance(), positionFlag);

	Hero::updateSprite(this);
}

bool Hero::isBelow(Hero this, Shape shape, const CollisionInformation* collisionInformation)
{
	ASSERT(this, "Hero::isAboveEntity: null this");

	RightBox shapeRightBox = Shape::getSurroundingRightBox(shape);
	RightBox collidingShapeRightBox = Shape::getSurroundingRightBox(collisionInformation->collidingShape);

	fix10_6 heroBottomPosition = shapeRightBox.y1 - ((shapeRightBox.y1 - shapeRightBox.y0) >> 1) - (Body::getLastDisplacement(this->body).y << 1) / 2;

	return heroBottomPosition > collidingShapeRightBox.y0 || __ABS(collisionInformation->solutionVector.direction.y) < __ABS(collisionInformation->solutionVector.direction.x);
}

u16 Hero::getAxisForFlipping(Hero this __attribute__ ((unused)))
{
	return __X_AXIS;
}

void Hero::onPowerUpTransitionComplete(Hero this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Hero::onPowerUpTransitionComplete: null this");

	MessageDispatcher::dispatchMessage(300, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroResumePhysics, NULL);
}

bool Hero::isAffectedByRelativity(Hero this __attribute__ ((unused)))
{
	ASSERT(this, "Hero::isAffectedByRelativity: null this");

	return true;
}

void Hero::syncRotationWithBody(Hero this)
{
	ASSERT(this, "Hero::syncRotationWithBody: null this");

	fix10_6 xLastDisplacement = Body::getLastDisplacement(this->body).x;

	Direction direction = Entity::getDirection(__SAFE_CAST(Entity, this));

	if(0 < xLastDisplacement)
	{
		direction.x = __RIGHT;
		Entity::setDirection(__SAFE_CAST(Entity, this), direction);
	}
	else if(0 > xLastDisplacement)
	{
		direction.x = __LEFT;
		Entity::setDirection(__SAFE_CAST(Entity, this), direction);
	}
}

void Hero::exitCollision(Hero this, Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable)
{
	ASSERT(this, "Hero::exitCollision: null this");

	SpatialObject nonCollidingSpatialObject = Shape::getOwner(shapeNotCollidingAnymore);

	switch(SpatialObject::getInGameType(nonCollidingSpatialObject))
	{
		case kHideLayer:

			HideLayer::unsetOverlapping(__SAFE_CAST(HideLayer, nonCollidingSpatialObject));
			break;

		case kDoor:

			Hero::hideHint(this);
			Door::unsetOverlapping(__SAFE_CAST(Door, nonCollidingSpatialObject));
			this->currentlyOverlappedDoor = NULL;
			break;

		case kWaterPond:

			this->underWater = false;
			break;
	}

	Base::exitCollision(this, shape, shapeNotCollidingAnymore, isShapeImpenetrable);
}

u16 Hero::getAxesForShapeSyncWithDirection(Hero this __attribute__ ((unused)))
{
	return __NO_AXIS;
}
