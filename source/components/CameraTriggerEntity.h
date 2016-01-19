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

#ifndef CAMERA_TRIGGER_ENTITY_H_
#define CAMERA_TRIGGER_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <TriggerEntity.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define CameraTriggerEntity_METHODS																		\
		TriggerEntity_METHODS																			\

#define CameraTriggerEntity_SET_VTABLE(ClassName)														\
		TriggerEntity_SET_VTABLE(ClassName)																\
		__VIRTUAL_SET(ClassName, CameraTriggerEntity, transform);										\

#define CameraTriggerEntity_ATTRIBUTES																	\
																										\
	/* super's attributes */																			\
	TriggerEntity_ATTRIBUTES																			\
																										\
	/* update axis flag */																				\
	VBVec3DFlag overridePositionFlag;																	\

__CLASS(CameraTriggerEntity);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S ROM DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef TriggerEntityDefinition CameraTriggerEntityDefinition;
typedef const CameraTriggerEntityDefinition CameraTriggerEntityROMDef;


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(CameraTriggerEntity, CameraTriggerEntityDefinition* cameraTriggerEntityDefinition, s16 id, const char* const name);

void CameraTriggerEntity_constructor(CameraTriggerEntity this, CameraTriggerEntityDefinition* cameraTriggerEntityDefinition, s16 id, const char* const name);
void CameraTriggerEntity_destructor(CameraTriggerEntity this);
void CameraTriggerEntity_transform(CameraTriggerEntity this, const Transformation* environmentTransform);
void CameraTriggerEntity_setOverridePositionFlag(CameraTriggerEntity this, VBVec3DFlag overridePositionFlag);
VBVec3DFlag CameraTriggerEntity_getOverridePositionFlag(CameraTriggerEntity this);


#endif