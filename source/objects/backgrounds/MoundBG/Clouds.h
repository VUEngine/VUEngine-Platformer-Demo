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

#ifndef CLOUDS_H_
#define CLOUDS_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Image.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CLOUDS_MOVE_DELAY 100


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Clouds_METHODS															    \
	Image_METHODS;
	

#define Clouds_SET_VTABLE(ClassName)												\
	Image_SET_VTABLE(ClassName);								    				\
	__VIRTUAL_SET(ClassName, Clouds, update);										\
    __VIRTUAL_SET(ClassName, Clouds, isVisible);									\

__CLASS(Clouds);

#define Clouds_ATTRIBUTES															\
																				    \
	/* it is derivated from */													    \
	Image_ATTRIBUTES															    \
																					\
	/* displacement per cycle */												    \
	fix19_13 displacement;															    \


typedef struct CloudsDefinition
{
	// it has an Image at the beginning
	ImageDefinition imageDefinition;

	// displacement per cycle
	fix19_13 displacement;

} CloudsDefinition;

typedef const CloudsDefinition CloudsROMDef;
//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Clouds, CloudsDefinition* cloudsDefinition, int id, const char* const name);

void Clouds_constructor(Clouds this, CloudsDefinition* cloudsDefinition, int id, const char* const name);
void Clouds_destructor(Clouds this);
void Clouds_update(Clouds this);
bool Clouds_isVisible(Clouds this, int pad);


#endif