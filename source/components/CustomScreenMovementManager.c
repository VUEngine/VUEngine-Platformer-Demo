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
#include <Actor.h>
#include <PhysicalWorld.h>
#include <debugConfig.h>


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

static Screen _screen = NULL;


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
	
	this->positionFlag.x = 0;
	this->positionFlag.y = 0;
	this->positionFlag.z = 0;
	
	this->shakeTimeLeft = 0;
	this->previousTime = 0;
	
	_screen = Screen_getInstance();
	
	NM_ASSERT(_screen, "CustomScreenMovementManager::constructor: null _screen");
}

// class's destructor
void CustomScreenMovementManager_destructor(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::destructor: null this");

	// destroy base
	__SINGLETON_DESTROY;
}

// center world's _screen in function of focus actor's position
void CustomScreenMovementManager_position(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving)
{
	ASSERT(this, "CustomScreenMovementManager::update: null this");

	if(this->tempFocusInGameEntity)
	{
		return;
	}

	_screen->lastDisplacement.x = 0;
	_screen->lastDisplacement.y = 0;
	_screen->lastDisplacement.z = 0;

	fix19_13 elapsedTime = PhysicalWorld_getElapsedTime(Game_getPhysicalWorld(Game_getInstance()));

	// if focusInGameEntity is defined
	if(_screen->focusInGameEntity)
	{
		Direction direction = InGameEntity_getDirection(__SAFE_CAST(InGameEntity, _screen->focusInGameEntity));
		
		ASSERT(__SAFE_CAST(Actor, _screen->focusInGameEntity), "CustomScreenMovementManager::update: focus entity is not an actor");
		Velocity velocity = Actor_getVelocity(__SAFE_CAST(Actor, _screen->focusInGameEntity));
		
		VBVec3D screenPreviousPosition = _screen->position;

		const VBVec3D* focusInGameEntityPosition = Entity_getPosition(__SAFE_CAST(Entity, _screen->focusInGameEntity));

		{
			bool focusEntityOutOfBounds = focusInGameEntityPosition->x > _screen->position.x + ITOFIX19_13( __SCREEN_WIDTH - SCREEN_WIDTH_REDUCTION) || focusInGameEntityPosition->x < _screen->position.x + ITOFIX19_13(SCREEN_WIDTH_REDUCTION);
	
			if(this->positionFlag.x || focusEntityOutOfBounds)
			{
				// update vertical position
				const VBVec3D* focusInGameEntityPosition = __VIRTUAL_CALL(const VBVec3D*, SpatialObject, getPosition, _screen->focusInGameEntity);
	
				fix19_13 horizontalPosition = _screen->position.x;
				fix19_13 horizontalTarget = (focusInGameEntityPosition->x + _screen->focusEntityPositionDisplacement.x - ITOFIX19_13((__SCREEN_WIDTH / 2) - direction.x * SCREEN_HORIZONTAL_DISPLACEMENT));
				
				fix19_13 easingDisplacement = velocity.x? ITOFIX19_13(SCREEN_EASING_X_DISPLACEMENT): ITOFIX19_13(1);
				easingDisplacement = FIX19_13_MULT(easingDisplacement, elapsedTime);

				if(horizontalPosition + easingDisplacement < horizontalTarget)
				{
					_screen->position.x += easingDisplacement;
					
				}
				else if(horizontalPosition - easingDisplacement > horizontalTarget)
				{
					_screen->position.x -= easingDisplacement;
				}
				else
				{
					_screen->position.x = focusInGameEntityPosition->x + _screen->focusEntityPositionDisplacement.x - ITOFIX19_13((__SCREEN_WIDTH / 2) - direction.x * SCREEN_HORIZONTAL_DISPLACEMENT);
				}
				
				if(!this->tempFocusInGameEntity)
				{
					if(0 > _screen->position.x)
					{
						_screen->position.x = 0;
					}
					else if(ITOFIX19_13(_screen->stageSize.x) < _screen->position.x + ITOFIX19_13(__SCREEN_WIDTH))
					{
						_screen->position.x = ITOFIX19_13(_screen->stageSize.x - __SCREEN_WIDTH);
					}
				}
	
				_screen->lastDisplacement.x = (_screen->position.x - screenPreviousPosition.x);
			}
		}

		{
			// update vertical position
			fix19_13 verticalPosition = 0xFFFFE000 & _screen->position.y;
			fix19_13 verticalTarget = 0xFFFFE000 & (focusInGameEntityPosition->y + _screen->focusEntityPositionDisplacement.y - ITOFIX19_13(SCREEN_VERTICAL_DISPLACEMENT));

			bool focusEntityOutOfBounds = focusInGameEntityPosition->y > _screen->position.y + ITOFIX19_13( __SCREEN_HEIGHT - SCREEN_HEIGHT_REDUCTION) || focusInGameEntityPosition->y < _screen->position.y + ITOFIX19_13(SCREEN_HEIGHT_REDUCTION);

			if(this->positionFlag.y || focusEntityOutOfBounds)
			{
				fix19_13 downEasingDisplacement = ITOFIX19_13(1);
				fix19_13 upEasingDisplacement = ITOFIX19_13(1);

				if(velocity.y)
				{
					downEasingDisplacement = ITOFIX19_13(SCREEN_POSITIVE_EASING_Y_DISPLACEMENT);
					upEasingDisplacement = ITOFIX19_13(SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT);
				}

				downEasingDisplacement = FIX19_13_MULT(downEasingDisplacement, elapsedTime);
				upEasingDisplacement = FIX19_13_MULT(upEasingDisplacement, elapsedTime);

				if(verticalPosition + downEasingDisplacement < verticalTarget)
				{
					_screen->position.y += downEasingDisplacement;
				}
				else if(verticalPosition - upEasingDisplacement > verticalTarget)
				{
					_screen->position.y -= upEasingDisplacement;
				}
	
				if(!this->tempFocusInGameEntity)
				{
					if(0 > _screen->position.y)
					{
						_screen->position.y = 0;
					}
					else if(ITOFIX19_13(_screen->stageSize.y) < _screen->position.y + ITOFIX19_13(__SCREEN_HEIGHT))
					{
						_screen->position.y = ITOFIX19_13(_screen->stageSize.y - __SCREEN_HEIGHT);
					}
				}
				
				_screen->lastDisplacement.y = 0xFFFFE000 & (_screen->position.y - screenPreviousPosition.y);
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
			
			ScreenMovementManager_startEffect(__SAFE_CAST(ScreenMovementManager, this), effect, duration);
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
			
			ScreenMovementManager_stopEffect(__SAFE_CAST(ScreenMovementManager, this), effect);
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
	Screen _screen = Screen_getInstance();
    this->tempFocusInGameEntity = Screen_getFocusInGameEntity(_screen);
	//Screen_unsetFocusInGameEntity(_screen);

    // set desired fx duration
    this->shakeTimeLeft = duration;

    this->lastShakeOffset.x = ITOFIX19_13(4);

    // discard pending screen shake messages from previously started shake fx
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kShake);

    // instantly send shake message to self to start fx
    MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kShake, NULL);
}

// stop shaking the _screen
void CustomScreenMovementManager_FXShakeStop(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::FXShakeStop: null this");

    this->shakeTimeLeft = 0;
}

// shake the _screen
static void CustomScreenMovementManager_onScreenShake(CustomScreenMovementManager this)
{
	ASSERT(this, "Screen::onScreenShake: null this");

    // stop if no shaking time left
    if(this->shakeTimeLeft == 0)
    {
        // if needed, undo last offset
        if(this->lastShakeOffset.x != 0 || this->lastShakeOffset.y != 0)
        {
            this->tempFocusInGameEntity = NULL;

            //Screen_setFocusInGameEntity(_screen, this->tempFocusInGameEntity);
            this->lastShakeOffset.x = 0;
        }

        return;
    }
    
	long seed = Utilities_randomSeed();

    int nextShakeDelay = MINIMUM_SHAKE_DELAY + Utilities_random(seed, abs(SHAKE_DELAY_DELTA));

    // subtract time until next shake
    this->shakeTimeLeft = (this->shakeTimeLeft <= nextShakeDelay) ? 0 : this->shakeTimeLeft - nextShakeDelay;

    // new offset
    this->lastShakeOffset.x = -this->lastShakeOffset.x;

    // move screen a bit
    Screen_move(_screen, this->lastShakeOffset, false);

    // send message for next screen movement
	MessageDispatcher_dispatchMessage(nextShakeDelay, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kShake, NULL);
}

void CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager this, VBVec3DFlag positionFlag)
{
	ASSERT(this, "CustomScreenMovementManager::setPositionFlag: null this");

	this->positionFlag = positionFlag;
}

VBVec3DFlag CustomScreenMovementManager_getPositionFlag(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::getPositionFlag: null this");

	return this->positionFlag;
}
