/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
void Hint::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, id, internalId, name);

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
		case kHintPlayAnimation:

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

void Hint::open(u8 hintType)
{
	this->type = hintType;

	Entity::show(this);

	AnimatedEntity::playAnimation(this, "Open");
}

void Hint::close()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kHintPlayAnimation);

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

		case kKeyHint:
			this->languageAnimName = "Key";
			break;
	}

	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(this), kHintPlayAnimation, NULL);
}
