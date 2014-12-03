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
#include <Printing.h>

#include "SplashScreen.h"
#include <objects.h>
#include <macros.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

static void SplashScreen_destructor(SplashScreen this);

// class's constructor
static void SplashScreen_constructor(SplashScreen this);

// state's enter
static void SplashScreen_enter(SplashScreen this, void* owner);

// state's execute
static void SplashScreen_execute(SplashScreen this, void* owner);

// state's enter
static void SplashScreen_exit(SplashScreen this, void* owner);

// state's on message
static int SplashScreen_handleMessage(SplashScreen this, void* owner, Telegram telegram);

// load stage
static void SplashScreen_loadStage(SplashScreen this, StageDefinition* stageDefinition);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											DECLARATIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

extern const u16 ASCII_CH[];
extern State __CONCAT(START_LEVEL, _getInstance)();

enum Screens {
	kPvbScreen = 0,
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

#define SplashScreen_ATTRIBUTES			\
										\
	/* inherits */						\
	Level_ATTRIBUTES					\
										\
	/* screen */						\
	u8 currentScreen;					\


__CLASS_DEFINITION(SplashScreen);


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
__SINGLETON_DYNAMIC(SplashScreen);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
static void SplashScreen_constructor(SplashScreen this){
		
	__CONSTRUCT_BASE(Level);
	
	this->currentScreen = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
static void SplashScreen_destructor(SplashScreen this){
	
	// destroy base
	__SINGLETON_DESTROY(Level);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
static void SplashScreen_enter(SplashScreen this, void* owner){
	
	Printing_setAscii((const u16*)ASCII_CH);
	
	Level_loadStage((Level)this, (StageDefinition*)&PVB_ST, false, true);

	this->currentScreen = kPvbScreen;
	
	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
static void SplashScreen_execute(SplashScreen this, void* owner){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
static void SplashScreen_exit(SplashScreen this, void* owner){
	
	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
static int SplashScreen_handleMessage(SplashScreen this, void* owner, Telegram telegram){
	
	// process message
	switch(Telegram_getMessage(telegram)){
	
		case kKeyPressed:	

			switch(this->currentScreen){
			
				case kPvbScreen:

						SplashScreen_loadStage(this, (StageDefinition*)&PRECAUTION_ST);
						this->currentScreen = kPrecautionScreen;
						break;
						
				case kPrecautionScreen:

						SplashScreen_loadStage(this, (StageDefinition*)&VBJAE_ST);
						this->currentScreen = kVbJaeScreen;
						break;
						
				case kVbJaeScreen:
					
						this->currentScreen = kSplashExitScreen;
						Game_changeState(Game_getInstance(), (State)__CONCAT(START_LEVEL, _getInstance)());
						break;
			}

			break;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// load stage
static void SplashScreen_loadStage(SplashScreen this, StageDefinition* stageDefinition) {
	
	// make a fade out
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);
	
	// turn back the background
	VIP_REGS[BKCOL] = 0x00;

	Level_loadStage((Level)this, stageDefinition, false, true);

	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}