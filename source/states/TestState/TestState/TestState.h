/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#ifndef TEST_STATE_H_
#define TEST_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define PRESS_START_BLINK_DELAY 500


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define TestState_METHODS(ClassName)																\
		GameState_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define TestState_SET_VTABLE(ClassName)															\
		GameState_SET_VTABLE(ClassName)																	\
		__VIRTUAL_SET(ClassName, TestState, enter);												\
		__VIRTUAL_SET(ClassName, TestState, exit);													\
		__VIRTUAL_SET(ClassName, TestState, resume);												\
		__VIRTUAL_SET(ClassName, TestState, suspend);												\
		__VIRTUAL_SET(ClassName, TestState, processMessage);										\
		__VIRTUAL_SET(ClassName, TestState, processUserInput);										\

__CLASS(TestState);

#define TestState_ATTRIBUTES																		\
		/* inherits */																					\
		GameState_ATTRIBUTES																			\


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

TestState TestState_getInstance(void);
void TestState_processUserInput(TestState this, UserInput userInput);

#endif
