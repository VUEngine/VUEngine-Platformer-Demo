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

#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <I18n.h>
#include "Hint.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Hint, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Hint, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Hint, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void Hint_constructor(Hint this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Hint::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, internalId, name);

	this->type = kEnterHint;
	this->languageAnimName = NULL;
}

// class's destructor
void Hint_destructor(Hint this)
{
	ASSERT(this, "Hint::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

bool Hint_handleMessage(Hint this, void* telegram)
{
	ASSERT(this, "Hint::handleMessage: null this");

	// handle messages that any state would handle here
	switch(Telegram_getMessage(telegram))
	{
		case kHintPlayAnimation:

			AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), this->languageAnimName);
			return true;
			break;
	}

	return false;
}

void Hint_resume(Hint this)
{
	ASSERT(this, "Hint::resume: null this");

	Entity_resume(__SAFE_CAST(Entity, this));
	Hint_onHintOpened(this, NULL);
}

void Hint_open(Hint this, u8 hintType)
{
	ASSERT(this, "Hint::open: null this");

	this->type = hintType;

	Entity_show(__SAFE_CAST(Entity, this));

	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Open");
}

void Hint_close(Hint this)
{
	ASSERT(this, "Hint::close: null this");

	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHintPlayAnimation);

	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Close");
}

void Hint_onCloseDone(Hint this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Hint::onCloseDone: null this");

	Entity_hide(__SAFE_CAST(Entity, this));
}

void Hint_onHintOpened(Hint this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "Hint::onHintOpened: null this");

	this->languageAnimName = "";

	switch(this->type)
	{
		default:
		case kEnterHint:
			switch(I18n_getActiveLanguage(I18n_getInstance()))
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
			switch(I18n_getActiveLanguage(I18n_getInstance()))
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

	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHintPlayAnimation, NULL);
}
