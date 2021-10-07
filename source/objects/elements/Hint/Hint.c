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

#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <I18n.h>
#include "Hint.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Hint::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);

	this->type = kEnterHint;
	this->languageAnimName = NULL;
}

// class's destructor
void Hint::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

bool Hint::handleMessage(void* telegram)
{
	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
		case kMessageHintPlayAnimation:

			AnimatedEntity::playAnimation(this, this->languageAnimName);
			return true;
			break;
	}

	return false;
}

void Hint::resume()
{
	Base::resume(this);

	Hint::onHintOpened(this, NULL);
}

void Hint::open(uint8 hintType)
{
	this->type = hintType;

	Entity::show(this);

	AnimatedEntity::playAnimation(this, "Open");
}

void Hint::close()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageHintPlayAnimation);

	AnimatedEntity::playAnimation(this, "Close");
}

void Hint::onCloseDone(Object eventFirer __attribute__ ((unused)))
{
	Entity::hide(this);
}

void Hint::onHintOpened(Object eventFirer __attribute__ ((unused)))
{
	this->languageAnimName = "";

	switch(this->type)
	{
		default:
		case kEnterHint:
			switch(I18n::getActiveLanguage(I18n::getInstance()))
			{
				default:
				case 0:
					this->languageAnimName = "EnterEnglish";
					break;

				case 1:
					this->languageAnimName = "EnterDeutsch";
					break;

				case 2:
					this->languageAnimName = "EnterEspanol";
					break;

				case 3:
					this->languageAnimName = "EnterFrancais";
					break;
			}
			break;

		case kPickUpHint:
			switch(I18n::getActiveLanguage(I18n::getInstance()))
			{
				default:
				case 0:
					this->languageAnimName = "PickUpEnglish";
					break;

				case 1:
					this->languageAnimName = "PickUpDeutsch";
					break;

				case 2:
					this->languageAnimName = "PickUpEspanol";
					break;

				case 3:
					this->languageAnimName = "PickUpFrancais";
					break;
			}
			break;

		case kTypeKeyHint:
			this->languageAnimName = "Key";
			break;
	}

	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(this), kMessageHintPlayAnimation, NULL);
}
