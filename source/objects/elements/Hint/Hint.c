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
void Hint::constructor(Hint this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Hint::constructor: null this");

	// construct base
	Base::constructor(animatedEntityDefinition, id, internalId, name);

	this->type = kEnterHint;
	this->languageAnimName = NULL;
}

// class's destructor
void Hint::destructor(Hint this)
{
	ASSERT(this, "Hint::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

bool Hint::handleMessage(Hint this, void* telegram)
{
	ASSERT(this, "Hint::handleMessage: null this");

	// handle messages that any state would handle here
	switch(Telegram::getMessage(telegram))
	{
		case kHintPlayAnimation:

			AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), this->languageAnimName);
			return true;
			break;
	}

	return false;
}

void Hint::resume(Hint this)
{
	ASSERT(this, "Hint::resume: null this");

	Base::resume(this);

	Hint::onHintOpened(this, NULL);
}

void Hint::open(Hint this, u8 hintType)
{
	ASSERT(this, "Hint::open: null this");

	this->type = hintType;

	Entity::show(__SAFE_CAST(Entity, this));

	AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Open");
}

void Hint::close(Hint this)
{
	ASSERT(this, "Hint::close: null this");

	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kHintPlayAnimation);

	AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Close");
}

void Hint::onCloseDone(Hint this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Hint::onCloseDone: null this");

	Entity::hide(__SAFE_CAST(Entity, this));
}

void Hint::onHintOpened(Hint this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Hint::onHintOpened: null this");

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

	MessageDispatcher::dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHintPlayAnimation, NULL);
}
