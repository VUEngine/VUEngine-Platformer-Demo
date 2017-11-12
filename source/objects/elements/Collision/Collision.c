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


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <debugConfig.h>
#include "Collision.h"


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const Size collision_2_28_1 = 	{2 * 8, 	28 * 8, 	1 * 8};
const Size collision_2_64_1 = 	{2 * 8, 	64 * 8, 	1 * 8};
const Size collision_3_2_1 = 	{3 * 8, 	2 * 8, 		1 * 8};
const Size collision_4_2_1 = 	{4 * 8, 	2 * 8, 		1 * 8};
const Size collision_4_4_1 = 	{4 * 8, 	4 * 8, 		1 * 8};
const Size collision_4_8_1 = 	{4 * 8, 	8 * 8, 		1 * 8};
const Size collision_6_4_1 = 	{6 * 8, 	4 * 8, 		1 * 8};
const Size collision_7_2_1 = 	{7 * 8, 	2 * 8, 		1 * 8};
const Size collision_8_3_1 = 	{8 * 8, 	3 * 8, 		1 * 8};
const Size collision_8_4_1 = 	{8 * 8, 	4 * 8, 		1 * 8};
const Size collision_8_20_1 = 	{8 * 8, 	20 * 8, 	1 * 8};
const Size collision_12_4_1 = 	{12 * 8, 	4 * 8, 		1 * 8};
const Size collision_12_12_1 = {12 * 8, 	12 * 8, 	1 * 8};
const Size collision_14_6_1 = 	{14 * 8, 	6 * 8, 		1 * 8};
const Size collision_14_18_1 = {14 * 8, 	18 * 8, 	1 * 8};
const Size collision_16_2_1 = 	{16 * 8, 	2 * 8, 		1 * 8};
const Size collision_18_6_1 = 	{18 * 8, 	6 * 8, 		1 * 8};
const Size collision_20_2_1 = 	{20 * 8, 	2 * 8, 		1 * 8};
const Size collision_20_6_1 = 	{20 * 8, 	6 * 8, 		1 * 8};
const Size collision_20_32_1 = {20 * 8, 	32 * 8, 	1 * 8};
const Size collision_28_8_1 = 	{28 * 8, 	8 * 8, 		1 * 8};
const Size collision_28_16_1 = {28 * 8, 	16 * 8, 	1 * 8};
const Size collision_32_14_1 = {32 * 8, 	14 * 8, 	1 * 8};
const Size collision_32_4_1 = 	{32 * 8, 	4 * 8, 		1 * 8};
const Size collision_30_33_1 = {30 * 8, 	33 * 8, 	1 * 8};
const Size collision_34_30_1 = {34 * 8, 	30 * 8, 	1 * 8};
const Size collision_38_10_1 = {38 * 8, 	10 * 8, 	1 * 8};
const Size collision_42_18_1 = {42 * 8, 	18 * 8, 	1 * 8};
const Size collision_47_3_1 = 	{47 * 8, 	3 * 8, 		1 * 8};
const Size collision_48_2_1 = 	{48 * 8, 	2 * 8, 		1 * 8};
const Size collision_48_3_1 = 	{48 * 8, 	3 * 8, 		1 * 8};
const Size collision_48_4_1 = 	{48 * 8, 	4 * 8, 		1 * 8};
const Size collision_48_10_1 = {48 * 8, 	10 * 8, 	1 * 8};
const Size collision_48_18_1 = {48 * 8, 	18 * 8, 	1 * 8};
const Size collision_48_28_1 = {48 * 8, 	28 * 8, 	1 * 8};
const Size collision_49_5_1 = 	{49 * 8, 	5 * 8, 		1 * 8};
const Size collision_67_25_1 = {67 * 8, 	25 * 8, 	1 * 8};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Collision, Entity);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Collision, EntityDefinition* inGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Collision, inGameEntityDefinition, id, internalId, name);

// class's constructor
void Collision_constructor(Collision this, EntityDefinition* inGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Entity, inGameEntityDefinition, id, internalId, name);
}

// class's destructor
void Collision_destructor(Collision this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// set extra info
void Collision_setExtraInfo(Collision this, void* extraInfo)
{
	ASSERT(this, "Collision::setExtraInfo: null this");

	this->size = *((Size*)extraInfo);
}

void Collision_initialTransform(Collision this, Transformation* environmentTransform, u32 recursive)
{
	ASSERT(this, "Collision::setExtraInfo: null this");

	__CALL_BASE_METHOD(Entity, initialTransform, this, environmentTransform, recursive);

	if(!this->shapes)
	{
		this->shapes = __NEW(VirtualList);

		ShapeDefinition shapeDefinition =
		{
			// class allocator
			__TYPE(Box),

			// size
			this->size,

			// displacement modifier
			{0, 0, 0},

			// rotation modifier
			{0, 0, 0},

			// scale modifier
			{0, 0, 0},

			// if true this shape checks for collisions against other shapes
			false
		};

		Shape shape = CollisionManager_createShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), &shapeDefinition);
		Shape_setActive(shape, true);
		Shape_setCheckForCollisions(shape, false);

		const Vector3D* myPosition = Entity_getPosition(__SAFE_CAST(Entity, this));
		const Rotation* myRotation = Entity_getRotation(__SAFE_CAST(Entity, this));
		const Scale* myScale = Entity_getScale(__SAFE_CAST(Entity, this));

		__VIRTUAL_CALL(Shape, setup, shape, myPosition, myRotation, myScale, &this->size);

		VirtualList_pushBack(this->shapes, shape);
	}
}
