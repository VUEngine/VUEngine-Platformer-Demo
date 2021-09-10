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
