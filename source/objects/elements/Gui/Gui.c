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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <Printing.h>

#include <objects.h>
#include "Gui.h"

#include <PlatformerLevelState.h>
#include <ProgressManager.h>
#include <EventManager.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Gui, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Gui_printAll(Gui this);
static void Gui_onSecondChange(Gui this, Object eventFirer);
static void Gui_onHitTaken(Gui this, Object eventFirer);
static void Gui_onCoinTaken(Gui this, Object eventFirer);
static void Gui_onKeyTaken(Gui this, Object eventFirer);
static void Gui_onPowerUp(Gui this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern CharSetDefinition GUI_CH;
extern CharSetDefinition GUI_BANDANA_CH;


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Gui, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Gui, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void Gui_constructor(Gui this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, internalId, name);

    // add event listeners
	Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)Gui_onSecondChange, kEventSecondChanged);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onHitTaken, kEventHitTaken);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onCoinTaken, kEventCoinTaken);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onKeyTaken, kEventKeyTaken);
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onPowerUp, kEventPowerUp);
}

// class's destructor
void Gui_destructor(Gui this)
{
    // remove event listeners
	Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)Gui_onSecondChange, kEventSecondChanged);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onHitTaken, kEventHitTaken);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onCoinTaken, kEventCoinTaken);
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onKeyTaken, kEventKeyTaken);
    Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui_onPowerUp, kEventPowerUp);

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Gui_ready(Gui this, u32 recursive)
{
	ASSERT(this, "Gui::ready: null this");

	// call base
	AnimatedInGameEntity_ready(__SAFE_CAST(AnimatedInGameEntity, this), recursive);

	// initially print gui
    Gui_printAll(this);
}

// print elapsed time to gui
void Gui_printClock(Gui this __attribute__ ((unused)))
{
	Clock_print(PlatformerLevelState_getClock(PlatformerLevelState_getInstance()), GUI_X_POS + 36, GUI_Y_POS, GUI_FONT);
}

// print best time to gui
void Gui_printBestTime(Gui this __attribute__ ((unused)))
{
	u32 bestTime = ProgressManager_getCurrentLevelBestTime(ProgressManager_getInstance());

	if(bestTime)
	{
		Clock clock = __NEW(Clock);
		Clock_setTimeInMilliSeconds(clock, bestTime);
		Clock_print(clock, GUI_X_POS + 42, GUI_Y_POS + 1, NULL);
	}
	else
	{
		Printing_text(Printing_getInstance(), "--:--", GUI_X_POS + 42, GUI_Y_POS + 1, NULL);
	}
}

// print number of coins to gui
void Gui_printCoins(Gui this __attribute__ ((unused)))
{
    u8 coins = ProgressManager_getCurrentLevelNumberOfCollectedCoins(ProgressManager_getInstance());

    // bound to 64
    if(coins > 64)
    {
        coins = 64;
    }

    // compute x position
    u8 printPos = GUI_X_POS + (coins >= 10) ? 11 : 12;

    // print
	Printing_text(Printing_getInstance(), "00/64", GUI_X_POS + 11, GUI_Y_POS, GUI_FONT);
    Printing_int(Printing_getInstance(), coins, printPos, GUI_Y_POS, GUI_FONT);
}

// print hero's energy to gui
void Gui_printEnergy(Gui this __attribute__ ((unused)))
{
	Printing_text(Printing_getInstance(), "\x7B\x7B\x7B", GUI_X_POS + 4, GUI_Y_POS, GUI_FONT);
    u8 i;
	for(i=0; i < Hero_getEnergy(Hero_getInstance()); i++)
	{
    	Printing_text(Printing_getInstance(), "\x60", GUI_X_POS + 4 + i, GUI_Y_POS, GUI_FONT);
	}
}

// print keys icon to gui
void Gui_printKey(Gui this __attribute__ ((unused)))
{
    if(Hero_hasKey(Hero_getInstance()))
    {
	    Printing_text(Printing_getInstance(), "\x7E\x7F", GUI_X_POS + 21, GUI_Y_POS, GUI_FONT);
    }
    else
    {
	    Printing_text(Printing_getInstance(), "  ", GUI_X_POS + 21, GUI_Y_POS, GUI_FONT);
    }
}

// print current level to gui
void Gui_printLevel(Gui this __attribute__ ((unused)))
{
    PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState_getInstance());
	Printing_text(Printing_getInstance(), platformerLevelDefinition->identifier, GUI_X_POS + 29, GUI_Y_POS, GUI_FONT);
}

// update sprite, e.g. after collecting a power-up
void Gui_updateSprite(Gui this)
{
    CharSet charSet = Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites))), true);

    CharSetDefinition* charSetDefinition = NULL;

	switch(Hero_getPowerUp(Hero_getInstance()))
	{
		case kPowerUpBandana:

		    charSetDefinition = &GUI_BANDANA_CH;
			break;

		default:
		case kPowerUpNone:

		    charSetDefinition = &GUI_CH;
			break;
	}

    CharSet_setCharSetDefinition(charSet, charSetDefinition);
	CharSet_rewrite(charSet);
}

// print current level to gui
void Gui_printAll(Gui this)
{
	// calls Gui_updateSprite, which modifies Sprites. These are not yet available in the entity's
	// construction phase, so we need to utilize the ready method.
	Gui_updateSprite(this);

	Gui_printClock(this);
	Gui_printBestTime(this);
	Gui_printCoins(this);
	Gui_printEnergy(this);
	Gui_printKey(this);
	Gui_printLevel(this);
}

// handle event
static void Gui_onSecondChange(Gui this, Object eventFirer __attribute__ ((unused)))
{
#ifdef __DEBUG_TOOLS
	if(!Game_isInSpecialMode(Game_getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isInSpecialMode(Game_getInstance()))
#endif
#ifdef __ANIMATION_EDITOR
	if(!Game_isInSpecialMode(Game_getInstance()))
#endif

	Gui_printClock(this);
}

// handle event
static void Gui_onHitTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui_printEnergy(this);
}

// handle event
static void Gui_onCoinTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui_printCoins(this);
}

// handle event
static void Gui_onKeyTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui_printKey(this);
}

// handle event
static void Gui_onPowerUp(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui_updateSprite(this);
}

bool Gui_handlePropagatedMessage(Gui this, int message)
{
	ASSERT(this, "Gui::handlePropagatedMessage: null this");

	switch(message)
	{
		case kLevelSetUp:
		case kLevelResumed:

			Gui_printAll(this);
			break;
	}

	return false;
}
