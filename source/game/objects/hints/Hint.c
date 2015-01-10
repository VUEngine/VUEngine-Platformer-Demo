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
#include <Screen.h>
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

__CLASS_DEFINITION(Hint);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Hint_delete(Hint this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Hint, __PARAMETERS(AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID))
__CLASS_NEW_END(Hint, __ARGUMENTS(animatedInGameEntityDefinition, ID));

// class's constructor
void Hint_constructor(Hint this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, __ARGUMENTS(animatedInGameEntityDefinition, ID));
}

// class's destructor
void Hint_destructor(Hint this)
{
	// delete the super object
	__DESTROY_BASE(AnimatedInGameEntity);
}

// state's on message
bool Hint_handleMessage(Hint this, Telegram telegram)
{
	return false;
}

void Hint_open(Hint this)
{
    AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Open");
}

void Hint_close(Hint this)
{
    AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Close");
}

void Hint_delete(Hint this, Object eventFirer)
{
	Container_deleteMyself((Container)this);
}

void Hint_playActiveLanguageHint(Hint this, Object eventFirer)
{
    AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, I18n_getActiveLanguageName(I18n_getInstance()));
}