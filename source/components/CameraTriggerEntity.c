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
#include <CustomScreenMovementManager.h>


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
	__CONSTRUCT_BASE(TriggerEntity, (TriggerEntityDefinition*)cameraTriggerEntityDefinition, id, name);

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

	VBVec3D currentGlobalPosition = this->transform.globalPosition;

	Container_transform(__SAFE_CAST(Container, this), environmentTransform);

	if(this->overridePositionFlag.x)
	{
		this->transform.globalPosition.x = currentGlobalPosition.x;
	}

	if(this->overridePositionFlag.y)
	{
		this->transform.globalPosition.y = currentGlobalPosition.y;
	}

    __VIRTUAL_CALL(Shape, position, this->shape);

/*
	if(this->shape)
	{
		__VIRTUAL_CALL(Shape, draw, this->shape);
	}
*/
}

void CameraTriggerEntity_setOverridePositionFlag(CameraTriggerEntity this, VBVec3DFlag overridePositionFlag)
{
	ASSERT(this, "CameraTriggerEntity::setOverridePositionFlag: null this");

	Container_invalidateGlobalPosition(__SAFE_CAST(Container, this), __XAXIS | __YAXIS | __ZAXIS);

	Transformation environmentTransform = Container_getEnvironmentTransform(this->parent);

    // don't lock yet, allow the global position to be calculated before locking
	this->overridePositionFlag.y = false;
	CameraTriggerEntity_transform(this, &environmentTransform);

	this->overridePositionFlag = overridePositionFlag;
}

VBVec3DFlag CameraTriggerEntity_getOverridePositionFlag(CameraTriggerEntity this)
{
	ASSERT(this, "CameraTriggerEntity::getOverridePositionFlag: null this");

	return this->overridePositionFlag;
}
