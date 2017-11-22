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

#ifndef TEST_COG_WHEEL_H_
#define TEST_COG_WHEEL_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define COG_WHEEL_ROTATION_DELAY 200


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define TestCogWheel_METHODS(ClassName)																	\
		Entity_METHODS(ClassName)																		\

#define TestCogWheel_SET_VTABLE(ClassName)																\
		Entity_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, TestCogWheel, ready);													\
		__VIRTUAL_SET(ClassName, TestCogWheel, handleMessage);											\

__CLASS(TestCogWheel);

#define TestCogWheel_ATTRIBUTES																			\
		/* it is derived from */																		\
		Entity_ATTRIBUTES																				\

typedef const EntityDefinition TestCogWheelDefinition;
typedef const TestCogWheelDefinition TestCogWheelROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(TestCogWheel, EntityDefinition* EntityDefinition, s16 id, s16 internalId, const char* const name);

void TestCogWheel_constructor(TestCogWheel this, EntityDefinition* definition, s16 id, s16 internalId, const char* const name);
void TestCogWheel_destructor(TestCogWheel this);
void TestCogWheel_ready(TestCogWheel this, bool recursive);
bool TestCogWheel_handleMessage(TestCogWheel this, Telegram telegram);


#endif