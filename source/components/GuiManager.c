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

#include <Hero.h>
#include <PlatformerLevelState.h>
#include "GuiManager.h"


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

#define GuiManager_ATTRIBUTES																			\
																										\
	/* super's attributes */																			\
	Object_ATTRIBUTES;																					\

// define the GuiManager
__CLASS_DEFINITION(GuiManager, Object);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void GuiManager_constructor(GuiManager this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(GuiManager);

// class's constructor
static void GuiManager_constructor(GuiManager this)
{
	ASSERT(this, "GuiManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE();
}

// class's destructor
void GuiManager_destructor(GuiManager this)
{
	ASSERT(this, "GuiManager::destructor: null this");

	// destroy base
	__SINGLETON_DESTROY;
}

// print elapsed time to gui
void GuiManager_printClock(GuiManager this)
{
	Clock_print(Game_getInGameClock(Game_getInstance()), GUI_X_POS + 42, GUI_Y_POS, GUI_FONT);
}

// print number of coins to gui
void GuiManager_printCoins(GuiManager this)
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
void GuiManager_printEnergy(GuiManager this)
{
	Printing_text(Printing_getInstance(), "\x7B\x7B\x7B", GUI_X_POS + 4, GUI_Y_POS, GUI_FONT);
    u8 i;
	for(i=0; i < Hero_getEnergy(Hero_getInstance()); i++)
	{
    	Printing_text(Printing_getInstance(), "\x60", GUI_X_POS + 4 + i, GUI_Y_POS, GUI_FONT);
	}
}

// print keys icon to gui
void GuiManager_printKey(GuiManager this)
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
void GuiManager_printLevel(GuiManager this)
{
    PlatformerStageDefinition* platformerStageDefinition = PlatformerLevelState_getStage(PlatformerLevelState_getInstance());
	Printing_text(Printing_getInstance(), platformerStageDefinition->identifier, GUI_X_POS + 35, GUI_Y_POS, GUI_FONT);
}

// print current level to gui
void GuiManager_printAll(GuiManager this)
{
	GuiManager_printClock(this);
	GuiManager_printCoins(this);
	GuiManager_printEnergy(this);
	GuiManager_printKey(this);
	GuiManager_printLevel(this);
}