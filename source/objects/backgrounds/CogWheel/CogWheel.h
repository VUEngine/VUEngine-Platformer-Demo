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

#ifndef COG_WHEEL_H_
#define COG_WHEEL_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Image.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define COG_WHEEL_ROTATION_DELAY 400


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define CogWheel_METHODS(ClassName)																		\
    	Image_METHODS(ClassName)																		\

#define CogWheel_SET_VTABLE(ClassName)																	\
        Image_SET_VTABLE(ClassName)																		\
        __VIRTUAL_SET(ClassName, CogWheel, ready);														\
        __VIRTUAL_SET(ClassName, CogWheel, handleMessage);												\

__CLASS(CogWheel);

#define CogWheel_ATTRIBUTES																				\
        /* it is derived from */																    	\
        Image_ATTRIBUTES																				\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(CogWheel, ImageDefinition* imageDefinition, s16 id, const char* const name);

void CogWheel_constructor(CogWheel this, ImageDefinition* definition, s16 id, const char* const name);
void CogWheel_destructor(CogWheel this);
void CogWheel_ready(CogWheel this, u32 recursive);
bool CogWheel_handleMessage(CogWheel this, Telegram telegram);


#endif
