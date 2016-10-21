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

#ifndef GUI_H_
#define GUI_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Gui_METHODS(ClassName)																			\
	    AnimatedInGameEntity_METHODS(ClassName)															\

#define Gui_SET_VTABLE(ClassName)																		\
        AnimatedInGameEntity_SET_VTABLE(ClassName)														\
        __VIRTUAL_SET(ClassName, Gui, ready);															\
        __VIRTUAL_SET(ClassName, Gui, handlePropagatedMessage);											\

__CLASS(Gui);

#define Gui_ATTRIBUTES																					\
        /* it is derived from */																		\
        AnimatedInGameEntity_ATTRIBUTES																	\


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define GUI_FONT    "GuiFont"
#define GUI_X_POS   0
#define GUI_Y_POS   26


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Gui, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name);

void Gui_constructor(Gui this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name);
void Gui_destructor(Gui this);
void Gui_ready(Gui this, u32 recursive);
void Gui_printClock(Gui this);
void Gui_printBestTime(Gui this);
void Gui_printCoins(Gui this);
void Gui_printEnergy(Gui this);
void Gui_printKey(Gui this);
void Gui_printLevel(Gui this);
void Gui_printAll(Gui this);
bool Gui_handlePropagatedMessage(Gui this, int message);


#endif
