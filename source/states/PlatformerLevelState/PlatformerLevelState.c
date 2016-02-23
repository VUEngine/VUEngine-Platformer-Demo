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
#include <Game.h>
#include <Screen.h>
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
#include <EventManager.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PlatformerLevelState_constructor(PlatformerLevelState this);
static void PlatformerLevelState_destructor(PlatformerLevelState this);
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_suspend(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner);
static bool PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram);
static void PlatformerLevelState_getEntityNamesToIngnore(PlatformerLevelState this, VirtualList entityNamesToIgnore);
bool PlatformerLevelState_isStartingLevel(PlatformerLevelState this);
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this);
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this);

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
static void PlatformerLevelState_constructor(PlatformerLevelState this)
{
	__CONSTRUCT_BASE();

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

static void PlatformerLevelState_getEntityNamesToIngnore(PlatformerLevelState this, VirtualList entityNamesToIgnore)
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

void PlatformerLevelState_testPostProcessingEffect(u32 frameBufferSetToModify)
{
    int size = 192;
    int xCounter = size;
    int yCounter = size;
    int x = __SCREEN_WIDTH / 2 - xCounter / 2;
    int y = __SCREEN_HEIGHT / 2 - yCounter / 2;

    if(0 == frameBufferSetToModify || 0x8000 == frameBufferSetToModify)
    {
        u32 buffer = 0;
        for(;buffer < 2; buffer++)
        {
            for(yCounter = 56, y = __SCREEN_HEIGHT / 2 - yCounter / 2; yCounter >= 0; yCounter -= 4, y += 4)
            {
                for(xCounter = 192, x = __SCREEN_WIDTH / 2 - xCounter / 2; xCounter--; x++)
                {
                    BYTE* sourcePointer = (BYTE*) (frameBufferSetToModify | (buffer? 0x00010000: 0 ));
                    sourcePointer += ((x << 6) + (y >> 2));
                    *sourcePointer = (*sourcePointer & 0x03)| (*sourcePointer << 2);
                }

            }
        }
    }
}

// state's enter
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner)
{
	// call base
	GameState_enter(__SAFE_CAST(GameState, this), owner);

	// set the custom movement screen manager now
	Screen_setScreenMovementManager(Screen_getInstance(), __SAFE_CAST(ScreenMovementManager, CustomScreenMovementManager_getInstance()));

	Game_disableKeypad(Game_getInstance());

	// reset progress manager if this is a level start entry point
	if(PlatformerLevelState_isStartingLevel(this))
	{
		ProgressManager_reset(ProgressManager_getInstance());
	}

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

                hero = __SAFE_CAST(Container, Stage_addPositionedEntity(this->stage, &positionedEntity, true));

                // make sure that the streaming doesn't load the hero again
                Stage_registerEntityId(this->stage, Container_getId(hero), &HERO_AC);
            }
            else
            {
                Actor_setPosition(__SAFE_CAST(Actor, hero), initialPosition);
            }
        }
	}
	else
	{
	    // load stage
	    GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&(this->currentStageEntryPoint->stageDefinition), entityNamesToIgnore, true);
	}

    // free some memory
	__DELETE(entityNamesToIgnore);

	// level is paused
	PlatformerLevelState_setModeToPaused(this);

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);

	// reset clocks
	GameState_startClocks(__SAFE_CAST(GameState, this));

	Game_addPostProcessingEffect(Game_getInstance(), PlatformerLevelState_testPostProcessingEffect);
}

// state's exit
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner)
{
	// make a fade out
	Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);

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
    Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);

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
    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);

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
static bool PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kLevelSetUp:
			{
				// print level name if at level start point
				if(PlatformerLevelState_isStartingLevel(this) && this->currentLevel->name)
	            {
				    char* strLevelName = I18n_getText(I18n_getInstance(), (int)this->currentLevel->name);
	                Printing_text(Printing_getInstance(), "\"", 17, 6, "GUIFont");
	                Printing_text(Printing_getInstance(), strLevelName, 18, 6, "GUIFont");
	                Printing_text(Printing_getInstance(), "\"", 18 + strlen(strLevelName), 6, "GUIFont");

                    if(this->currentLevel->identifier)
                    {
                        char* strLevel = I18n_getText(I18n_getInstance(), STR_LEVEL);
                        char* strLevelName = this->currentLevel->identifier;
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

			// fade in
		    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);

			// erase level message in n milliseconds
            MessageDispatcher_dispatchMessage(2000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kHideLevelMessage, NULL);

			// reset clock and restart
			Clock_reset(this->inGameClock);

			// tell any interested entity
			GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelStarted);

			// restart clock
			// pause physical simulations
			GameState_startInGameClock(__SAFE_CAST(GameState, this));

        	PlatformerLevelState_setModeToPlaying(this);

        	Game_enableKeypad(Game_getInstance());

			break;

		case kHideLevelMessage:

			Printing_text(Printing_getInstance(), "                                                ", 0, 5, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 6, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 7, NULL);
			break;

		case kKeyPressed:

			if(kPlaying == this->mode)
            {
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

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

				Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_KEY_PRESSED);
			}
			return true;
			break;

		case kKeyReleased:

			if(kPlaying == this->mode)
            {
				Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_KEY_RELEASED);
			}
			return true;
			break;

		case kKeyHold:

			if(kPlaying == this->mode)
            {
				Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_KEY_HOLD);
			}
			return true;
			break;

		case kHeroDied:

			Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OverworldState_getInstance()));
			return true;
			break;
	}

	return false;
}

// get current level's definition
PlatformerLevelDefinition* PlatformerLevelState_getLevel(PlatformerLevelState this)
{
	return this->currentLevel;
}

// start a given level
void PlatformerLevelState_startLevel(PlatformerLevelState this, PlatformerLevelDefinition* platformerLevelDefinition)
{
	this->currentLevel = platformerLevelDefinition;
	this->currentStageEntryPoint = this->currentLevel->entryPoint;
}

// start a given stage
void PlatformerLevelState_enterStage(PlatformerLevelState this, StageEntryPointDefinition* entryPointDefinition)
{
	this->currentStageEntryPoint = entryPointDefinition;

	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, this));
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
