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

#ifndef COIN_H_
#define COIN_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Collectable.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Coin_METHODS(ClassName)																			\
		Collectable_METHODS(ClassName)																	\

#define Coin_SET_VTABLE(ClassName)																		\
		Collectable_SET_VTABLE(ClassName)																\
		__VIRTUAL_SET(ClassName, Coin, initialize);														\
		__VIRTUAL_SET(ClassName, Coin, collect);														\

__CLASS(Coin);

#define Coin_ATTRIBUTES																					\
		/* it is derived from */																		\
		Collectable_ATTRIBUTES																			\


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Coin, AnimatedInGameEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void Coin_constructor(Coin this, AnimatedInGameEntityDefinition* definition, s16 id, s16 internalId, const char* const name);
void Coin_destructor(Coin this);
void Coin_initialize(Coin this, u32 recursive);
void Coin_collect(Coin this);


#endif
