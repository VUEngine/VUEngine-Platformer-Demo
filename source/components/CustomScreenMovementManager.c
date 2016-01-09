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
// 											CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------

#define __SCREEN_EASING_X_DISPLACEMENT					3
#define __SCREEN_POSITIVE_EASING_Y_DISPLACEMENT			8
#define __SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT			3
#define __SCREEN_EASING_Y_DISPLACEMENT					3
#define __SCREEN_HORIZONTAL_DISPLACEMENT 				30
#define __SCREEN_VERTICAL_DISPLACEMENT 					(__SCREEN_HEIGHT / 2) + 30


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
	this->transformationBaseEntity = NULL;

	this->lastShakeOffset.x = 0;
	this->lastShakeOffset.y = 0;
	this->lastShakeOffset.z = 0;
	
	this->positionFlag.x = 0;
	this->positionFlag.y = 0;
	this->positionFlag.z = 0;
	
	this->shakeTimeLeft = 0;
	
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

	// if focusInGameEntity is defined
	if(_screen->focusInGameEntity && this->transformationBaseEntity)
	{
		Container transformationBaseEntityParent = Container_getParent(__SAFE_CAST(Container, this->transformationBaseEntity));
		
		if(transformationBaseEntityParent)
		{
			// transform focus entity
			Transformation environmentTransform = Container_getEnvironmentTransform(transformationBaseEntityParent);

			// apply transformations
			__VIRTUAL_CALL(void, Container, transform, this->transformationBaseEntity, &environmentTransform);
	
			Direction direction = InGameEntity_getDirection(__SAFE_CAST(InGameEntity, this->transformationBaseEntity));
			
			VBVec3D screenPreviousPosition = _screen->position;
			
			if(this->positionFlag.x)
			{
				// update vertical position
				const VBVec3D* focusInGameEntityPosition = Entity_getPosition(__SAFE_CAST(Entity, _screen->focusInGameEntity));

				fix19_13 horizontalPosition = 0xFFFFE000 & _screen->position.x;
				fix19_13 horizontalTarget = 0xFFFFE000 & (focusInGameEntityPosition->x + _screen->focusEntityPositionDisplacement.x - ITOFIX19_13((__SCREEN_WIDTH / 2) - direction.x * __SCREEN_HORIZONTAL_DISPLACEMENT));
				
				if(horizontalPosition + ITOFIX19_13(__SCREEN_EASING_X_DISPLACEMENT) < horizontalTarget)
				{
					_screen->position.x += ITOFIX19_13(__SCREEN_EASING_X_DISPLACEMENT);
				}
				else if(horizontalPosition - ITOFIX19_13(__SCREEN_EASING_X_DISPLACEMENT) > horizontalTarget)
				{
					_screen->position.x -= ITOFIX19_13(__SCREEN_EASING_X_DISPLACEMENT);
				}
				else
				{
					_screen->position.x = focusInGameEntityPosition->x + _screen->focusEntityPositionDisplacement.x - ITOFIX19_13((__SCREEN_WIDTH / 2) - direction.x * __SCREEN_HORIZONTAL_DISPLACEMENT);
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
			
			if(this->positionFlag.y)
			{
				// update vertical position
				const VBVec3D* focusInGameEntityPosition = Entity_getPosition(__SAFE_CAST(Entity, _screen->focusInGameEntity));
				fix19_13 verticalPosition = 0xFFFFE000 & _screen->position.y;
				fix19_13 verticalTarget = 0xFFFFE000 & (focusInGameEntityPosition->y + _screen->focusEntityPositionDisplacement.y - ITOFIX19_13(__SCREEN_VERTICAL_DISPLACEMENT));

				if(verticalPosition + ITOFIX19_13(__SCREEN_POSITIVE_EASING_Y_DISPLACEMENT) < verticalTarget)
				{
					_screen->position.y += ITOFIX19_13(__SCREEN_POSITIVE_EASING_Y_DISPLACEMENT);
				}
				else if(verticalPosition - ITOFIX19_13(__SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT) > verticalTarget)
				{
					_screen->position.y -= ITOFIX19_13(__SCREEN_NEGATIVE_EASING_Y_DISPLACEMENT);
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

void CustomScreenMovementManager_setTransformationBaseEntity(CustomScreenMovementManager this, Entity transformationBaseEntity)
{
	ASSERT(this, "Screen::setTransformationBaseEntity: null this");

	this->transformationBaseEntity = transformationBaseEntity;
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
            GameState_transform(__SAFE_CAST(GameState, Game_getCurrentState(Game_getInstance())));
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
    Screen_move(_screen, this->lastShakeOffset, false);

    // apply _screen offset
    GameState_transform(__SAFE_CAST(GameState, StateMachine_getCurrentState(Game_getStateMachine(Game_getInstance()))));

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
