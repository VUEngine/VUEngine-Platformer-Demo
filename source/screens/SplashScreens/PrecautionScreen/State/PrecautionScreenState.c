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

#include <macros.h>
#include <Game.h>
#include <Screen.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <I18n.h>
#include <SoundManager.h>
#include <PrecautionScreenState.h>
#include <AdjustmentScreenState.h>
#include <Utilities.h>
#include <Languages.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_ST;
extern const u16 COLLECT_SND[];


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PrecautionScreenState_destructor(PrecautionScreenState this);
static void PrecautionScreenState_constructor(PrecautionScreenState this);
static void PrecautionScreenState_print(PrecautionScreenState this);
static bool PrecautionScreenState_processMessage(PrecautionScreenState this, void* owner __attribute__ ((unused)), Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PrecautionScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(PrecautionScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) PrecautionScreenState_constructor(PrecautionScreenState this)
{
	__CONSTRUCT_BASE(SplashScreenState);

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, this), __SAFE_CAST(GameState, AdjustmentScreenState_getInstance()));
	this->stageDefinition = (StageDefinition*)&EMPTY_ST;
}

// class's destructor
static void PrecautionScreenState_destructor(PrecautionScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's handle message
static bool PrecautionScreenState_processMessage(PrecautionScreenState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kScreenStarted:
			{
	            // play start-up sound
	            VBVec3D position = {0, 0, 0};
				SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, position);

	            // wait some seconds for the screen to stabilize, as defined by Nintendo in the official development manual
	            Game_wait(Game_getInstance(), 3000);

				// start fade in effect
				Screen_startEffect(Screen_getInstance(),
				    kFadeTo, // effect type
				    0, // initial delay (in ms)
				    NULL, // target brightness
				    __FADE_DELAY, // delay between fading steps (in ms)
				    NULL, // callback function
				    NULL // callback scope
				);

	            // show this screen for at least 2 seconds, as defined by Nintendo in the official development manual (Appendix 1)
	            MessageDispatcher_dispatchMessage(2000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kScreenAllowUserInput, NULL);
            }
			break;

		case kScreenAllowUserInput:
			{
                Game_enableKeypad(Game_getInstance());
            }
			break;

		case kKeyPressed:
		    {
                u32 pressedKey = *((u32*)Telegram_getExtraInfo(telegram));

                if(pressedKey & ~K_PWR)
                {
                    __VIRTUAL_CALL(SplashScreenState, processInput, this, pressedKey);
                }
            }
            break;
	}

	return false;
}

static void PrecautionScreenState_print(PrecautionScreenState this __attribute__ ((unused)))
{
    const char* strPrecautionTitle = I18n_getText(I18n_getInstance(), STR_IMPORTANT);
    const char* strPrecautionTitleFont = "LargeFont";
    Size titleSize = Printing_getTextSize(Printing_getInstance(), strPrecautionTitle, strPrecautionTitleFont);

    const char* strPrecautionText = I18n_getText(I18n_getInstance(), STR_PRECAUTION_SCREEN_TEXT);
    Size textSize = Printing_getTextSize(Printing_getInstance(), strPrecautionText, NULL);

    u8 totalHeight = titleSize.y + textSize.y;

    Printing_text(
        Printing_getInstance(),
        Utilities_toUppercase(strPrecautionTitle),
        (__SCREEN_WIDTH >> 4) - (titleSize.x >> 1),
        (__SCREEN_HEIGHT >> 4) - (totalHeight >> 1) - 1,
        strPrecautionTitleFont
    );

    Printing_text(
        Printing_getInstance(),
        strPrecautionText,
        (__SCREEN_WIDTH >> 4) - (textSize.x >> 1),
        (__SCREEN_HEIGHT >> 4) - (totalHeight >> 1) + titleSize.y,
        NULL
    );
}
