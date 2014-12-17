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

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Hero);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void Hero_onKeyPressed(Hero this);
static void Hero_onKeyReleased(Hero this);
static void Hero_onKeyHold(Hero this);


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

#define HERO_INPUT_FORCE 						ITOFIX19_13(10)
#define HERO_WEIGHT								10
#define FRICTION 								0.01f

#define HERO_VELOCITY_X							ITOFIX19_13(7)
#define HERO_VELOCITY_Y							FTOFIX19_13(-6.0f)
#define HERO_VELOCITY_Z							ITOFIX19_13(7)
#define HERO_ACCELERATION_X						ITOFIX19_13(10)
#define HERO_ACCELERATION_Y						ITOFIX19_13(0)
#define HERO_ACCELERATION_Z						ITOFIX19_13(0)
#define HERO_BOOST_VELOCITY_X					ITOFIX19_13(9)
#define HERO_NORMAL_JUMP_HERO_INPUT_FORCE		ITOFIX19_13(-350)
#define HERO_BOOST_JUMP_HERO_INPUT_FORCE		ITOFIX19_13(-425)
#define HERO_SPEED_MULTIPLIER_X	FTOFIX19_13(1.5f)
#define HERO_SPEED_MULTIPLIER_Y	FTOFIX19_13(1.2f)

// time to wait after a hit, to die
#define HERO_TIME_TO_DIE		500	// miliseconds

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
__CLASS_NEW_DEFINITION(Hero, __PARAMETERS(ActorDefinition* actorDefinition, int ID))
__CLASS_NEW_END(Hero, __ARGUMENTS(actorDefinition, ID));

// class's constructor
void Hero_constructor(Hero this, ActorDefinition* actorDefinition, int ID)
{
	// construct base
	__CONSTRUCT_BASE(Actor, __ARGUMENTS(actorDefinition, ID));

	this->lifes = 3;
	this->energy = 1;
	this->coins = 0;

	// initialize me as idle
	StateMachine_swapState(this->stateMachine, (State)HeroIdle_getInstance());

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), (Entity)this, kCuboid);

	{
		// register a body for physics
		this->body = PhysicalWorld_registerBody(PhysicalWorld_getInstance(), (Actor)this, ITOFIX19_13(HERO_WEIGHT));
		
		Body_setElasticity(this->body, FTOFIX19_13(0.0f));
		
		Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));
	}
	
	// I'm not holding anything
	this->holdObject = NULL;
	
	// I always start in the first layer
	this->layer = 0;
	
	this->movingOverZ = false;
	
	this->actionTime = 0;
	
	this->boost = false;
	this->sensibleToFriction.y = false;
	
	Hero_setInstance(this);

	{
		Acceleration gravity =
        {
            FTOFIX19_13(0),
            FTOFIX19_13(9.0f),
            FTOFIX19_13(0)
        };
		PhysicalWorld_setGravity(PhysicalWorld_getInstance(), gravity);
		PhysicalWorld_setFriction(PhysicalWorld_getInstance(), FTOFIX19_13(FRICTION));
	}
	
	Object_addEventListener((Object)Game_getCurrentState(Game_getInstance()), (Object)this, (void (*)(Object))Hero_onKeyPressed, EVENT_KEY_PRESSED);
	Object_addEventListener((Object)Game_getCurrentState(Game_getInstance()), (Object)this, (void (*)(Object))Hero_onKeyReleased, EVENT_KEY_RELEASED);
	Object_addEventListener((Object)Game_getCurrentState(Game_getInstance()), (Object)this, (void (*)(Object))Hero_onKeyHold, EVENT_KEY_HOLD);
}

// class's destructor
void Hero_destructor(Hero this)
{
	// free the instance pointer
	ASSERT(hero == this, "Hero::destructor: more than on instance");

	MessageDispatcher_dispatchMessage(0, (Object)this, (Object)Game_getInstance(), kHeroDied, NULL);

	hero = NULL;
	
	Object_removeEventListener((Object)Game_getCurrentState(Game_getInstance()), (Object)this, (void (*)(Object))Hero_onKeyPressed, EVENT_KEY_PRESSED);
	Object_removeEventListener((Object)Game_getCurrentState(Game_getInstance()), (Object)this, (void (*)(Object))Hero_onKeyReleased, EVENT_KEY_RELEASED);
	Object_removeEventListener((Object)Game_getCurrentState(Game_getInstance()), (Object)this, (void (*)(Object))Hero_onKeyHold, EVENT_KEY_HOLD);

	Screen_setFocusInGameEntity(Screen_getInstance(), NULL);

	// delete the super object
	__DESTROY_BASE(Actor);
}

// keep adding force to jump
void Hero_addMomentumToJump(Hero this)
{
	if (this->body)
    {
		Velocity velocity = Body_getVelocity(this->body);

		if (HERO_VELOCITY_Y < velocity.y && 0 > FIX19_13TOF(velocity.y) && !AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Fall"))
        {
			
			Force force =
            {
                0,
                ITOFIX19_13(-30),
                0
            };
			Body_addForce(this->body, &force);
		}
		else
        {
			
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
		}
	}
}

// make him jump
void Hero_jump(Hero this, int changeState, int checkIfYMovement)
{
	Hero_startedMovingOnAxis(this, __YAXIS);

	if (this->body)
    {
        Velocity velocity = Body_getVelocity(this->body);

		if (!checkIfYMovement || !velocity.y)
        {
			Force force =
            {
                0,
                this->boost ? HERO_BOOST_JUMP_HERO_INPUT_FORCE : HERO_NORMAL_JUMP_HERO_INPUT_FORCE,
                0
            };
			Body_addForce(this->body, &force);
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Jump");
		}
	}
}

// keep movement
void Hero_addForce(Hero this, int changedDirection, int axis)
{
	ASSERT(this->body, "Hero::keepMoving: no body");
	static int movementType = 0;

	fix19_13 maxVelocity = this->boost? HERO_BOOST_VELOCITY_X: HERO_VELOCITY_X;
	
	Velocity velocity = Body_getVelocity(this->body);
	
	if (changedDirection || ((__XAXIS & axis) && maxVelocity > fabs(velocity.x)) || ((__ZAXIS & axis) && maxVelocity > fabs(velocity.z)) || Actor_changedDirection((Actor)this, __XAXIS) || Actor_changedDirection((Actor)this, __ZAXIS))
    {
		Acceleration acceleration =
        {
        	(__XAXIS & axis)? __RIGHT == this->direction.x ? HERO_INPUT_FORCE : -HERO_INPUT_FORCE: 0,
			0,
			(__ZAXIS & axis)? __FAR == this->direction.z ? HERO_INPUT_FORCE : -HERO_INPUT_FORCE: 0,
		};

		if (velocity.x || velocity.z || ( __XAXIS & Actor_canMoveOverAxis((Actor)this, &acceleration)) || ( __ZAXIS & Actor_canMoveOverAxis((Actor)this, &acceleration)))
        {
			fix19_13 xForce = (__XAXIS & axis)? __RIGHT == this->direction.x? HERO_INPUT_FORCE: -HERO_INPUT_FORCE: 0;
			fix19_13 zForce = (__ZAXIS & axis)? __FAR == this->direction.z? HERO_INPUT_FORCE: -HERO_INPUT_FORCE: 0;
			Force force =
            {
                xForce,
                0,
                zForce
            };
			Body_addForce(this->body, &force);
			movementType = __ACCELERATED_MOVEMENT;
		}
		
		if (AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Slide"))
        {
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
		}			
	}
	else
    {
		Velocity newVelocity =
        {
        	(__XAXIS & axis)? ((int)maxVelocity * this->direction.x): 0,
			0,
			(__ZAXIS & axis)? ((int)maxVelocity * this->direction.z): 0,
		};
		
		if (__UNIFORM_MOVEMENT != movementType)
        {
			movementType = __UNIFORM_MOVEMENT;
			Body_moveUniformly(this->body, newVelocity);
		}
	}
}

// start movement
void Hero_stopMovement(Hero this)
{
	Velocity velocity = Body_getVelocity(this->body);

	if (!velocity.y)
    {
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Slide");
	}
	else if (!AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Fall"))
    {
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
	}

    //	fix19_13 maxVelocity = this->boost? HERO_BOOST_VELOCITY_X: HERO_VELOCITY_X;

    //	velocity.x = HERO_VELOCITY_X * this->direction.x;
	
	// only modify y axis
	velocity.y = 0;
	
	// clear acceleration
	Body_moveUniformly(this->body, velocity);

	// begin to desaccelerate
	int axisOfDeacceleartion = 0;
	axisOfDeacceleartion |= velocity.x? __XAXIS: 0;
	axisOfDeacceleartion |= velocity.z? __ZAXIS: 0;
	Body_moveAccelerated(this->body, axisOfDeacceleartion);
}

// started moving over axis
void Hero_startedMovingOnAxis(Hero this, int axis)
{
	// start movement
	if ((State)HeroMoving_getInstance() != StateMachine_getCurrentState(Actor_getStateMachine((Actor) this)))
    {
 		if (__XAXIS & axis)
        {
			Acceleration acceleration =
            {
                __RIGHT == this->direction.x ? HERO_INPUT_FORCE : -HERO_INPUT_FORCE,
                0,
                0
			};
			
			if ( __XAXIS & Actor_canMoveOverAxis((Actor)this, &acceleration))
            {
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
				StateMachine_swapState(Actor_getStateMachine((Actor) this), (State) HeroMoving_getInstance());
			}
		}
		if (__YAXIS & axis)
        {
			Acceleration acceleration =
            {
        		0,
                __DOWN == this->direction.x ? HERO_INPUT_FORCE : -HERO_INPUT_FORCE,
                0
			};
			
			if ( __YAXIS & Actor_canMoveOverAxis((Actor)this, &acceleration))
            {
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
				StateMachine_swapState(Actor_getStateMachine((Actor) this), (State) HeroMoving_getInstance());
			}
		}

		if (__ZAXIS & axis)
        {
			Acceleration acceleration =
            {
            	0,
                0,
                __FAR == this->direction.z ? HERO_INPUT_FORCE : -HERO_INPUT_FORCE
			};
			
			if (__ZAXIS & Actor_canMoveOverAxis((Actor)this, &acceleration))
            {
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
				StateMachine_swapState(Actor_getStateMachine((Actor) this), (State) HeroMoving_getInstance());
			}
		}

	}
	else
	{
		int movementState = Body_isMoving(this->body);

		if ((__XAXIS & axis)  && !(__YAXIS & movementState))
        {
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
		}

		if (__YAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
		}

		if (__ZAXIS & axis)
        {
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
		}
	}
}

// stop moving over axis
int Hero_stopMovingOnAxis(Hero this, int axis)
{
	int movementState = Body_isMoving(this->body);

	if ((__XAXIS & axis) && !(__YAXIS & movementState))
    {
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Idle");
	}

	if (__YAXIS & axis)
    {
		MovementType movementType = Body_getMovementType(this->body);
		
		if (__UNIFORM_MOVEMENT == movementType.x)
        {
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
		}
		else
        {
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Slide");
		}
	}

	if (__ZAXIS & axis)
    {
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Idle");
		StateMachine_swapState(Actor_getStateMachine((Actor) this), (State)HeroIdle_getInstance());					
		return true;
	}

	if (!Body_isMoving(Actor_getBody((Actor)this)) && (State)HeroIdle_getInstance() != StateMachine_getCurrentState(Actor_getStateMachine((Actor) this)))
    {

		StateMachine_swapState(Actor_getStateMachine((Actor) this), (State)HeroIdle_getInstance());					
	}
	
	return false;
}

// check direction
void Hero_checkDirection(Hero this, u16 pressedKey, char* animation)
{
	if ((K_LR & pressedKey) && __RIGHT != this->direction.x)
    {
		this->direction.x = __RIGHT;
	}
	else if ((K_LL & pressedKey) && __LEFT != this->direction.x)
    {
		this->direction.x = __LEFT;
	}
	else if ((K_LU & pressedKey) && __FAR != this->direction.z)
    {
		this->direction.z = __FAR;
	}
	else if ((K_LD & pressedKey) && __NEAR != this->direction.z)
    {
		this->direction.z = __NEAR;
	}

	int movementState = Body_isMoving(this->body);

	if (animation && !(__YAXIS & movementState))
    {
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, animation);
	}
}

void Hero_takeHitFrom(Hero this, Actor other)
{
	//VBVec3D position = Entity_getPosition((Entity)other);
	/*
	// first stop all movement
	Actor_stopMovement((Actor)this, __XAXIS | __YAXIS | __ZAXIS);
	
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
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitFront");
		}
		else{
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitBehind");
		}
	}
	else
	{
		if (__LEFT == this->direction.x)
		{
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitFront");
		}
		else
		{
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitBehind");
		}							
	}
	
	// register time
	this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);
	*/
}

/*
int Hero_isHitByEnemy(Hero this, Enemy enemy, int axis)
{
	ASSERT(enemy, "Hero::isHitByEnemy: null enemy");

	
	// if enemy is already dead
	if (kDead == Actor_getInGameState((Actor)enemy))
    {
		return false;
	}
	
	// if it is the holdobject which wants to hit me
	if (this->holdObject == (Actor)enemy)
    {
		this->holdObject = NULL;
		return true;
	}
	

	// check if I'm over the enemy
	if ((this->velocity.y && __DOWN == this->direction.y) &&
	    (
    		this->transform.globalPosition.y + ITOFIX19_13(Entity_getHeight((Entity)this) >> 2) <
    		Entity_getPosition((Entity)enemy).y
    	)
    )
    {
		// align to the colliding object
		Actor_alignTo((Actor)this, (InGameEntity)enemy, __XAXIS, 2);
		
		//check if player wants to jump over z axis
		if (!Hero_checkIfZJump(this))
        {
			
			if (this->holdObject)
            {
				// play animation
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "JumpHolding");
			}
			else{
				
				// play animation
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Jump");
			}
		}

		// if A button is pressed boost the y velocity
		if (K_A & vbKeyPressed())
        {
			// I will bounce
			Actor_jump((Actor)this, FIX19_13_MULT(HERO_VELOCITY_Y, HERO_SPEED_MULTIPLIER_Y), HERO_ACCELERATION_Y);
		}
		else
		{
			// I will bounce
			Actor_jump((Actor)this, HERO_VELOCITY_Y , HERO_ACCELERATION_Y);
		}

		// tell enemy I've hit him
		if (this->movingOverZ)
        {
			__VIRTUAL_CALL(void, Enemy, takeHit, (Enemy)enemy, __ARGUMENTS(__ZAXIS, this->direction.z));
		}
		else
		{
			__VIRTUAL_CALL(void, Enemy, takeHit, (Enemy)enemy, __ARGUMENTS(__XAXIS, this->direction.x));
		}
			
		return false;
	}

	// if I'm holding something and facing to the side
	if (this->holdObject && !this->movingOverZ)
    {
		// if I'm facing the enemy
		if ((this->transform.globalPosition.x <  Entity_getPosition((Entity)enemy).x && __RIGHT == this->direction.x)
			||
			(this->transform.globalPosition.x >  Entity_getPosition((Entity)enemy).x && __LEFT == this->direction.x)
			)
        {
			// tell enemy to die
			__VIRTUAL_CALL(void, Actor, die, (Actor)enemy);
			
			// hold object must be destroyed
			__VIRTUAL_CALL(void, Actor, die, (Actor)this->holdObject);
			
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
				Hero_pickupObject(this, (Actor)enemy);
				return false;
			}
		}
		
		// stop my movement
		Actor_stopMovement((Actor)this, __XAXIS);

		// align to the colliding object
		Actor_alignTo((Actor)this, (InGameEntity)enemy, __XAXIS, 1);

		// tell enemy to begin bouncing
		__VIRTUAL_CALL(void, Enemy, takeHit, (Enemy)enemy, __ARGUMENTS(__XAXIS, this->direction.x));

		// I will bounce
		Actor_jump((Actor)this, FIX19_13_DIV(HERO_VELOCITY_Y, ITOFIX19_13(2)), HERO_ACCELERATION_Y);
		
		if (this->holdObject)
        {
			// play animation
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "JumpHolding");
		}
		else
		{
			// play animation
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Jump");
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
	ASSERT(this->sprites, "Hero::setAnimationDelta: null sprites");

	VirtualNode node = VirtualList_begin(this->sprites);
	
	for(; node; node = VirtualNode_getNext(node))
	{
		AnimatedSprite_setFrameDelayDelta((AnimatedSprite)VirtualNode_getData(node), this->boost? -2: -1);
	}
}

// disable boost
void Hero_disableBoost(Hero this)
{
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

	__VIRTUAL_CALL(void, Container, addChild, (Container)this, __ARGUMENTS(child));

	this->holdObject = object;
	
	// set hold object's position
	Hero_updateHoldObjectPosition(this);
	
	// remove from collision detection system
	InGameEntity_setShapeState((InGameEntity)this->holdObject, false);
	*/
}

int Hero_checkIfZJump(Hero this)
{
	return false;
}

void Hero_fallDead(Hero this)
{
	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitFront");
	
	Hero_die(this);
}

// was jumping over z?
int  Hero_isMovingOverZ(Hero this)
{
	return this->movingOverZ;
}

// set jumping over z status
void Hero_setMovingOverZ(Hero this, int  state)
{
	this->movingOverZ = state;
}

// set hold object's position
void Hero_updateHoldObjectPosition(Hero this)
{
}

// make hero to look to the player
void Hero_lookFront(Hero this)
{
	// if already not playing
	if (!AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Front"))
    {
		// play animation
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Front");
	}
}

// make hero to look away the player
void Hero_lookBack(Hero this)
{
	// if already not playing
	if (!AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Back"))
    {
		// play animation
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Back");
	}
}

// set  graphical gap
void Hero_setGap(Hero this)
{
	this->gap = this->inGameEntityDefinition->gap;
	
	// if I'm not in the edge, return ROM gap
	if (AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "OnEdge"))
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
	StateMachine_swapState(this->stateMachine, (State)HeroDead_getInstance());
	
	// if I have something being hold
	if (this->holdObject)
    {
		// hold object must be destroyed
		__VIRTUAL_CALL(void, Actor, die, (Actor)this->holdObject);
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
	for(i = 0; i < TOTAL_GAME_LAYERS; i++)
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
	
	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "WalkBack");
	
	Actor_startMovement((Actor)this, __ZAXIS, __UNIFORMMOVE, FIX19_13_DIV(HERO_VELOCITY_Z, ITOFIX19_13(4)), 0);
	
	this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	*/
}

// goal reached
void Hero_moveOnWin(Hero this)
{
}

// process user input
static void Hero_onKeyPressed(Hero this)
{
	u16 pressedKey = KeypadManager_getPressedKey(KeypadManager_getInstance());
	
	// inform my current states about the key pressed		
	MessageDispatcher_dispatchMessage(0, (Object)this, (Object)this->stateMachine, kKeyPressed, &pressedKey);
}

// process user input
static void Hero_onKeyReleased(Hero this)
{
	u16 releasedKey = KeypadManager_getReleasedKey(KeypadManager_getInstance());

	// inform my current states about the key up		
	MessageDispatcher_dispatchMessage(0, (Object)this, (Object)this->stateMachine, kKeyUp, &releasedKey);
}

// process user input
static void Hero_onKeyHold(Hero this)
{
	u16 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

	// inform my current states about the key hold		
	MessageDispatcher_dispatchMessage(0, (Object)this, (Object)this->stateMachine, kKeyHold, &holdKey);
}

// collect a coin
void Hero_collectCoin(Hero this)
{
	this->coins++;
	Object_fireEvent((Object)PlatformerLevelState_getInstance(), EVENT_COIN_TAKEN);
}

// get number of coins
u8 Hero_getCoins(Hero this)
{
	return this->coins;
}

// get number of lifes
u8 Hero_getLifes(Hero this)
{
	return this->lifes;
}

// process collisions
int Hero_processCollision(Hero this, Telegram telegram)
{
	VirtualList collidingObjects = (VirtualList)Telegram_getExtraInfo(telegram);
	ASSERT(collidingObjects, "HeroMoving::handleMessage: null collidingObjects");

	VirtualNode node = NULL;

	VirtualList collidingObjectsToRemove = __NEW(VirtualList);

	for(node = VirtualList_begin(collidingObjects); node; node = VirtualNode_getNext(node))
    {
		InGameEntity inGameEntity = (InGameEntity)VirtualNode_getData(node);
		
		switch(InGameEntity_getInGameType(inGameEntity))
        {
			case kCoin:

				Hero_collectCoin(this);
				MessageDispatcher_dispatchMessage(0, (Object)this, (Object)inGameEntity, kTakeCoin, NULL);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;
								
			case kDoor:

				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				MessageDispatcher_dispatchMessage(0, (Object)this, (Object)inGameEntity, kEnterDoor, NULL);
				break;
		}
	}
	
	for(node = VirtualList_begin(collidingObjectsToRemove); node; node = VirtualNode_getNext(node))
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
	switch(message)
	{
		case kSetUpLevel:
			{
				// then set myself as the focus
				Screen_setFocusInGameEntity(Screen_getInstance(), (InGameEntity)this);

				// I'm the focus actor
				VBVec3D screenDisplacement =
				{
	                0,
	                ITOFIX19_13(0),
	                ITOFIX19_13(-PLAYABLE_LAYER_0),
				};
				
				Screen_setFocusEntityPositionDisplacement(Screen_getInstance(), screenDisplacement);
				
				return true;
			}
			break;
	}
	
	return false;
}