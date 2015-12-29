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

#include <objects.h>
#include "GUI.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(GUI, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void GUI_onSecondChange(GUI this, Object eventFirer);
static void GUI_onHitTaken(GUI this, Object eventFirer);
static void GUI_onCoinTaken(GUI this, Object eventFirer);
static void GUI_onKeyTaken(GUI this, Object eventFirer);
static void GUI_onBandanaTaken(GUI this, Object eventFirer);
static void GUI_onBandanaLost(GUI this, Object eventFirer);
static void GUI_onHeroDied(GUI this, Object eventFirer);
static void GUI_onLevelEnter(GUI this, Object eventFirer);
static void GUI_onLevelResume(GUI this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern CharSetDefinition GUI_CH;
extern CharSetDefinition GUI_BANDANA_CH;


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(GUI, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(GUI, animatedInGameEntityDefinition, id, name);

// class's constructor
void GUI_constructor(GUI this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, id, name);

    // add event listeners
    Object_addEventListener(__SAFE_CAST(Object, Game_getInGameClock(Game_getInstance())), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onSecondChange, __EVENT_SECOND_CHANGED);
    Object_addEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onHitTaken, EVENT_HIT_TAKEN);
    Object_addEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onCoinTaken, EVENT_COIN_TAKEN);
    Object_addEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onKeyTaken, EVENT_KEY_TAKEN);
    Object_addEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onBandanaTaken, EVENT_BANDANA_TAKEN);
    Object_addEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onBandanaLost, EVENT_BANDANA_LOST);
    Object_addEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onHeroDied, EVENT_HERO_DIED);
    Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onLevelEnter, EVENT_LEVEL_ENTER);
    Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onLevelResume, EVENT_LEVEL_RESUME);

    GUI_printAll(this);
}

// class's destructor
void GUI_destructor(GUI this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// print elapsed time to gui
void GUI_printClock(GUI this)
{
	Clock_print(Game_getInGameClock(Game_getInstance()), GUI_X_POS + 42, GUI_Y_POS, GUI_FONT);
}

// print number of coins to gui
void GUI_printCoins(GUI this)
{
    u8 coins = Hero_getCoins(Hero_getInstance());
    u8 printPos = GUI_X_POS + 13;
	Printing_text(Printing_getInstance(), "000/100", GUI_X_POS + 11, GUI_Y_POS, GUI_FONT);
    if(coins >= 10)
    {
        printPos--;
    }
    if(coins >= 100)
    {
        printPos--;
    }
    Printing_int(Printing_getInstance(), coins, printPos, GUI_Y_POS, GUI_FONT);
}

// print hero's energy to gui
void GUI_printEnergy(GUI this)
{
	Printing_text(Printing_getInstance(), "\x7B\x7B\x7B", GUI_X_POS + 4, GUI_Y_POS, GUI_FONT);
    u8 i;
	for(i=0; i < Hero_getEnergy(Hero_getInstance()); i++)
	{
    	Printing_text(Printing_getInstance(), "\x60", GUI_X_POS + 4 + i, GUI_Y_POS, GUI_FONT);
	}
}

// print keys icon to gui
void GUI_printKey(GUI this)
{
    if(Hero_hasKey(Hero_getInstance())) {
	    Printing_text(Printing_getInstance(), "\x7E\x7F", GUI_X_POS + 24, GUI_Y_POS, GUI_FONT);
    }
    else
    {
	    Printing_text(Printing_getInstance(), "  ", GUI_X_POS + 24, GUI_Y_POS, GUI_FONT);
    }
}

// print current level to gui
void GUI_printLevel(GUI this)
{
    PlatformerStageDefinition* platformerStageDefinition = PlatformerLevelState_getStage(PlatformerLevelState_getInstance());
	Printing_text(Printing_getInstance(), platformerStageDefinition->identifier, GUI_X_POS + 35, GUI_Y_POS, GUI_FONT);
}

// print current level to gui
void GUI_printAll(GUI this)
{
	GUI_printClock(this);
	GUI_printCoins(this);
	GUI_printEnergy(this);
	GUI_printKey(this);
	GUI_printLevel(this);
}

// handle event
static void GUI_onSecondChange(GUI this, Object eventFirer)
{
	GUI_printClock(this);
}

// handle event
static void GUI_onHitTaken(GUI this, Object eventFirer)
{
	GUI_printEnergy(this);
}

// handle event
static void GUI_onCoinTaken(GUI this, Object eventFirer)
{
	GUI_printCoins(this);
}

// handle event
static void GUI_onKeyTaken(GUI this, Object eventFirer)
{
	GUI_printKey(this);
}

// handle event
static void GUI_onBandanaTaken(GUI this, Object eventFirer)
{
	CharSet_setCharSetDefinition(Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites)))), &GUI_BANDANA_CH);
}

// handle event
static void GUI_onBandanaLost(GUI this, Object eventFirer)
{
	CharSet_setCharSetDefinition(Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites)))), &GUI_CH);
}

// handle event
static void GUI_onLevelEnter(GUI this, Object eventFirer)
{
	GUI_printAll(this);
}

// handle event
static void GUI_onLevelResume(GUI this, Object eventFirer)
{
	GUI_printAll(this);
}

// handle event
static void GUI_onHeroDied(GUI this, Object eventFirer)
{
    // remove event listeners
	Object_removeEventListener(__SAFE_CAST(Object, Game_getInGameClock(Game_getInstance())), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onSecondChange, __EVENT_SECOND_CHANGED);
	Object_removeEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onHitTaken, EVENT_HIT_TAKEN);
	Object_removeEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onCoinTaken, EVENT_COIN_TAKEN);
	Object_removeEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onKeyTaken, EVENT_KEY_TAKEN);
    Object_removeEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onBandanaTaken, EVENT_BANDANA_TAKEN);
    Object_removeEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onBandanaLost, EVENT_BANDANA_LOST);
    Object_removeEventListener(__SAFE_CAST(Object, Hero_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onHeroDied, EVENT_HERO_DIED);
    Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onLevelEnter, EVENT_LEVEL_ENTER);
    Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getInstance()), __SAFE_CAST(Object, this), (void (*)(Object, Object))GUI_onLevelResume, EVENT_LEVEL_RESUME);
}
