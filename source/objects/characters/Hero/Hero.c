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
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Screen.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <KeypadManager.h>
#include <objects.h>
#include "Hero.h"
#include "states/HeroIdle.h"
#include "states/HeroMoving.h"
#include <CustomScreenMovementManager.h>
#include <CameraTriggerEntity.h>
#include <EventManager.h>
#include <Hint.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Hero, Actor);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void Hero_onKeyPressed(Hero this, Object eventFirer);
static void Hero_onKeyReleased(Hero this, Object eventFirer);
static void Hero_onKeyHold(Hero this, Object eventFirer);
void Hero_enterDoor(Hero this);
void Hero_hideHint(Hero this);
void Hero_resetCurrentlyOverlappingDoor(Hero this);
void Hero_resetCurrentlyOverlappingHideLayer(Hero this);
void Hero_updateSprite(Hero this);
static void Hero_addHints(Hero this);
static void Hero_addFeetDust(Hero this);
static void Hero_slide(Hero this);
static void Hero_showDust(Hero this, bool autoHideDust);
static void Hero_hideDust(Hero this);


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern double fabs (double);

extern const u16 COLLECT_SND[];
extern const u16 FIRE_SND[];
extern const u16 JUMP_SND[];
extern CharSetDefinition HERO_CH;
extern CharSetDefinition HERO_BANDANA_CH;
extern EntityDefinition DUST_PS;
extern EntityDefinition HINT_ENTER_MC;

#define HERO_INPUT_FORCE 						ITOFIX19_13(5050)
#define HERO_JUMPING_INPUT_FORCE				ITOFIX19_13(3800)

#define HERO_VELOCITY_X							ITOFIX19_13(120)
#define HERO_VELOCITY_Y							ITOFIX19_13(-200)
#define HERO_VELOCITY_Z							ITOFIX19_13(60)
#define HERO_BOOST_VELOCITY_X					FTOFIX19_13(170)
#define HERO_NORMAL_JUMP_HERO_INPUT_FORCE		ITOFIX19_13(-48000)
#define HERO_BOOST_JUMP_HERO_INPUT_FORCE		ITOFIX19_13(-57000)


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Hero_losePowerUp(Hero this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
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
__CLASS_NEW_DEFINITION(Hero, ActorDefinition* actorDefinition, int id, const char* const name)
__CLASS_NEW_END(Hero, actorDefinition, id, name);

// class's constructor
void Hero_constructor(Hero this, ActorDefinition* actorDefinition, int id, const char* const name)
{
	ASSERT(this, "Hero::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(actorDefinition, id, name);

	// init class variables
	this->coins = 0;
	this->hasKey = false;
	this->currentHint = NULL;
	this->feetDust = NULL;
	this->cameraBoundingBox = NULL;
	this->energy = HERO_INITIAL_ENERGY;
	this->powerUp = kPowerUpNone;
	this->invincible = false;
	this->currentlyOverlappingDoor = NULL;
	this->currentlyOverlappingHideLayer = NULL;
	this->boost = false;

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __SAFE_CAST(SpatialObject, this), kCuboid);
	ASSERT(this->shape, "Hero::constructor: null shape");

	// register a body for physics
	this->body = PhysicalWorld_registerBody(PhysicalWorld_getInstance(), __SAFE_CAST(SpatialObject, this), actorDefinition->mass);
	Body_setElasticity(this->body, actorDefinition->elasticity);
	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));
	this->collisionSolver = __NEW(CollisionSolver, __SAFE_CAST(SpatialObject, this), &this->transform.globalPosition, &this->transform.localPosition);

	Hero_setInstance(this);

	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))Hero_onKeyPressed, EVENT_KEY_PRESSED);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))Hero_onKeyReleased, EVENT_KEY_RELEASED);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))Hero_onKeyHold, EVENT_KEY_HOLD);

	this->inputDirection = this->direction;
}

// class's destructor
void Hero_destructor(Hero this)
{
	ASSERT(this, "Hero::destructor: null this");
	ASSERT(hero, "Hero::destructor: already deleted");
	ASSERT(hero == this, "Hero::destructor: more than one instance");

	// unset the hero as transformation base entity from the custom screen movement manager
	CustomScreenMovementManager_setTransformationBaseEntity(CustomScreenMovementManager_getInstance(), NULL);

    // remove event listeners
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))Hero_onKeyPressed, EVENT_KEY_PRESSED);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))Hero_onKeyReleased, EVENT_KEY_RELEASED);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))Hero_onKeyHold, EVENT_KEY_HOLD);

    // discard pending delayed messages
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kFlash);

	// inform the game about the hero's death
	MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kHeroDied, NULL);

	// free the instance pointers
	this->feetDust = NULL;
	this->currentHint = NULL;
	this->cameraBoundingBox = NULL;
	hero = NULL;

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Hero_ready(Hero this)
{
	ASSERT(this, "HeroMoving::ready: null this");

	Entity_ready(__SAFE_CAST(Entity, this));

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
	}

	// initialize me as idle
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));

	Hero_addHints(this);
	Hero_addFeetDust(this);
}

SpatialObject CollisionManager_searchNextObjectOfCollision(CollisionManager this, const Shape shape, VBVec3D direction);

void Hero_locateOverNextFloor(Hero this)
{
	VBVec3D direction = {0, 1, 0};
	
	SpatialObject collidingSpatialObject = CollisionManager_searchNextObjectOfCollision(CollisionManager_getInstance(), this->shape, direction);
	ASSERT(collidingSpatialObject, "Hero::locateOverNextFloor: null collidingSpatialObject");

	if(collidingSpatialObject && this->collisionSolver)
	{
		VirtualList collidingSpatialObjects = __NEW(VirtualList);
		VirtualList_pushBack(collidingSpatialObjects, collidingSpatialObject);

		VBVec3D displacement = 
		{
			ITOFIX19_13(0),
			ITOFIX19_13(1),
			ITOFIX19_13(0),
		};

		CollisionSolver_resolveCollision(this->collisionSolver, collidingSpatialObjects, __YAXIS, displacement, &this->transform.globalScale);
		
		__DELETE(collidingSpatialObjects);
//		Actor_updateSourroundingFriction(this);
	}
}

// make him jump
void Hero_jump(Hero this, int changeState, int checkIfYMovement)
{
	ASSERT(this, "Hero::jump: null this");

	Hero_startedMovingOnAxis(this, __YAXIS);

	if(this->body)
    {
        Velocity velocity = Body_getVelocity(this->body);

		Acceleration acceleration =
        {
        	0,
			ITOFIX19_13(1),
			0
		};

		if((!checkIfYMovement || !velocity.y) && !(__YAXIS & Actor_canMoveOverAxis(__SAFE_CAST(Actor, this), &acceleration)))
        {
			Force force =
            {
                0,
                this->boost ? HERO_BOOST_JUMP_HERO_INPUT_FORCE : HERO_NORMAL_JUMP_HERO_INPUT_FORCE,
                0
            };
			
			Actor_addForce(__SAFE_CAST(Actor, this), &force);
			
	    	Hero_hideDust(this);

			AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Jump");

			SoundManager_playFxSound(SoundManager_getInstance(), JUMP_SND, this->transform.globalPosition);
		}
	}
}

// keep movement
void Hero_addForce(Hero this, int changedDirection, int axis)
{
	ASSERT(this, "Hero::addForce: null this");

	static int movementType = 0;

	fix19_13 maxVelocity = this->boost? HERO_BOOST_VELOCITY_X: HERO_VELOCITY_X;
	
	Velocity velocity = Body_getVelocity(this->body);
	
	if(this->direction.x != this->inputDirection.x ||
			((__XAXIS & axis) && maxVelocity > fabs(velocity.x)) || 
			((__ZAXIS & axis) && maxVelocity > fabs(velocity.z)) || 
			Actor_changedDirection(__SAFE_CAST(Actor, this), __XAXIS) || 
			Actor_changedDirection(__SAFE_CAST(Actor, this), __ZAXIS))
    {
		fix19_13 inputForce = __YAXIS & Body_isMoving(this->body) ? HERO_JUMPING_INPUT_FORCE : HERO_INPUT_FORCE;
		fix19_13 xForce = (__XAXIS & axis) ? __RIGHT == this->inputDirection.x ? inputForce : -inputForce : 0;
		fix19_13 zForce = 0; //(__ZAXIS & axis) ? __FAR == this->inputDirection.z ? inputForce : -inputForce : 0;
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
		Velocity newVelocity =
        {
        	(__XAXIS & axis) ? ((int)maxVelocity * this->inputDirection.x) : 0,
			0,
			(__ZAXIS & axis) ? ((int)maxVelocity * this->inputDirection.z) : 0,
		};
		
		if(__UNIFORM_MOVEMENT != movementType || (abs(velocity.x) > maxVelocity && !(__YAXIS & Body_isMoving(this->body))))
        {
			movementType = __UNIFORM_MOVEMENT;
			Body_moveUniformly(this->body, newVelocity);
		}
	}
}

static void Hero_slide(Hero this)
{
	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Slide");
	
	Hero_showDust(this, false);
}

static void Hero_showDust(Hero this, bool autoHideDust)
{
	ParticleSystem_start(this->feetDust);

	if(autoHideDust)
	{
		// stop the dust after some time
	    MessageDispatcher_dispatchMessage(200, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kStopFeetDust, NULL);
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

	// no input
//	this->inputDirection.x = 0;
//	this->inputDirection.y = 0;
//	this->inputDirection.z = 0;

	if(!(__YAXIS & Body_isMoving(this->body)))
    {
		Hero_slide(this);
	}
	else if(!AnimatedInGameEntity_isAnimationLoaded(__SAFE_CAST(AnimatedInGameEntity, this), "Fall"))
    {
		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Fall");
	}

	// begin to decelerate
	int axisOfDeacceleartion = 0;
	axisOfDeacceleartion |= velocity.x? __XAXIS: 0;
	axisOfDeacceleartion |= velocity.z? __ZAXIS: 0;
	Body_clearAcceleration(this->body, __XAXIS);
	Body_moveAccelerated(this->body, axisOfDeacceleartion);
}

// started moving over axis
void Hero_startedMovingOnAxis(Hero this, int axis)
{
	if(__YAXIS & axis)
	{
		Hero_hideDust(this);
	}
	
	// start movement
	if(__SAFE_CAST(State, HeroMoving_getInstance()) != StateMachine_getCurrentState(this->stateMachine))
    {
 		if(__XAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Walk");
		}
 		else if(__YAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Fall");
		}

		StateMachine_swapState(Actor_getStateMachine(__SAFE_CAST(Actor,  this)), __SAFE_CAST(State,  HeroMoving_getInstance()));
	}
	else
	{
		bool movementState = Body_isMoving(this->body);

		if((__XAXIS & axis)  && !(__YAXIS & movementState))
        {
			AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Walk");
		}

		if(__YAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Fall");
		}

		if(__ZAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Walk");
		}
	}
}

void Hero_lockCameraTriggerMovement(Hero this, u8 axisToLockUp, bool locked)
{
	if(this->cameraBoundingBox)
	{
        VBVec3DFlag overridePositionFlag = CameraTriggerEntity_getOverridePositionFlag(__SAFE_CAST(CameraTriggerEntity, this->cameraBoundingBox));

        if(__XAXIS & axisToLockUp)
        {
            overridePositionFlag.x = locked;
            
			VBVec3DFlag positionFlag = CustomScreenMovementManager_getPositionFlag(CustomScreenMovementManager_getInstance());
		    positionFlag.x = !locked;
		    CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager_getInstance(), positionFlag);
        }

        if(__YAXIS & axisToLockUp)
        {
            overridePositionFlag.y = locked;
        }

	    CameraTriggerEntity_setOverridePositionFlag(__SAFE_CAST(CameraTriggerEntity, this->cameraBoundingBox), overridePositionFlag);
	}
}

// retrieve friction of colliding objects
void Hero_updateSourroundingFriction(Hero this)
{
	ASSERT(this, "Hero::updateSourroundingFriction: null this");
	ASSERT(this->body, "Hero::updateSourroundingFriction: null body");

	Force totalFriction = {this->actorDefinition->friction, this->actorDefinition->friction, this->actorDefinition->friction};
	
	if(this->collisionSolver)
	{
		Force sourroundingFriction = CollisionSolver_getSourroundingFriction(this->collisionSolver);
		totalFriction.x += sourroundingFriction.x;
	}

	Body_setFriction(this->body, totalFriction);
}

// stop moving over axis
bool Hero_stopMovingOnAxis(Hero this, int axis)
{
	ASSERT(this, "Hero::stopMovingOnAxis: null this");

	bool movementState = Body_isMoving(this->body);

	if((__XAXIS & axis) && !(__YAXIS & movementState))
    {
		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Idle");

    	Hero_hideDust(this);
    	Hero_lockCameraTriggerMovement(this, __XAXIS, true);
    }

	if(__YAXIS & axis)
    {
    	Hero_lockCameraTriggerMovement(this, __YAXIS, true);

		if(__XAXIS & Body_isMoving(this->body))
		{
			if(this->inputDirection.x)
	        {
				AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Walk");
				
				Hero_showDust(this, true);
			}
			else
	        {
				Hero_slide(this);
			}
		}
	}
	
	if(__ZAXIS & axis)
    {
		StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));					
		return true;
	}

	if(!Body_isMoving(Actor_getBody(__SAFE_CAST(Actor, this))) && __SAFE_CAST(State, HeroIdle_getInstance()) != StateMachine_getCurrentState(this->stateMachine))
    {
		StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroIdle_getInstance()));					
	}
	
	return false;
}

// check direction
void Hero_checkDirection(Hero this, u16 pressedKey, char* animation)
{
	ASSERT(this, "Hero::checkDirection: null this");

	bool movementState = Body_isMoving(this->body);

	Hero_hideDust(this);
	
	if(K_LR & pressedKey)
    {
		this->inputDirection.x = __RIGHT;

		VBVec3D position = *Container_getLocalPosition(__SAFE_CAST(Container, this->feetDust));
		position.x = abs(position.x) * -1;
		Container_setLocalPosition(__SAFE_CAST(Container, this->feetDust), &position);
		Hero_lockCameraTriggerMovement(this, __XAXIS, true);
	}
	else if(K_LL & pressedKey)
    {
		this->inputDirection.x = __LEFT;

		VBVec3D position = *Container_getLocalPosition(__SAFE_CAST(Container, this->feetDust));
		position.x = abs(position.x);
		Container_setLocalPosition(__SAFE_CAST(Container, this->feetDust), &position);
		Hero_lockCameraTriggerMovement(this, __XAXIS, true);
	}
	else if(K_LU & pressedKey)
    {
		this->inputDirection.z = __FAR;
	}
	else if(K_LD & pressedKey)
    {
		this->inputDirection.z = __NEAR;
	}

	if(animation && !(__YAXIS & movementState))
    {
		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), animation);
	}
}

void Hero_takeHitFrom(Hero this, Actor other, bool pause)
{
    if (!Hero_isInvincible(this))
    {
        if((this->energy > 0) || (this->powerUp != kPowerUpNone))
        {
        	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Hit");

            Hero_setInvincible(this, true);

            // reset invincible a bit later
            MessageDispatcher_dispatchMessage(HERO_FLASH_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kStopInvincibility, NULL);

            // start flashing of hero
            MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kFlash);
            MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kFlash, NULL);

            // lose power-up or reduce energy
            if(this->powerUp != kPowerUpNone)
            {
                Hero_losePowerUp(this);
            }
            else
            {
                this->energy--;
            }

            if(pause)
            {
	        	Game_pausePhysics(Game_getInstance(), true);
	        	MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kResumeGame, NULL);
	        	Game_disableKeypad(Game_getInstance());
            }

            // start short screen shake
            Screen_startEffect(Screen_getInstance(), kShake, 200);

            // play hit sound
            SoundManager_playFxSound(SoundManager_getInstance(), FIRE_SND, this->transform.globalPosition);
        }
        else
        {
            Hero_setInvincible(this, true);

            MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kFlash, NULL);
            Game_pausePhysics(Game_getInstance(), true);
        	MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroDied, NULL);
        	return;
        }

        // inform others to update ui etc
        Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_HIT_TAKEN);

        // must unregister the shape for collision detections
        // Shape_setActive(this->shape, false);
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
        MessageDispatcher_dispatchMessage(HERO_FLASH_INTERVAL, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kFlash, NULL);
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
void Hero_setAnimationDelta(Hero this, int delta)
{
	ASSERT(this, "Hero::setAnimationDelta: null this");

	ASSERT(this->sprites, "Hero::setAnimationDelta: null sprites");

	VirtualNode node = VirtualList_begin(this->sprites);
	
	for(; node; node = VirtualNode_getNext(node))
	{
		Sprite_setFrameDelayDelta(__SAFE_CAST(Sprite, VirtualNode_getData(node)), this->boost ? -2 : -1);
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

// check if the hero is overlapping a door
bool Hero_isOverlappingDoor(Hero this)
{
	ASSERT(this, "Hero::isOverlappingDoor: null this");

	bool isOverlapping = false;

	// check if hero recently passed a door and is still doing so
	if(
		(Hero_getCurrentlyOverlappingDoor(this) != NULL) &&
		__VIRTUAL_CALL(int, Shape, overlaps, Entity_getShape(__SAFE_CAST(Entity, this)), Entity_getShape(__SAFE_CAST(Entity, Hero_getCurrentlyOverlappingDoor(this))))
	)
	{
		isOverlapping = true;
	}

	return isOverlapping;
}

// check if the hero is overlapping a hide layer
bool Hero_isOverlappingHideLayer(Hero this)
{
	ASSERT(this, "Hero::isOverlappingHideLayer: null this");

	bool isOverlapping = false;

	// check if hero recently passed a hide layer and is still doing so
	if(
		(Hero_getCurrentlyOverlappingHideLayer(this) != NULL) &&
		__VIRTUAL_CALL(int, Shape, overlaps, Entity_getShape(__SAFE_CAST(Entity, this)), Entity_getShape(__SAFE_CAST(Entity, Hero_getCurrentlyOverlappingHideLayer(this))))
	)
	{
		isOverlapping = true;
	}

	return isOverlapping;
}

void Hero_enterDoor(Hero this)
{
	ASSERT(this, "Hero::enterDoor: null this");

	Hero_lookBack(this);

	if((__YAXIS | __ZAXIS) & Body_isMoving(this->body))
	{
		return;
	}

	// inform the door entity
	MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Hero_getCurrentlyOverlappingDoor(this)), kEnterDoor, NULL);

	// reset currently overlapping door
	Hero_setCurrentlyOverlappingDoor(this, NULL);

	// hide hint immediately
	if(this->currentHint != NULL)
	{
		Entity_hide(__SAFE_CAST(Entity, this->currentHint));
	}

	// play door sound
    SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, this->transform.globalPosition);
}

static void Hero_addHints(Hero this)
{
	ASSERT(this, "Hero::addHints: null this");

	VBVec3D position = {FTOFIX19_13(25), FTOFIX19_13(-20), FTOFIX19_13(-SORT_INCREMENT * 4)};

    // save the hint entity, so we can remove it later
	this->currentHint = Entity_addChildFromDefinition(__SAFE_CAST(Entity, this), &HINT_ENTER_MC, -1, "enterHint", &position, NULL);
}

static void Hero_addFeetDust(Hero this)
{
	ASSERT(this, "Hero::addFeetDust: null this");

	VBVec3D position = 
	{
		FTOFIX19_13(-6), FTOFIX19_13(11), FTOFIX19_13(1)
	};

	this->feetDust = __SAFE_CAST(ParticleSystem, Entity_addChildFromDefinition(__SAFE_CAST(Entity, this), &DUST_PS, -1, "feetDust", &position, NULL));

	ASSERT(this->feetDust, "Hero::addFeetDust: null feetDust");
}

void Hero_showHint(Hero this, char* hintName)
{
	ASSERT(this, "Hero::showHint: null this");
	
	// close any previous opened hint
	Hero_hideHint(this);

	this->currentHint = __SAFE_CAST(Entity, Container_getChildByName(__SAFE_CAST(Container, this), hintName, false));
    
	ASSERT(this->currentHint, "Hero::showHint: null currentHint");

	Hint_open((Hint)this->currentHint);
}

void Hero_hideHint(Hero this)
{
    // check if a hint is being shown at the moment
	if(this->currentHint)
	{
	    // play the closing animation (the hint will delete itself afterwards)
		Hint_close(__SAFE_CAST(Hint, this->currentHint));
	}
}

// make hero to look to the player
void Hero_lookFront(Hero this)
{
	// if already not playing
	if(!AnimatedInGameEntity_isAnimationLoaded(__SAFE_CAST(AnimatedInGameEntity, this), "Front"))
    {
		// play animation
		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Front");
	}
}

// make hero to look away from the player
void Hero_lookBack(Hero this)
{
	// if already not playing
	if(!AnimatedInGameEntity_isAnimationLoaded(__SAFE_CAST(AnimatedInGameEntity, this), "Back"))
    {
		// play animation
		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Back");
	}
}

// die hero
void Hero_die(Hero this)
{
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_HERO_DIED);

    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kFlash);

	Container_deleteMyself(__SAFE_CAST(Container, this));

    /*
	// go to dead state
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, HeroDead_getInstance()));

	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);

	// change in game state
	this->inGameState = kDead;
	*/
}

// process user input
static void Hero_onKeyPressed(Hero this, Object eventFirer)
{
	u16 pressedKey = KeypadManager_getPressedKey(KeypadManager_getInstance());
	
	// inform my current states about the key pressed
	MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this->stateMachine), kKeyPressed, &pressedKey);
}

// process user input
static void Hero_onKeyReleased(Hero this, Object eventFirer)
{
	u16 releasedKey = KeypadManager_getReleasedKey(KeypadManager_getInstance());

	// inform my current states about the key up		
	MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this->stateMachine), kKeyReleased, &releasedKey);
}

// process user input
static void Hero_onKeyHold(Hero this, Object eventFirer)
{
	u16 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

	// inform my current states about the key hold		
	MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this->stateMachine), kKeyHold, &holdKey);
}

// collect a key
void Hero_collectKey(Hero this)
{
	this->hasKey = true;
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_KEY_TAKEN);
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
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_POWERUP);

	Game_pausePhysics(Game_getInstance(), true);
	MessageDispatcher_dispatchMessage(1000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kResumeGame, NULL);

	// TODO: play "get powerup" animation
    //AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Transition");

	// play collect sound
    SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, this->transform.globalPosition);
}

// lose a power-up
void Hero_losePowerUp(Hero this)
{
	this->powerUp = kPowerUpNone;
	Hero_updateSprite(this);
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_POWERUP);
}

// update sprite, i.e. after collecting a power-up
void Hero_updateSprite(Hero this)
{
	switch(this->powerUp)
	{
		case kPowerUpBandana:
			CharSet_setCharSetDefinition(Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites)))), &HERO_BANDANA_CH);
			break;

		default:
		case kPowerUpNone:
			CharSet_setCharSetDefinition(Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites)))), &HERO_CH);
			break;
	}
}

// get current power-up
u8 Hero_getPowerUp(Hero this)
{
	return this->powerUp;
}

// collect a coin
void Hero_collectCoin(Hero this, Coin coin)
{
    if(!Coin_taken(coin))
    {
        int numberOfCollectedCoins = ProgressManager_getNumberOfCollectedCoins(ProgressManager_getInstance());
        numberOfCollectedCoins++;
        ProgressManager_setNumberOfCollectedCoins(ProgressManager_getInstance(), numberOfCollectedCoins);
        ProgressManager_setCoinStatus(ProgressManager_getInstance(), Container_getName(__SAFE_CAST(Container, coin)), true);
        Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_COIN_TAKEN);

        SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, this->transform.globalPosition);
    }
}

// get number of collected coins
u8 Hero_getCoins(Hero this)
{
	return ProgressManager_getNumberOfCollectedCoins(ProgressManager_getInstance());
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

// get door the hero is currently overlapping
Door Hero_getCurrentlyOverlappingDoor(Hero this)
{
	return this->currentlyOverlappingDoor;
}

// get hide layer the hero is currently overlapping
HideLayer Hero_getCurrentlyOverlappingHideLayer(Hero this)
{
	return this->currentlyOverlappingHideLayer;
}

// set door the hero is currently overlapping
void Hero_setCurrentlyOverlappingDoor(Hero this, Door door)
{
	if(door) 
	{
		// open the door
		MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, door), kOpenDoor, NULL);
	}
	else if(this->currentlyOverlappingDoor)
	{
		// close the door
		MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this->currentlyOverlappingDoor), kCloseDoor, NULL);
	}
	
	this->currentlyOverlappingDoor = door;
}

// set hide layer the hero is currently overlapping
void Hero_setCurrentlyOverlappingHideLayer(Hero this, HideLayer hideLayer)
{
	if(hideLayer)
	{
        AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, hideLayer), "ToTransparent");
	}

	this->currentlyOverlappingHideLayer = hideLayer;
}

void Hero_resetCurrentlyOverlappingDoor(Hero this)
{
	// reset currently overlapping door
	Hero_setCurrentlyOverlappingDoor(this, NULL);

	// remove door enter hint
	Hero_hideHint(this);
}

void Hero_resetCurrentlyOverlappingHideLayer(Hero this)
{
    if(this->currentlyOverlappingHideLayer)
    {
        AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this->currentlyOverlappingHideLayer), "ToSolid");
    }

	// reset currently overlapping hide layer
	Hero_setCurrentlyOverlappingHideLayer(this, NULL);
}

// process collisions
int Hero_processCollision(Hero this, Telegram telegram)
{
	ASSERT(this, "HeroMoving::processCollision: null this");
	VirtualList collidingObjects = __SAFE_CAST(VirtualList, Telegram_getExtraInfo(telegram));
	ASSERT(collidingObjects, "HeroMoving::processCollision: null collidingObjects");

	VirtualNode node = NULL;

	VirtualList collidingObjectsToRemove = __NEW(VirtualList);

	for(node = VirtualList_begin(collidingObjects); node; node = VirtualNode_getNext(node))
    {
		InGameEntity inGameEntity = __SAFE_CAST(InGameEntity, VirtualNode_getData(node));

		switch(InGameEntity_getInGameType(inGameEntity))
        {
			case kCameraTarget:
				{
					VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);

	                // get the axis of collision
	                u8 axisOfCollision = __VIRTUAL_CALL(
	                    int,
	                    Shape,
	                    getAxisOfCollision,
	                    this->shape,
	                    VirtualNode_getData(node),
	                    Body_getLastDisplacement(this->body),
	                    CollisionSolver_getOwnerPreviousPosition(this->collisionSolver)
	                );
	                
                    if(axisOfCollision & __YAXIS)
                    {
                    	Hero_lockCameraTriggerMovement(this, __YAXIS, false);
                    }

                    if(axisOfCollision & __XAXIS)
                    {
                    	Hero_lockCameraTriggerMovement(this, __XAXIS, false);
                    }
                    else
                    {
                    	Hero_lockCameraTriggerMovement(this, __YAXIS, false);
                    }

					VBVec3D position =
					{
		                0,
		                ITOFIX19_13(-8),
		                0,
					};
	
					__VIRTUAL_CALL(void, Container, setLocalPosition, this->cameraBoundingBox, &position);
				}
				break;
				
			case kCoin:

				Hero_collectCoin(this, __SAFE_CAST(Coin, inGameEntity));
				MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, inGameEntity), kTaken, NULL);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kKey:

				Hero_collectKey(this);
				MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, inGameEntity), kTaken, NULL);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kBandana:

				Hero_collectPowerUp(this, kPowerUpBandana);
				MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, inGameEntity), kTaken, NULL);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kHideLayer:

			    // TODO: let the overlapping entities handle overlapping logic

                // first contact with hide layer?
				if(Hero_getCurrentlyOverlappingHideLayer(this) == NULL)
				{
                    Hero_setCurrentlyOverlappingHideLayer(this, __SAFE_CAST(HideLayer, inGameEntity));

                    // remind hero to check if hide layer is still overlapping in 100 milliseconds
                    MessageDispatcher_dispatchMessage(100, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCheckForOverlappingHideLayer, NULL);
				}
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kDoor:

			    // TODO: let the overlapping entities handle overlapping logic

                // first contact with door?
				if(Hero_getCurrentlyOverlappingDoor(this) == NULL && Door_hasDestination((Door)inGameEntity))
				{
				    Hero_showHint(this, "enterHint");
                    Hero_setCurrentlyOverlappingDoor(this, __SAFE_CAST(Door, inGameEntity));

                    // remind hero to check if door is still overlapping in 100 milliseconds
                    MessageDispatcher_dispatchMessage(100, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCheckForOverlappingDoor, NULL);
				}
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kLava:

				Hero_die(this);
//				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kSawBlade:
			case kCannonBall:

                Hero_takeHitFrom(this, __SAFE_CAST(Actor, inGameEntity), true);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kHit:

                Hero_takeHitFrom(this, NULL, true);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kLavaTrigger:

				MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, inGameEntity), kLavaTriggerStart, NULL);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				Hero_stopAddingForce(this);		
				break;

				/*
			case kTopSolid:
            {
            	
                // get the axis of collision
                u8 axisOfCollision = __VIRTUAL_CALL(
                    int,
                    Shape,
                    getAxisOfCollision,
                    this->shape,
                    VirtualNode_getData(node),
                    Body_getLastDisplacement(this->body),
                    CollisionSolver_getOwnerPreviousPosition(this->collisionSolver)
                );

                // get positions of colliding entities
                int heroBottomPosition = this->transform.globalPosition.y + ITOFIX19_13(Entity_getHeight(__SAFE_CAST(Entity, this)) >> 2);
                int collidingEntityTopPosition = Entity_getPosition(__SAFE_CAST(Entity, VirtualNode_getData(node)))->y - ITOFIX19_13(Entity_getHeight(__SAFE_CAST(Entity, inGameEntity)) >> 2);

                // process collision only if axis of collision is y and if hero is above platform
                if(!((__YAXIS & axisOfCollision) && (heroBottomPosition <= collidingEntityTopPosition)))
                {
    				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
                }
                */
			case kTopSolid:

				if(0 >= Body_getVelocity(this->body).y)
            	{
    				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
                }

				break;
		}
	}

	for(node = VirtualList_begin(collidingObjectsToRemove); node; node = VirtualNode_getNext(node))
    {
		// whenever you process some objects of a collisions list remove them and leave the Actor handle
		// the ones you don't care about, i.e.: in most cases, the ones which are solid
		VirtualList_removeElement(collidingObjects, VirtualNode_getData(node));
	}
	
	__DELETE(collidingObjectsToRemove);

	return !VirtualList_getSize(collidingObjects);
}

bool Hero_handleMessage(Hero this, Telegram telegram)
{
	ASSERT(this, "HeroMoving::handleMessage: null this");

	// handle messages that any state would handle here
	switch(Telegram_getMessage(telegram))
    {
        case kCheckForOverlappingDoor:

            if(!Hero_isOverlappingDoor(this))
            {
                Hero_resetCurrentlyOverlappingDoor(this);
            }
            else
            {
                // remind hero to check again in 100 milliseconds
                MessageDispatcher_dispatchMessage(100, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCheckForOverlappingDoor, NULL);
            }

            return true;
            break;

        case kCheckForOverlappingHideLayer:

            if(!Hero_isOverlappingHideLayer(this))
            {
                Hero_resetCurrentlyOverlappingHideLayer(this);
            }
            else
            {
                // remind hero to check again in 100 milliseconds
                MessageDispatcher_dispatchMessage(100, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCheckForOverlappingHideLayer, NULL);
            }

            return true;
            break;

        case kStopFeetDust:

            Hero_hideDust(this);
            return true;
            break;

        case kStopInvincibility:

            Hero_setInvincible(this, false);
            return true;
            break;

        case kFlash:

        	Hero_flash(this);
            return true;
            break;

        case kResumeGame:

        	Game_pausePhysics(Game_getInstance(), false);
        	Game_enableKeypad(Game_getInstance());
        	if(!(__YAXIS & Body_isMoving(this->body)))
        	{
        		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Walk");
        	}
        	break;

        case kHeroDied:
        	
        	Hero_die(this);
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
		case kSetUpLevel:
			{
				// set focus on the hero
				VBVec3D position =
				{
	                ITOFIX19_13(0),
	                ITOFIX19_13(-16),
	                ITOFIX19_13(0),
				};
	
				CustomScreenMovementManager_setTransformationBaseEntity(CustomScreenMovementManager_getInstance(), __SAFE_CAST(Entity, this));
				this->cameraBoundingBox = Entity_addChildFromDefinition(__SAFE_CAST(Entity, this), (EntityDefinition*)&CAMERA_BOUNDING_BOX_IG, 0, NULL, &position, NULL);
				CollisionManager_shapeStartedMoving(CollisionManager_getInstance(), Entity_getShape(__SAFE_CAST(Entity, this->cameraBoundingBox)));
	
				// set focus on the hero
				VBVec3D screenDisplacement =
				{
	                0,
	                ITOFIX19_13(0),
	                ITOFIX19_13(-LAYER_0),
				};
	
				Screen_setFocusEntityPositionDisplacement(Screen_getInstance(), screenDisplacement);

				Hero_lockCameraTriggerMovement(this, __XAXIS | __YAXIS, true);
			}
			
			//Hero_locateOverNextFloor(this);

			break;

	}

	return false;
}

void Hero_suspend(Hero this)
{
	ASSERT(this, "Hero::suspend: null this");

	Entity_suspend(__SAFE_CAST(Entity, this));
	
	ParticleSystem_pause(this->feetDust);
	
//	Hero_lockCameraTriggerMovement(this, __XAXIS | __YAXIS, true);
}

void Hero_resume(Hero this)
{
	ASSERT(this, "Hero::resume: null this");

	Actor_resume(__SAFE_CAST(Actor, this));

	Screen_position(Screen_getInstance(), false);
	
	Hero_lockCameraTriggerMovement(this, __XAXIS | __YAXIS, true);

	VBVec3DFlag positionFlag = {true, true, true};
    CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager_getInstance(), positionFlag);
	CustomScreenMovementManager_setTransformationBaseEntity(CustomScreenMovementManager_getInstance(), __SAFE_CAST(Entity, this));
}	
