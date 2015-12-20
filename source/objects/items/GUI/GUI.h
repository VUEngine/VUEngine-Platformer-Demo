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

#define GUI_METHODS																						\
	AnimatedInGameEntity_METHODS;

#define GUI_SET_VTABLE(ClassName)																		\
	AnimatedInGameEntity_SET_VTABLE(ClassName)															\

__CLASS(GUI);

#define GUI_ATTRIBUTES																					\
																										\
	/* it is derivated from */																			\
	AnimatedInGameEntity_ATTRIBUTES																		\


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define GUI_FONT    "GUIFont"
#define GUI_X_POS   0
#define GUI_Y_POS   26


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(GUI, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);

void GUI_constructor(GUI this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);
void GUI_destructor(GUI this);
void GUI_printClock(GUI this);
void GUI_printCoins(GUI this);
void GUI_printEnergy(GUI this);
void GUI_printKey(GUI this);
void GUI_printLevel(GUI this);
void GUI_printAll(GUI this);


#endif