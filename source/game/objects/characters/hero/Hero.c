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


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Screen.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <KeypadManager.h>

#include <objects.h>
#include "Hero.h"
#include "HeroIdle.h"
#include "HeroMoving.h"

#include <PlatformerLevelState.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											 CLASS'S MACROS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// Hero.c

// A Hero!
__CLASS_DEFINITION(Hero); 

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

extern double fabs (double);

// process user input
static void Hero_onKeyPressed(Hero this);

// process user input
static void Hero_onKeyReleased(Hero this);

// process user input
static void Hero_onKeyHold(Hero this);


// a static member of this class
static u32 gameLayers[TOTAL_GAME_LAYERS] = {
	ITOFIX19_13(LAYER_0),
	ITOFIX19_13(LAYER_1),
	ITOFIX19_13(LAYER_2),
	ITOFIX19_13(LAYER_3),
	ITOFIX19_13(LAYER_4),
};

#define HERO_INPUT_FORCE ITOFIX19_13(10)
#define HERO_WEIGHT		10
#define FRICTION 	0.01f

#define HERO_VELOCITY_X			ITOFIX19_13(7)
#define HERO_VELOCITY_Y			FTOFIX19_13(-6.0f)
#define HERO_VELOCITY_Z			ITOFIX19_13(175)
#define HERO_ACCELERATION_X		ITOFIX19_13(10)
#define HERO_ACCELERATION_Y		ITOFIX19_13(0)
#define HERO_ACCELERATION_Z		ITOFIX19_13(0)
#define HERO__BOOST_VELOCITY_X		ITOFIX19_13(9)
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

#define HERO_DISPLACEMENT_ON_BRIDGE	FTOFIX19_13(2.0f / __FPS_ANIM_FACTOR)

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// Only one instance
Hero hero = NULL;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// there can only be one mario instantiated
Hero Hero_getInstance(){
	
	return hero;
}

void Hero_setInstance(Hero instance){
	
	ASSERT(!hero, "Hero::setInstance: already instantiated");
	
	hero = instance;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Hero, __PARAMETERS(ActorDefinition* actorDefinition, int ID))
__CLASS_NEW_END(Hero, __ARGUMENTS(actorDefinition, ID));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
void Hero_constructor(Hero this, ActorDefinition* actorDefinition, int ID){
	
	// construct base
	__CONSTRUCT_BASE(Actor, __ARGUMENTS(actorDefinition, ID));

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
		Acceleration gravity = {FTOFIX19_13(0), FTOFIX19_13(9.0f), FTOFIX19_13(0)};
		PhysicalWorld_setGravity(PhysicalWorld_getInstance(), gravity);
		PhysicalWorld_setFriction(PhysicalWorld_getInstance(), FTOFIX19_13(FRICTION));
	}
	
	// I'm the focus actor
	Screen_setFocusInGameEntity(Screen_getInstance(), (InGameEntity)this);

	Object_addEventListener((Object)PlatformerLevelState_getInstance(), (Object)this, (void (*)(Object))Hero_onKeyPressed, EVENT_KEY_PRESSED);
	Object_addEventListener((Object)PlatformerLevelState_getInstance(), (Object)this, (void (*)(Object))Hero_onKeyReleased, EVENT_KEY_RELEASED);
	Object_addEventListener((Object)PlatformerLevelState_getInstance(), (Object)this, (void (*)(Object))Hero_onKeyHold, EVENT_KEY_HOLD);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
void Hero_destructor(Hero this){

	// free the instance pointer
	ASSERT(hero == this, "Hero::destructor: more than on instance");

	hero = NULL;
	
	Object_removeEventListener((Object)PlatformerLevelState_getInstance(), (Object)this, (void (*)(Object))Hero_onKeyPressed, EVENT_KEY_PRESSED);
	Object_removeEventListener((Object)PlatformerLevelState_getInstance(), (Object)this, (void (*)(Object))Hero_onKeyReleased, EVENT_KEY_RELEASED);
	Object_removeEventListener((Object)PlatformerLevelState_getInstance(), (Object)this, (void (*)(Object))Hero_onKeyHold, EVENT_KEY_HOLD);

	// delete the super object
	__DESTROY_BASE(Actor);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// update movement
void Hero_move(Hero this){


	/*
	// pick the current pressed key
	if (this->body) {
		
		int movingState = Body_isMoving(this->body);
		Velocity velocity = Body_getVelocity(this->body);

		if(0 < velocity.y && (__YAXIS & movingState) && !AnimatedInGameEntity_isAnimationLoaded((Actor)this, "Fall")){
			
			{
				static int xx = 0;
				
				Printing_text("Hero", 1, 17);
				Printing_int(xx++, 1, 18);
				Printing_hex(movingState, 1, 19);
				
			}

			// must play walk animation of not playing it
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
		}
	}
	*/
	/*
	// check if must throw the object
	if(this->holdObject){
	
		Hero_throwObject(this);
	}
	
	if(this->velocity.z){

		if(__FAR == this->direction.z && this->transform.globalPosition.z > gameLayers[this->layer]){

			Actor_stopMovement((Actor)this, __ZAXIS);
			
			this->transform.globalPosition.z = gameLayers[this->layer];
			
			return;
		}
		else{
			
			if(__NEAR == this->direction.z && this->transform.globalPosition.z < gameLayers[this->layer]){
				
				Actor_stopMovement((Actor)this, __ZAXIS);
				
				this->transform.globalPosition.z = gameLayers[this->layer];
				
				return;
			}
		}

		
		// move the actor
		Actor_move((Actor)this);
		
		// if I'm holding something
		if(this->holdObject){
			
			// update object's position
			Hero_updateHoldObjectPosition(this);
		}		
		return;
	}

	//if mario is moving and all keys are left
	if((this->velocity.x) && (!currentPressedKey  || (!(currentPressedKey & K_LR) && !(currentPressedKey &  K_LL)))){

		if(!(this->moveType &__RETARMOVEX)){

			// must start to stop
			this->moveType |=__RETARMOVEX;
			
			// don't slide if holding something 
			if(!this->holdObject){
				
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Slide");
			}
			
			this->velocity.x = HERO_VELOCITY_X;
		}
	}
	else{

		char walkStr[] = "Walk";
		char walkHoldStr[] = "WalkHolding";
		char* walkAnimation = walkStr;
		
		if(this->holdObject){
			
			walkAnimation = walkHoldStr;
		}

		// if it is only moving over the x axis and walking animation is no playing
		if(!this->velocity.y && !AnimatedSprite_isPlayingFunction((AnimatedSprite)this->sprite, this->actorDefinition->animationDescription, walkAnimation)){
			
			// must play walk animation of not playing it
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, walkAnimation);
			
			// start moving
			Actor_startMovement((Actor)this, __XAXIS, __RETARMOVEX, HERO_VELOCITY_X, HERO_ACCELERATION_X);
		}
	}

	// if movement is uniform
	if(!(this->moveType &__RETARMOVEX)){

		// if B button is pressed
		if(currentPressedKey & K_B){
			
			// boost velocity
			this->velocity.x = FIX19_13_MULT(HERO_VELOCITY_X, HERO_SPEED_MULTIPLIER_X);
		}
		else{
			
			// shoot the shell
			//this->velocity.x = HERO_VELOCITY_X;
		}
	}

	// might be jumping
	// TODO: increse y velocity if A button hold while jumping
	if(this->velocity.y){
		
		if(__UP == this->direction.y){
			
			if(vbPadPreviousKey() & K_A){
				
				this->acceleration.y = (HERO_ACCELERATION_Y + __GRAVITY) * (-1) / HERO_SPEED_MULTIPLIER_X;
			}
		}
	}


	// if not jumping over z
	if(!this->movingOverZ){

		// if mario is falling
		if(this->velocity.y && __DOWN == this->direction.y ) {
	
			char fallStr[] = "Fall";
			char fallHoldStr[] = "FallHolding";
			char* fallAnimation = fallStr;
			
			if(this->holdObject){
				
				fallAnimation = fallHoldStr;
			}
	
			// and not playing corresponding animation
			if(!AnimatedSprite_isPlayingFunction((AnimatedSprite)this->sprite, this->actorDefinition->animationDescription, fallAnimation)){
			
				// play animation
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, fallAnimation);
			}
		}
	}
	
	// move the actor
	Actor_move((Actor)this);

	// if I'm holding something
	if(this->holdObject){
		
		// update object's position
		Hero_updateHoldObjectPosition(this);
	}

	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// keep adding force to jump
void Hero_addMomentumToJump(Hero this) {
	
	if (this->body) {
		
		Velocity velocity = Body_getVelocity(this->body);

		if (HERO_VELOCITY_Y < velocity.y && 0 > FIX19_13TOF(velocity.y) && !AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Fall")){
			
			Force force = {0, ITOFIX19_13(-30), 0};
			Body_addForce(this->body, &force);
		}
		else {
			
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// make him jump
void Hero_jump(Hero this, int changeState){

	Hero_startedMovingOnAxis(this, __YAXIS);

	if (this->body) {
		
		Velocity velocity = Body_getVelocity(this->body);

		if (!velocity.y){
			
			Force force = {0, this->boost? HERO_BOOST_JUMP_HERO_INPUT_FORCE: HERO_NORMAL_JUMP_HERO_INPUT_FORCE, 0};
			Body_addForce(this->body, &force);
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Jump");
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// start movement
void Hero_startMoving(Hero this){

	/*
	int movingState = Body_isMoving(this->body);
	
	if(movingState)
	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// keep movement
void Hero_keepMoving(Hero this, int changedDirection){

	ASSERT(this->body, "Hero::keepMoving: no body");
	static int movementType = 0;

	fix19_13 maxVelocity = this->boost? HERO__BOOST_VELOCITY_X: HERO_VELOCITY_X;
	
	Velocity velocity = Body_getVelocity(this->body);
	
	if (changedDirection || maxVelocity > fabs(velocity.x) || Actor_changedDirection((Actor)this, __XAXIS)){
		
		Acceleration acceleration = {
				__RIGHT == this->direction.x? ITOFIX19_13(5): ITOFIX19_13(-5),
				0,
				0
		};

		if(velocity.x || ( __XAXIS & Actor_canMoveOverAxis((Actor)this, &acceleration))){

			fix19_13 xForce = 0 < this->direction.x? HERO_INPUT_FORCE: -HERO_INPUT_FORCE;
			Force force = {xForce, 0, 0};
			Body_addForce(this->body, &force);
			movementType = __ACCELERATED_MOVEMENT;
		}
		
		if(AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Slide")){
			
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
		}			
	}
	else {
		
		Velocity velocity = {
			((int)maxVelocity * this->direction.x),
			0,
			0,
		};
		
		if(__UNIFORM_MOVEMENT != movementType){
			
			movementType = __UNIFORM_MOVEMENT;
			Body_moveUniformly(this->body, velocity);
		}
	}
	
	/*
	int movementAxis = Body_isMoving(this->body);
	
	if(!(__YAXIS & movementAxis) && !AnimatedInGameEntity_isAnimationLoaded((Actor)this, "Walk") && !AnimatedInGameEntity_isAnimationLoaded((Actor)this, "Jump")){
		
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
	}
	else if(0 < velocity.y && !AnimatedInGameEntity_isAnimationLoaded((Actor)this, "Fall")){
		
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
	}
*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// start movement
void Hero_stopMoving(Hero this){

	Velocity velocity = Body_getVelocity(this->body);

	if(!velocity.y) {
		
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Slide");
	}
	else if(!AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Fall")){
		
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
	}

//	fix19_13 maxVelocity = this->boost? HERO__BOOST_VELOCITY_X: HERO_VELOCITY_X;

//	velocity.x = HERO_VELOCITY_X * this->direction.x;
	
	// only modify x axis
	velocity.y = 0;
	velocity.z = 0;
	
	// clear acceleration
	Body_moveUniformly(this->body, velocity);

	// begin to desaccelerate
	Body_moveAccelerated(this->body, __XAXIS);
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// started moving over axis
void Hero_startedMovingOnAxis(Hero this, int axis){

	// start movement
	if((State)HeroMoving_getInstance() != StateMachine_getCurrentState(Actor_getStateMachine((Actor) this))) {
	
 		if(__XAXIS & axis) {

			Acceleration acceleration = {
					__RIGHT == this->direction.x? ITOFIX19_13(5): ITOFIX19_13(-5),
					0,
					0
					
			};
			
			if( __XAXIS & Actor_canMoveOverAxis((Actor)this, &acceleration)){
				
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");

				StateMachine_swapState(Actor_getStateMachine((Actor) this), (State) HeroMoving_getInstance());
			}
		}
		if(__YAXIS & axis){

			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");	

			StateMachine_swapState(Actor_getStateMachine((Actor) this), (State) HeroMoving_getInstance());
		}
	}
	else{

		int movementState = Body_isMoving(this->body);

		if((__XAXIS & axis)  && !(__YAXIS & movementState)) {

			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
		}

		if(__YAXIS & axis) {

			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Fall");
		}

		if(__ZAXIS & axis) {

		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// stop moving over axis
int Hero_stopMovingOnAxis(Hero this, int axis){
	
	int movementState = Body_isMoving(this->body);

	if((__XAXIS & axis) && !(__YAXIS & movementState)) {
		
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Idle");
	}

	if(__YAXIS & axis) {
		
		MovementType movementType = Body_getMovementType(this->body);
		
		if(__UNIFORM_MOVEMENT == movementType.x) {

			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Walk");
		}
		else {
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Slide");
		}
	}

	if(__ZAXIS & axis) {

	}

	if(!Body_isMoving(Actor_getBody((Actor)this)) && (State)HeroIdle_getInstance() != StateMachine_getCurrentState(Actor_getStateMachine((Actor) this))) {

		StateMachine_swapState(Actor_getStateMachine((Actor) this), (State)HeroIdle_getInstance());					
	}
	
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// check direction
void Hero_checkDirection(Hero this, u16 pressedKey, char* animation){

	int previousDirection = this->direction.x;
	
	if((K_LR & pressedKey) && __RIGHT != this->direction.x){
	
		this->direction.x = __RIGHT;
	}
	else if((K_LL & pressedKey) && __LEFT != this->direction.x){
	
		this->direction.x = __LEFT;
	}

	if (previousDirection != this->direction.x) {
		
		//Body_stopMovement(this->body, __XAXIS);
	}

	int movementState = Body_isMoving(this->body);

	if(animation && !(__YAXIS & movementState)){
		
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, animation);
	}

	/*
	// don't allow movement over x while moving over z
	if(this->movingOverZ){
		
		return;
	}	
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hero_takeHitFrom(Hero this, Actor other){
	
	//VBVec3D position = Entity_getPosition((Entity)other);
	/*
	// first stop all movement
	Actor_stopMovement((Actor)this, __XAXIS | __YAXIS | __ZAXIS);
	
	// reduce energy
	if(--this->energy){

	}
	else{

		// now die
		Hero_die(this);
	}
	
	// determine which animation to play 
	// based on my position relative to the
	// enemy position
	if(position.x > this->transform.globalPosition.x){
		
		if(__RIGHT == this->direction.x){
			
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitFront");
		}
		else{
		
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitBehind");
		}
	}
	else{
		if(__LEFT == this->direction.x){
			
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitFront");
		}
		else{
		
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitBehind");
		}							
	}
	
	// register time
	this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
int Hero_isHitByEnemy(Hero this, Enemy enemy, int axis){

	ASSERT(enemy, "Hero::isHitByEnemy: null enemy");

	
	// if enemy is already dead
	if(kDead == Actor_getInGameState((Actor)enemy)){
		
		return false;
	}
	
	// if it is the holdobject which wants to hit me
	if(this->holdObject == (Actor)enemy){
		
		this->holdObject = NULL;
		return true;
	}
	

	// check if I'm over the koopa
	if((this->velocity.y && __DOWN == this->direction.y) && 
	    (
    		this->transform.globalPosition.y + ITOFIX19_13(Entity_getHeight((Entity)this) >> 2) <
    		Entity_getPosition((Entity)enemy).y
    	)
    ){
		
		// align to the colliding object
		Actor_alignTo((Actor)this, (InGameEntity)enemy, __XAXIS, 2);
		
		//check if player wants to jump over z axis
		if(!Hero_checkIfZJump(this)){
			
			if(this->holdObject){

				// play animation
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "JumpHolding");
			}
			else{
				
				// play animation
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Jump");
			}
		}

		// if A button is pressed boost the y velocity
		if(K_A & vbKeyPressed()){

			// I will bounce
			Actor_jump((Actor)this, FIX19_13_MULT(HERO_VELOCITY_Y, HERO_SPEED_MULTIPLIER_Y), HERO_ACCELERATION_Y);
		}
		else
		{
			// I will bounce
			Actor_jump((Actor)this, HERO_VELOCITY_Y , HERO_ACCELERATION_Y);
		}
		

		// tell koopa I've hit him
		if(this->movingOverZ){

			__VIRTUAL_CALL(void, Enemy, takeHit, (Enemy)enemy, __ARGUMENTS(__ZAXIS, this->direction.z));
		}
		else{
			
			__VIRTUAL_CALL(void, Enemy, takeHit, (Enemy)enemy, __ARGUMENTS(__XAXIS, this->direction.x));
		}
			
		return false;
	}

	// if I'm holding something and facing to the side
	if(this->holdObject && !this->movingOverZ){
		
		
		// if I'm facing the enemy
		if((this->transform.globalPosition.x <  Entity_getPosition((Entity)enemy).x && __RIGHT == this->direction.x)
			||
			(this->transform.globalPosition.x >  Entity_getPosition((Entity)enemy).x && __LEFT == this->direction.x)
			){
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
	if(kCollisionX == axis && !(__VIRTUAL_CALL(int, Enemy, canAttack, enemy) ||	this->holdObject)){

		// if B button is pressed, pick up 
		if(K_B & vbKeyPressed()){
			
			if(!this->holdObject){
				
				Hero_pickupObject(this, (Actor)enemy);
				
				return false;
			}
		}
		
		// stop my movement
		Actor_stopMovement((Actor)this, __XAXIS);

		// align to the colliding object
		Actor_alignTo((Actor)this, (InGameEntity)enemy, __XAXIS, 1);

		// tell koopa to begin bouncing
		__VIRTUAL_CALL(void, Enemy, takeHit, (Enemy)enemy, __ARGUMENTS(__XAXIS, this->direction.x));

		// I will bounce
		Actor_jump((Actor)this, FIX19_13_DIV(HERO_VELOCITY_Y, ITOFIX19_13(2)), HERO_ACCELERATION_Y);
		
		if(this->holdObject){

			// play animation
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "JumpHolding");
		}
		else{
			
			// play animation
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Jump");
		}
		return false;
	}
	// otherwise... I was hit by the enemy
	return true;
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set animation delta
void Hero_setAnimationDelta(Hero this, int delta){

	ASSERT(this->sprites, "Hero::setAnimationDelta: null sprites");

	VirtualNode node = VirtualList_begin(this->sprites);
	
	for(; node; node = VirtualNode_getNext(node)){
	
		AnimatedSprite_setFrameDelayDelta((AnimatedSprite)VirtualNode_getData(node), this->boost? -2: -1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// disable boost
void Hero_disableBoost(Hero this){

	if(this->boost) {
	
		this->boost = false;
		Hero_setAnimationDelta(this, -1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// enable boost
void Hero_enableBoost(Hero this){
	
	if(!this->boost) {
	
		this->boost = true;
		
		Hero_setAnimationDelta(this, -2);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set action time
void Hero_setActionTime(Hero this, u32 time){
	
	//this->actionTime = time;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// retrieve action time
u32 Hero_getActionTime(Hero this){

	return 0;
//	return this->actionTime;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// pickup an object
void Hero_pickupObject(Hero this, Actor object){
	
	/*

	VBVec3D position = {ITOFIX19_13(-25), ITOFIX19_13(-10), 0};
	Entity child = Entity_load(&FLOOR1_BG, &position, 1, NULL);

	__VIRTUAL_CALL(void, Container, addChild, (Container)this, __ARGUMENTS(child));

	this->holdObject = object;
	
	// set hold object's position 
	Hero_updateHoldObjectPosition(this);
	
	// remove from collision detection system
	InGameEntity_setShapeState((InGameEntity)this->holdObject, false);
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Hero_checkIfZJump(Hero this){

	/*
	// if up/down pressed
	u16 pressedKey = vbKeyPressed();
	
	this->movingOverZ = false;
	
	// if I'm on a bridge
	if(this->bridge){
	
		// can't jump over z
		return false;
	}
	
	if((pressedKey & K_LU) && this->layer < (TOTAL_GAME_LAYERS -1 )){
	
		// moving to next layer
		this->layer++;
		
		// play animation
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "JumpBack");
		
		// don't allow movement over x axis
		Actor_stopMovement((Actor)this, __XAXIS);
		
		// I'm going further
		this->direction.z = __FAR;
		
		// start moving in the new direction
		Actor_startMovement((Actor)this, __ZAXIS, ~(__ACCELMOVEX | __RETARMOVEX),
				HERO_VELOCITY_Z, HERO_ACCELERATION_Z);

		this->movingOverZ = true;

		return true;
	}
	else{
	
		if((pressedKey & K_LD) && this->layer > 0){
		
			// moving to previous layer
			this->layer--;
			
			// play animation
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "JumpFront");
			
			// don't move over x axis
			Actor_stopMovement((Actor)this, __XAXIS);
			
			// I'm  moving toward the screen
			this->direction.z = __NEAR;
		
			// start movement
			Actor_startMovement((Actor)this, __ZAXIS, ~(__ACCELMOVEX | __RETARMOVEX)
					, HERO_VELOCITY_Z, HERO_ACCELERATION_Z);

			this->movingOverZ = true;
			
			return true;
		}
	}
*/
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hero_fallDead(Hero this){

	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "HitFront");
	
	Hero_die(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// was jumping over z?
int  Hero_isMovingOverZ(Hero this){
	
	return this->movingOverZ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set jumping over z status
void Hero_setMovingOverZ(Hero this, int  state){
	
	this->movingOverZ = state;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set hold object's position 
void Hero_updateHoldObjectPosition(Hero this){
	
	/*
	// make sure there is an object being hold
	if(!this->holdObject){
		
		return;
	}
	{
		VBVec3D position = Entity_getPosition((Entity)this);
		
	
		if(!this->movingOverZ){
		
			position.x += ITOFIX19_13(HERO_HOLD_OBJECT_X * this->direction.x);
			position.y += ITOFIX19_13(HERO_HOLD_OBJECT_Y);
		}
		
		position.z += ITOFIX19_13(HERO_HOLD_OBJECT_Z * this->direction.z);
		
		Container_setLocalPosition((Container)this->holdObject, position);
	}
	{
		MovementState movementState = {this->movementState.x | this->movementState.y, __PASSIVE, this->movingOverZ};

		Actor_setMovementState(this->holdObject, movementState);
	}
*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// make mario to look to the player
void Hero_lookFront(Hero this){

	// if already not playing
	if(!AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Front")){

		// play animation
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Front");
	}

	/*
	// I'm looking to the screen
	this->direction.z = __NEAR;
	

	// change it to being able to update properly hold object's position
	this->movingOverZ = true;
	
	// update hold object's position
	Hero_updateHoldObjectPosition(this);
*/	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// make mario to look away the player
void Hero_lookBack(Hero this){

	// if already not playing
	if(!AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "Back")){

		// play animation
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Back");
	}
/*
	// I'm looking away the screen
	this->direction.z = __FAR;


	// change it to being able to update properly hold object's position
	this->movingOverZ = true;
	
	// update hold object's position
	Hero_updateHoldObjectPosition(this);
	*/
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set  graphical gap
void Hero_setGap(Hero this){

	this->gap = this->inGameEntityDefinition->gap;
	
	// if I'm not in the edge, return ROM gap
	if(AnimatedInGameEntity_isAnimationLoaded((AnimatedInGameEntity)this, "OnEdge")){
	
		// this is texture specific
		this->gap.left += 4;
		this->gap.right += 4;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// make mario to look to the side
void Hero_lookSide(Hero this){
	/*
	char blinkStr[] = "Blink";
	char idleStr[] = "Idle";
	
	char blinkHoldStr[] = "BlinkHolding";
	char idleHoldStr[] = "IdleHolding";
	
	char* animationToPlay;

	// I'm always going to the screen while looking to the side
	this->direction.z = __NEAR;
	
	// if I'm holding something
	if(this->holdObject){

		animationToPlay = blinkHoldStr; 
	}
	else{
		
		animationToPlay = blinkStr;
	}

	// first check if I'm over something
	if(this->objectBelow){
		
		VBVec3D position = Entity_getPosition((Entity)this->objectBelow);
		int width = ITOFIX19_13(abs(Entity_getWidth((Entity)this->objectBelow) - (Entity_getWidth((Entity)this) >> 1)) >> 1) ;
	
		if(this->transform.globalPosition.x > position.x + width || this->transform.globalPosition.x < position.x - width){
			
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "OnEdge");
			
			return;
		}
	}
	
	// if not playing blinking animation
	if(!AnimatedInGameEntity_isAnimationLoaded((Actor)this, animationToPlay)){

		u32 currentTime = Clock_getTime(Game_getClock(Game_getInstance()));
		
		// randomly select if play blinking
		if(currentTime - this->actionTime > HERO_BLINK_DELAY){
			
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, animationToPlay);
			
			// back to normal
			this->movingOverZ = false;

			// update hold object's position
			Hero_updateHoldObjectPosition(this);
			
			this->actionTime = currentTime;
		}
		else{
			
			// otherwhise
			if(animationToPlay == blinkHoldStr){
			
				animationToPlay = idleHoldStr;
			}
			else{
				
				animationToPlay = idleStr;
			}
		
			// if not playing idle animation
			if(!AnimatedInGameEntity_isAnimationLoaded((Actor)this, animationToPlay)){
			
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, animationToPlay);
				
				// back to normal
				this->movingOverZ = false;

				// update hold object's position
				Hero_updateHoldObjectPosition(this);
				
			}
		}
	}
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// check if must thrown an object
void Hero_throwObject(Hero this){
	
	/*
	// if I'm not holding anything
	if(!this->holdObject){
		
		return;
	}
	
	// if player released B button
	if(!(K_B & vbKeyPressed())){

		s8 direction = this->direction.x;
		int  axis = __XAXIS;
		


		// first place it in the same z coordinate
		//VBVec3D position = Entity_getPosition((Entity)this->holdObject);
		
		Hero_updateHoldObjectPosition(this);
		
		//position.z = this->transform.globalPosition.z;
		//Entity_setPosition((Entity)this->holdObject, position);

		// if moving over z axis
		if(this->movingOverZ){
		
			direction = this->direction.z;
			axis = __ZAXIS;
		}
		
		// firt align the object to be thrown 
		// to not produce a collision with me after
		// throwing it
		if(__XAXIS == axis){
			
			Actor_alignTo(this->holdObject, (InGameEntity)this, __XAXIS, 3);
		}
		else{

			Actor_alignTo(this->holdObject, (InGameEntity)this, __XAXIS, this->actorDefinition->inGameEntityDefinition.deep + 1);
		}
		
		// inform the object that it has been thrown
		__VIRTUAL_CALL(void, Actor, beThrown, this->holdObject, __ARGUMENTS(axis, direction));
	
		// add to collision detection system again
		InGameEntity_setShapeState((InGameEntity)this->holdObject, true);

		// not holding it anumore
		this->holdObject = NULL;
	}
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// die mario
void Hero_die(Hero this){
/*
	// go to dead state
	StateMachine_swapState(this->stateMachine, (State)HeroDead_getInstance());
	
	// if I have something being hold
	if(this->holdObject){
	
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// check if must move over a bridge
void Hero_checkIfBridge(Hero this, int keyPressed){

	/*
	// if I'm close to a bridge
	if(this->bridge){
		
		char walkFrontStr[] = "WalkFront";
		char walkFrontHoldStr[] = "WalkFront";
		char walkBackStr[] = "WalkBack";
		char walkBackHoldStr[] = "WalkBack";
		
		
		char* walkAnimation = walkFrontStr;

		// if up key pressed
		if(K_LU & keyPressed){
			
			if(__FAR != Bridge_getDirection(this->bridge)){
				
				return;
			}
		}

		// if down key pressed
		if(K_LD & keyPressed){
			
			if(__NEAR != Bridge_getDirection(this->bridge)){
				
				return;
			}
		}

		// check that I'm close to the bridge
		{
			VBVec3D position = Entity_getPosition((Entity)this->bridge);
			int width = ITOFIX19_13(Entity_getWidth((Entity)this->bridge) >> 1);
			Gap gap = InGameEntity_getGap((InGameEntity)this->bridge);
			
			if(this->transform.globalPosition.x < position.x - width + ITOFIX19_13(gap.left) 
			   || 
			   this->transform.globalPosition.x > position.x + width - ITOFIX19_13(gap.right)){

				return;
			}
		}
		
		
		if(this->holdObject){
			
			
			if(__NEAR == this->direction.z){
				
				walkAnimation = walkFrontHoldStr;	
			}
			else{
				
				walkAnimation = walkBackHoldStr;
			}
		}
		else{
			
			if(__FAR == this->direction.z){
				
				walkAnimation = walkBackStr;
			}

		}

		// if it is only moving over the x axis and walking animation is no playing
		if(!AnimatedSprite_isPlayingFunction((AnimatedSprite)this->sprite, this->actorDefinition->animationDescription, walkAnimation)){
			
			// must play walk animation of not playing it
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, walkAnimation);
		}

		// change state
		StateMachine_swapState(this->stateMachine, (State)HeroOnBridge_getInstance());
	}
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// update movement over the bridge
void Hero_moveOnBridge(Hero this){

/*
	this->transform.globalPosition.z += FIX19_13_MULT(HERO_DISPLACEMENT_ON_BRIDGE, ITOFIX19_13(this->direction.z));
	
	// if I'm holding something
	if(this->holdObject){
		
		// update object's position
		Hero_updateHoldObjectPosition(this);
	}
	*/
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// determine which layer I'm
void Hero_determineLayer(Hero this){
//
	int i = 0;
	for(i = 0; i < TOTAL_GAME_LAYERS; i++){
		
		if((u16)this->transform.globalPosition.z > gameLayers[i] - ITOFIX19_13(5) && (unsigned)this->transform.globalPosition.z < gameLayers[i] + ITOFIX19_13(5)){
			
			this->layer = (int )i;
			return;
		}
			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// clear the actionTime
void Hero_resetActionTime(Hero this){

	//this->actionTime = Clock_getTime(Game_getClock(Game_getInstance()));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// goal reached
void Hero_win(Hero this){
	/*
	this->direction.z = __FAR;
	
	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "WalkBack");
	
	Actor_startMovement((Actor)this, __ZAXIS, __UNIFORMMOVE, FIX19_13_DIV(HERO_VELOCITY_Z, ITOFIX19_13(4)), 0);
	
	this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// goal reached
void Hero_moveOnWin(Hero this){
	
	/*
	u32 currentTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	
	if(this->velocity.z){
	
			
			// inform the game that I'm dead
			//GameWorld_levelCleared(GameWorld_getInstance());
		}
		
		if(currentTime - this->actionTime < HERO_WIN_DELAY / 2){
				
			Actor_move((Actor)this);
		}
		return;
	}
	
	Actor_move((Actor)this);
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// process user input
static void Hero_onKeyPressed(Hero this){

	u16 pressedKey = KeypadManager_getPressedKey(KeypadManager_getInstance());
	
	// inform my current states about the key pressed		
	MessageDispatcher_dispatchMessage(0, (Object)this, (Object)this->stateMachine, kKeyPressed, &pressedKey);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// process user input
static void Hero_onKeyReleased(Hero this){

	u16 releasedKey = KeypadManager_getReleasedKey(KeypadManager_getInstance());

	// inform my current states about the key up		
	MessageDispatcher_dispatchMessage(0, (Object)this, (Object)this->stateMachine, kKeyUp, &releasedKey);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// process user input
static void Hero_onKeyHold(Hero this){

	u16 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

	// inform my current states about the key hold		
	MessageDispatcher_dispatchMessage(0, (Object)this, (Object)this->stateMachine, kKeyHold, &holdKey);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// check if dead
void Hero_checkIfDied(Hero this) {

	ASSERT(this->body, "Hero::checkIfDied: null body");
		
	Velocity velocity = Body_getVelocity(this->body);

	if (0 < velocity.y){
		
		if(this->transform.globalPosition.y > ITOFIX19_13(384)) {

			MessageDispatcher_dispatchMessage(0, (Object)this, (Object)Game_getInstance(), kHeroDied, NULL);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// collect a coin
void Hero_collectCoin(Hero this)
{
	this->coins++;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// process collisions
int Hero_processCollision(Hero this, Telegram telegram){
	
	VirtualList collidingObjects = (VirtualList)Telegram_getExtraInfo(telegram);
	ASSERT(collidingObjects, "HeroMoving::handleMessage: null collidingObjects");

	VirtualNode node = NULL;

	VirtualList collidingObjectsToRemove = __NEW(VirtualList);

	for(node = VirtualList_begin(collidingObjects); node; node = VirtualNode_getNext(node)){
	
		InGameEntity inGameEntity = (InGameEntity)VirtualNode_getData(node);
		
		switch(InGameEntity_getInGameType(inGameEntity)){
								
			case kCoin:

				Hero_collectCoin(this);
				MessageDispatcher_dispatchMessage(0, (Object)this, (Object)inGameEntity, kTakeCoin, NULL);
				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;
								
			case kDoor:

				VirtualList_pushBack(collidingObjectsToRemove, inGameEntity);
				break;
		}
	}
	
	for(node = VirtualList_begin(collidingObjectsToRemove); node; node = VirtualNode_getNext(node)){

		// when ever you process some objects of a collisions list
		// remove them and leave the Actor handle the ones you don't
		// care, i.e.: in most cases, the ones which are solid 
		VirtualList_removeElement(collidingObjects, VirtualNode_getData(node));
	}
	
	__DELETE(collidingObjectsToRemove);
	
	return !VirtualList_getSize(collidingObjects);
}
