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
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameEvents.h>
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
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

// define the CustomScreenMovementManager
__CLASS_DEFINITION(CustomScreenMovementManager, ScreenMovementManager);

__CLASS_FRIEND_DEFINITION(Screen);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void CustomScreenMovementManager_constructor(CustomScreenMovementManager this);
static bool CustomScreenMovementManager_doFocusWithNoEasing(CustomScreenMovementManager this, u32 checkIfFocusEntityIsMoving, u32 introFocusing);
static bool CustomScreenMovementManager_dontFocus(CustomScreenMovementManager this, u32 checkIfFocusEntityIsMoving, u32 introFocusing);
static bool CustomScreenMovementManager_doFocus(CustomScreenMovementManager this, u32 checkIfFocusEntityIsMoving, u32 introFocusing);
static bool CustomScreenMovementManager_doFocusAndAlertWhenTargetReached(CustomScreenMovementManager this, u32 checkIfFocusEntityIsMoving, u32 introFocusing);


//---------------------------------------------------------------------------------------------------------
//												GLOBALS
//---------------------------------------------------------------------------------------------------------

static Screen _screen = NULL;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(CustomScreenMovementManager);

// class's constructor
static void __attribute__ ((noinline)) CustomScreenMovementManager_constructor(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE(ScreenMovementManager);

	this->positionFlag.x = 0;
	this->positionFlag.y = 0;
	this->positionFlag.z = 0;

	this->focusFunction = &CustomScreenMovementManager_doFocus;
	this->previousFocusFunction = this->focusFunction;

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
void CustomScreenMovementManager_focus(CustomScreenMovementManager this, u32 checkIfFocusEntityIsMoving __attribute__ ((unused)))
{
	ASSERT(this, "CustomScreenMovementManager::focus: null this");

	this->focusFunction(this, checkIfFocusEntityIsMoving, false);
}

static bool CustomScreenMovementManager_doFocusWithNoEasing(CustomScreenMovementManager this __attribute__ ((unused)), u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	ASSERT(this, "CustomScreenMovementManager::doFocusWithNoEasing: null this");

	Vector3D focusEntityPosition = *_screen->focusEntityPosition;
	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, _screen->focusEntity));
	_screen->position.x = focusEntityPosition.x + direction.x * _screen->focusEntityPositionDisplacement.x - __I_TO_FIX19_13(__SCREEN_WIDTH / 2);
	_screen->position.y = focusEntityPosition.y + _screen->focusEntityPositionDisplacement.y - __I_TO_FIX19_13(__SCREEN_HEIGHT / 2);

	Screen_capPosition(_screen);
	Screen_forceDisplacement(_screen, true);

	return true;
}

// center world's _screen in function of focus actor's position
static bool CustomScreenMovementManager_dontFocus(CustomScreenMovementManager this __attribute__ ((unused)), u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	ASSERT(this, "CustomScreenMovementManager::dontFocus: null this");

	return false;
}

// center world's _screen in function of focus actor's position
static bool CustomScreenMovementManager_doFocus(CustomScreenMovementManager this, u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	ASSERT(this, "CustomScreenMovementManager::doFocus: null this");

	_screen->lastDisplacement.x = 0;
	_screen->lastDisplacement.y = 0;
	_screen->lastDisplacement.z = 0;

	// if focusEntity is defined
	if(!_screen->focusEntity)
	{
		return false;
	}

	Direction direction = Entity_getDirection(__SAFE_CAST(Entity, _screen->focusEntity));

	ASSERT(__SAFE_CAST(Actor, _screen->focusEntity), "CustomScreenMovementManager::update: focus entity is not an actor");

	Vector3D screenPreviousPosition = _screen->position;

	Vector3DFlag reachedTargetFlag = {true, true, true};

	Vector3D focusEntityPosition = *_screen->focusEntityPosition;

	Vector3D position3D = focusEntityPosition;
	Vector2D position2D;

	// normalize the position to screen coordinates
	__OPTICS_NORMALIZE(position3D);

	// project position to 2D space
	__OPTICS_PROJECT_TO_2D(position3D, position2D);

	{
		bool focusEntityOutOfBounds = (unsigned)(__FIX19_13_TO_I(position2D.x) - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION) > (unsigned)(_cameraFrustum->x1 - _cameraFrustum->x0 - SCREEN_WIDTH_REDUCTION);

		if(this->positionFlag.x | focusEntityOutOfBounds)
		{
			// calculate the target position
			fix19_13 horizontalPosition = _screen->position.x;
			fix19_13 horizontalTarget = focusEntityPosition.x + direction.x * _screen->focusEntityPositionDisplacement.x - __I_TO_FIX19_13(__SCREEN_WIDTH / 2);

			fix19_13 easingDisplacement = __I_TO_FIX19_13(7);

			if(introFocusing)
			{
				easingDisplacement = __1I_FIX19_13;
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
			else if(__I_TO_FIX19_13(_screen->stageSize.x) < _screen->position.x + __I_TO_FIX19_13(__SCREEN_WIDTH))
			{
				_screen->position.x = __I_TO_FIX19_13(_screen->stageSize.x - __SCREEN_WIDTH);
				reachedTargetFlag.x = true;
			}

			_screen->lastDisplacement.x = (_screen->position.x - screenPreviousPosition.x);
		}
	}

	{
		bool focusEntityOutOfBounds = __FIX19_13_TO_I(position2D.y) > _cameraFrustum->y1 - SCREEN_HEIGHT_REDUCTION || __FIX19_13_TO_I(position2D.y) < _cameraFrustum->y0 + SCREEN_HEIGHT_REDUCTION / 4;

		if(this->positionFlag.y | focusEntityOutOfBounds)
		{
			// calculate the target position
			fix19_13 verticalPosition = _screen->position.y;
			fix19_13 verticalTarget = focusEntityPosition.y + _screen->focusEntityPositionDisplacement.y - __I_TO_FIX19_13(__SCREEN_HEIGHT / 2);

			fix19_13 downEasingDisplacement = __I_TO_FIX19_13(3);
			fix19_13 upEasingDisplacement = __I_TO_FIX19_13(3);

			if(introFocusing)
			{
				downEasingDisplacement = __1I_FIX19_13;
				upEasingDisplacement = __1I_FIX19_13;
			}
			else
			{
				Velocity velocity = Actor_getVelocity(__SAFE_CAST(Actor, _screen->focusEntity));

				if(0 < velocity.y)
				{
					downEasingDisplacement = __I_TO_FIX19_13(8);
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
			else if(__I_TO_FIX19_13(_screen->stageSize.y) < _screen->position.y + __I_TO_FIX19_13(__SCREEN_HEIGHT))
			{
				_screen->position.y = __I_TO_FIX19_13(_screen->stageSize.y - __SCREEN_HEIGHT);
				reachedTargetFlag.y = true;
			}

			_screen->lastDisplacement.y = _screen->position.y - screenPreviousPosition.y;
		}
	}

	if(reachedTargetFlag.x && reachedTargetFlag.y)
	{
		return true;
	}

	return false;
}

// center world's _screen in function of focus actor's position
static bool CustomScreenMovementManager_doFocusAndAlertWhenTargetReached(CustomScreenMovementManager this, u32 checkIfFocusEntityIsMoving __attribute__ ((unused)), u32 introFocusing __attribute__ ((unused)))
{
	if(CustomScreenMovementManager_doFocus(this, checkIfFocusEntityIsMoving, true))
	{
		Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventScreenFocused);

		return true;
	}

	return false;
}

void CustomScreenMovementManager_setPositionFlag(CustomScreenMovementManager this, Vector3DFlag positionFlag)
{
	ASSERT(this, "CustomScreenMovementManager::setPositionFlag: null this");

	this->positionFlag = positionFlag;
}

Vector3DFlag CustomScreenMovementManager_getPositionFlag(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::getPositionFlag: null this");

	return this->positionFlag;
}

void CustomScreenMovementManager_enable(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::enable: null this");

	this->focusFunction = this->previousFocusFunction;
	this->previousFocusFunction = this->focusFunction;
}

void CustomScreenMovementManager_disable(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::disable: null this");

	if(&CustomScreenMovementManager_dontFocus != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &CustomScreenMovementManager_dontFocus;
}

void CustomScreenMovementManager_enableFocusEasing(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::enableFocusEasing: null this");

	this->focusFunction = &CustomScreenMovementManager_doFocus;
	this->previousFocusFunction = this->focusFunction;
}

void CustomScreenMovementManager_disableFocusEasing(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::disableFocusEasing: null this");

	this->focusFunction = &CustomScreenMovementManager_doFocusWithNoEasing;
	this->previousFocusFunction = this->focusFunction;
}

void CustomScreenMovementManager_alertWhenTargetFocused(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::alertWhenTargetFocused: null this");

	if(&CustomScreenMovementManager_doFocusAndAlertWhenTargetReached != this->focusFunction)
	{
		this->previousFocusFunction = this->focusFunction;
	}

	this->focusFunction = &CustomScreenMovementManager_doFocusAndAlertWhenTargetReached;
}

void CustomScreenMovementManager_dontAlertWhenTargetFocused(CustomScreenMovementManager this)
{
	ASSERT(this, "CustomScreenMovementManager::dontAlertWhenTargetFocused: null this");

	this->focusFunction = this->previousFocusFunction;
}
