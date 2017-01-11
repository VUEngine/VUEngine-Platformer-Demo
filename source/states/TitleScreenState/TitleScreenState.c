/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>

#include <Game.h>
#include <Screen.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <I18n.h>
#include <Languages.h>
#include <PhysicalWorld.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include <macros.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <OptionsScreenState.h>
#include <CustomScreenMovementManager.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <OverworldState.h>
#include <KeyPadManager.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef TITLE_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void TitleScreenState_destructor(TitleScreenState this);
static void TitleScreenState_constructor(TitleScreenState this);
static void TitleScreenState_enter(TitleScreenState this, void* owner);
static void TitleScreenState_execute(TitleScreenState this, void* owner);
static void TitleScreenState_exit(TitleScreenState this, void* owner);
static void TitleScreenState_resume(TitleScreenState this, void* owner);
static void TitleScreenState_suspend(TitleScreenState this, void* owner);
static bool TitleScreenState_processMessage(TitleScreenState this, void* owner, Telegram telegram);
static void TitleScreenState_showMessage(TitleScreenState this);
static void TitleScreenState_hideMessage(TitleScreenState this);
static void TitleScreenState_onSecondChange(TitleScreenState this, Object eventFirer);
static void TitleScreenState_onFadeInComplete(TitleScreenState this, Object eventFirer);
static void TitleScreenState_onFadeOutComplete(TitleScreenState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(TitleScreenState, GameState);
__SINGLETON(TitleScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) TitleScreenState_constructor(TitleScreenState this)
{
	__CONSTRUCT_BASE(GameState);

	// init members
	this->mode = kTitleScreenModeShowPressStart;
	this->optionsSelector = NULL;
}

// class's destructor
static void TitleScreenState_destructor(TitleScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void TitleScreenState_enter(TitleScreenState this, void* owner)
{
	// reset mode
	this->mode = kTitleScreenModeShowPressStart;

	// add event listener for "press start" message
	Object_addEventListener(__SAFE_CAST(Object, Game_getUpdateClock(Game_getInstance())), __SAFE_CAST(Object, this), (EventListener)TitleScreenState_onSecondChange, kEventSecondChanged);

	// call base
	GameState_enter(__SAFE_CAST(GameState, this), owner);

    // disable user input
	Game_disableKeypad(Game_getInstance());

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&TITLE_SCREEN_STAGE_ST, NULL, true);

	// create and populate main menu
    VirtualList options = __NEW(VirtualList);
	if(ProgressManager_hasProgress(ProgressManager_getInstance()))
	{
        this->optionsSelector = __NEW(OptionsSelector, 3, 1, NULL);
        Option* option = NULL;

        option = __NEW_BASIC(Option);
        option->value = (char*)I18n_getText(I18n_getInstance(), STR_CONTINUE);
        option->type = kString;
        option->callback = NULL;
        option->callbackScope = NULL;
        VirtualList_pushBack(options, option);

        option = __NEW_BASIC(Option);
        option->value = (char*)I18n_getText(I18n_getInstance(), STR_OPTIONS);
        option->type = kString;
        option->callback = NULL;
        option->callbackScope = NULL;
        VirtualList_pushBack(options, option);

        option = __NEW_BASIC(Option);
        option->value = (char*)I18n_getText(I18n_getInstance(), STR_NEW_GAME);
        option->type = kString;
        option->callback = NULL;
        option->callbackScope = NULL;
        VirtualList_pushBack(options, option);

        Size strContinueSize = Printing_getTextSize(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_CONTINUE), NULL);
        Size strOptionsSize = Printing_getTextSize(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_OPTIONS), NULL);
        Size strNewGameSize = Printing_getTextSize(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_NEW_GAME), NULL);
        u8 width = (strContinueSize.x > strOptionsSize.x) ? strContinueSize.x : strOptionsSize.x;
        width = (width > strNewGameSize.x) ? width : strNewGameSize.x;
        OptionsSelector_setColumnWidth(this->optionsSelector, width + 1);
	}
	else
	{
        this->optionsSelector = __NEW(OptionsSelector, 2, 1, NULL);
        Option* option = NULL;

        option = __NEW_BASIC(Option);
        option->value = (char*)I18n_getText(I18n_getInstance(), STR_NEW_GAME);
        option->type = kString;
        option->callback = NULL;
        option->callbackScope = NULL;
        VirtualList_pushBack(options, option);

        option = __NEW_BASIC(Option);
        option->value = (char*)I18n_getText(I18n_getInstance(), STR_OPTIONS);
        option->type = kString;
        option->callback = NULL;
        option->callbackScope = NULL;
        VirtualList_pushBack(options, option);

        Size strOptionsSize = Printing_getTextSize(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_OPTIONS), NULL);
        Size strNewGameSize = Printing_getTextSize(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_NEW_GAME), NULL);
        u8 width = (strOptionsSize.x > strNewGameSize.x) ? strOptionsSize.x : strNewGameSize.x;
        OptionsSelector_setColumnWidth(this->optionsSelector, width + 1);
	}

    OptionsSelector_setOptions(this->optionsSelector, options);
	__DELETE(options);

	// make a little bit of physical simulations so each entity is placed at the floor
	GameState_startClocks(__SAFE_CAST(GameState, this));

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);
}

// state's execute
static void TitleScreenState_execute(TitleScreenState this, void* owner)
{
	// call base
	GameState_execute(__SAFE_CAST(GameState, this), owner);
}

// state's exit
static void TitleScreenState_exit(TitleScreenState this, void* owner)
{
	// call base
	GameState_exit(__SAFE_CAST(GameState, this), owner);
}

// state's resume
static void TitleScreenState_resume(TitleScreenState this, void* owner)
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

	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), false);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_EDITOR
	}
#endif
}

// state's suspend
static void TitleScreenState_suspend(TitleScreenState this, void* owner)
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

static void TitleScreenState_showMessage(TitleScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "TitleScreenState::showMessage: null this");

    const char* strPressStartButton = I18n_getText(I18n_getInstance(), STR_PRESS_START_BUTTON);
    Size strPressStartButtonSize = Printing_getTextSize(Printing_getInstance(), strPressStartButton, NULL);
    u8 strXPos = (__SCREEN_WIDTH >> 4) - (strPressStartButtonSize.x >> 1);
    Printing_text(Printing_getInstance(), strPressStartButton, strXPos, 26, NULL);
}

static void TitleScreenState_hideMessage(TitleScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "TitleScreenState::hideMessage: null this");

    Printing_text(Printing_getInstance(), "                                                ", 0, 25, NULL);
    Printing_text(Printing_getInstance(), "                                                ", 0, 26, NULL);
    Printing_text(Printing_getInstance(), "                                                ", 0, 27, NULL);
}

// state's handle message
static bool TitleScreenState_processMessage(TitleScreenState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kLevelSetUp:

			// tell any interested entity
			GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelSetUp);

			// show level after a little delay
			MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelStarted, NULL);
			break;

		case kLevelStarted:

			// fade in screen
            Screen_startEffect(Screen_getInstance(),
                kFadeTo, // effect type
                0, // initial delay (in ms)
                NULL, // target brightness
                __FADE_DELAY, // delay between fading steps (in ms)
                (void (*)(Object, Object))TitleScreenState_onFadeInComplete, // callback function
                __SAFE_CAST(Object, this) // callback scope
            );

			break;

		case kKeyPressed:
		{
			u32 pressedKey = *((u32*)Telegram_getExtraInfo(telegram));

			if((K_STA & pressedKey) || (K_A & pressedKey))
			{
				switch(this->mode)
				{
					case kTitleScreenModeShowPressStart:
					{
						// disable blinking "press start button"
						Object_removeEventListener(__SAFE_CAST(Object, Game_getUpdateClock(Game_getInstance())), __SAFE_CAST(Object, this), (void (*)(Object, Object))TitleScreenState_onSecondChange, kEventSecondChanged);
						TitleScreenState_hideMessage(this);

						// print options
						OptionsSelector_printOptions(
						    this->optionsSelector,
						    1 + (((__SCREEN_WIDTH >> 3) - OptionsSelector_getWidth(this->optionsSelector)) >> 1),
						    26
                        );

						// set mode to showing options
						this->mode = kTitleScreenModeShowOptions;

						break;
					}
					case kTitleScreenModeShowOptions:
					{
						int selectedOption = OptionsSelector_getSelectedOption(this->optionsSelector);

						switch(selectedOption)
						{
							case kTitleScreenOptionContinue:
							case kTitleScreenOptionOptions:

								// disable user input
								Game_disableKeypad(Game_getInstance());

								// fade out screen
								Brightness brightness = (Brightness){0, 0, 0};
								Screen_startEffect(Screen_getInstance(),
									kFadeTo, // effect type
									0, // initial delay (in ms)
									&brightness, // target brightness
									__FADE_DELAY, // delay between fading steps (in ms)
									(void (*)(Object, Object))TitleScreenState_onFadeOutComplete, // callback function
									__SAFE_CAST(Object, this) // callback scope
								);

								break;

							case kTitleScreenOptionNewGame:

								// remove main menu
								TitleScreenState_hideMessage(this);

								// set mode to new game confirm
								this->mode = kTitleScreenModeShowConfirmNewGame;

								// print warning
								const char* strNewGameConfirm = I18n_getText(I18n_getInstance(), STR_PROGRESS_WILL_BE_ERASED);
								Size strNewGameConfirmSize = Printing_getTextSize(Printing_getInstance(), strNewGameConfirm, NULL);
								u8 strNewGameConfirmXPos = (((__SCREEN_WIDTH >> 3) - strNewGameConfirmSize.x) >> 1);
								const char* strAreYouSure = I18n_getText(I18n_getInstance(), STR_ARE_YOU_SURE);
								Size strAreYouSureSize = Printing_getTextSize(Printing_getInstance(), strAreYouSure, NULL);
								u8 strAreYouSureXPos = (((__SCREEN_WIDTH >> 3) - strAreYouSureSize.x) >> 1);
								Printing_text(
									Printing_getInstance(),
									strNewGameConfirm,
									strNewGameConfirmXPos,
									25,
									NULL
								);
								Printing_text(
									Printing_getInstance(),
									strAreYouSure,
									strAreYouSureXPos,
									26,
									NULL
								);

								// print warning options
								const char* strYes = I18n_getText(I18n_getInstance(), STR_YES);
								Size strYesSize = Printing_getTextSize(Printing_getInstance(), strYes, NULL);
								const char* strNo = I18n_getText(I18n_getInstance(), STR_NO);
								Size strNoSize = Printing_getTextSize(Printing_getInstance(), strNo, NULL);

								u8 strYesXPos = ((__SCREEN_WIDTH >> 3) - (strYesSize.x + strNoSize.x + 3)) >> 1;
								u8 strNoXPos = strYesXPos + strYesSize.x + 2;

								Printing_text(Printing_getInstance(), __CHAR_A_BUTTON, strYesXPos - 1, 27, NULL);
								Printing_text(Printing_getInstance(), strYes, strYesXPos, 27, NULL);
								Printing_text(Printing_getInstance(), __CHAR_B_BUTTON, strNoXPos - 1, 27, NULL);
								Printing_text(Printing_getInstance(), strNo, strNoXPos, 27, NULL);

								break;
						}

						break;
					}
					case kTitleScreenModeShowConfirmNewGame:
					{
						// clear progress
						ProgressManager_clearProgress(ProgressManager_getInstance());

						// disable user input
						Game_disableKeypad(Game_getInstance());

						// fade out screen
						Brightness brightness = (Brightness){0, 0, 0};
						Screen_startEffect(Screen_getInstance(),
							kFadeTo, // effect type
							0, // initial delay (in ms)
							&brightness, // target brightness
							__FADE_DELAY, // delay between fading steps (in ms)
							(void (*)(Object, Object))TitleScreenState_onFadeOutComplete, // callback function
							__SAFE_CAST(Object, this) // callback scope
						);

						break;
					}
				}
			}
			else if((this->mode == kTitleScreenModeShowOptions) && ((pressedKey & K_LL) || (pressedKey & K_RL)))
			{
				OptionsSelector_selectPrevious(this->optionsSelector);
			}
			else if((this->mode == kTitleScreenModeShowOptions) && ((pressedKey & K_LR) || (pressedKey & K_RR)))
			{
				OptionsSelector_selectNext(this->optionsSelector);
			}
			else if((this->mode == kTitleScreenModeShowConfirmNewGame) && (pressedKey & K_B))
			{
				// remove message
				TitleScreenState_hideMessage(this);

				// print options
				OptionsSelector_setSelectedOption(this->optionsSelector, kTitleScreenOptionContinue);
                OptionsSelector_printOptions(
                    this->optionsSelector,
                    1 + (((__SCREEN_WIDTH >> 3) - OptionsSelector_getWidth(this->optionsSelector)) >> 1),
                    26
                );

				// set mode to showing options
				this->mode = kTitleScreenModeShowOptions;
			}

			break;
		}
	}

	return false;
}

// handle event
static void TitleScreenState_onSecondChange(TitleScreenState this, Object eventFirer __attribute__ ((unused)))
{
    if((Clock_getSeconds(Game_getUpdateClock(Game_getInstance())) % 2) == 0)
    {
        TitleScreenState_showMessage(this);
    }
    else
    {
        TitleScreenState_hideMessage(this);
    }
}

// handle event
static void TitleScreenState_onFadeInComplete(TitleScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "TitleScreenState::onFadeInComplete: null this");

    // tell any interested entity
    GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelStarted);

    // enable user input
    Game_enableKeypad(Game_getInstance());
}

// handle event
static void TitleScreenState_onFadeOutComplete(TitleScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "TitleScreenState::onFadeOutComplete: null this");


	int selectedOption = OptionsSelector_getSelectedOption(this->optionsSelector);

	switch(selectedOption)
	{
		case kTitleScreenOptionContinue:
		case kTitleScreenOptionNewGame:

			// switch to overworld
    		Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OverworldState_getInstance()));

			break;

		case kTitleScreenOptionOptions:

			// switch to options screen
			OptionsScreenState_setNextState(OptionsScreenState_getInstance(), __SAFE_CAST(GameState, this));
			Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OptionsScreenState_getInstance()));

			break;
	}
}
