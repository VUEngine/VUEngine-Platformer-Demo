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

#ifndef LAVA_H_
#define LAVA_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define LAVA_MOVE_DELAY 	50


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Lava_METHODS(ClassName)																			\
		Entity_METHODS(ClassName)																		\

#define Lava_SET_VTABLE(ClassName)																		\
		Entity_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, Lava, handleMessage);													\
		__VIRTUAL_SET(ClassName, Lava, isVisible);														\

__CLASS(Lava);

#define Lava_ATTRIBUTES																					\
		/* it is derived from */																		\
		Entity_ATTRIBUTES																				\

typedef const EntityDefinition LavaDefinition;
typedef const LavaDefinition LavaROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Lava, EntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void Lava_constructor(Lava this, EntityDefinition* definition, s16 id, s16 internalId, const char* const name);
void Lava_destructor(Lava this);
void Lava_startMoving(Lava this);
bool Lava_handleMessage(Lava this, Telegram telegram);
bool Lava_isVisible(Lava this, int pad, bool recursive);


#endif
