/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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

#define HERO_FORCE_FOR_STOPPING 			__F_TO_FIX10_6(-0.05f)
#define HERO_INPUT_FORCE 					__I_TO_FIX10_6(5)
#define HERO_X_INPUT_FORCE_WHILE_JUMPING	__I_TO_FIX10_6(10)

#define HERO_MAX_VELOCITY_X					__F_TO_FIX10_6(3.5f)
#define HERO_MAX_VELOCITY_Y					__F_TO_FIX10_6(15)
#define HERO_MAX_VELOCITY_Z					__F_TO_FIX10_6(4)
#define HERO_BOOST_VELOCITY_X				__F_TO_FIX10_6(4.0f)
#define HERO_NORMAL_JUMP_INPUT_FORCE		__F_TO_FIX10_6(-240)
#define HERO_BOOST_JUMP_INPUT_FORCE			__F_TO_FIX10_6(-270)

#define CAMERA_BOUNDING_BOX_DISPLACEMENT	{__PIXELS_TO_METERS(0), __PIXELS_TO_METERS(-24/16), __PIXELS_TO_METERS(0)}

#define HeroCharsetECK_Y_VELOCITY				(20/16)


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const ActorSpec HeroSpec;
typedef const HeroSpec HeroROMSpec;

class Hero : Actor
{
	/* a reference to the last door the hero passed */
	Door currentlyOverlappedDoor;
	/* hint entity */
	Entity hint;
	/* feet dust */
	ParticleSystem feetDust;
	/* used to know if gap must be changed */
	NormalizedDirection inputDirection;
	/* hero has energy	*/
	uint8 energy;
	/* boost flag */
	bool boost;
	/* number of collected coins */
	uint8 coins;
	/* flag for collected key */
	bool hasKey;
	/* currently active power-up */
	uint8 powerUp;
	/* number of jumps performed (for double jump) */
	int8 jumps;
	/* flag for invincible mode (after being hit) */
	bool invincible;
	/* flag to keep applying force to the x axis */
	bool keepAddingForce;
	/* flag to keep applying force to the x axis */
	bool underWater;

	static Hero getInstance();
	void constructor(HeroSpec* heroSpec, int16 internalId, const char* const name);
	void applyForceOnAxis(uint16 axis, bool enableAddingForce);
	void stopAddingForce();
	void startedMovingOnAxis(uint16 axis);
	bool stopMovingOnAxis(uint16 axis);
	void move();
	void jump(bool checkIfYMovement);
	void addMomentumToJump();
	void checkDirection(uint32 currentPressedKey, char * animation);
	void takeDamageFrom(SpatialObject collidingObject, int energyToReduce, bool pause, bool invincibleWins);
	void flash();
	void toggleFlashPalette();
	void resetPalette();
	void disableBoost();
	void enableBoost();
	Door getOverlappedDoor();
	void enterDoor();
	void showHint(uint32 hintType);
	void hideHint();
	void lookFront();
	void lookBack();
	void die();
	void collectKey();
	bool hasKey();
	void collectPowerUp(uint8 powerUp);
	uint8 getPowerUp();
	uint8 getEnergy();
	void setInvincible(bool invincible);
	bool isInvincible();
	void lockCameraTriggerMovement(uint8 axisToLockUp, bool locked);
	void getOutOfDoor(Vector3D* outOfDoorPosition);
	bool isBelow(Collider shape, const CollisionInformation* collisionInformation);
	void onPowerUpTransitionComplete(Object eventFirer);
	void capVelocity(bool discardPreviousMessages);
	override void ready(bool recursive);
	override bool handlePropagatedMessage(int message);
	override bool handleMessage(Telegram telegram);
	override void suspend();
	override void resume();
	override fix10_6 getFrictionOnCollision(SpatialObject collidingObject, const Vector3D* collidingObjectNormal);
	override bool enterCollision(const CollisionInformation* collisionInformation);
	override bool updateCollision(const CollisionInformation* collisionInformation);
	override void syncRotationWithBody();
	override void exitCollision(Collider shape, Collider shapeNotCollidingAnymore, bool isColliderImpenetrable);
}


#endif

