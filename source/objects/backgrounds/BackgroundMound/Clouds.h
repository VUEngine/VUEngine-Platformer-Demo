/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef CLOUDS_H_
#define CLOUDS_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CLOUDS_MOVE_DELAY 100


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Clouds_METHODS(ClassName)																		\
		Entity_METHODS(ClassName)																	\

#define Clouds_SET_VTABLE(ClassName)																	\
		Entity_SET_VTABLE(ClassName)																\
		__VIRTUAL_SET(ClassName, Clouds, update);														\
		__VIRTUAL_SET(ClassName, Clouds, isVisible);													\

__CLASS(Clouds);

#define Clouds_ATTRIBUTES																				\
		/* it is derived from */																		\
		Entity_ATTRIBUTES																			\
		/* displacement per cycle */																	\
		fix19_13 displacement;																			\


typedef struct CloudsDefinition
{
	// it has an Entity at the beginning
	EntityDefinition EntityDefinition;

	// displacement per cycle
	fix19_13 displacement;

} CloudsDefinition;

typedef const CloudsDefinition CloudsROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Clouds, CloudsDefinition* cloudsDefinition, s16 id, s16 internalId, const char* const name);

void Clouds_constructor(Clouds this, CloudsDefinition* cloudsDefinition, s16 id, s16 internalId, const char* const name);
void Clouds_destructor(Clouds this);
void Clouds_update(Clouds this, u32 elapsedTime);
bool Clouds_isVisible(Clouds this, int pad, bool recursive);


#endif
