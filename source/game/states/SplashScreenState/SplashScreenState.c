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
#include <Screen.h>
#include <I18n.h>
#include <Printing.h>

#include "SplashScreenState.h"
#include <objects.h>
#include <macros.h>
#include <text.h>
#include "stages.h"
#include "TitleScreenState.h"


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

static void SplashScreenState_destructor(SplashScreenState this);

// class's constructor
static void SplashScreenState_constructor(SplashScreenState this);

// state's enter
static void SplashScreenState_enter(SplashScreenState this, void* owner);

// state's execute
static void SplashScreenState_execute(SplashScreenState this, void* owner);

// state's enter
static void SplashScreenState_exit(SplashScreenState this, void* owner);

// state's on message
static int SplashScreenState_handleMessage(SplashScreenState this, void* owner, Telegram telegram);

// load stage
static void SplashScreenState_loadStage(SplashScreenState this, StageDefinition* stageDefinition);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											DECLARATIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

extern const u16 FontTiles[];

enum Screens {
	kAdjustmentScreen = 0,
	kPrecautionScreen,
	kVbJaeScreen,
	kSplashExitScreen
};

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#define SplashScreenState_ATTRIBUTES											\
																				\
	/* inherits */																\
	GameState_ATTRIBUTES														\
																				\
	/* screen */																\
	u8 currentScreen;															\

__CLASS_DEFINITION(SplashScreenState);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// it's a singleton
__SINGLETON_DYNAMIC(SplashScreenState);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
static void SplashScreenState_constructor(SplashScreenState this){
		
	__CONSTRUCT_BASE(GameState);
	
	this->currentScreen = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
static void SplashScreenState_destructor(SplashScreenState this){
	
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
static void SplashScreenState_enter(SplashScreenState this, void* owner){
	
	Printing_setFontDefinition((const u16*)FontTiles);
	
	GameState_loadStage((GameState)this, (StageDefinition*)&ADJUSTMENT_ST, false, true);

	this->currentScreen = kAdjustmentScreen;
	
	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
static void SplashScreenState_execute(SplashScreenState this, void* owner){

	if (this->currentScreen == kVbJaeScreen) {
	
		VBVec3D translation = {
			ITOFIX19_13(1),
			ITOFIX19_13(0), 
			ITOFIX19_13(0)
		};

		Screen_move(Screen_getInstance(), translation, false);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
static void SplashScreenState_exit(SplashScreenState this, void* owner){
	
	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
static int SplashScreenState_handleMessage(SplashScreenState this, void* owner, Telegram telegram){
	
	// process message
	switch(Telegram_getMessage(telegram)){
	
		case kKeyPressed:	

			switch(this->currentScreen){
			
				case kAdjustmentScreen:

					SplashScreenState_loadStage(this, (StageDefinition*)&PRECAUTION_ST);
					Printing_text(I18n_getText(I18n_getInstance(), STR_PRECAUTION), 8, 6);
					this->currentScreen = kPrecautionScreen;
					break;
						
				case kPrecautionScreen:

					SplashScreenState_loadStage(this, (StageDefinition*)&VBJAE_ST);
					this->currentScreen = kVbJaeScreen;
					break;
						
				case kVbJaeScreen:
				
					this->currentScreen = kSplashExitScreen;
					Game_changeState(Game_getInstance(), (State)TitleScreenState_getInstance());
					break;
			}

			break;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// load stage
static void SplashScreenState_loadStage(SplashScreenState this, StageDefinition* stageDefinition) {
	
	// make a fade out
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);
	
	// turn back the background
	VIP_REGS[BKCOL] = 0x00;

	GameState_loadStage((GameState)this, stageDefinition, false, true);

	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}