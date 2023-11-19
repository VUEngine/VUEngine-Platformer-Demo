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

#include <GameEvents.h>
#include <VUEngine.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Camera.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <KeypadManager.h>
#include "Hero.h"
#include "states/HeroIdle.h"
#include "states/HeroMoving.h"
#include <PlatformerCameraMovementManager.h>
#include <CustomCameraEffectManager.h>
#include <PlatformerCameraTriggerEntity.h>
#include <EventManager.h>
#include <Hint.h>
#include <SoundManager.h>
#include <debugConfig.h>
#include <gameDebugConfig.h>
#include <HideLayer.h>
#include <StateMachine.h>
#include <VirtualList.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern double fabs (double);

extern CharSetSpec HeroCharset;
extern CharSetSpec HeroBandanaCharset;

extern EntitySpec DustParticleSystem;
extern EntitySpec HintMc;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// Only one instance
static Hero hero = NULL;

// there can only be one hero instantiated
static Hero Hero::getInstance()
{
	return hero;
}

static void Hero::setInstance(Hero instance)
{
	ASSERT(!hero, "Hero::setInstance: already instantiated");

	hero = instance;
}


// class's constructor
void Hero::constructor(HeroSpec* heroSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)heroSpec, internalId, name);

	// init class variables
	this->coins = 0;
	this->hasKey = false;
	this->hint = NULL;
	this->feetDust = NULL;
	this->energy = HERO_INITIAL_ENERGY;
	this->powerUp = kPowerUpNone;
	this->invincible = false;
	this->currentlyOverlappedDoor = NULL;
	this->boost = false;
	this->jumps = 0;
	this->keepAddingForce = false;
	this->underWater = false;

	Hero::setInstance(this);

	ListenerObject::addEventListener(ListenerObject::safeCast(PlatformerLevelState::getInstance()), ListenerObject::safeCast(this), (EventListener)Hero::onUserInput, kEventUserInput);

	this->inputDirection = Entity::getNormalizedDirection(this);
}

// class's destructor
void Hero::destructor()
{
	ASSERT(hero, "Hero::destructor: already deleted");
	ASSERT(hero == this, "Hero::destructor: more than one instance");

	// remove event listeners
	ListenerObject::removeEventListener(PlatformerLevelState::getInstance(), ListenerObject::safeCast(this), (EventListener)Hero::onUserInput, kEventUserInput);

	// announce my dead
	ListenerObject::fireEvent(EventManager::getInstance(), kEventHeroDied);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageHeroCheckVelocity);
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageHeroFlash);

	// free the instance pointers
	this->feetDust = NULL;
	this->hint = NULL;
	hero = NULL;

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Hero::ready(bool recursive)
{
	Entity::activeCollisionChecks(this, true);

	// call base
	Base::ready(this, recursive);

	// override with progress from progress manager
	ProgressManager progressManager = ProgressManager::getInstance();
	if(progressManager)
	{
		this->energy = ProgressManager::getHeroCurrentEnergy(progressManager);

		uint8 currentPowerUp = ProgressManager::getHeroCurrentPowerUp(progressManager);
		if(currentPowerUp != this->powerUp)
		{
			this->powerUp = currentPowerUp;
			Hero::updateSprite(this);
		}

		this->hasKey = ProgressManager::heroHasKey(ProgressManager::getInstance());
	}

	// initialize me as idle
	Hero::initializeStateMachine(this, State::safeCast(HeroIdle::getInstance()));

	Hero::addHint(this);
	Hero::addFeetDust(this);
}

void Hero::locateOverNextFloor()
{
/*	Vector3D direction = {0, 1, 0};

	SpatialObject collidingSpatialObject = CollisionManager::searchNextObjectOfCollision(VUEngine::getCollisionManager(VUEngine::getInstance()), this->shape, direction);
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
void Hero::jump(bool checkIfYMovement)
{
	if(this->body)
	{
		// determine the maximum number of possible jumps before reaching ground again
		int8 allowedNumberOfJumps = this->underWater ? 127 : (this->powerUp == kPowerUpBandana) ? 2 : 1;

#ifdef GOD_MODE
	allowedNumberOfJumps = 127;
#endif

		// check if more jumps are allowed
		if(this->jumps < allowedNumberOfJumps)
		{
			// init a force to add to the hero's momentum
			Vector3D force = {0, 0, 0};

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
				Hero::applyForce(this, &force, true);
			}
			else
			{
				// hack to avoid the processing of kMessageBodyStopped message triggered by the call to Actor::stopMovement
				this->jumps = -1;

				// stop movement to gain full momentum of the jump force that will be added
				Actor::stopMovement(this, __Y_AXIS);

				// set second jump performed
				this->jumps = 2;

				// double jumps can never have boost
				force.y = HERO_NORMAL_JUMP_INPUT_FORCE;

				// add the force to actually make the hero jump
				Hero::applyForce(this, &force, true);

				// show dust
				Hero::showDust(this, true);
			}

			// play jump animation
			AnimatedEntity::playAnimation(this, "Jump");

			extern Sound JumpSound;
			SoundManager::playSound(SoundManager::getInstance(), &JumpSound, kPlayAll, (const Vector3D*)&this->transformation.globalPosition, kSoundWrapperPlaybackNormal, NULL, NULL);
		}
	}
}

// keep movement
void Hero::applyForceOnAxis(uint16 axis, bool enableAddingForce)
{
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

	Vector3D velocity = *Body::getVelocity(this->body);

	NormalizedDirection direction = Entity::getNormalizedDirection(this);

	if(direction.x != this->inputDirection.x ||
		((__X_AXIS & axis) && maxVelocity > __ABS(velocity.x)) ||
		((__Z_AXIS & axis) && maxVelocity > __ABS(velocity.z)) ||

		// BREAKS MOVEMENT
		Actor::hasChangedDirection(this, __X_AXIS, NULL) ||
		Actor::hasChangedDirection(this, __Z_AXIS, NULL))
	{
		fix10_6 inputForce = !Body::getNormal(this->body).y ? HERO_X_INPUT_FORCE_WHILE_JUMPING : HERO_INPUT_FORCE;
		fix10_6 xForce = (__X_AXIS & axis) ? __RIGHT == this->inputDirection.x ? inputForce : -inputForce : 0;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		
		Vector3D force =
		{
			xForce,
			0,
			zForce
		};

		Hero::applyForce(this, &force, true);
	}
	else
	{
		if(__UNIFORM_MOVEMENT != Body::getMovementType(this->body).x || (__ABS(velocity.x) > maxVelocity && !(__Y_AXIS & Body::getMovementOnAllAxis(this->body))))
		{
			Vector3D newVelocity =
			{
				(__X_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.x) : 0,
				0,
				(__Z_AXIS & axis) ? ((int)maxVelocity * this->inputDirection.z) : 0,
			};

			Body::moveUniformly(this->body, newVelocity);
		}
	}
}

void Hero::slide()
{
	AnimatedEntity::playAnimation(this, "Slide");

	Hero::showDust(this, false);
}

void Hero::showDust(bool autoHideDust)
{
	if(this->feetDust)
	{
		ParticleSystem::start(this->feetDust);
		ParticleSystem::show(this->feetDust);
	}

	if(autoHideDust)
	{
		// stop the dust after some time
		MessageDispatcher::dispatchMessage(200, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroStopFeetDust, NULL);
	}
}

void Hero::hideDust()
{
	if(this->feetDust)
	{
		ParticleSystem::pause(this->feetDust);
		ParticleSystem::hide(this->feetDust);
	}
}

// start movement
void Hero::stopAddingForce()
{
	Vector3D velocity = *Body::getVelocity(this->body);

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
	uint16 axisOfDeacceleration = 0;
	axisOfDeacceleration |= velocity.x? __X_AXIS: 0;
	axisOfDeacceleration |= velocity.z? __Z_AXIS: 0;

	if(axisOfDeacceleration)
	{
		fix10_6 inputForce = HERO_FORCE_FOR_STOPPING;
		fix10_6 xForce = __RIGHT == this->inputDirection.x ? inputForce : -inputForce;
		fix10_6 zForce = 0; //(__Z_AXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
		
		Vector3D force =
		{
			xForce,
			0,
			zForce
		};

		Hero::applyForce(this, &force, true);
	}
	else
	{
		Hero::stopMovingOnAxis(this, __X_AXIS | __Z_AXIS);
	}
}

// started moving over axis
void Hero::startedMovingOnAxis(uint16 axis)
{
	if(__Y_AXIS & axis)
	{
		Hero::hideDust(this);
		Hero::capVelocity(this, true);
	}

	// start movement
	if(State::safeCast(HeroMoving::getInstance()) != StateMachine::getCurrentState(this->stateMachine))
	{
		if(__X_AXIS & axis)
		{
			this->keepAddingForce = true;
			AnimatedEntity::playAnimation(this, "Walk");
		}

		StateMachine::swapState(this->stateMachine, State::safeCast( HeroMoving::getInstance()));
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
bool Hero::stopMovingOnAxis(uint16 axis)
{
	// if being hit do nothing
	if(!Body::isActive(this->body))
	{
		return false;
	}

	bool movementState = Body::getMovementOnAllAxis(this->body);

	if((__X_AXIS & axis) && !(__Y_AXIS & movementState))
	{
		AnimatedEntity::playAnimation(this, "Idle");

		Hero::hideDust(this);
	}

	// if there is something below
	if(0 > Body::getNormal(this->body).y)
	{
		if(__Y_AXIS & axis)
		{
			MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageHeroCheckVelocity);

			PlatformerCameraMovementManager::lockMovement(PlatformerCameraMovementManager::getInstance(), __Y_AXIS, true);

			this->jumps = 0;

			if(Body::getVelocity(this->body)->x)
			{
				if(this->inputDirection.x)
				{
					AnimatedEntity::playAnimation(this, "Walk");

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
			StateMachine::swapState(this->stateMachine, State::safeCast(HeroIdle::getInstance()));
			return true;
		}

		if(!movementState && State::safeCast(HeroIdle::getInstance()) != StateMachine::getCurrentState(this->stateMachine))
		{
			this->keepAddingForce = false;
			this->jumps = 0;
			StateMachine::swapState(this->stateMachine, State::safeCast(HeroIdle::getInstance()));
			return true;
		}
		else
		{
			// make sure that hitting the floor doesn't slow me down because of the friction
			if(__UNIFORM_MOVEMENT == Body::getMovementType(this->body).x)
			{
				fix10_6 maxVelocity = HERO_BOOST_VELOCITY_X;

				Vector3D newVelocity =
				{
					(int)maxVelocity * this->inputDirection.x,
					0,
					0,
				};

				Body::moveUniformly(this->body, newVelocity);
			}

			AnimatedEntity::playAnimation(this, "Walk");
		}
	}
	else
	{
		AnimatedEntity::playAnimation(this, "Fall");
	}

	return false;
}

// check direction
void Hero::checkDirection(uint32 pressedKey, char* animation)
{
	bool movementState = Body::getMovementOnAllAxis(this->body);

	Hero::hideDust(this);

	if(K_LR & pressedKey)
	{
		this->inputDirection.x = __RIGHT;

		if(this->feetDust)
		{
			Vector3D position = *Container::getLocalPosition(this->feetDust);
			position.x = __ABS(position.x) * -1;
			Container::setLocalPosition(this->feetDust, &position);
		}
	}
	else if(K_LL & pressedKey)
	{
		this->inputDirection.x = __LEFT;

		if(this->feetDust)
		{
			Vector3D position = *Container::getLocalPosition(this->feetDust);
			position.x = __ABS(position.x);
			Container::setLocalPosition(this->feetDust, &position);
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

	if(animation && !(__Y_AXIS & movementState))
	{
		AnimatedEntity::playAnimation(this, animation);
	}
}

void Hero::takeDamageFrom(SpatialObject collidingObject, int energyToReduce, bool pause, bool invincibleWins)
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
			MessageDispatcher::dispatchMessage(HERO_FLASH_DURATION, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroStopInvincibility, NULL);

			// start flashing of hero
			MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageHeroFlash);
			MessageDispatcher::dispatchMessage(0, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroFlash, NULL);

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
				Actor::stopAllMovement(this);
				VUEngine::disableKeypad(VUEngine::getInstance());
				GameState::pausePhysics(VUEngine::getCurrentState(VUEngine::getInstance()), true);
				//GameState::pauseAnimations(VUEngine::getCurrentState(VUEngine::getInstance()), true);
				MessageDispatcher::dispatchMessage(500, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroResumePhysics, collidingObject);
			}
		}
		else
		{
			VUEngine::disableKeypad(VUEngine::getInstance());
			Hero::setInvincible(this, true);
			this->energy = 0;
			Hero::flash(this);
			GameState::pausePhysics(VUEngine::getCurrentState(VUEngine::getInstance()), true);
			GameState::pauseAnimations(VUEngine::getCurrentState(VUEngine::getInstance()), true);
			Entity::allowCollisions(this, false);
			MessageDispatcher::dispatchMessage(500, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroDied, NULL);
		}

		// start short screen shake
		Camera::startEffect(Camera::getInstance(), kShake, 200);

		// play hit sound
		extern Sound FireSound;
		SoundManager::playSound(SoundManager::getInstance(), &FireSound, kPlayAll, (const Vector3D*)&this->transformation.globalPosition, kSoundWrapperPlaybackNormal, NULL, NULL);

		AnimatedEntity::playAnimation(this, "Hit");

		// inform others to update ui etc
		ListenerObject::fireEvent(EventManager::getInstance(), kEventHitTaken);
	}
}

// flash after being hit
void Hero::flash()
{
	// only flash as long as hero is invincible
	if(Hero::isInvincible(this))
	{
		// toggle between original and flash palette
		Hero::toggleFlashPalette(this);

		// next flash state change after HERO_FLASH_INTERVAL milliseconds
		MessageDispatcher::dispatchMessage(HERO_FLASH_INTERVAL, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroFlash, NULL);
	}
	else
	{
		// set palette back to original
		Hero::resetPalette(this);
	}
}

void Hero::toggleFlashPalette()
{
	// get all of the hero's sprites and loop through them
	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		// get sprite's texture
		Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		// get original palette
		TextureSpec* textureSpec = Texture::getSpec(texture);

		// set new palette
		if(Texture::getPalette(texture) == textureSpec->palette)
		{
			Texture::setPalette(texture, HERO_FLASH_PALETTE);
		}
		else
		{
			Texture::setPalette(texture, textureSpec->palette);
		}

		// rewrite sprite to bgmap to apply changed palette
		Sprite::rewrite(sprite);
	}
}

void Hero::resetPalette()
{
	// get all of hero's sprites and loop through them
	VirtualList sprites = Entity::getSprites(this);
	VirtualNode node = VirtualList::begin(sprites);
	for(; node; node = VirtualNode::getNext(node))
	{
		// get sprite's texture
		Sprite sprite = Sprite::safeCast(VirtualNode::getData(node));
		Texture texture = Sprite::getTexture(sprite);

		// get original palette and set it
		TextureSpec* textureSpec = Texture::getSpec(texture);
		Texture::setPalette(texture, textureSpec->palette);

		// rewrite sprite to bgmap to apply changed palette
		Sprite::rewrite(sprite);
	}
}

// set animation delta
void Hero::setAnimationDelta(int delta __attribute__ ((unused)))
{
	ASSERT(this->sprites, "Hero::setAnimationDelta: null sprites");

	VirtualNode node = VirtualList::begin(this->sprites);

	for(; node; node = VirtualNode::getNext(node))
	{
		Sprite::setFrameCycleDecrement(Sprite::safeCast(VirtualNode::getData(node)), this->boost ? 2 : 1);
	}
}

// disable boost
void Hero::disableBoost()
{
	if(this->boost)
	{
		this->boost = false;
		Hero::setAnimationDelta(this, -1);
	}
}

// enable boost
void Hero::enableBoost()
{
	if(!this->boost)
	{
		this->boost = true;

		Hero::setAnimationDelta(this, -2);
	}
}

// get the door overlapped by the hero
Door Hero::getOverlappedDoor()
{
	return this->currentlyOverlappedDoor;
}

void Hero::enterDoor()
{
	if((__Y_AXIS | __Z_AXIS) & Body::getMovementOnAllAxis(this->body))
	{
		return;
	}

	// play animation
	AnimatedEntity::playAnimation(this, "WalkingBack");

	// move towards door
	/*
	Body::setAxisSubjectToGravity(this->body, 0);
	Vector3D velocity = {0, 0, __I_TO_FIX10_6(8)};
	Body::moveUniformly(this->body, velocity);
	*/

	// inform the door entity
	if(this->currentlyOverlappedDoor)
	{
		MessageDispatcher::dispatchMessage(1, ListenerObject::safeCast(this), ListenerObject::safeCast(this->currentlyOverlappedDoor), kMessageHeroEnterDoor, NULL);
	}

	// hide hint immediately
	if(this->hint != NULL)
	{
		Entity::hide(this->hint);
	}

	// play door sound
	extern Sound CollectSound;
	SoundManager::playSound(SoundManager::getInstance(), &CollectSound, kPlayAll, (const Vector3D*)&this->transformation.globalPosition, kSoundWrapperPlaybackNormal, NULL, NULL);
}

void Hero::addHint()
{
	Vector3D position = {0, 0, __PIXELS_TO_METERS(-4)};

	// save the hint entity, so we can remove it later
	this->hint = Entity::addChildEntity(this, &HintMc, -1, "hint", &position, NULL);
	Entity::setInheritEnvironment(this->hint, __INHERIT_POSITION);

	Hero::hideHint(this);
}

void Hero::addFeetDust()
{
	Vector3D position = {__PIXELS_TO_METERS(-8), __PIXELS_TO_METERS(10), __PIXELS_TO_METERS(12)};

	this->feetDust = ParticleSystem::safeCast(Entity::addChildEntity(this, &DustParticleSystem, -1, "feetDust", &position, NULL));
	ASSERT(this->feetDust, "Hero::addFeetDust: null feetDust");

	ParticleSystem::spawnAllParticles(this->feetDust);

	Hero::hideDust(this);
}

void Hero::showHint(uint32 hintType)
{
	ASSERT(this->hint, "Hero::showHint: null hint");

	Hint::open((Hint)this->hint, hintType);
}

void Hero::hideHint()
{
	// check if a hint is being shown at the moment
	if(this->hint)
	{
		// play the closing animation
		Hint::close(this->hint);
	}
}

// make hero to look to the player
void Hero::lookFront()
{
	// if not already playing
	if(!AnimatedEntity::isAnimationLoaded(this, "Front"))
	{
		// play animation
		AnimatedEntity::playAnimation(this, "Front");
	}
}

// make hero to look away from the player
void Hero::lookBack()
{
	// if not already playing
	if(!AnimatedEntity::isAnimationLoaded(this, "Back"))
	{
		// play animation
		AnimatedEntity::playAnimation(this, "Back");
	}
}

// die hero
void Hero::die()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageHeroFlash);

	GameState::pauseAnimations(VUEngine::getCurrentState(VUEngine::getInstance()), false);
	Container::deleteMyself(this);

	/*
	// go to dead state
	StateMachine::swapState(this->stateMachine, State::safeCast(HeroDead::getInstance()));

	// must unregister the shape for collision detections
	Entity::allowCollisions(this, false);

	// change in game state
	this->inGameState = kDead;
	*/
}

// process user input
void Hero::onUserInput(Object eventFirer __attribute__ ((unused)))
{
	UserInput userInput = PlatformerLevelState::getUserInput(PlatformerLevelState::getInstance());

	HeroState currentState = HeroState::safeCast(StateMachine::getCurrentState(this->stateMachine));

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
bool Hero::hasKey()
{
	return this->hasKey;
}

// collect a power-up
void Hero::collectPowerUp(uint8 powerUp)
{
	this->powerUp = powerUp;
	this->keepAddingForce = false;

	Hero::updateSprite(this);

	Actor::stopAllMovement(this);
	VUEngine::disableKeypad(VUEngine::getInstance());
	GameState::pausePhysics(VUEngine::getCurrentState(VUEngine::getInstance()), true);

	AnimatedEntity::playAnimation(this, "Transition");
}

// lose a power-up
void Hero::losePowerUp()
{
	this->powerUp = kPowerUpNone;
	Hero::updateSprite(this);
	ListenerObject::fireEvent(EventManager::getInstance(), kEventPowerUp);
}

// update sprite, e.g. after collecting a power-up
void Hero::updateSprite()
{
	CharSet charSet = Texture::getCharSet(Sprite::getTexture(Sprite::safeCast(VirtualList::front(this->sprites))), true);

	CharSetSpec* charSetSpec = NULL;

	switch(this->powerUp)
	{
		case kPowerUpBandana:

			charSetSpec = &HeroBandanaCharset;
			break;

		default:
		case kPowerUpNone:

			charSetSpec = &HeroCharset;
			break;
	}

	CharSet::setCharSetSpec(charSet, charSetSpec);
	CharSet::rewrite(charSet);
}

// get current power-up
uint8 Hero::getPowerUp()
{
	return this->powerUp;
}

// get energy
uint8 Hero::getEnergy()
{
	return this->energy;
}

// set invincibility
void Hero::setInvincible(bool invincible)
{
	this->invincible = invincible;
}

// get invincibility
bool Hero::isInvincible()
{
	return this->invincible;
}

fix10_6 Hero::getFrictionOnCollision(SpatialObject collidingObject, const Vector3D* collidingObjectNormal)
{
	// ignore friction on y axis
	if(collidingObjectNormal->x && !collidingObjectNormal->y)
	{
		return 0;
	}

	return Base::getFrictionOnCollision(this, collidingObject, collidingObjectNormal);
}

// process collisions
bool Hero::enterCollision(const CollisionInformation* collisionInformation)
{
	ASSERT(collisionInformation->collidingShape, "Hero::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		// speed things up by breaking early
		case kTypeShape:
			break;

		case kTypeCoin:

			MessageDispatcher::dispatchMessage(0, ListenerObject::safeCast(this), ListenerObject::safeCast(collidingObject), kMessageTakeItem, NULL);
			return false;
			break;

		case kTypeKey:

			this->hasKey = true;
			MessageDispatcher::dispatchMessage(0, ListenerObject::safeCast(this), ListenerObject::safeCast(collidingObject), kMessageTakeItem, NULL);
			return false;
			break;

		case kTypeBandana:

			Hero::collectPowerUp(this, kPowerUpBandana);
			MessageDispatcher::dispatchMessage(0, ListenerObject::safeCast(this), ListenerObject::safeCast(collidingObject), kMessageTakeItem, NULL);
			return false;
			break;

		case kTypeHideLayer:

			// first contact with hide layer?
			HideLayer::setOverlapping((HideLayer)collidingObject);
			return false;
			break;

		case kTypeDoor:
			{
				Door door = Door::safeCast(collidingObject);
				Hero::showHint(this, Door::getHintType(door));
				Door::setOverlapping(door);
				this->currentlyOverlappedDoor = door;
			}
			return false;
			break;

		case kTypeWaterPond:

			if(Body::getMovementOnAllAxis(this->body))
			{
				this->underWater = true;

				MessageDispatcher::dispatchMessage(0, ListenerObject::safeCast(this), ListenerObject::safeCast(collidingObject), kMessageReactToCollision, NULL);

				Body::setSurroundingFrictionCoefficient(this->body, Actor::getSurroundingFrictionCoefficient(this) + SpatialObject::getFrictionCoefficient(collidingObject));
			}
			return true;
			break;

		case kTypeLava:

			Hero::takeDamageFrom(this, NULL, this->energy, true, false);
			return false;
			break;

		case kTypeSawBlade:
		case kTypeSnail:

			Hero::takeDamageFrom(this, collidingObject, 1, true, true);
			return false;
			break;

		case kTypeCannonBall:

			Hero::takeDamageFrom(this, collidingObject, 2, true, true);
			return false;
			break;

		case kTypeHit:

			Hero::takeDamageFrom(this, collidingObject, 1, true, true);
			return false;
			break;

		case kTypeLavaTrigger:

			MessageDispatcher::dispatchMessage(0, ListenerObject::safeCast(this), ListenerObject::safeCast(collidingObject), kMessageLavaTriggerStart, NULL);
			Hero::stopAddingForce(this);
			return false;
			break;

		case kTypeMovingPlatform:
		case kTypeTopShape:
			{
				if((0 > Body::getVelocity(this->body)->y) || Hero::isBelow(this, collisionInformation->shape, collisionInformation))
				{
					// don't further process collision
					return false;
				}
			}
			break;
	}

	return Base::enterCollision(this, collisionInformation) && (__ABS(collisionInformation->solutionVector.direction.y) > __ABS(collisionInformation->solutionVector.direction.x));
}

// process collisions
bool Hero::updateCollision(const CollisionInformation* collisionInformation)
{
	ASSERT(collisionInformation->collidingShape, "Hero::enterCollision: null collidingObjects");

	Shape collidingShape = collisionInformation->collidingShape;
	SpatialObject collidingObject = Shape::getOwner(collidingShape);

	switch(SpatialObject::getInGameType(collidingObject))
	{
		case kTypeHit:

			Hero::takeDamageFrom(this, collidingObject, 1, true, true);
			return false;
			break;

		case kTypeWaterPond:

			if(Body::getMovementOnAllAxis(this->body))
			{
				MessageDispatcher::dispatchMessage(0, ListenerObject::safeCast(this), ListenerObject::safeCast(collidingObject), kMessageReactToCollision, NULL);
			}
			return false;
	}

	return false;
}

void Hero::capVelocity(bool discardPreviousMessages)
{
	if(discardPreviousMessages)
	{
		MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageHeroCheckVelocity);
	}

	if(Body::isActive(this->body))
	{
		Vector3D velocity = *Body::getVelocity(this->body);

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
				MessageDispatcher::dispatchMessage(HeroCharsetECK_Y_VELOCITY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroCheckVelocity, NULL);
			}
		}
		else
		{
			MessageDispatcher::dispatchMessage(1, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroCheckVelocity, NULL);
		}
	}
}

bool Hero::handleMessage(Telegram telegram)
{
	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
		case kMessageHeroCheckVelocity:

			Hero::capVelocity(this, false);
			return true;
			break;

		case kMessageHeroStopFeetDust:

			Hero::hideDust(this);
			return true;
			break;

		case kMessageHeroStopInvincibility:

			Hero::setInvincible(this, false);
			return true;
			break;

		case kMessageHeroFlash:

			Hero::flash(this);
			return true;
			break;

		case kMessageHeroResumePhysics:

			VUEngine::enableKeypad(VUEngine::getInstance());
			GameState::pausePhysics(VUEngine::getCurrentState(VUEngine::getInstance()), false);
			GameState::pauseAnimations(VUEngine::getCurrentState(VUEngine::getInstance()), false);

			Vector3D velocity = *Body::getVelocity(this->body);

			if(!velocity.y)
			{
				if(velocity.x)
				{
					AnimatedEntity::playAnimation(this, "Walk");
				}
				else
				{
					AnimatedEntity::playAnimation(this, "Idle");
				}
			}
			else if(velocity.x)
			{
				AnimatedEntity::playAnimation(this, "Walk");
			}
			else
			{
				AnimatedEntity::playAnimation(this, "Idle");
			}

			break;

		case kMessageHeroDied:

			Hero::die(this);
			break;

		case kMessageBodyStopped:

			if(-1 == this->jumps)
			{
				return true;
			}
			break;
	}

	return Base::handleMessage(this, telegram);
}

// process message
bool Hero::handlePropagatedMessage(int message)
{
	switch(message)
	{
		case kMessageLevelStarted:
			{
				Vector3DFlag positionFlag = {true, true, true};
				PlatformerCameraMovementManager::setPositionFlag(PlatformerCameraMovementManager::getInstance(), positionFlag);
			}
			break;

	}

	return false;
}

void Hero::getOutOfDoor(Vector3D* outOfDoorPosition)
{
	// stop all movement
	Actor::stopAllMovement(this);

	// set new position
	Actor::setPosition(this, outOfDoorPosition);

	// must make sure that collision detection is reset
//	Actor::resetCollisionStatus(this);

	// make the camera active for collision detection
	PlatformerCameraMovementManager::lockMovement(PlatformerCameraMovementManager::getInstance(), __X_AXIS | __Y_AXIS, false);

	Entity::activeCollisionChecks(this, true);

	Container::invalidateGlobalTransformation(this);

	Body::setAxisSubjectToGravity(this->body, __Y_AXIS);

	this->currentlyOverlappedDoor = NULL;
}

void Hero::suspend()
{
	Base::suspend(this);

	if(this->feetDust)
	{
		ParticleSystem::pause(this->feetDust);
	}
}

void Hero::resume()
{
	Base::resume(this);

	Hero::updateSprite(this);

	Hero::hideDust(this);
}

bool Hero::isBelow(Shape shape, const CollisionInformation* collisionInformation __attribute__((unused)))
{
	return false;
/*	
	RightBox shapeRightBox = Shape::getSurroundingRightBox(shape);
	RightBox collidingShapeRightBox = Shape::getSurroundingRightBox(collisionInformation->collidingShape);

	fix10_6 heroBottomPosition = shapeRightBox.y1 - ((shapeRightBox.y1 - shapeRightBox.y0) >> 1) - (Body::getLastDisplacement(this->body).y << 1) / 2;

	return heroBottomPosition > collidingShapeRightBox.y0 || __ABS(collisionInformation->solutionVector.direction.y) < __ABS(collisionInformation->solutionVector.direction.x);
	*/
}

void Hero::onPowerUpTransitionComplete(Object eventFirer __attribute__ ((unused)))
{
	MessageDispatcher::dispatchMessage(300, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageHeroResumePhysics, NULL);
}

void Hero::syncRotationWithBody()
{
	fix10_6 xLastDisplacement = Body::getLastDisplacement(this->body).x;

	NormalizedDirection normalizedDirection = Entity::getNormalizedDirection(this);

	if(0 < xLastDisplacement)
	{
		normalizedDirection.x = __RIGHT;
		Entity::setNormalizedDirection(this, normalizedDirection);
	}
	else if(0 > xLastDisplacement)
	{
		normalizedDirection.x = __LEFT;
		Entity::setNormalizedDirection(this, normalizedDirection);
	}
}

void Hero::exitCollision(Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable)
{
	SpatialObject nonCollidingSpatialObject = Shape::getOwner(shapeNotCollidingAnymore);

	switch(SpatialObject::getInGameType(nonCollidingSpatialObject))
	{
		case kTypeHideLayer:

			HideLayer::unsetOverlapping(nonCollidingSpatialObject);
			break;

		case kTypeDoor:

			Hero::hideHint(this);
			Door::unsetOverlapping(nonCollidingSpatialObject);
			this->currentlyOverlappedDoor = NULL;
			break;

		case kTypeWaterPond:

			this->underWater = false;
			break;
	}

	Base::exitCollision(this, shape, shapeNotCollidingAnymore, isShapeImpenetrable);
}
