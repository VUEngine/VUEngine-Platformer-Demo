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

#ifndef CAMERA_TRIGGER_ENTITY_H_
#define CAMERA_TRIGGER_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <TriggerEntity.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define CameraTriggerEntity_METHODS(ClassName)															\
		TriggerEntity_METHODS(ClassName)																\

#define CameraTriggerEntity_SET_VTABLE(ClassName)														\
		TriggerEntity_SET_VTABLE(ClassName)																\
		__VIRTUAL_SET(ClassName, CameraTriggerEntity, transform);										\

#define CameraTriggerEntity_ATTRIBUTES																	\
		/* super's attributes */																		\
		TriggerEntity_ATTRIBUTES																		\
		/* update axis flag */																			\
		VBVec3DFlag overridePositionFlag;																\

__CLASS(CameraTriggerEntity);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S ROM DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef TriggerEntityDefinition CameraTriggerEntityDefinition;
typedef const CameraTriggerEntityDefinition CameraTriggerEntityROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(CameraTriggerEntity, CameraTriggerEntityDefinition* cameraTriggerEntityDefinition, s16 id, s16 internalId, const char* const name);

void CameraTriggerEntity_constructor(CameraTriggerEntity this, CameraTriggerEntityDefinition* cameraTriggerEntityDefinition, s16 id, s16 internalId, const char* const name);
void CameraTriggerEntity_destructor(CameraTriggerEntity this);
void CameraTriggerEntity_transform(CameraTriggerEntity this, const Transformation* environmentTransform);
void CameraTriggerEntity_setOverridePositionFlag(CameraTriggerEntity this, VBVec3DFlag overridePositionFlag);
VBVec3DFlag CameraTriggerEntity_getOverridePositionFlag(CameraTriggerEntity this);


#endif
