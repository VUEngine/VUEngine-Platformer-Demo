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

#ifndef HINT_H_
#define HINT_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

enum HintTypes
{
	kEnterHint = 0,
	kPickUpHint,
	kKeyHint
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Hint_METHODS(ClassName)																			\
		AnimatedEntity_METHODS(ClassName)															\

#define Hint_SET_VTABLE(ClassName)																		\
		AnimatedEntity_SET_VTABLE(ClassName)														\
		__VIRTUAL_SET(ClassName, Hint, resume);															\
		__VIRTUAL_SET(ClassName, Hint, handleMessage);													\

__CLASS(Hint);

#define Hint_ATTRIBUTES																					\
		/* it is derived from */																		\
		AnimatedEntity_ATTRIBUTES																	\
		/* the current hint type to show */																\
		u8 type;																						\
		/* name of the animation to play */																\
		char* languageAnimName;

//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Hint, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void Hint_constructor(Hint this, AnimatedEntityDefinition* definition, s16 id, s16 internalId, const char* const name);
void Hint_destructor(Hint this);
bool Hint_handleMessage(Hint this, void* telegram);
void Hint_resume(Hint this);
void Hint_open(Hint this, u8 hintType);
void Hint_close(Hint this);
void Hint_onCloseDone(Hint this, Object eventFirer);
void Hint_onHintOpened(Hint this, Object eventFirer);


#endif
