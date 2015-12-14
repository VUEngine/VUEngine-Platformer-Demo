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

#ifndef LAYER_SWITCH_DOOR_H_
#define LAYER_SWITCH_DOOR_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Door.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define LayerSwitchDoor_METHODS																			\
	Door_METHODS;
	

#define LayerSwitchDoor_SET_VTABLE(ClassName)															\
	Door_SET_VTABLE(ClassName);																			\
	__VIRTUAL_SET(ClassName, LayerSwitchDoor, handleMessage);

__CLASS(LayerSwitchDoor);

#define LayerSwitchDoor_ATTRIBUTES																		\
																										\
	/* it is derivated from */																			\
	Door_ATTRIBUTES																						\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(LayerSwitchDoor, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);

void LayerSwitchDoor_constructor(LayerSwitchDoor this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);
void LayerSwitchDoor_destructor(LayerSwitchDoor this);
bool LayerSwitchDoor_handleMessage(LayerSwitchDoor this, Telegram telegram);


#endif