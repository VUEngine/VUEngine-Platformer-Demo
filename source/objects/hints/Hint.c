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

#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <I18n.h>

#include <objects.h>
#include "Hint.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Hint, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Hint, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(Hint, animatedInGameEntityDefinition, id, name);

// class's constructor
void Hint_constructor(Hint this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	ASSERT(this, "Hint::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, id, name);
}

// class's destructor
void Hint_destructor(Hint this)
{
	ASSERT(this, "Hint::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Hint_resume(Hint this)
{
	ASSERT(this, "Hint::resume: null this");

	Entity_resume(__SAFE_CAST(Entity, this));
	Entity_hide(__SAFE_CAST(Entity, this));
}

// state's on message
bool Hint_handleMessage(Hint this, Telegram telegram)
{
	ASSERT(this, "Hint::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
	{
		case kSuspend:

			__VIRTUAL_CALL(void, Container, suspend, this);
			return true;
			break;
	}
	
	return false;
}

void Hint_open(Hint this)
{
	ASSERT(this, "Hint::open: null this");

	Entity_show(__SAFE_CAST(Entity, this));
	
    AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Open");
}

void Hint_close(Hint this)
{
	ASSERT(this, "Hint::close: null this");

	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Close");
}

void Hint_onCloseDone(Hint this, Object eventFirer)
{
	ASSERT(this, "Hint::onCloseDone: null this");

	Entity_hide(__SAFE_CAST(Entity, this));
}

void Hint_playActiveLanguageHint(Hint this, Object eventFirer)
{
	ASSERT(this, "Hint::playActiveLanguageHint: null this");

    char* LanguageAnimName;

    switch(I18n_getActiveLanguage(I18n_getInstance()))
    {
        default:
        case 0:
            LanguageAnimName = "English";
            break;

        case 1:
            LanguageAnimName = "Deutsch";
            break;

        case 2:
            LanguageAnimName = "Espanol";
            break;

        case 3:
            LanguageAnimName = "Francais";
            break;
    }

	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), LanguageAnimName);
}