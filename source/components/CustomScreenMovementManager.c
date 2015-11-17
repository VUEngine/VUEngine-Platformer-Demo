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

#include <CustomScreenMovementManager.h>
#include <Screen.h>
#include <MessageDispatcher.h>

//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------


// define the CustomScreenMovementManager
__CLASS_DEFINITION(CustomScreenMovementManager, ScreenMovementManager);

__CLASS_FRIEND_DEFINITION(Screen);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void CustomScreenMovementManager_constructor(CustomScreenMovementManager this);
static void CustomScreenMovementManager_FXShakeStart(CustomScreenMovementManager this, u16 duration);
static void CustomScreenMovementManager_FXShakeStop(CustomScreenMovementManager this);
static void CustomScreenMovementManager_onScreenShake(CustomScreenMovementManager this);


//---------------------------------------------------------------------------------------------------------
// 												GLOBALS
//---------------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(CustomScreenMovementManager);

// class's constructor
static void CustomScreenMovementManager_constructor(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE();
	
	this->tempFocusInGameEntity = NULL;

	this->lastShakeOffset.x = 0;
	this->lastShakeOffset.y = 0;
	this->lastShakeOffset.z = 0;
	
	this->shakeTimeLeft = 0;
}

// class's destructor
void CustomScreenMovementManager_destructor(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::destructor: null this");

	// destroy base
	__SINGLETON_DESTROY;
}

// center world's screen in function of focus actor's position
void CustomScreenMovementManager_positione(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving)
{
	ASSERT(this, "CustomScreenMovementManager::update: null this");

	Screen screen = Screen_getInstance();
	
	// if focusInGameEntity is defined
	if(screen && screen->focusInGameEntity)
	{
		Container focusInGameEntityParent = Container_getParent(__GET_CAST(Container, screen->focusInGameEntity));
		
		if(focusInGameEntityParent)
		{
			// transform focus entity
			Transformation environmentTransform = Container_getEnvironmentTransform(focusInGameEntityParent);

			// apply transformations
			__VIRTUAL_CALL(void, Container, transform, screen->focusInGameEntity, &environmentTransform);
	
			// get focusInGameEntity is moving
			if(__VIRTUAL_CALL(bool, InGameEntity, isMoving, screen->focusInGameEntity) || !checkIfFocusEntityIsMoving)
			{
				// save last position
				screen->lastDisplacement = screen->position;
	
				// get focusInGameEntity's position
				screen->position = *Entity_getPosition(__GET_CAST(Entity, screen->focusInGameEntity));
				
				screen->position.x += screen->focusEntityPositionDisplacement.x - ITOFIX19_13(__SCREEN_WIDTH >> 1);
				screen->position.y += screen->focusEntityPositionDisplacement.y - ITOFIX19_13(__SCREEN_HEIGHT >> 1);
				screen->position.z += screen->focusEntityPositionDisplacement.z - ITOFIX19_13(__SCREEN_DEPTH >> 1);
	
				if(0 > screen->position.x)
				{
					screen->position.x = 0;
				}
				else if(ITOFIX19_13(screen->stageSize.x) < screen->position.x + ITOFIX19_13(__SCREEN_WIDTH))
				{
					screen->position.x = ITOFIX19_13(screen->stageSize.x - __SCREEN_WIDTH);
				}
	
				if(0 > screen->position.y)
				{
					screen->position.y = 0;
				}
				else if(ITOFIX19_13(screen->stageSize.y) < screen->position.y + ITOFIX19_13(__SCREEN_HEIGHT))
				{
					screen->position.y = ITOFIX19_13(screen->stageSize.y - __SCREEN_HEIGHT);
				}
	
				screen->lastDisplacement.x = screen->position.x - screen->lastDisplacement.x;
				screen->lastDisplacement.y = screen->position.y - screen->lastDisplacement.y;
				screen->lastDisplacement.z = screen->position.z - screen->lastDisplacement.z;
			}
			else
			{
				// not moving
				screen->lastDisplacement.x = 0;
				screen->lastDisplacement.y = 0;
				screen->lastDisplacement.z = 0;
			}
		}
	}
}

void CustomScreenMovementManager_startEffect(CustomScreenMovementManager this, int effect, int duration)
{
	ASSERT(this, "CustomScreenMovementManager::startEffect: null this");
	
	switch(effect)
	{
		case kShake:
			
			CustomScreenMovementManager_FXShakeStart(this, duration);
			break;

		default:
			
			ScreenMovementManager_startEffect(__GET_CAST(ScreenMovementManager, this), effect, duration);
			break;
	}
}

void CustomScreenMovementManager_stopEffect(CustomScreenMovementManager this, int effect)
{
	ASSERT(this, "CustomScreenMovementManager::stopEffect: null this");

	switch(effect)
	{
		case kShake:
			
			CustomScreenMovementManager_FXShakeStop(this);
			break;

		default:
			
			ScreenMovementManager_stopEffect(__GET_CAST(ScreenMovementManager, this), effect);
			break;
	}
}

bool CustomScreenMovementManager_handleMessage(CustomScreenMovementManager this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kShake:
			
			CustomScreenMovementManager_onScreenShake(this);
            break;
	}

	return false;
}

// start shaking the screen
static void CustomScreenMovementManager_FXShakeStart(CustomScreenMovementManager this, u16 duration)
{
	ASSERT(this, "Screen::FXShakeStart: null this");

	// don't follow the focus entity while shaking
	Screen screen = Screen_getInstance();
    this->tempFocusInGameEntity = Screen_getFocusInGameEntity(screen);
	//Screen_unsetFocusInGameEntity(screen);

    // set desired fx duration
    this->shakeTimeLeft = duration;

    this->lastShakeOffset.x = ITOFIX19_13(2);

    // discard pending screen shake messages from previously started shake fx
    MessageDispatcher_discardDelayedMessages(MessageDispatcher_getInstance(), kShake);

    // instantly send shake message to self to start fx
    MessageDispatcher_dispatchMessage(0, __GET_CAST(Object, this), __GET_CAST(Object, this), kShake, NULL);
}

// stop shaking the screen
void CustomScreenMovementManager_FXShakeStop(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::FXShakeStop: null this");

    this->shakeTimeLeft = 0;
}

// shake the screen
static void CustomScreenMovementManager_onScreenShake(CustomScreenMovementManager this)
{
	ASSERT(this, "Screen::onScreenShake: null this");

	Screen screen = Screen_getInstance();
	
    // stop if no shaking time left
    if(this->shakeTimeLeft == 0)
    {
        // if needed, undo last offset
        if(this->lastShakeOffset.x != 0 || this->lastShakeOffset.y != 0)
        {
            //Screen_setFocusInGameEntity(screen, this->tempFocusInGameEntity);
            this->lastShakeOffset.x = 0;
            GameState_transform(__GET_CAST(GameState, Game_getCurrentState(Game_getInstance())));
        }

        return;
    }
    
	long seed = Utilities_randomSeed();

    u16 nextShakeDelay = MINIMUM_SHAKE_DELAY + Utilities_random(seed, abs(SHAKE_DELAY_DELTA));

    // substract time until next shake
    this->shakeTimeLeft = (this->shakeTimeLeft <= nextShakeDelay) ? 0 : this->shakeTimeLeft - nextShakeDelay;

    // new offset
    this->lastShakeOffset.x = -this->lastShakeOffset.x;

    // move screen a bit
    Screen_move(screen, this->lastShakeOffset, false);

    // apply screen offset
    GameState_transform(__GET_CAST(GameState, StateMachine_getCurrentState(Game_getStateMachine(Game_getInstance()))));

    // send message for next screen movement
	MessageDispatcher_dispatchMessage(nextShakeDelay, __GET_CAST(Object, this), __GET_CAST(Object, this), kShake, NULL);
}