/* VbJaEngine: bitmap graphics engine for the Nintendo Virtual Boy 
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

#include "TitleScreen.h"
#include <objects.h>
#include <macros.h>

#include "GameLevel.h"

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

static void TitleScreen_destructor(TitleScreen this);

// class's constructor
static void TitleScreen_constructor(TitleScreen this);

// state's enter
static void TitleScreen_enter(TitleScreen this, void* owner);

// state's execute
static void TitleScreen_execute(TitleScreen this, void* owner);

// state's enter
static void TitleScreen_exit(TitleScreen this, void* owner);

// state's execute
static void TitleScreen_pause(TitleScreen this, void* owner){}

// state's execute
static void TitleScreen_resume(TitleScreen this, void* owner){}

// state's on message
static int TitleScreen_handleMessage(TitleScreen this, void* owner, Telegram telegram);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											DECLARATIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(TitleScreen);


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
__SINGLETON_DYNAMIC(TitleScreen);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
static void TitleScreen_constructor(TitleScreen this){
		
	__CONSTRUCT_BASE(Level);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
static void TitleScreen_destructor(TitleScreen this){
	
	// destroy base
	__SINGLETON_DESTROY(Level);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
static void TitleScreen_enter(TitleScreen this, void* owner){
	
	Level_loadStage((Level)this, (StageDefinition*)&TITLE_ST, false);
	
	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
static void TitleScreen_execute(TitleScreen this, void* owner){
	
	// print clock if the second has changed
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
static void TitleScreen_exit(TitleScreen this, void* owner){
	
	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
static int TitleScreen_handleMessage(TitleScreen this, void* owner, Telegram telegram){

	// process message
	switch(Telegram_getMessage(telegram)){
	
		case kKeyPressed:	
		
			Game_changeState(Game_getInstance(), (State)GameLevel_getInstance());
			break;
	}

	return false;
}
