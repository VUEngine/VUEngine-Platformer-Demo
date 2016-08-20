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
#include <Optics.h>
#include <Screen.h>
#include <MessageDispatcher.h>
#include <Actor.h>
#include <Game.h>
#include <PhysicalWorld.h>
#include <EventManager.h>
#include <Utilities.h>

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
static bool CustomScreenMovementManager_doFocusWithNoEasing(CustomScreenMovementManager this __attribute__ ((unused)), u8 checkIfFocusEntityIsMoving __attribute__ ((unused)), u8 introFocusing  __attribute__ ((unused)));
static bool CustomScreenMovementManager_dontFocus(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving __attribute__ ((unused)), u8 introFocusing  __attribute__ ((unused)));
static bool CustomScreenMovementManager_doFocus(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving __attribute__ ((unused)), u8 introFocusing  __attribute__ ((unused)));
static void CustomScreenMovementManager_doFocusAndAlertWhenTargetReached(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving __attribute__ ((unused)), u8 introFocusing  __attribute__ ((unused)));
static void CustomScreenMovementManager_FXShakeStart(CustomScreenMovementManager this, u16 duration);
static void CustomScreenMovementManager_FXShakeStop(CustomScreenMovementManager this);
static void CustomScreenMovementManager_onScreenShake(CustomScreenMovementManager this);


//---------------------------------------------------------------------------------------------------------
// 												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Screen _screen = NULL;
extern const VBVec3D* _screenPosition;
extern const VBVec3D* _screenDisplacement;
extern const Optical* _optical;


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(CustomScreenMovementManager);

// class's constructor
static void __attribute__ ((noinline)) CustomScreenMovementManager_constructor(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE(ScreenMovementManager);

	this->lastShakeOffset.x = 0;
	this->lastShakeOffset.y = 0;
	this->lastShakeOffset.z = 0;

	this->positionFlag.x = 0;
	this->positionFlag.y = 0;
	this->positionFlag.z = 0;

	this->shakeTimeLeft = 0;

	this->focusFunction = &CustomScreenMovementManager_doFocus;
    this->previuosFocusFunction = this->focusFunction;

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
void CustomScreenMovementManager_focus(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving __attribute__ ((unused)))
{
	ASSERT(this, "CustomScreenMovementManager::focus: null this");

    this->focusFunction(this, checkIfFocusEntityIsMoving, false);
}

static bool CustomScreenMovementManager_doFocusWithNoEasing(CustomScreenMovementManager this __attribute__ ((unused)), u8 checkIfFocusEntityIsMoving __attribute__ ((unused)), u8 introFocusing  __attribute__ ((unused)))
{
	ASSERT(this, "CustomScreenMovementManager::doFocusWithNoEasing: null this");

    const VBVec3D* focusInGameEntityPosition = __VIRTUAL_CALL(SpatialObject, getPosition, _screen->focusInGameEntity);
    Direction direction = InGameEntity_getDirection(__SAFE_CAST(InGameEntity, _screen->focusInGameEntity));
    _screen->position.x = focusInGameEntityPosition->x + direction.x * _screen->focusEntityPositionDisplacement.x - ITOFIX19_13(__SCREEN_WIDTH / 2);
    _screen->position.y = focusInGameEntityPosition->y + _screen->focusEntityPositionDisplacement.y - ITOFIX19_13(__SCREEN_HEIGHT / 2);

    Screen_capPosition(_screen);
    Screen_forceDisplacement(_screen, true);

    return true;
}

// center world's _screen in function of focus actor's position
static bool CustomScreenMovementManager_dontFocus(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving __attribute__ ((unused)), u8 introFocusing  __attribute__ ((unused)))
{
	ASSERT(this, "CustomScreenMovementManager::dontFocus: null this");

    return false;
}

// center world's _screen in function of focus actor's position
static bool CustomScreenMovementManager_doFocus(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving __attribute__ ((unused)), u8 introFocusing  __attribute__ ((unused)))
{
	ASSERT(this, "CustomScreenMovementManager::doFocus: null this");

	_screen->lastDisplacement.x = 0;
	_screen->lastDisplacement.y = 0;
	_screen->lastDisplacement.z = 0;

	// if focusInGameEntity is defined
	if(_screen->focusInGameEntity)
	{
		Direction direction = InGameEntity_getDirection(__SAFE_CAST(InGameEntity, _screen->focusInGameEntity));

		ASSERT(__SAFE_CAST(Actor, _screen->focusInGameEntity), "CustomScreenMovementManager::update: focus entity is not an actor");

		VBVec3D screenPreviousPosition = _screen->position;

		VBVec3DFlag reachedTargetFlag = {true, true, true};

        const VBVec3D* focusInGameEntityPosition = __VIRTUAL_CALL(SpatialObject, getPosition, _screen->focusInGameEntity);

        VBVec3D position3D = *focusInGameEntityPosition;
        VBVec2D position2D;

        // normalize the position to screen coordinates
        __OPTICS_NORMALIZE(position3D);

        // project position to 2D space
        __OPTICS_PROJECT_TO_2D(position3D, position2D);

		{
			bool focusEntityOutOfBounds = (unsigned)(FIX19_13TOI(position2D.x) - SCREEN_WIDTH_REDUCTION) > __SCREEN_WIDTH - SCREEN_WIDTH_REDUCTION;

			if(this->positionFlag.x || focusEntityOutOfBounds)
			{
                // calculate the target position
				fix19_13 horizontalPosition = _screen->position.x;
    			fix19_13 horizontalTarget = focusInGameEntityPosition->x + direction.x * _screen->focusEntityPositionDisplacement.x - ITOFIX19_13(__SCREEN_WIDTH / 2);

				fix19_13 easingDisplacement = ITOFIX19_13(7);

				if(introFocusing)
				{
				    easingDisplacement = ITOFIX19_13(1);
				}

                reachedTargetFlag.x = false;

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
					_screen->position.x = horizontalTarget;
					reachedTargetFlag.x = true;
				}

                if(0 > _screen->position.x)
                {
                    _screen->position.x = 0;
                    reachedTargetFlag.x = true;
                }
                else if(ITOFIX19_13(_screen->stageSize.x) < _screen->position.x + ITOFIX19_13(__SCREEN_WIDTH))
                {
                    _screen->position.x = ITOFIX19_13(_screen->stageSize.x - __SCREEN_WIDTH);
                    reachedTargetFlag.x = true;
                }

				_screen->lastDisplacement.x = (_screen->position.x - screenPreviousPosition.x);
			}
		}

		{
            bool focusEntityOutOfBounds = FIX19_13TOI(position2D.y) > __SCREEN_HEIGHT - SCREEN_HEIGHT_REDUCTION ||  FIX19_13TOI(position2D.y) < SCREEN_HEIGHT_REDUCTION / 4;

			if(this->positionFlag.y || focusEntityOutOfBounds)
			{
                // calculate the target position
                fix19_13 verticalPosition = _screen->position.y;
                fix19_13 verticalTarget = focusInGameEntityPosition->y + _screen->focusEntityPositionDisplacement.y - ITOFIX19_13(__SCREEN_HEIGHT / 2);

				fix19_13 downEasingDisplacement = ITOFIX19_13(3);
				fix19_13 upEasingDisplacement = ITOFIX19_13(3);

				if(introFocusing)
				{
				    downEasingDisplacement = ITOFIX19_13(1);
                    upEasingDisplacement = ITOFIX19_13(1);
				}
				else
				{
                    Velocity velocity = Actor_getVelocity(__SAFE_CAST(Actor, _screen->focusInGameEntity));

                    if(0 < velocity.y)
                    {
                        downEasingDisplacement = ITOFIX19_13(8);
                    }
				}

                reachedTargetFlag.y = false;

				if(focusEntityOutOfBounds)
				{
				    this->positionFlag.y = true;
				}

				if(verticalPosition + downEasingDisplacement < verticalTarget)
				{
					_screen->position.y += downEasingDisplacement;
				}
				else if(verticalPosition - upEasingDisplacement > verticalTarget)
				{
					_screen->position.y -= upEasingDisplacement;
				}
				else
				{
					_screen->position.y = verticalTarget;
					this->positionFlag.y = false;
					reachedTargetFlag.y = true;
				}

                if(0 > _screen->position.y)
                {
                    _screen->position.y = 0;
					reachedTargetFlag.y = true;
                }
                else if(ITOFIX19_13(_screen->stageSize.y) < _screen->position.y + ITOFIX19_13(__SCREEN_HEIGHT))
                {
                    _screen->position.y = ITOFIX19_13(_screen->stageSize.y - __SCREEN_HEIGHT);
					reachedTargetFlag.y = true;
                }

				_screen->lastDisplacement.y = _screen->position.y - screenPreviousPosition.y;
			}
		}

        if(reachedTargetFlag.x && reachedTargetFlag.y)
        {
            return true;
        }
    }

    return false;
}

// center world's _screen in function of focus actor's position
static void CustomScreenMovementManager_doFocusAndAlertWhenTargetReached(CustomScreenMovementManager this, u8 checkIfFocusEntityIsMoving __attribute__ ((unused)), u8 introFocusing  __attribute__ ((unused)))
{
    if(CustomScreenMovementManager_doFocus(this, checkIfFocusEntityIsMoving, true))
    {
        Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), EVENT_SCREEN_FOCUSED);

        return true;
	}

	return false;
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
	ASSERT(this, "CustomScreenMovementManager::handleMessage: null this");

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
	ASSERT(this, "CustomScreenMovementManager::FXShakeStart: null this");

	// don't follow the focus entity while shaking
	Screen _screen = Screen_getInstance();
    this->focusFunction = &CustomScreenMovementManager_dontFocus;

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
	ASSERT(this, "CustomScreenMovementManager::onScreenShake: null this");

    // stop if no shaking time left
    if(this->shakeTimeLeft == 0)
    {
        // if needed, undo last offset
        if(this->lastShakeOffset.x != 0 || this->lastShakeOffset.y != 0)
        {
            this->lastShakeOffset.x = 0;
        }

        this->focusFunction = &CustomScreenMovementManager_doFocus;

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

void CustomScreenMovementManager_enable(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::enable: null this");

    this->focusFunction = this->previuosFocusFunction;
    this->previuosFocusFunction = this->focusFunction;
}

void CustomScreenMovementManager_disable(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::disable: null this");

    this->previuosFocusFunction = this->focusFunction;
    this->focusFunction = &CustomScreenMovementManager_dontFocus;
}

void CustomScreenMovementManager_enableFocusEasing(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::enableFocusEasing: null this");

    this->focusFunction = &CustomScreenMovementManager_doFocus;
    this->previuosFocusFunction = this->focusFunction;
}

void CustomScreenMovementManager_disableFocusEasing(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::disableFocusEasing: null this");

    this->focusFunction = &CustomScreenMovementManager_doFocusWithNoEasing;
    this->previuosFocusFunction = this->focusFunction;
}

void CustomScreenMovementManager_alertWhenTargetFocused(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::alertWhenTargetFocused: null this");

    this->previuosFocusFunction = this->focusFunction;
	this->focusFunction = &CustomScreenMovementManager_doFocusAndAlertWhenTargetReached;
}

void CustomScreenMovementManager_dontAlertWhenTargetFocused(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::dontAlertWhenTargetFocused: null this");

	this->focusFunction = this->previuosFocusFunction;
}
