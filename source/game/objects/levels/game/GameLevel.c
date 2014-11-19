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
#include <MessageDispatcher.h>
#include <PhysicalWorld.h>


#include <GameLevel.h>
#include <TitleScreen.h>
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

static void GameLevel_destructor(GameLevel this);

// class's constructor
static void GameLevel_constructor(GameLevel this);

// state's enter
static void GameLevel_enter(GameLevel this, void* owner);

// state's execute
static void GameLevel_execute(GameLevel this, void* owner);

// state's enter
static void GameLevel_exit(GameLevel this, void* owner);

// state's execute
static void GameLevel_pause(GameLevel this, void* owner){}

// state's execute
static void GameLevel_resume(GameLevel this, void* owner){}

// state's on message
static int GameLevel_handleMessage(GameLevel this, void* owner, Telegram telegram);

// move view point
//static void GameLevel_movePerspective(GameLevel this);

extern const u16 ASCII_CH[];

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(GameLevel);


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
__SINGLETON_DYNAMIC(GameLevel);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
static void GameLevel_constructor(GameLevel this){
		
	__CONSTRUCT_BASE(Level);
	
	this->marioIsDead = false;
	
	this->levelCleared = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
static void GameLevel_destructor(GameLevel this){
	
	// destroy base
	__SINGLETON_DESTROY(Level);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
static void GameLevel_enter(GameLevel this, void* owner){
	
	Optical optical = Game_getOptical(Game_getInstance());
	optical.verticalViewPointCenter = ITOFIX19_13(112 + 112/2);
	Game_setOptical(Game_getInstance(), optical);

	//load stage
	Level_loadStage((Level)this, (StageDefinition*)&LEVEL_0_0_0_ST, true, true);

	// mario is alive!
	this->marioIsDead = false;
	
	// the level is not cleared yet
	this->levelCleared = false;
	
	// playing by default
	this->mode = kPaused;
	
	// show up level after a little bit
	MessageDispatcher_dispatchMessage(500, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
static void GameLevel_execute(GameLevel this, void* owner){
	
	// print clock if the second has changed
	static int previousSecond = 0;	
	int currentSecond = Clock_getSeconds(Game_getInGameClock(Game_getInstance()));
	
	if(currentSecond != previousSecond){
		
		currentSecond = previousSecond;
		
		Printing_text("Time ", 37, 0);

		Clock_print(Game_getInGameClock(Game_getInstance()), 42, 0);
	}


	// call base
	Level_execute((Level)this, owner);
/*
	// if mario is dead
	if(this->marioIsDead){
		
		// force exit and enter to next state
		Game_changeState(Game_getInstance(), (Level)TitleScreen_getInstance());
			
		return;
	}

	// if mario is dead
	if(this->levelCleared){
		
		// force exit and enter to next state
		Game_changeState(Game_getInstance(), (Level)VbJaeScreen_getInstance());

		return;
	}

#ifdef __DEBUG
	if(kPlaying == this->mode){
#endif	
		// center the screen
		Stage_centerScreen(this->stage);

#ifdef __DEBUG		
	}
#endif
*/

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
static void GameLevel_exit(GameLevel this, void* owner){
	
	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
static int GameLevel_handleMessage(GameLevel this, void* owner, Telegram telegram){

	// process message
	switch(Telegram_getMessage(telegram)){

		case kSetUpLevel:
		
			Printing_text("Time ", 37, 0);
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			Clock_print(Game_getInGameClock(Game_getInstance()), 42, 0);
			Clock_start(Game_getInGameClock(Game_getInstance()));
	
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			MessageDispatcher_dispatchMessage(1000, (Object)this, (Object)Game_getInstance(), kShowUpLevel, NULL);

			this->mode = kSettingUp;
			break;	

		case kShowUpLevel:

			Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
			Printing_text("GET READY", 21, 6);
			Clock_stop(Game_getInGameClock(Game_getInstance()));
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			Clock_print(Game_getInGameClock(Game_getInstance()), 42, 0);
			
			MessageDispatcher_dispatchMessage(1500, (Object)this, (Object)Game_getInstance(), kStartLevel, NULL);

			this->mode = kShowingUp;
			break;
			
		case kStartLevel:

			Printing_text("    GO!        ", 21, 6);
			
			MessageDispatcher_dispatchMessage(1000, (Object)this, (Object)Game_getInstance(), kHideStartUpMessage, NULL);
			Clock_start(Game_getInGameClock(Game_getInstance()));

			this->mode = kPlaying;
			break;

		case kHideStartUpMessage:
			
			Printing_text("               ", 21, 6);
			break;
			
		case kKeyPressed:	
			
			// update level's stage
			if(kPlaying == this->mode){
				
				return Level_handleMessage((Level)this, owner, telegram);
			}
			
			//if start button pressed
			/*
			if(vbNewKeyPressed(K_STA)){
				
				if(kPaused == this->mode){					
					
					this->mode = kPlaying;
					Printing_text("     ", 22, 13);
					Clock_pause(Game_getInGameClock(Game_getInstance()), false);
					
					VIP_REGS[GPLT0] = __GPLT0VALUE;	
					VIP_REGS[GPLT1] = __GPLT1VALUE;	
					VIP_REGS[GPLT2] = __GPLT2VALUE;
					VIP_REGS[GPLT3] = __GPLT3VALUE;
					
				}
				else{
					
					Printing_text("                  ", 0, 0);
					this->mode = kPaused;
					Printing_text("Pause", 22, 13);
					Clock_pause(Game_getInGameClock(Game_getInstance()), true);
					
					VIP_REGS[GPLT0] = 0xA0;
					VIP_REGS[GPLT1] = 0x90;
					
				}
				return true;
			}
			*/

			if(kPaused == this->mode){
				
				return true;
			}
			
/*
#ifdef __DEBUG
			//if select button pressed
			if(vbNewKeyPressed(K_SEL)){
				this->mode++;
				if(this->mode > GAMEWORLD_MODES - 1){
					this->mode = 1;
				}
				
				if(kMovingScreen == this->mode){
					
					this->lastTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
					Printing_text("Moving screen     ", 0, 0);
				}
				
				if(kMovingPerspective == this->mode){
					
					this->lastTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
					Printing_text("Moving perspective", 0, 0);
				}
				
				if(kPlaying == this->mode){
					
					this->lastTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
					Printing_text("                  ", 0, 0);
				}				
			}
			
			if(kMovingScreen == this->mode){
				
				if((K_LU | K_LD | K_LL | K_LR) & vbKeyPressed()){

					GameLevel_moveScreen(this);

				}
			}
			
			if(kMovingPerspective == this->mode){
				
				if(vbKeyPressed()){

					//GameLevel_movePerspective(this);
				}
			}			
#endif 
*/
			break;
			
		case kKeyUp:
		case kKeyHold:
			
			return Level_handleMessage((Level)this, owner, telegram);
			break;

		case kHeroDied:	
			
			Game_changeState(Game_getInstance(), (State)TitleScreen_getInstance());
			return true;
			break;			
	}

	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mario is dead
void GameLevel_marioIsDead(GameLevel this){

	// now he's dead
	this->marioIsDead = true;
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// level completed
void GameLevel_levelCleared(GameLevel this){

	// now he's dead
	this->levelCleared = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// move the screen
void GameLevel_moveScreen(GameLevel this){
/*
	
	u32 currentTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
	int displacement = 200 * (currentTime - this->lastTime) / 1000;
	displacement = 50;

	if(currentTime - this->lastTime > 200){
		
		this->lastTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));;
		displacement = 4;
	}
	this->lastTime = currentTime;
	
	displacement = ITOFIX19_13(displacement);
	displacement = ITOFIX19_13(50);
	
	
	if(vbKeyPressed() & K_LL){
		
		if(_screenPosition->x - displacement > 0){
			
			_screenPosition->x -= displacement;
			
			_screenMovementState->x = __ACTIVE;
		}
	}
	
	if(vbKeyPressed() & K_LR){
		
		//if(_screenPosition.x > displacement > 0){
			
			_screenPosition->x += displacement;
			
			_screenMovementState->x = __ACTIVE;
			
		//}
	}
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// move view point
/*
static void GameLevel_movePerspective(GameLevel this){

	switch(vbKeyPressed()){
	
		case K_LL:
			
			if(optical.horizontalViewPointCenter > 0){
				
				optical.horizontalViewPointCenter--;
			}
			else{
				optical.horizontalViewPointCenter=0;
			}
			
			break;
			
		case K_LR:
			
			if(optical.horizontalViewPointCenter < 384){
				
				optical.horizontalViewPointCenter++;
			}
			else{
				optical.horizontalViewPointCenter=384;
			}

			break;
			
		case K_LU:
			
			if(optical.verticalViewPointCenter > 0){
				
				optical.verticalViewPointCenter--;
			}
			else{
				optical.verticalViewPointCenter=0;
			}

			break;
			
		case K_LD:
			
			if(optical.verticalViewPointCenter < 224){
				
				optical.verticalViewPointCenter++;
			}
			else{
				optical.verticalViewPointCenter=224;
			}

			break;
			
		case K_RL:
			
			if(optical.baseDistance > 10){
				
				optical.baseDistance -=10;
			}
			else{
				optical.baseDistance = 1;
			}
	
			break;
			
		case K_RR:
			
			if(optical.baseDistance < __BASE_FACTOR +__BASE_FACTOR/2){
				
				optical.baseDistance += 10;
			}
			else{
				optical.baseDistance=__BASE_FACTOR+__BASE_FACTOR/2;
			}
	
			break;

			
		case K_RU:
			
			if(optical.maximunViewDistance > __MAXVIEWDISTANCE/2){
				
				optical.maximunViewDistance--;
			}
			else{
				
				optical.maximunViewDistance =__MAXVIEWDISTANCE/2;
			}

			
			break;
			
		case K_RD:
			
			if(optical.maximunViewDistance < __MAXVIEWDISTANCE+__MAXVIEWDISTANCE/2){
				
				optical.maximunViewDistance++;
			}
			else{
				optical.maximunViewDistance = __MAXVIEWDISTANCE+__MAXVIEWDISTANCE/2;
			}

			break;
			
		//}
		
	
	//_screenMovementState->x = _screenMovementState->y = _screenMovementState->z = __ACTIVE; 

}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get working mode
int GameLevel_getMode(GameLevel this){
	
	return this->mode;
}
