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

#include <string.h>
#include <GameEvents.h>
#include <Game.h>
#include <Optics.h>
#include <Screen.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <PhysicalWorld.h>
#include <I18n.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <OverworldState.h>
#include <PauseScreenState.h>
#include <Hero.h>
#include "../stages/stages.h"
#include <macros.h>
#include <Languages.h>
#include <objects.h>
#include <ProgressManager.h>
#include <CustomScreenMovementManager.h>
#include <CustomScreenEffectManager.h>
#include <EventManager.h>
#include <KeyPadManager.h>
#include <Utilities.h>
#include <PostProcessingEffects.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PlatformerLevelState_constructor(PlatformerLevelState this);
static void PlatformerLevelState_destructor(PlatformerLevelState this);
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_suspend(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner);
static bool PlatformerLevelState_processMessage(PlatformerLevelState this, void* owner, Telegram telegram);
static void PlatformerLevelState_getEntityNamesToIngnore(PlatformerLevelState this, VirtualList entityNamesToIgnore);
bool PlatformerLevelState_isStartingLevel(PlatformerLevelState this);
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this);
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this);
void PlatformerLevelState_onScreenFocused(PlatformerLevelState this, Object eventFirer);
void PlatformerLevelState_onHeroDied(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onLevelStartedFadeInComplete(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onEnterStageFadeOutComplete(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onHeroDiedFadeOutComplete(PlatformerLevelState this, Object eventFirer);

extern PlatformerLevelDefinition LEVEL_1_LV;


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PlatformerLevelState, GameState);
__SINGLETON(PlatformerLevelState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) PlatformerLevelState_constructor(PlatformerLevelState this)
{
	__CONSTRUCT_BASE(GameState);

	// set default entry point
	this->currentLevel = (PlatformerLevelDefinition*)&LEVEL_1_LV;
	this->currentStageEntryPoint = this->currentLevel->entryPoint;
}

// class's destructor
static void PlatformerLevelState_destructor(PlatformerLevelState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

static void PlatformerLevelState_getEntityNamesToIngnore(PlatformerLevelState this  __attribute__ ((unused)), VirtualList entityNamesToIgnore __attribute__ ((unused)))
{
	ASSERT(entityNamesToIgnore, "PlatformerLevelState::getEntityNamesToIngnore: null entityNamesToIgnore");

	/*
	int i = 0;
	for(;this->currentStageEntryPoint->stageDefinition->entities[i].entityDefinition; i++)
	{
		if(ProgressManager_getCoinStatus(ProgressManager_getInstance(), this->currentStageEntryPoint->stageDefinition->entities[i].name))
		{
			VirtualList_pushBack(entityNamesToIgnore, this->stageDefinition->stageDefinition->entities[i].name);
		}
	}
	*/
}

// state's enter
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner)
{
	// call base
	GameState_enter(__SAFE_CAST(GameState, this), owner);

	// set the custom screen managers
	Screen_setScreenMovementManager(Screen_getInstance(), __SAFE_CAST(ScreenMovementManager, CustomScreenMovementManager_getInstance()));
	Screen_setScreenEffectManager(Screen_getInstance(), __SAFE_CAST(ScreenEffectManager, CustomScreenEffectManager_getInstance()));

	Game_disableKeypad(Game_getInstance());

    // get list of entities that should not be loaded
	VirtualList entityNamesToIgnore = __NEW(VirtualList);
	PlatformerLevelState_getEntityNamesToIngnore(this, entityNamesToIgnore);

	// check if destination entity name is given
	if(this->currentStageEntryPoint->destinationName)
	{
	    // iterate stage definition to find global position of destination entity
		VBVec3D environmentPosition = {0, 0, 0};
		VBVec3D* initialPosition = Entity_calculateGlobalPositionFromDefinitionByName(this->currentStageEntryPoint->stageDefinition->entities.children, environmentPosition, this->currentStageEntryPoint->destinationName);

		// if global position of destination entity could be found, move the hero and the screen there
        if(initialPosition)
        {
            // apply entry point offset
            initialPosition->x += this->currentStageEntryPoint->offset.x;
            initialPosition->y += this->currentStageEntryPoint->offset.y;
            initialPosition->z += this->currentStageEntryPoint->offset.z;

            // set world's limits
            Screen_setStageSize(Screen_getInstance(), this->currentStageEntryPoint->stageDefinition->level.size);

            // focus screen on new position
            VBVec3D screenPosition =
            {
                initialPosition->x - ITOFIX19_13(__SCREEN_WIDTH >> 1),
                initialPosition->y - ITOFIX19_13(__SCREEN_HEIGHT >> 1),
                initialPosition->z
            };

            Screen_setPosition(Screen_getInstance(), screenPosition);

    	    // load stage
    	    GameState_loadStage(__SAFE_CAST(GameState, this), this->currentStageEntryPoint->stageDefinition, entityNamesToIgnore, false);

            // get hero entity
            Container hero = Container_getChildByName(__SAFE_CAST(Container, this->stage), HERO_NAME, true);

			// if no hero could be found, create one. otherwise, move found hero.
            if(!hero)
            {
                PositionedEntity positionedEntity =
                {
                    &HERO_AC,
                    {
                        initialPosition->x,
                        initialPosition->y,
                        initialPosition->z
                    },
                    HERO_NAME,
                    NULL,
                    NULL,
                    false
                };

                hero = __SAFE_CAST(Container, Stage_addChildEntity(this->stage, &positionedEntity, true));

                // make sure that the streaming doesn't load the hero again
                Stage_registerEntityId(this->stage, Container_getId(hero), &HERO_AC);
            }
            else
            {
                Actor_setPosition(__SAFE_CAST(Actor, hero), initialPosition);
            }

            // make sure that fucusing gets completed inmediatly
            CustomScreenMovementManager_enable(CustomScreenMovementManager_getInstance());
            CustomScreenMovementManager_disableFocusEasing(CustomScreenMovementManager_getInstance());

            // update actor's global transformations
            GameState_transform(__SAFE_CAST(GameState, this));

            // set focus on the hero
            Screen_setFocusInGameEntity(Screen_getInstance(), __SAFE_CAST(InGameEntity, hero));
            VBVec3D screenDisplacement = {ITOFIX19_13(50), ITOFIX19_13(-30), 0};
            Screen_setFocusEntityPositionDisplacement(Screen_getInstance(), screenDisplacement);

            // apply changes to the visuals
            GameState_updateVisuals(__SAFE_CAST(GameState, this));
        }
	}
	else
	{
	    // load stage
	    GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&(this->currentStageEntryPoint->stageDefinition), entityNamesToIgnore, true);
	}

    CustomScreenMovementManager_disable(CustomScreenMovementManager_getInstance());

    // free some memory
	__DELETE(entityNamesToIgnore);

	// level is paused
	PlatformerLevelState_setModeToPaused(this);

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);

	// reset clocks
	GameState_startClocks(__SAFE_CAST(GameState, this));

    Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onHeroDied, kEventHeroDied);

    // TODO: attach enduring effects to stages instead of doing it the hacky way as below

    // activate pulsating effect in indoor stages
    if(this->currentStageEntryPoint->stageDefinition->rendering.colorConfig.brightnessRepeat != NULL)
    {
        Screen_startEffect(Screen_getInstance(), kScreenPulsate);
    }

    // activate post processing effect
//	Game_addPostProcessingEffect(Game_getInstance(), PostProcessingEffects_dwarfPlanet, NULL);
//	Game_addPostProcessingEffect(Game_getInstance(), PostProcessingEffects_tiltScreen, NULL);
//	Game_addPostProcessingEffect(Game_getInstance(), PostProcessingEffects_wobble, NULL);
//	Game_addPostProcessingEffect(Game_getInstance(), PostProcessingEffects_lightingTest, NULL);
}

// state's exit
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner)
{
    Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onHeroDied, kEventHeroDied);

	// call base
	GameState_exit(__SAFE_CAST(GameState, this), owner);
}

static void PlatformerLevelState_suspend(PlatformerLevelState this, void* owner)
{
	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), true);

#ifdef __DEBUG_TOOLS
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __ANIMATION_EDITOR
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif

	// make a fade out
    Screen_startEffect(Screen_getInstance(), kFadeOut, __FADE_DURATION);

	GameState_suspend(__SAFE_CAST(GameState, this), owner);
}

static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner)
{
	GameState_resume(__SAFE_CAST(GameState, this), owner);

#ifdef __DEBUG_TOOLS
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __ANIMATION_EDITOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif

	// tell any interested entity
	GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelResumed);

	// make a fade in
    Screen_startEffect(Screen_getInstance(), kFadeIn, __FADE_DURATION);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_EDITOR
	}
#endif

	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), false);

	PlatformerLevelState_setModeToPlaying(this);
}

// state's handle message
static bool PlatformerLevelState_processMessage(PlatformerLevelState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kLevelSetUp:
			{
				// print level name if at level start point
				if(PlatformerLevelState_isStartingLevel(this) && this->currentLevel->name)
	            {
				    const char* strLevelName = I18n_getText(I18n_getInstance(), (int)this->currentLevel->name);
	                Printing_text(Printing_getInstance(), "\"", 17, 6, "GUIFont");
	                Printing_text(Printing_getInstance(), strLevelName, 18, 6, "GUIFont");
	                Printing_text(Printing_getInstance(), "\"", 18 + strlen(strLevelName), 6, "GUIFont");

                    if(this->currentLevel->identifier)
                    {
                        const char* strLevel = I18n_getText(I18n_getInstance(), STR_LEVEL);
                        const char* strLevelName = this->currentLevel->identifier;
                        Printing_text(Printing_getInstance(), strLevel, 20, 5, NULL);
                        Printing_text(Printing_getInstance(), strLevelName, 21 + strlen(strLevel), 5, NULL);
                    }
	            }

				// tell any interested entity
				GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelSetUp);

				// show level after a little delay
				MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelStarted, NULL);

				this->mode = kShowingUp;
			}
			break;

		case kLevelStarted:

			// fade in screen
            Screen_startEffect(Screen_getInstance(),
                kFadeTo, // effect type
                0, // initial delay (in ms)
                NULL, // target brightness
                __FADE_DELAY, // delay between fading steps (in ms)
                (void (*)(Object, Object))PlatformerLevelState_onLevelStartedFadeInComplete, // callback function
                __SAFE_CAST(Object, this) // callback scope
            );

			break;

		case kHideLevelMessage:

			Printing_text(Printing_getInstance(), "                                                ", 0, 5, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 6, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 7, NULL);
			break;

		case kKeyPressed:

			if(kPlaying == this->mode)
            {
				u32 pressedKey = *((u32*)Telegram_getExtraInfo(telegram));

				if(K_SEL & pressedKey)
				{
    				// adjustment screen
	                PlatformerLevelState_setModeToPaused(this);
					SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, AdjustmentScreenState_getInstance()), NULL);
					Game_pause(Game_getInstance(), __SAFE_CAST(GameState, AdjustmentScreenState_getInstance()));
					break;
            	}
				else if(K_STA & pressedKey)
                {
                    // pause screen
					PlatformerLevelState_setModeToPaused(this);
                    Game_pause(Game_getInstance(), __SAFE_CAST(GameState, PauseScreenState_getInstance()));
                    break;
                }

				Object_fireEvent(__SAFE_CAST(Object, this), kEventKeyPressed);
			}
			return true;
			break;

		case kKeyReleased:

			if(kPlaying == this->mode)
            {
				Object_fireEvent(__SAFE_CAST(Object, this), kEventKeyReleased);
			}
			return true;
			break;

		case kKeyHold:

			if(kPlaying == this->mode)
            {
				Object_fireEvent(__SAFE_CAST(Object, this), kEventKeyHold);
			}
			return true;
			break;
	}

	return false;
}

void PlatformerLevelState_onScreenFocused(PlatformerLevelState this, Object eventFirer __attribute__ ((unused)))
{
    Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onScreenFocused, kEventScreenFocused);
    CustomScreenMovementManager_dontAlertWhenTargetFocused(CustomScreenMovementManager_getInstance());
    Game_enableKeypad(Game_getInstance());
}

void PlatformerLevelState_onHeroDied(PlatformerLevelState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	// unset the hero as focus entity from the custom screen movement manager
	Screen_setFocusInGameEntity(Screen_getInstance(), NULL);

    // start a fade out effect
    Brightness brightness = (Brightness){0, 0, 0};
    Screen_startEffect(Screen_getInstance(),
        kFadeTo, // effect type
        0, // initial delay (in ms)
        &brightness, // target brightness
        __FADE_DELAY, // delay between fading steps (in ms)
        (void (*)(Object, Object))PlatformerLevelState_onHeroDiedFadeOutComplete, // callback function
        __SAFE_CAST(Object, this) // callback scope
    );
}

// get current level's definition
PlatformerLevelDefinition* PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState this)
{
	return this->currentLevel;
}

// start a given level
void PlatformerLevelState_startLevel(PlatformerLevelState this, PlatformerLevelDefinition* platformerLevelDefinition)
{
	this->currentLevel = platformerLevelDefinition;
	this->currentStageEntryPoint = this->currentLevel->entryPoint;

    // announce level start
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventLevelStarted);

	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, this));
}

// start a given stage
void PlatformerLevelState_enterStage(PlatformerLevelState this, StageEntryPointDefinition* entryPointDefinition)
{
	this->currentStageEntryPoint = entryPointDefinition;

    // start a fade out effect
    Brightness brightness = (Brightness){0, 0, 0};
    Screen_startEffect(Screen_getInstance(),
        kFadeTo, // effect type
        0, // initial delay (in ms)
        &brightness, // target brightness
        __FADE_DELAY, // delay between fading steps (in ms)
        (void (*)(Object, Object))PlatformerLevelState_onEnterStageFadeOutComplete, // callback function
        __SAFE_CAST(Object, this) // callback scope
    );
}

// determine if starting a new level
bool PlatformerLevelState_isStartingLevel(PlatformerLevelState this)
{
	return (this->currentStageEntryPoint == this->currentLevel->entryPoint);
}

// set paused mode
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this)
{
	this->mode = kPaused;
}

// set kplaying mode
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this)
{
	this->mode = kPlaying;
}

// handle event
static void PlatformerLevelState_onLevelStartedFadeInComplete(PlatformerLevelState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PlatformerLevelState::onLevelStartedFadeInComplete: null this");

    // erase level message in n milliseconds
    MessageDispatcher_dispatchMessage(2000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kHideLevelMessage, NULL);

    // reset clock and restart
    //Clock_reset(this->inGameClock);

    // tell any interested entity
    GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelStarted);

    // restart clock
    // pause physical simulations
    //GameState_startInGameClock(__SAFE_CAST(GameState, this));

    PlatformerLevelState_setModeToPlaying(this);

    // enable focus easing
    Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)PlatformerLevelState_onScreenFocused, kEventScreenFocused);
    CustomScreenMovementManager_enableFocusEasing(CustomScreenMovementManager_getInstance());
    CustomScreenMovementManager_enable(CustomScreenMovementManager_getInstance());
    CustomScreenMovementManager_alertWhenTargetFocused(CustomScreenMovementManager_getInstance());
}

// handle event
static void PlatformerLevelState_onEnterStageFadeOutComplete(PlatformerLevelState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PlatformerLevelState::onEnterStageFadeOutComplete: null this");

	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, this));
}

// handle event
static void PlatformerLevelState_onHeroDiedFadeOutComplete(PlatformerLevelState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PlatformerLevelState::onEnterStageFadeOutComplete: null this");

	// go to overworld
    Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OverworldState_getInstance()));
}
