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

#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>
#include <Actor.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CANNON_BALL_MINIMUM_Z_VALUE -64


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define CannonBall_METHODS(ClassName)																	\
    	Actor_METHODS(ClassName)																		\

#define CannonBall_SET_VTABLE(ClassName)																\
        Actor_SET_VTABLE(ClassName)																	    \
        __VIRTUAL_SET(ClassName, CannonBall, getAxisFreeForMovement);									\
        __VIRTUAL_SET(ClassName, CannonBall, ready);													\
        __VIRTUAL_SET(ClassName, CannonBall, update);											        \
        __VIRTUAL_SET(ClassName, CannonBall, handleMessage);											\

__CLASS(CannonBall);

#define CannonBall_ATTRIBUTES																			\
																										\
	/* it is derived from */																			\
	Actor_ATTRIBUTES																					\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// allocator
__CLASS_NEW_DECLARE(CannonBall, ActorDefinition* definition, s16 id, s16 internalId, const char* const name);

void CannonBall_constructor(CannonBall this, ActorDefinition* definition, s16 id, s16 internalId, const char* const name);
void CannonBall_destructor(CannonBall this);
void CannonBall_ready(CannonBall this, u32 recursive);
void CannonBall_update(CannonBall this, u32 elapsedTime);
void CannonBall_registerShape(CannonBall this);
void CannonBall_unregisterShape(CannonBall this);
int CannonBall_getAxisFreeForMovement(CannonBall this);
void CannonBall_startMovement(CannonBall this);
void CannonBall_stopMovement(CannonBall this);
void CannonBall_checkPosition(CannonBall this);
bool CannonBall_handleMessage(CannonBall this, Telegram telegram);


#endif
