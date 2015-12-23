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

#ifndef HIDE_LAYER_H_
#define HIDE_LAYER_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define HideLayer_METHODS															\
	AnimatedInGameEntity_METHODS;


#define HideLayer_SET_VTABLE(ClassName)												\
	AnimatedInGameEntity_SET_VTABLE(ClassName);									    \

__CLASS(HideLayer);

#define HideLayer_ATTRIBUTES														\
																				    \
	/* it is derived from */													    \
	AnimatedInGameEntity_ATTRIBUTES												    \


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(HideLayer, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);

void HideLayer_constructor(HideLayer this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);
void HideLayer_destructor(HideLayer this);


#endif