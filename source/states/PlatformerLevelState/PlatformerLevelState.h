/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PLATFORMER_LEVEL_STATE_H_
#define PLATFORMER_LEVEL_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <KeypadManager.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINES
//---------------------------------------------------------------------------------------------------------

#define PLATFORMER_MESSAGE_DURATION		3000
#define PLATFORMER_CAMERA_OFFSET_X		__PIXELS_TO_METERS(50)
#define PLATFORMER_CAMERA_OFFSET_Y		__PIXELS_TO_METERS(-30)

enum PlatformerLevelModes
{
	kPlaying = 1,
	kShowingUp,
	kPaused,
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct StageEntryPointSpec
{
	// the stage to load
	StageSpec* stageSpec;

	// name of the entity to start at
	char* destinationName;

	// offset from entry point (x, y, z)
	ScreenPixelVector offset;

	// facing direction of the hero
	int8 direction;

	// whether this entry point acts as a checkpoint
	bool isCheckPoint;

} StageEntryPointSpec;

typedef const StageEntryPointSpec StageEntryPointROMSpec;


typedef struct PlatformerLevelSpec
{
	// starting entry point
	StageEntryPointSpec* entryPoint;

	// id
	uint8 id;

	// identifier
	void* identifier;

	// name
	void* name;

	// slogan
	void* slogan;

} PlatformerLevelSpec;

typedef const PlatformerLevelSpec PlatformerLevelROMSpec;


enum PlatformerLevelStateMessageTypes
{
	kMessageCannonBallCheckDisplacement = kMessageLastEngine + 1,
	kMessageCannonShoot,
	kMessageCogWheelMove,
	kMessageCogWheelStop,
	kMessageHeroCheckVelocity,
	kMessageHeroDied,
	kMessageHeroEnterDoor,
	kMessageHeroFlash,
	kMessageHeroResumePhysics,
	kMessageHeroSleep,
	kMessageHeroStopFeetDust,
	kMessageHeroStopInvincibility,
	kMessageHideLevelMessage,
	kMessageHintPlayAnimation,
	kMessageLavaMove,
	kMessageLavaTriggerEnd,
	kMessageLavaTriggerStart,
	kMessagePrintUI,
	kMessageLevelResumed,
	kMessageLevelSetUp,
	kMessageLevelStarted,
	kMessageLoadCheckPoint,
	kMessageMovingEntityCheckDirection,
	kMessageMovingEntityStartMoving,
	kMessageReactToCollision,
	kMessageScreenFocused,
	kMessageStopReactToCollision,
	kMessageTakeItem,

	// don't remove me
	kMessageLastGame
};


singleton class PlatformerLevelState : GameState
{
	/* previous user input */
	UserInput userInput;
	/* the currently loaded level */
	PlatformerLevelSpec* currentLevel;
	/* the currently loaded entry point */
	StageEntryPointSpec* currentStageEntryPoint;
	/* the last reached checkpoint */
	StageEntryPointSpec* currentCheckPoint;
	/* in-game clock */
	Clock clock;
	/* to allow moving the screen */
	uint8 mode;

	static PlatformerLevelState getInstance(void);
	PlatformerLevelSpec* getCurrentLevelSpec();
	void startLevel(PlatformerLevelSpec* platformerLevelSpec);
	void enterStage(StageEntryPointSpec* entryPointSpec);
	void setModeToPaused();
	void setModeToPlaying();
	UserInput getUserInput();
	override void enter(void* owner);
	override void exit(void* owner);
	override void suspend(void* owner);
	override void resume(void* owner);
	override bool processMessage(void* owner, Telegram telegram);
	override void processUserInput(UserInput userInput);
	override Clock getClock();
}


#endif
