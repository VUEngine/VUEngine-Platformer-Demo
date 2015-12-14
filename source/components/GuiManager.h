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

#ifndef GUI_MANAGER_H_
#define GUI_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Object.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define GuiManager_METHODS																				\
    	Object_METHODS																					\

// declare the virtual methods which are redefined
#define GuiManager_SET_VTABLE(ClassName)																\
    	Object_SET_VTABLE(ClassName)																	\

// declare a GuiManager
__CLASS(GuiManager);


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define GUI_FONT    "GUIFont"
#define GUI_X_POS   0
#define GUI_Y_POS   26


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

GuiManager GuiManager_getInstance();

void GuiManager_destructor(GuiManager this);
void GuiManager_printClock(GuiManager this);
void GuiManager_printCoins(GuiManager this);
void GuiManager_printEnergy(GuiManager this);
void GuiManager_printKey(GuiManager this);
void GuiManager_printLevel(GuiManager this);
void GuiManager_printAll(GuiManager this);


#endif