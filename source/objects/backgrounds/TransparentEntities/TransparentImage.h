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

#ifndef TRANSPARENT_IMAGE_H_
#define TRANSPARENT_IMAGE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Image.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define TransparentImage_METHODS(ClassName)																\
    	Image_METHODS(ClassName)																		\

#define TransparentImage_SET_VTABLE(ClassName)															\
        Image_SET_VTABLE(ClassName)																		\
        __VIRTUAL_SET(ClassName, TransparentImage, update);												\

__CLASS(TransparentImage);

#define TransparentImage_ATTRIBUTES																		\
        Image_ATTRIBUTES																				\
        bool visible;																					\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(TransparentImage, ImageDefinition* imageDefinition, s16 id, s16 internalId, const char* const name);

void TransparentImage_constructor(TransparentImage this, ImageDefinition* definition, s16 id, s16 internalId, const char* const name);
void TransparentImage_destructor(TransparentImage this);
void TransparentImage_update(TransparentImage this);


#endif
