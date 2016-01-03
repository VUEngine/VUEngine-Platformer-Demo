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


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CameraTriggerEntity.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <Shape.h>
#include <Prototypes.h>
#include <Screen.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

// define the CameraTriggerEntity
__CLASS_DEFINITION(CameraTriggerEntity, TriggerEntity);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(CameraTriggerEntity, CameraTriggerEntityDefinition* cameraTriggerEntityDefinition, s16 id, const char* const name)
__CLASS_NEW_END(CameraTriggerEntity, cameraTriggerEntityDefinition, id, name);

// class's constructor
void CameraTriggerEntity_constructor(CameraTriggerEntity this, CameraTriggerEntityDefinition* cameraTriggerEntityDefinition, s16 id, const char* const name)
{
	ASSERT(this, "CameraTriggerEntity::constructor: null this");
	ASSERT(cameraTriggerEntityDefinition, "CameraTriggerEntity::constructor: null definition");

	// construct base object
	__CONSTRUCT_BASE((TriggerEntityDefinition*)cameraTriggerEntityDefinition, id, name);

	this->overridePositionFlag.x = false;
	this->overridePositionFlag.y = false;
	this->overridePositionFlag.z = false;
}

// class's destructor
void CameraTriggerEntity_destructor(CameraTriggerEntity this)
{
	ASSERT(this, "CameraTriggerEntity::destructor: null this");

	Screen_setFocusInGameEntity(Screen_getInstance(), NULL);

	// destroy the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void CameraTriggerEntity_transform(CameraTriggerEntity this, const Transformation* environmentTransform)
{
	ASSERT(this, "CameraTriggerEntity::transform: null this");

	VBVec3D currentGlobalPosition = *Container_getGlobalPosition(__SAFE_CAST(Container, this));

	Entity_transform(__SAFE_CAST(Entity, this), environmentTransform);

	if(this->overridePositionFlag.x)
	{
		this->transform.globalPosition.x = currentGlobalPosition.x;
	}

	if(this->overridePositionFlag.y)
	{
		this->transform.globalPosition.y = currentGlobalPosition.y;
	}
	
	if(this->shape)
	{
		__VIRTUAL_CALL(void, Shape, position, this->shape);
//		__VIRTUAL_CALL(void, Shape, draw, this->shape);
	}
}

// process message
int CameraTriggerEntity_doMessage(CameraTriggerEntity this, int message)
{
	ASSERT(this, "HeroMoving::doMessage: null this");

	switch(message)
	{
		case kStartLevel:

			Screen_setFocusInGameEntity(Screen_getInstance(), __SAFE_CAST(InGameEntity, this));
			return true;
			break;
		
	}
	
	return false;
}

void CameraTriggerEntity_setOverridePositionFlag(CameraTriggerEntity this, VBVec3DFlag overridePositionFlag)
{
	ASSERT(this, "CameraTriggerEntity::setOverridePositionFlag: null this");

	this->overridePositionFlag = overridePositionFlag;
	Container_invalidateGlobalPosition(__SAFE_CAST(Container, this));
	
	Transformation environmentTransform = Container_getEnvironmentTransform(this->parent);
	Entity_transform(__SAFE_CAST(Entity, this), &environmentTransform);
}

VBVec3DFlag CameraTriggerEntity_getOverridePositionFlag(CameraTriggerEntity this)
{
	ASSERT(this, "CameraTriggerEntity::getOverridePositionFlag: null this");

	return this->overridePositionFlag;
}
