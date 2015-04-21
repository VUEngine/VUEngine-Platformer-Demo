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

#include <Hint.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------


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


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern double fabs (double);

static u32 gameLayers[TOTAL_GAME_LAYERS] =
{
	ITOFIX19_13(LAYER_0),
	ITOFIX19_13(LAYER_1),
	ITOFIX19_13(LAYER_2),
	ITOFIX19_13(LAYER_3),
	ITOFIX19_13(LAYER_4),
};

#define HERO_INPUT_FORCE 						ITOFIX19_13(750)
#define HERO_WHILE_JUMPIN_INPUT_FORCE			ITOFIX19_13(400)
#define HERO_MASS								(10)
#define FRICTION 								0.01f

#define HERO_VELOCITY_X							ITOFIX19_13(60)
#define HERO_VELOCITY_Y							ITOFIX19_13(-60)
#define HERO_VELOCITY_Z							ITOFIX19_13(60)
#define HERO_ACCELERATION_X						ITOFIX19_13(100)
#define HERO_ACCELERATION_Y						ITOFIX19_13(0)
#define HERO_ACCELERATION_Z						ITOFIX19_13(0)
#define HERO_BOOST_VELOCITY_X					FTOFIX19_13(90)
#define HERO_STEERING_VELOCITY_X				FTOFIX19_13(30)
#define HERO_NORMAL_JUMP_HERO_INPUT_FORCE		ITOFIX19_13(-18000)
#define HERO_BOOST_JUMP_HERO_INPUT_FORCE		ITOFIX19_13(-21000)

#define HERO_TIME_TO_DIE		500	// milliseconds

#define HERO_HOLD_OBJECT_X		10
#define HERO_HOLD_OBJECT_Y		0
#define HERO_HOLD_OBJECT_Z		1

#define HERO_WIN_DELAY			1800
#define HERO_BLINK_DELAY		2000


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
__CLASS_NEW_DEFINITION(Hero, ActorDefinition* actorDefinition, int ID)
__CLASS_NEW_END(Hero, actorDefinition, ID);

// class's constructor
void Hero_constructor(Hero this, ActorDefinition* actorDefinition, int ID)
{
	ASSERT(this, "Hero::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(actorDefinition, ID);

	this->lifes = 3;
	this->energy = 1;
	this->coins = 0;
	this->keys = 0;
	this->currentHint = NULL;

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __UPCAST(Entity, this), kCuboid);

	{
		// register a body for physics
		this->body = PhysicalWorld_registerBody(PhysicalWorld_getInstance(), __UPCAST(Entity, this), ITOFIX19_13(HERO_MASS));
		
		Body_setElasticity(this->body, FTOFIX19_13(0.0f));
		
		Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));
	}

    // no door overlapping at start
	Hero_setCurrentlyOverlappingDoor(this, NULL);

	// I'm not holding anything
	this->holdObject = NULL;
	
	// I always start in the first layer
	this->layer = 0;

	this->actionTime = 0;
	
	this->boost = false;
	this->sensibleToFriction.y = false;
	
	Hero_setInstance(this);

	{
		Acceleration gravity =
        {
            ITOFIX19_13(0),
            ITOFIX19_13(4000),
            ITOFIX19_13(0)
        };
		
		PhysicalWorld_setGravity(PhysicalWorld_getInstance(), gravity);
		PhysicalWorld_setFriction(PhysicalWorld_getInstance(), FTOFIX19_13(FRICTION));
	}
	
	Object_addEventListener(__UPCAST(Object, Game_getCurrentState(Game_getInstance())), __UPCAST(Object, this), (void (*)(Object, Object))Hero_onKeyPressed, EVENT_KEY_PRESSED);
	Object_addEventListener(__UPCAST(Object, Game_getCurrentState(Game_getInstance())), __UPCAST(Object, this), (void (*)(Object, Object))Hero_onKeyReleased, EVENT_KEY_RELEASED);
	Object_addEventListener(__UPCAST(Object, Game_getCurrentState(Game_getInstance())), __UPCAST(Object, this), (void (*)(Object, Object))Hero_onKeyHold, EVENT_KEY_HOLD);

	this->inputDirection = this->direction;
}

// class's destructor
void Hero_destructor(Hero this)
{
	// free the instance pointer
	ASSERT(this, "Hero::destructor: null this");
	ASSERT(hero, "Hero::destructor: already deleted");
	ASSERT(hero == this, "Hero::destructor: more than one instance");

	MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, Game_getInstance()), kHeroDied, NULL);

	hero = NULL;
	
	Object_removeEventListener(__UPCAST(Object, Game_getCurrentState(Game_getInstance())), __UPCAST(Object, this), (void (*)(Object, Object))Hero_onKeyPressed, EVENT_KEY_PRESSED);
	Object_removeEventListener(__UPCAST(Object, Game_getCurrentState(Game_getInstance())), __UPCAST(Object, this), (void (*)(Object, Object))Hero_onKeyReleased, EVENT_KEY_RELEASED);
	Object_removeEventListener(__UPCAST(Object, Game_getCurrentState(Game_getInstance())), __UPCAST(Object, this), (void (*)(Object, Object))Hero_onKeyHold, EVENT_KEY_HOLD);

	Screen_setFocusInGameEntity(Screen_getInstance(), NULL);

	// delete the super object
	__DESTROY_BASE;
}

// initialize method
void Hero_initialize(Hero this)
{
	ASSERT(this, "Hero::initialize: null this");

	AnimatedInGameEntity_initialize(__UPCAST(AnimatedInGameEntity, this));
	
	// initialize me as idle
	StateMachine_swapState(this->stateMachine, __UPCAST(State, HeroIdle_getInstance()));
}

// make him jump
void Hero_jump(Hero this, int changeState, int checkIfYMovement)
{
	ASSERT(this, "Hero::jump: null this");

	Hero_startedMovingOnAxis(this, __YAXIS);

	if (this->body)
    {
        Velocity velocity = Body_getVelocity(this->body);

		Acceleration acceleration =
        {
        	0,
			ITOFIX19_13(1),
			0
		};

		if ((!checkIfYMovement || !velocity.y) && !(__YAXIS & Actor_canMoveOverAxis(__UPCAST(Actor, this), &acceleration)))
        {
			Force force =
            {
                0,
                this->boost ? HERO_BOOST_JUMP_HERO_INPUT_FORCE : HERO_NORMAL_JUMP_HERO_INPUT_FORCE,
                0
            };
			
			Actor_addForce(__UPCAST(Actor, this), &force);
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Jump");
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
	
	if (this->direction.x != this->inputDirection.x || 
			((__XAXIS & axis) && maxVelocity > fabs(velocity.x)) || 
			((__ZAXIS & axis) && maxVelocity > fabs(velocity.z)) || 
			Actor_changedDirection(__UPCAST(Actor, this), __XAXIS) || 
			Actor_changedDirection(__UPCAST(Actor, this), __ZAXIS))
    {
		fix19_13 inputForce = __YAXIS & Body_isMoving(this->body)? HERO_WHILE_JUMPIN_INPUT_FORCE: HERO_INPUT_FORCE;
		fix19_13 xForce = (__XAXIS & axis)? __RIGHT == this->inputDirection.x? inputForce: -inputForce: 0;
		fix19_13 zForce = 0; //(__ZAXIS & axis)? __FAR == this->inputDirection.z? inputForce: -inputForce: 0;
		Force force =
        {
            xForce,
            0,
            zForce
        };

		Actor_addForce(__UPCAST(Actor, this), &force);
		movementType = __ACCELERATED_MOVEMENT;
	}
	else
    {
		Velocity newVelocity =
        {
        	(__XAXIS & axis)? ((int)maxVelocity * this->inputDirection.x): 0,
			0,
			(__ZAXIS & axis)? ((int)maxVelocity * this->inputDirection.z): 0,
		};
		
		if (__UNIFORM_MOVEMENT != movementType || (abs(velocity.x) > maxVelocity && !(__YAXIS & Body_isMoving(this->body))))
        {
			movementType = __UNIFORM_MOVEMENT;
			Body_moveUniformly(this->body, newVelocity);
		}
	}
	
	if (!(__YAXIS & Body_isMoving(this->body)) && AnimatedInGameEntity_isAnimationLoaded(__UPCAST(AnimatedInGameEntity, this), "Slide"))
    {
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Walk");
	}			
}

// start movement
void Hero_stopMovement(Hero this)
{
	ASSERT(this, "Hero::stopMovement: null this");

	Velocity velocity = Body_getVelocity(this->body);

	if (!(__YAXIS & Body_isMoving(this->body)))
    {
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Slide");
	}
	else if (!AnimatedInGameEntity_isAnimationLoaded(__UPCAST(AnimatedInGameEntity, this), "Fall"))
    {
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Fall");
	}

	// begin to desaccelerate
	int axisOfDeacceleartion = 0;
	axisOfDeacceleartion |= velocity.x? __XAXIS: 0;
	axisOfDeacceleartion |= velocity.z? __ZAXIS: 0;
	Body_clearAcceleration(this->body, __XAXIS);
	Body_moveAccelerated(this->body, axisOfDeacceleartion);
}

// started moving over axis
void Hero_startedMovingOnAxis(Hero this, int axis)
{
	// start movement
	if (__UPCAST(State, HeroMoving_getInstance()) != StateMachine_getCurrentState(this->stateMachine))
    {
 		if (__XAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Walk");
		}
 		else if (__YAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Fall");
		}

		StateMachine_swapState(Actor_getStateMachine(__UPCAST(Actor,  this)), __UPCAST(State,  HeroMoving_getInstance()));
	}
	else
	{
		bool movementState = Body_isMoving(this->body);

		if ((__XAXIS & axis)  && !(__YAXIS & movementState))
        {
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Walk");
		}

		if (__YAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Fall");
		}

		if (__ZAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Walk");
		}
	}
}

// stop moving over axis
bool Hero_stopMovingOnAxis(Hero this, int axis)
{
	ASSERT(this, "Hero::stopMovingOnAxis: null this");

	bool movementState = Body_isMoving(this->body);

	if ((__XAXIS & axis) && !(__YAXIS & movementState))
    {
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Idle");
	}

	if (__YAXIS & axis)
    {
		MovementType movementType = Body_getMovementType(this->body);
		
		if (__UNIFORM_MOVEMENT == movementType.x)
        {
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Walk");
		}
		else
        {
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Slide");
		}
	}

	if (__ZAXIS & axis)
    {
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Idle");
		StateMachine_swapState(this->stateMachine, __UPCAST(State, HeroIdle_getInstance()));					
		return true;
	}

	if (!Body_isMoving(Actor_getBody(__UPCAST(Actor, this))) && __UPCAST(State, HeroIdle_getInstance()) != StateMachine_getCurrentState(this->stateMachine))
    {
		StateMachine_swapState(this->stateMachine, __UPCAST(State, HeroIdle_getInstance()));					
	}
	
	return false;
}

// check direction
void Hero_checkDirection(Hero this, u16 pressedKey, char* animation)
{
	ASSERT(this, "Hero::checkDirection: null this");

	bool movementState = Body_isMoving(this->body);

	if (K_LR & pressedKey)
    {
		this->inputDirection.x = __RIGHT;
	}
	else if (K_LL & pressedKey)
    {
		this->inputDirection.x = __LEFT;
	}
	else if (K_LU & pressedKey)
    {
		this->inputDirection.z = __FAR;
	}
	else if (K_LD & pressedKey)
    {
		this->inputDirection.z = __NEAR;
	}

	if (animation && !(__YAXIS & movementState))
    {
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), animation);
	}
}

// check direction
void Hero_synchronizeDirectionWithVelocity(Hero this)
{
	ASSERT(this, "Hero::synchronizeDirectionWithVelocity: null this");

    Velocity velocity = Body_getVelocity(this->body);

	if (0 < velocity.x)
    {
		this->direction.x = __RIGHT;
	}
	else if (0 > velocity.x)
    {
		this->direction.x = __LEFT;
	}
}

void Hero_takeHitFrom(Hero this, Actor other)
{
	//VBVec3D position = Entity_getPosition(__UPCAST(Entity, other));
	/*
	// first stop all movement
	Actor_stopMovement(__UPCAST(Actor, this), __XAXIS | __YAXIS | __ZAXIS);
	
	// reduce energy
	if (--this->energy)
    {

	}
	else
	{
		// now die
		Hero_die(this);
	}
	
	// determine which animation to play
	// based on my position relative to the
	// enemy position
	if (position.x > this->transform.globalPosition.x)
    {
		if (__RIGHT == this->direction.x)
        {
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "HitFront");
		}
		else{
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "HitBehind");
		}
	}
	else
	{
		if (__LEFT == this->direction.x)
		{
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "HitFront");
		}
		else
		{
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "HitBehind");
		}							
	}
	
	// register time
	this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);
	*/
}

/*
bool Hero_isHitByEnemy(Hero this, Enemy enemy, int axis)
{
	ASSERT(enemy, "Hero::isHitByEnemy: null enemy");

	
	// if enemy is already dead
	if (kDead == Actor_getInGameState(__UPCAST(Actor, enemy)))
    {
		return false;
	}
	
	// if it is the holdobject which wants to hit me
	if (this->holdObject == __UPCAST(Actor, enemy))
    {
		this->holdObject = NULL;
		return true;
	}
	

	// check if I'm over the enemy
	if ((this->velocity.y && __DOWN == this->direction.y) &&
	    (
    		this->transform.globalPosition.y + ITOFIX19_13(Entity_getHeight(__UPCAST(Entity, this)) >> 2) <
    		Entity_getPosition(__UPCAST(Entity, enemy)).y
    	)
    )
    {
		// align to the colliding object
		Actor_alignTo(__UPCAST(Actor, this), __UPCAST(InGameEntity, enemy), __XAXIS, 2);
		
		//check if player wants to jump over z axis
		if (!Hero_checkIfZJump(this))
        {
			
			if (this->holdObject)
            {
				// play animation
				AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "JumpHolding");
			}
			else{
				
				// play animation
				AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Jump");
			}
		}

		// if A button is pressed boost the y velocity
		if (K_A & vbKeyPressed())
        {
			// I will bounce
			Actor_jump(__UPCAST(Actor, this), FIX19_13_MULT(HERO_VELOCITY_Y, HERO_SPEED_MULTIPLIER_Y), HERO_ACCELERATION_Y);
		}
		else
		{
			// I will bounce
			Actor_jump(__UPCAST(Actor, this), HERO_VELOCITY_Y , HERO_ACCELERATION_Y);
		}

		// tell enemy I've hit him
        __VIRTUAL_CALL(void, Enemy, takeHit, (Enemy)enemy, __XAXIS, this->direction.x);
			
		return false;
	}

	// if I'm holding something
	if (this->holdObject)
    {
		// if I'm facing the enemy
		if ((this->transform.globalPosition.x <  Entity_getPosition(__UPCAST(Entity, enemy)).x && __RIGHT == this->direction.x)
			||
			(this->transform.globalPosition.x >  Entity_getPosition(__UPCAST(Entity, enemy)).x && __LEFT == this->direction.x)
			)
        {
			// tell enemy to die
			__VIRTUAL_CALL(void, Actor, die, __UPCAST(Actor, enemy));
			
			// hold object must be destroyed
			__VIRTUAL_CALL(void, Actor, die, __UPCAST(Actor, this->holdObject));
			
			// holding nothing now
			this->holdObject = NULL;
			
			return false;
		}
	}

	// if collision was over x axis
	if (kCollisionX == axis && !(__VIRTUAL_CALL(int, Enemy, canAttack, enemy) ||	this->holdObject))
    {
		// if B button is pressed, pick up
		if (K_B & vbKeyPressed())
        {
			if (!this->holdObject)
            {
				Hero_pickupObject(this, __UPCAST(Actor, enemy));
				return false;
			}
		}
		
		// stop my movement
		Actor_stopMovement(__UPCAST(Actor, this), __XAXIS);

		// align to the colliding object
		Actor_alignTo(__UPCAST(Actor, this), __UPCAST(InGameEntity, enemy), __XAXIS, 1);

		// tell enemy to begin bouncing
		__VIRTUAL_CALL(void, Enemy, takeHit, (Enemy)enemy, __XAXIS, this->direction.x);

		// I will bounce
		Actor_jump(__UPCAST(Actor, this), FIX19_13_DIV(HERO_VELOCITY_Y, ITOFIX19_13(2)), HERO_ACCELERATION_Y);
		
		if (this->holdObject)
        {
			// play animation
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "JumpHolding");
		}
		else
		{
			// play animation
			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Jump");
		}
		return false;
	}
	// otherwise... I was hit by the enemy
	return true;
}
*/

// set animation delta
void Hero_setAnimationDelta(Hero this, int delta)
{
	ASSERT(this, "Hero::setAnimationDelta: null this");

	ASSERT(this->sprites, "Hero::setAnimationDelta: null sprites");

	VirtualNode node = VirtualList_begin(this->sprites);
	
	for (; node; node = VirtualNode_getNext(node))
	{
		Sprite_setFrameDelayDelta(__UPCAST(Sprite, VirtualNode_getData(node)), this->boost ? -2 : -1);
	}
}

// disable boost
void Hero_disableBoost(Hero this)
{
	ASSERT(this, "Hero::disableBoost: null this");

	if (this->boost)
    {
		this->boost = false;
		Hero_setAnimationDelta(this, -1);
	}
}

// enable boost
void Hero_enableBoost(Hero this)
{
	if (!this->boost)
    {
		this->boost = true;
		
		Hero_setAnimationDelta(this, -2);
	}
}

// set action time
void Hero_setActionTime(Hero this, u32 time)
{
	//this->actionTime = time;
}

// retrieve action time
u32 Hero_getActionTime(Hero this)
{
	return 0;
//	return this->actionTime;
}

// pickup an object
void Hero_pickupObject(Hero this, Actor object)
{
	/*
	VBVec3D position =
    {
        ITOFIX19_13(-25),
        ITOFIX19_13(-10),
        0
    };
	Entity child = Entity_load(&FLOOR1_BG, &position, 1, NULL);

	__VIRTUAL_CALL(void, Container, addChild, __UPCAST(Container, this), child);

	this->holdObject = object;
	
	// set hold object's position
	Hero_updateHoldObjectPosition(this);
	
	// remove from collision detection system
	InGameEntity_setShapeState(__UPCAST(InGameEntity, this->holdObject), false);
	*/
}

// check if the hero is overlapping a door
bool Hero_isOverlappingDoor(Hero this)
{
	ASSERT(this, "Hero::isOverlappingDoor: null this");

	bool isOverlapping = false;

	// check if hero recently passed a door and is still doing so
	if (
		(Hero_getCurrentlyOverlappingDoor(this) != NULL) &&
		__VIRTUAL_CALL(int, Shape, overlaps, Entity_getShape(__UPCAST(Entity, this)), Entity_getShape(__UPCAST(Entity, Hero_getCurrentlyOverlappingDoor(this))))
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

	if ((__YAXIS | __ZAXIS) & Body_isMoving(this->body)) 
	{
		return;
	}

	// inform the door entity
	MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, Hero_getCurrentlyOverlappingDoor(this)), kEnterDoor, NULL);

	// reset currently overlapping door
	Hero_setCurrentlyOverlappingDoor(this, NULL);
	
	// hide hint inmediately
	if (this->currentHint != NULL)
	{
		Entity_hide(__UPCAST(Entity, this->currentHint));
	}
}

void Hero_showHint(Hero this, u8 type)
{
	ASSERT(this, "Hero::showHint: null this");
	
    const EntityDefinition* hintEntityDefinition = NULL;

    // check if a hint is already being shown at the moment
	if (NULL == this->currentHint)
	{
	    // determine entity type for hint
	    switch (type)
	    {
	        default:
	        case kEnterHint:

	            hintEntityDefinition  = &HINT_ENTER_MC;
	            break;
	    }
	    
	    if(hintEntityDefinition)
	    {
	    	VBVec3D position = 
    		{
    			FTOFIX19_13(25), FTOFIX19_13(-20), FTOFIX19_13(0)
    		};

		    // save the hint entity, so we can remove it later
	    	this->currentHint = Entity_addChildFromDefinition(__UPCAST(Entity, this), hintEntityDefinition, -1, "enterHint", &position, NULL);
	    }
	}
	else
	{
		Hint_open((Hint)this->currentHint);
	}
}

void Hero_hideHint(Hero this)
{
    // check if a hint is being shown at the moment
	if (this->currentHint != NULL)
	{
	    // play the closing animation (the hint will delete itself afterwards)
		Hint_close((Hint)this->currentHint);
	}
}

void Hero_fallDead(Hero this)
{
	AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "HitFront");
	
	Hero_die(this);
}

// set hold object's position
void Hero_updateHoldObjectPosition(Hero this)
{
}

// make hero to look to the player
void Hero_lookFront(Hero this)
{
	// if already not playing
	if (!AnimatedInGameEntity_isAnimationLoaded(__UPCAST(AnimatedInGameEntity, this), "Front"))
    {
		// play animation
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Front");
	}
}

// make hero to look away the player
void Hero_lookBack(Hero this)
{
	// if already not playing
	if (!AnimatedInGameEntity_isAnimationLoaded(__UPCAST(AnimatedInGameEntity, this), "Back"))
    {
		// play animation
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Back");
	}
}

// set  graphical gap
void Hero_setGap(Hero this)
{
	this->gap = this->inGameEntityDefinition->gap;
	
	// if I'm not in the edge, return ROM gap
	if (AnimatedInGameEntity_isAnimationLoaded(__UPCAST(AnimatedInGameEntity, this), "OnEdge"))
    {
		// this is texture specific
		this->gap.left += 4;
		this->gap.right += 4;
	}
}

// make hero to look to the side
void Hero_lookSide(Hero this)
{
}

// check if must thrown an object
void Hero_throwObject(Hero this)
{
}

// die hero
void Hero_die(Hero this)
{
	this->lifes--;

    /*
	// go to dead state
	StateMachine_swapState(this->stateMachine, __UPCAST(State, HeroDead_getInstance()));

	// if I have something being hold
	if (this->holdObject)
    {
		// hold object must be destroyed
		__VIRTUAL_CALL(void, Actor, die, __UPCAST(Actor, this->holdObject));
	}

	// register time
	this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);

	// change in game state
	this->inGameState = kDead;
	*/
}

// determine which layer I'm
void Hero_determineLayer(Hero this)
{
	int i = 0;
	for (i = 0; i < TOTAL_GAME_LAYERS; i++)
    {
		if ((u16)this->transform.globalPosition.z > gameLayers[i] - HERO_INPUT_FORCE && (unsigned)this->transform.globalPosition.z < gameLayers[i] + HERO_INPUT_FORCE)
        {
			this->layer = (int )i;
			return;
		}
	}
}

// clear the actionTime
void Hero_resetActionTime(Hero this)
{
	//this->actionTime = Clock_getTime(Game_getClock(Game_getInstance()));
}

// goal reached
void Hero_win(Hero this)
{
	/*
	this->direction.z = __FAR;
	
	AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "WalkBack");
	
	Actor_startMovement(__UPCAST(Actor, this), __ZAXIS, __UNIFORMMOVE, FIX19_13_DIV(HERO_VELOCITY_Z, ITOFIX19_13(4)), 0);
	
	this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	*/
}

// goal reached
void Hero_moveOnWin(Hero this)
{
}

// process user input
static void Hero_onKeyPressed(Hero this, Object eventFirer)
{
	u16 pressedKey = KeypadManager_getPressedKey(KeypadManager_getInstance());
	
	// inform my current states about the key pressed
	MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, this->stateMachine), kKeyPressed, &pressedKey);
}

// process user input
static void Hero_onKeyReleased(Hero this, Object eventFirer)
{
	u16 releasedKey = KeypadManager_getReleasedKey(KeypadManager_getInstance());

	// inform my current states about the key up		
	MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, this->stateMachine), kKeyReleased, &releasedKey);
}

// process user input
static void Hero_onKeyHold(Hero this, Object eventFirer)
{
	u16 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

	// inform my current states about the key hold		
	MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, this->stateMachine), kKeyHold, &holdKey);
}

// collect a key
void Hero_collectKey(Hero this)
{
	this->keys++;
	Object_fireEvent(__UPCAST(Object, PlatformerLevelState_getInstance()), EVENT_KEY_TAKEN);
}

// get number of collected keys
u8 Hero_getKeys(Hero this)
{
	return this->keys;
}

// collect a coin
void Hero_collectCoin(Hero this)
{
	this->coins++;
	Object_fireEvent(__UPCAST(Object, PlatformerLevelState_getInstance()), EVENT_COIN_TAKEN);
}

// get number of collected coins
u8 Hero_getCoins(Hero this)
{
	return this->coins;
}

// get number of lifes
u8 Hero_getLifes(Hero this)
{
	return this->lifes;
}

// get door the hero is currently overlapping
Door Hero_getCurrentlyOverlappingDoor(Hero this)
{
	return this->currentlyOverlappingDoor;
}

// set door the hero is currently overlapping
void Hero_setCurrentlyOverlappingDoor(Hero this, Door door)
{
	if(door) 
	{
		// open the door
		MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, door), kOpenDoor, NULL);
	}
	else if(this->currentlyOverlappingDoor)
	{
		// close the door
		MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, this->currentlyOverlappingDoor), kCloseDoor, NULL);
	}
	
	this->currentlyOverlappingDoor = door;

}

void Hero_resetCurrentlyOverlappingDoor(Hero this)
{
	// reset currently overlapping door
	Hero_setCurrentlyOverlappingDoor(this, NULL);

	// remove door enter hint
	Hero_hideHint(this);
}

// process collisions
int Hero_processCollision(Hero this, Telegram telegram)
{
	VirtualList collidingObjects = __UPCAST(VirtualList, Telegram_getExtraInfo(telegram));
	ASSERT(collidingObjects, "HeroMoving::handleMessage: null collidingObjects");

	VirtualNode node = NULL;

	VirtualList collidingObjectsToRemove = __NEW(VirtualList);

	for (node = VirtualList_begin(collidingObjects); node; node = VirtualNode_getNext(node))
    {
		InGameEntity inGameEntity = __UPCAST(InGameEntity, VirtualNode_getData(node));
		
		switch (InGameEntity_getInGameType(inGameEntity))
        {
			case kCoin:

				Hero_collectCoin(this);
				MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, inGameEntity), kTakeCoin, NULL);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kKey:

				Hero_collectKey(this);
				MessageDispatcher_dispatchMessage(0, __UPCAST(Object, this), __UPCAST(Object, inGameEntity), kTakeKey, NULL);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kDoor:

                // first contact with a door?
				if (Hero_getCurrentlyOverlappingDoor(this) == NULL && Door_hasDestination((Door)inGameEntity))
				{
				    Hero_showHint(this, kEnterHint);
                    Hero_setCurrentlyOverlappingDoor(this, (Door)inGameEntity);

                    // remind hero to check if door is still overlapping in 100 milliseconds
                    MessageDispatcher_dispatchMessage(100, __UPCAST(Object, this), __UPCAST(Object, this), kCheckForOverlappingDoor, NULL);
				}
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;

			case kLava:

				Hero_die(this);
//				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;
		}
	}

	for (node = VirtualList_begin(collidingObjectsToRemove); node; node = VirtualNode_getNext(node))
    {
		// whenever you process some objects of a collisions list
		// remove them and leave the Actor handle the ones you don't
		// care, i.e.: in most cases, the ones which are solid
		VirtualList_removeElement(collidingObjects, VirtualNode_getData(node));
	}
	
	__DELETE(collidingObjectsToRemove);

	return !VirtualList_getSize(collidingObjects);
}

// process message
int Hero_doMessage(Hero this, int message)
{
	switch (message)
	{
		case kResumeLevel:
		case kSetUpLevel:
			{
				// then set myself as the focus
				Screen_setFocusInGameEntity(Screen_getInstance(), __UPCAST(InGameEntity, this));

				// set focus on the hero
				VBVec3D screenDisplacement =
				{
	                0,
	                ITOFIX19_13(0),
	                ITOFIX19_13(-LAYER_0),
				};
				
				Screen_setFocusEntityPositionDisplacement(Screen_getInstance(), screenDisplacement);
				
				if(Hero_getCurrentlyOverlappingDoor(this))
				{
                    // remind hero to check if door is still overlapping in 100 milliseconds
                    MessageDispatcher_dispatchMessage(100, __UPCAST(Object, this), __UPCAST(Object, this), kCheckForOverlappingDoor, NULL);
				}
				return true;
			}
			break;
	}

	return false;
}