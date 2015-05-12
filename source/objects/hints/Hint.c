/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
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
__CLASS_NEW_DEFINITION(Hint, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
__CLASS_NEW_END(Hint, animatedInGameEntityDefinition, ID);

// class's constructor
void Hint_constructor(Hint this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
{
	ASSERT(this, "Hint::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, ID);
}

// class's destructor
void Hint_destructor(Hint this)
{
	ASSERT(this, "Hint::destructor: null this");

	// delete the super object
	__DESTROY_BASE;
}

void Hint_resume(Hint this)
{
	ASSERT(this, "Hint::resume: null this");

	Entity_resume(__GET_CAST(Entity, this));
	
	// this wastes a WORLD, but makes things smoother
	Entity_hide(__GET_CAST(Entity, this));
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

	// this wastes a WORLD, but makes things smoother
	Entity_show(__GET_CAST(Entity, this));
	
    AnimatedInGameEntity_playAnimation(__GET_CAST(AnimatedInGameEntity, this), "Open");
}

void Hint_close(Hint this)
{
	ASSERT(this, "Hint::close: null this");

	AnimatedInGameEntity_playAnimation(__GET_CAST(AnimatedInGameEntity, this), "Close");
}

void Hint_onCloseDone(Hint this, Object eventFirer)
{
	ASSERT(this, "Hint::onCloseDone: null this");

	// this wastes a WORLD, but makes things smoother
	Entity_hide(__GET_CAST(Entity, this));
}

void Hint_playActiveLanguageHint(Hint this, Object eventFirer)
{
	ASSERT(this, "Hint::playActiveLanguageHint: null this");

	AnimatedInGameEntity_playAnimation(__GET_CAST(AnimatedInGameEntity, this), I18n_getActiveLanguageName(I18n_getInstance()));
}