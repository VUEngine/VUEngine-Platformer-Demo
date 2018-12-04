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

#include <string.h>
#include <GameEvents.h>
#include <Game.h>
#include <Optics.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <PhysicalWorld.h>
#include <Utilities.h>
#include <I18n.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <PauseScreenState.h>
#include <Hero.h>
#include <Languages.h>
#include <ProgressManager.h>
#include <PlatformerCameraMovementManager.h>
#include <CustomCameraEffectManager.h>
#include <EventManager.h>
#include <PostProcessingLantern.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern PlatformerLevelDefinition LEVEL_1_LV;
extern EntityDefinition HERO_AC;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void PlatformerLevelState::constructor()
{
	Base::constructor();

	// clock
	this->clock = new Clock();

	// set default entry point
	this->currentLevel = (PlatformerLevelDefinition*)&LEVEL_1_LV;
	this->currentStageEntryPoint = this->currentLevel->entryPoint;
	this->currentCheckPoint = this->currentLevel->entryPoint;
	this->userInput = (UserInput){0, 0, 0, 0, 0, 0, 0};
}

// class's destructor
void PlatformerLevelState::destructor()
{
	delete this->clock;

	// destroy base
	Base::destructor();
}

void PlatformerLevelState::getPositionedEntitiesToIgnore(VirtualList positionedEntitiesToIgnore)
{
	ASSERT(positionedEntitiesToIgnore, "PlatformerLevelState::getPositionedEntitiesToIgnore: null positionedEntitiesToIgnore");

	if(positionedEntitiesToIgnore)
	{
		extern EntityDefinition BANDANA_AG;
		extern EntityDefinition KEY_AG;

		// loop stage entities and remove items which have already been collected
		int i = 0;
		for(; this->currentStageEntryPoint->stageDefinition->entities.children[i].entityDefinition; i++)
		{
			if((this->currentStageEntryPoint->stageDefinition->entities.children[i].entityDefinition == (EntityDefinition*)&BANDANA_AG) ||
				(this->currentStageEntryPoint->stageDefinition->entities.children[i].entityDefinition == (EntityDefinition*)&KEY_AG))
			{
				if(ProgressManager::getItemStatus(ProgressManager::getInstance(), this->currentStageEntryPoint->stageDefinition->entities.children[i].id))
				{
					VirtualList::pushBack(positionedEntitiesToIgnore, &this->currentStageEntryPoint->stageDefinition->entities.children[i]);
				}
			}
		}
	}
}

// state's enter
void PlatformerLevelState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// set the custom screen managers
	Camera::setCameraMovementManager(Camera::getInstance(), CameraMovementManager::safeCast(PlatformerCameraMovementManager::getInstance()));
	Camera::setCameraEffectManager(Camera::getInstance(), CameraEffectManager::safeCast(CustomCameraEffectManager::getInstance()));

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// get list of entities that should not be loaded
	VirtualList positionedEntitiesToIgnore = new VirtualList();
	PlatformerLevelState::getPositionedEntitiesToIgnore(this, positionedEntitiesToIgnore);

	// focus camera on destination entity
	if(this->currentStageEntryPoint->destinationName)
	{
		// iterate stage definition to find global position of destination entity
		Vector3D environmentPosition = {0, 0, 0};
		Vector3D* initialPosition = Entity::calculateGlobalPositionFromDefinitionByName(this->currentStageEntryPoint->stageDefinition->entities.children, environmentPosition, this->currentStageEntryPoint->destinationName);

		Printing::int(Printing::getInstance(), initialPosition->x, 0, 0, NULL);
		Printing::int(Printing::getInstance(), initialPosition->y, 0, 1, NULL);
		Printing::int(Printing::getInstance(), initialPosition->z, 0, 2, NULL);

//		ASSERT(initialPosition, "PlatformerLevelState::enter: no initial position");

		// if global position of destination entity could be found, move the hero and the screen there
		if(initialPosition)
		{
			// apply entry point offset
			initialPosition->x += __PIXELS_TO_METERS(this->currentStageEntryPoint->offset.x);
			initialPosition->y += __PIXELS_TO_METERS(this->currentStageEntryPoint->offset.y);
			initialPosition->z += __PIXELS_TO_METERS(this->currentStageEntryPoint->offset.z + this->currentStageEntryPoint->offset.zDisplacement);

			// set world's limits
			Camera::setStageSize(Camera::getInstance(), Size::getFromPixelSize(this->currentStageEntryPoint->stageDefinition->level.pixelSize));

			// focus screen on new position
			Vector3D screenPosition =
			{
				initialPosition->x - __PIXELS_TO_METERS(__HALF_SCREEN_WIDTH) + (this->currentStageEntryPoint->direction * PLATFORMER_CAMERA_OFFSET_X),
				initialPosition->y - __PIXELS_TO_METERS(__HALF_SCREEN_HEIGHT) + PLATFORMER_CAMERA_OFFSET_Y,
				__PIXELS_TO_METERS(this->currentStageEntryPoint->stageDefinition->level.cameraInitialPosition.z),
			};

			Camera::setPosition(Camera::getInstance(), screenPosition);

			// load stage
			GameState::loadStage(this, this->currentStageEntryPoint->stageDefinition, positionedEntitiesToIgnore, false);

			// get hero entity
			Container hero = Container::getChildByName(this->stage, HERO_NAME, true);

			// if no hero could be found, create one. otherwise, move found hero.
			if(!hero)
			{
				PositionedEntity positionedEntity =
				{
					&HERO_AC,
					{
						__METERS_TO_PIXELS(initialPosition->x),
						__METERS_TO_PIXELS(initialPosition->y),
						__METERS_TO_PIXELS(initialPosition->z),
						0
					},
					0,
					HERO_NAME,
					NULL,
					NULL,
					false
				};

				hero = Container::safeCast(Stage::addChildEntity(this->stage, &positionedEntity, true));

				// make sure that the streaming doesn't load the hero again
				Stage::registerEntityId(this->stage, Entity::getInternalId(hero), &HERO_AC);
			}

			Object::addEventListener(hero, Object::safeCast(this), (EventListener)PlatformerLevelState::onHeroStreamedOut, kStageChildStreamedOut);

			// set hero's position
			Actor::setPosition(hero, initialPosition);

			// make sure that focusing gets completed immediately
			PlatformerCameraMovementManager::enable(PlatformerCameraMovementManager::getInstance());

			// update actor's global transformations
			GameState::transform(this);

			PlatformerCameraMovementManager::configure(PlatformerCameraMovementManager::getInstance(), kHero, kPlayerLayer, kCameraLayer, (PixelSize){12 * 8, 20 * 8, 4 * 8}, (Vector3D){__PIXELS_TO_METERS(0), __PIXELS_TO_METERS(-24/16), __PIXELS_TO_METERS(0)});

			// set focus on the hero
			Camera::setFocusGameEntity(Camera::getInstance(), Entity::safeCast(hero));
			Vector3D screenDisplacement = {PLATFORMER_CAMERA_OFFSET_X, PLATFORMER_CAMERA_OFFSET_Y, 0};
			Camera::setFocusEntityPositionDisplacement(Camera::getInstance(), screenDisplacement);

			// set direction according to entry point
			Direction direction = {this->currentStageEntryPoint->direction, __DOWN, __FAR};
			Entity::setDirection(Entity::safeCast(hero), direction);

			// apply changes to the visuals
			GameState::synchronizeGraphics(this);
		}
		else
		{
			// load stage
			GameState::loadStage(this, this->currentStageEntryPoint->stageDefinition, positionedEntitiesToIgnore, true);
		}
	}
	else
	{
		// load stage
		GameState::loadStage(this, this->currentStageEntryPoint->stageDefinition, positionedEntitiesToIgnore, true);
	}

	PlatformerCameraMovementManager::disable(PlatformerCameraMovementManager::getInstance());

	// free some memory
	delete positionedEntitiesToIgnore;

	// level is paused
	PlatformerLevelState::setModeToPaused(this);

	// start clocks
	Clock::start(this->clock);
	Clock::setTimeInMilliSeconds(this->clock, ProgressManager::getCurrentLevelTime(ProgressManager::getInstance()));
	GameState::startClocks(this);

	// register event listeners
	Object::addEventListener(Object::safeCast(EventManager::getInstance()), Object::safeCast(this), (EventListener)PlatformerLevelState::onHeroDied, kEventHeroDied);

	// TODO: this is hacky
	// activate pulsating effect in indoor stages
	if(this->currentStageEntryPoint->stageDefinition->rendering.colorConfig.brightnessRepeat != NULL)
	{
		Camera::startEffect(Camera::getInstance(), kScreenPulsate);
	}
	// activate lantern effect around hero
	if(this->currentStageEntryPoint->stageDefinition->rendering.colorConfig.brightness.brightRed == (__BRIGHTNESS_BRIGHT_RED >> 1))
	{
		Container hero = Container::getChildByName(this->stage, HERO_NAME, true);
		if(hero)
		{
			Game::pushBackProcessingEffect(Game::getInstance(), PostProcessingLantern::lantern, SpatialObject::safeCast(hero));
		}
	}

	// print level name if at level start point
	if(PlatformerLevelState::isStartingLevel(this) && this->currentLevel->name)
	{
		const char* strLevelName = I18n::getText(I18n::getInstance(), (int)this->currentLevel->name);
		Printing::text(
			Printing::getInstance(),
			strLevelName,
			((__SCREEN_WIDTH_IN_CHARS) - strlen(strLevelName)) >> 1,
			6,
			"AstonishS"
		);

		if(this->currentLevel->identifier)
		{
			const char* strLevel = I18n::getText(I18n::getInstance(), STR_LEVEL);
			const char* strLevelId = this->currentLevel->identifier;
			u8 strLevelLength = strlen(strLevel);
			u8 strLevelIdLength = strlen(strLevelId);
			Printing::text(
				Printing::getInstance(),
				strLevel,
				((__SCREEN_WIDTH_IN_CHARS) - strLevelLength - strLevelIdLength) >> 1,
				4,
				NULL
			);
			Printing::text(
				Printing::getInstance(),
				strLevelId,
				(((__SCREEN_WIDTH_IN_CHARS) - strLevelLength - strLevelIdLength) >> 1) + strLevelLength + 1,
				4,
				NULL
			);
		}

		if(this->currentLevel->slogan)
		{
			const char* strLevelSlogan = I18n::getText(I18n::getInstance(), (int)this->currentLevel->slogan);
			FontSize strLevelSloganSize = Printing::getTextSize(Printing::getInstance(), strLevelSlogan, NULL);
			Printing::text(
				Printing::getInstance(),
				strLevelSlogan,
				((__SCREEN_WIDTH_IN_CHARS) - strLevelSloganSize.x) >> 1,
				9,
				NULL
			);
		}

		// erase level message in a moment
		MessageDispatcher::dispatchMessage(PLATFORMER_MESSAGE_DURATION, Object::safeCast(this), Object::safeCast(Game::getInstance()), kHideLevelMessage, NULL);
	}
	else if(this->currentStageEntryPoint->isCheckPoint)
	{
		// write checkpoint message to screen
		const char* strCheckpoint = I18n::getText(I18n::getInstance(), STR_CHECKPOINT);
		Printing::text(
			Printing::getInstance(),
			strCheckpoint,
			((__SCREEN_WIDTH_IN_CHARS) - strlen(strCheckpoint)) >> 1,
			6,
			NULL
		);

		// erase checkpoint message in a moment
		MessageDispatcher::dispatchMessage(PLATFORMER_MESSAGE_DURATION, Object::safeCast(this), Object::safeCast(Game::getInstance()), kHideLevelMessage, NULL);
	}

	// tell any interested entity
	GameState::propagateMessage(this, kLevelSetUp);

	this->mode = kShowingUp;

	// fade in screen after a little delay
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		250, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PlatformerLevelState::onLevelStartedFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// state's exit
void PlatformerLevelState::exit(void* owner)
{
	Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)PlatformerLevelState::onHeroDied, kEventHeroDied);

	// call base
	Base::exit(this, owner);
}

void PlatformerLevelState::suspend(void* owner)
{
	// set pause mode
	PlatformerLevelState::setModeToPaused(this);

	// pause clocks
	Clock::pause(this->messagingClock, true);
	Clock::pause(this->clock, true);

	// pause physical simulations
	GameState::pausePhysics(this, true);

#ifdef __DEBUG_TOOLS
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif

	// do a fade out effect
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_INSPECTOR
	}
#endif

	// call base
	Base::suspend(this, owner);
}

void PlatformerLevelState::resume(void* owner)
{
	// resume in-game clock
	Clock::pause(this->messagingClock, false);
	Clock::pause(this->clock, false);

	// call base
	Base::resume(this, owner);

#ifdef __DEBUG_TOOLS
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif

	// tell any interested entity
	GameState::propagateMessage(this, kLevelResumed);

	// start a fade in effect
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		NULL, // callback function
		NULL // callback scope
	);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_INSPECTOR
	}
#endif

	// pause physical simulations
	GameState::pausePhysics(this, false);

	PlatformerLevelState::setModeToPlaying(this);

	UserInput userInput = KeypadManager::getUserInput(KeypadManager::getInstance());

	this->userInput.pressedKey 	= userInput.allKeys & ~this->userInput.previousKey;
	this->userInput.releasedKey = ~userInput.allKeys & this->userInput.previousKey;
	this->userInput.holdKey 	= userInput.allKeys & this->userInput.previousKey;

	// make sure that user input is taken into account
	Object::fireEvent(this, kEventUserInput);

	PlatformerLevelState::setPrintingLayerCoordinates(this);

	Game::enableKeypad(Game::getInstance());
}

void PlatformerLevelState::setPrintingLayerCoordinates()
{
	extern TextureROMDef GUI_TX;
	Printing::setWorldCoordinates(Printing::getInstance(), __PRINTING_BGMAP_X_OFFSET, __SCREEN_HEIGHT - (GUI_TX.rows * 8));
}

UserInput PlatformerLevelState::getUserInput()
{
	return this->userInput;
}

void PlatformerLevelState::processUserInput(UserInput userInput)
{
	if(kPlaying == this->mode)
	{
		this->userInput = userInput;

		if(this->userInput.pressedKey)
		{
			if(K_SEL & this->userInput.pressedKey)
			{
				// adjustment screen
				PlatformerLevelState::setModeToPaused(this);

				// pause game and switch to adjustment screen state
				Game::pause(Game::getInstance(), GameState::safeCast(AdjustmentScreenState::getInstance()));

				return;
			}
			else if(K_STA & this->userInput.pressedKey)
			{
				// pause game and switch to pause screen state
				Game::pause(Game::getInstance(), GameState::safeCast(PauseScreenState::getInstance()));

				return;
			}
		}

		Object::fireEvent(this, kEventUserInput);
	}
}

// state's handle message
bool PlatformerLevelState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram::getMessage(telegram))
	{
		case kHideLevelMessage:

			PlatformerLevelState::setPrintingLayerCoordinates(this);
			break;

		case kScreenFocused:

			Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)PlatformerLevelState::onScreenFocused, kEventScreenFocused);
			break;

		case kLoadCheckPoint:

			PlatformerLevelState::startStage(this, this->currentCheckPoint);

			// announce checkpoint loaded
			Object::fireEvent(EventManager::getInstance(), kEventCheckpointLoaded);
			break;
	}

	return false;
}

void PlatformerLevelState::onScreenFocused(Object eventFirer __attribute__ ((unused)))
{
	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(Game::getInstance()), kScreenFocused, NULL);

	PlatformerCameraMovementManager::dontAlertWhenTargetFocused(PlatformerCameraMovementManager::getInstance());

	Game::enableKeypad(Game::getInstance());
}

void PlatformerLevelState::onHeroDied(Object eventFirer __attribute__ ((unused)))
{
	// unset the hero as focus entity from the custom screen movement manager
	Camera::setFocusGameEntity(Camera::getInstance(), NULL);

	// start a fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PlatformerLevelState::onHeroDiedFadeOutComplete, // callback function
		Object::safeCast(this) // callback scope
	);

	Game::disableKeypad(Game::getInstance());
}

void PlatformerLevelState::onHeroStreamedOut(Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelState::setModeToPaused(this);
}

// get in-game clock
Clock PlatformerLevelState::getClock()
{
	return this->clock;
}

// get current level's definition
PlatformerLevelDefinition* PlatformerLevelState::getCurrentLevelDefinition()
{
	return this->currentLevel;
}

// start a given level
void PlatformerLevelState::startLevel(PlatformerLevelDefinition* platformerLevelDefinition)
{
	this->currentLevel = platformerLevelDefinition;
	this->currentCheckPoint = this->currentStageEntryPoint = this->currentLevel->entryPoint;

	// announce level start
	Object::fireEvent(EventManager::getInstance(), kEventLevelStarted);

	Game::changeState(Game::getInstance(), GameState::safeCast(this));
}

// enter a given stage
void PlatformerLevelState::enterStage(StageEntryPointDefinition* entryPointDefinition)
{
	// save stats if is checkpoint
	if(entryPointDefinition->isCheckPoint)
	{
		// write checkpoint stats
		ProgressManager::setCheckPointData(ProgressManager::getInstance());

		// set current checkpoint
		this->currentCheckPoint = entryPointDefinition;
	}

	PlatformerLevelState::startStage(this, entryPointDefinition);
}

// start a given stage
void PlatformerLevelState::startStage(StageEntryPointDefinition* entryPointDefinition)
{
	// set current entry point
	this->currentStageEntryPoint = entryPointDefinition;

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// pause physical simulations
	GameState::pausePhysics(this, true);

	// start a fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PlatformerLevelState::onStartStageFadeOutComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// determine if starting a new level
bool PlatformerLevelState::isStartingLevel()
{
	return (this->currentStageEntryPoint == this->currentLevel->entryPoint);
}

// set paused mode
void PlatformerLevelState::setModeToPaused()
{
	this->mode = kPaused;
}

// set playing mode
void PlatformerLevelState::setModeToPlaying()
{
	this->mode = kPlaying;
}

// handle event
void PlatformerLevelState::onLevelStartedFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// tell any interested entity
	GameState::propagateMessage(this, kLevelStarted);

	PlatformerLevelState::setModeToPlaying(this);

	// enable focus easing
	Object::addEventListener(Object::safeCast(EventManager::getInstance()), Object::safeCast(this), (EventListener)PlatformerLevelState::onScreenFocused, kEventScreenFocused);
	PlatformerCameraMovementManager::enableFocusEasing(PlatformerCameraMovementManager::getInstance());
	PlatformerCameraMovementManager::alertWhenTargetFocused(PlatformerCameraMovementManager::getInstance());
}

// handle event
void PlatformerLevelState::onStartStageFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::changeState(Game::getInstance(), GameState::safeCast(this));
}

// handle event
void PlatformerLevelState::onHeroDiedFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(Game::getInstance()), kLoadCheckPoint, NULL);
}
