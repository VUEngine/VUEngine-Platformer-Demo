/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "HeroMoving.h"
#include "HeroIdle.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HeroMoving::constructor()
{
	// construct base
	Base::constructor();

	this->bouncing = false;
}

// class's destructor
void HeroMoving::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageDisallowJumpOnBouncing);

	// destroy base
	Base::destructor();
}

// state's enter
void HeroMoving::enter(void* owner)
{
	uint32 holdKey = KeypadManager::getHoldKey(KeypadManager::getInstance());

	if(K_B & holdKey)
	{
		Hero::enableBoost(owner);
	}

#ifdef __DEBUG
	Printing::text(Printing::getInstance(), "HeroMoving", 38, (__SCREEN_HEIGHT_IN_CHARS) - 1, "Platformer");
#endif

	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_PRESSED | __KEY_RELEASED);

	// make sure that the hero's body is awaken right now so the check during
	// the execute method doesn't fail
	Hero::addForceOnAxis(owner, __X_AXIS, false);
}

void HeroMoving::execute(void* owner)
{
	// keep adding force
	if(((K_LL | K_LR ) & KeypadManager::getHoldKey(KeypadManager::getInstance())) && Body::isAwake(Actor::getBody(owner)))
	{
		Hero::addForceOnAxis(owner, __X_AXIS, false);
	}
}

// state's handle message
bool HeroMoving::processMessage(void* owner, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageBodyStopped:

			Hero::stopMovingOnAxis(owner, *(int*)Telegram::getExtraInfo(telegram));
			return true;
			break;

		case kMessageBodyStartedMoving:

			// start movement
			Hero::startedMovingOnAxis(owner, *(int*)Telegram::getExtraInfo(telegram));
			break;
	}

	return false;
}

void HeroMoving::onKeyPressed(void* owner, const UserInput* userInput)
{
	if(K_B & userInput->pressedKey)
	{
		Hero::enableBoost(owner);
	}

	if(K_A & userInput->pressedKey)
	{
		Hero::jump(owner, !this->bouncing);
	}

	// check direction
	if((K_LL | K_LR ) & (userInput->pressedKey | userInput->holdKey))
	{
		Hero::addForceOnAxis(owner, __X_AXIS, true);

		Hero::checkDirection(owner, userInput->pressedKey, "Walk");
	}
	else if(K_LU & userInput->pressedKey)
	{
		Hero::lookBack(owner);

		if(NULL != Hero::getOverlappedDoor(owner))
		{
			if(Door::canEnter(Hero::getOverlappedDoor(owner)))
			{
				Hero::enterDoor(owner);
				return;
			}
		}
	}
}

void HeroMoving::onKeyReleased(void* owner, const UserInput* userInput)
{
	if(K_B & userInput->releasedKey)
	{
		Hero::disableBoost(owner);
	}

	if((K_LL | K_LR) & userInput->releasedKey)
	{
		Hero::stopAddingForce(owner);
	}
}

