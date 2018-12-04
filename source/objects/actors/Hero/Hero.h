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

#ifndef HERO_H_
#define HERO_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <Door.h>
#include <ParticleSystem.h>
#include <ProgressManager.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

enum HeroPowerUps
{
	kPowerUpNone,
	kPowerUpBandana,
};

#define HERO_NAME							"John Hero"
#define HERO_INITIAL_ENERGY					3

#define HERO_MASS							1
#define HERO_BOUNCINESS						0.0f
#define HERO_FRICTION						0

#define HERO_FLASH_PALETTE					3
#define HERO_FLASH_DURATION					2000
#define HERO_FLASH_INTERVAL					100

#define HERO_SLEEP_DELAY					7500

#define HERO_FORCE_FOR_STOPPING 			__F_TO_FIX10_6(-4.5f)
#define HERO_INPUT_FORCE 					__I_TO_FIX10_6(60)
#define HERO_X_INPUT_FORCE_WHILE_JUMPING	__I_TO_FIX10_6(10)

#define HERO_MAX_VELOCITY_X					__F_TO_FIX10_6(3.5f)
#define HERO_MAX_VELOCITY_Y					__F_TO_FIX10_6(15)
#define HERO_MAX_VELOCITY_Z					__F_TO_FIX10_6(4)
#define HERO_BOOST_VELOCITY_X				__F_TO_FIX10_6(4.0f)
#define HERO_NORMAL_JUMP_INPUT_FORCE		__F_TO_FIX10_6(-240)
#define HERO_BOOST_JUMP_INPUT_FORCE			__F_TO_FIX10_6(-270)

#define CAMERA_BOUNDING_BOX_DISPLACEMENT	{__PIXELS_TO_METERS(0), __PIXELS_TO_METERS(-24/16), __PIXELS_TO_METERS(0)}

#define HERO_CHECK_Y_VELOCITY				(20/16)


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const ActorDefinition HeroDefinition;
typedef const HeroDefinition HeroROMDef;

class Hero : Actor
{
	/* a reference to the last door the hero passed */
	Door currentlyOverlappedDoor;
	/* hint entity */
	Entity hint;
	/* feet dust */
	ParticleSystem feetDust;
	/* used to know if gap must be changed */
	Direction inputDirection;
	/* hero has energy	*/
	u8 energy;
	/* boost flag */
	bool boost;
	/* number of collected coins */
	u8 coins;
	/* flag for collected key */
	bool hasKey;
	/* currently active power-up */
	u8 powerUp;
	/* number of jumps performed (for double jump) */
	s8 jumps;
	/* flag for invincible mode (after being hit) */
	bool invincible;
	/* flag to keep applying force to the x axis */
	bool keepAddingForce;
	/* flag to keep applying force to the x axis */
	bool underWater;

	static Hero getInstance();
	void constructor(HeroDefinition* heroDefinition, s16 id, s16 internalId, const char* const name);
	void addForce(u16 axis, bool enableAddingForce);
	void stopAddingForce();
	void startedMovingOnAxis(u16 axis);
	bool stopMovingOnAxis(u16 axis);
	void move();
	void jump(bool checkIfYMovement);
	void addMomentumToJump();
	void checkDirection(u32 currentPressedKey, char * animation);
	void takeHitFrom(SpatialObject collidingObject, int energyToReduce, bool pause, bool invincibleWins);
	void flash();
	void toggleFlashPalette();
	void resetPalette();
	void disableBoost();
	void enableBoost();
	Door getOverlappedDoor();
	void enterDoor();
	void showHint(u32 hintType);
	void hideHint();
	void lookFront();
	void lookBack();
	void die();
	void collectKey();
	bool hasKey();
	void collectPowerUp(u8 powerUp);
	u8 getPowerUp();
	u8 getEnergy();
	void setInvincible(bool invincible);
	bool isInvincible();
	void lockCameraTriggerMovement(u8 axisToLockUp, bool locked);
	void getOutOfDoor(Vector3D* outOfDoorPosition);
	bool isBelow(Shape shape, const CollisionInformation* collisionInformation);
	void onPowerUpTransitionComplete(Object eventFirer);
	void capVelocity(bool discardPreviousMessages);
	override void ready(bool recursive);
	override bool handlePropagatedMessage(int message);
	override bool handleMessage(Telegram telegram);
	override void suspend();
	override void resume();
	override bool isAffectedByRelativity();
	override fix10_6 getFrictionOnCollision(SpatialObject collidingObject, const Vector3D* collidingObjectNormal);
	override bool enterCollision(const CollisionInformation* collisionInformation);
	override bool updateCollision(const CollisionInformation* collisionInformation);
	override void syncRotationWithBody();
	override void exitCollision(Shape shape, Shape shapeNotCollidingAnymore, bool isShapeImpenetrable);
	override u16 getAxesForShapeSyncWithDirection();
}


#endif

