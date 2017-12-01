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
#include <macros.h>
#include <debugConfig.h>
#include "Collision.h"


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const Size collision_2_28_4 = 	{2 * 8, 	28 * 8, 	8 * 8};
const Size collision_2_64_4 = 	{2 * 8, 	64 * 8, 	8 * 8};
const Size collision_3_2_4 = 	{3 * 8, 	2 * 8, 		8 * 8};
const Size collision_4_2_4 = 	{4 * 8, 	2 * 8, 		8 * 8};
const Size collision_4_4_4 = 	{4 * 8, 	4 * 8, 		8 * 8};
const Size collision_4_8_4 = 	{4 * 8, 	8 * 8, 		8 * 8};
const Size collision_6_4_4 = 	{6 * 8, 	4 * 8, 		8 * 8};
const Size collision_7_2_4 = 	{7 * 8, 	2 * 8, 		8 * 8};
const Size collision_8_3_4 = 	{8 * 8, 	3 * 8, 		8 * 8};
const Size collision_8_4_4 = 	{8 * 8, 	4 * 8, 		8 * 8};
const Size collision_8_20_4 = 	{8 * 8, 	20 * 8, 	8 * 8};
const Size collision_12_4_4 = 	{12 * 8, 	4 * 8, 		8 * 8};
const Size collision_12_12_4 = {12 * 8, 	12 * 8, 	8 * 8};
const Size collision_14_6_4 = 	{14 * 8, 	6 * 8, 		8 * 8};
const Size collision_14_18_4 = {14 * 8, 	18 * 8, 	8 * 8};
const Size collision_16_2_4 = 	{16 * 8, 	2 * 8, 		8 * 8};
const Size collision_18_6_4 = 	{18 * 8, 	6 * 8, 		8 * 8};
const Size collision_20_2_4 = 	{20 * 8, 	2 * 8, 		8 * 8};
const Size collision_20_6_4 = 	{20 * 8, 	6 * 8, 		8 * 8};
const Size collision_20_32_4 = {20 * 8, 	32 * 8, 	8 * 8};
const Size collision_28_8_4 = 	{28 * 8, 	8 * 8, 		8 * 8};
const Size collision_28_16_4 = {28 * 8, 	16 * 8, 	8 * 8};
const Size collision_32_14_4 = {32 * 8, 	14 * 8, 	8 * 8};
const Size collision_32_4_4 = 	{32 * 8, 	4 * 8, 		8 * 8};
const Size collision_30_33_4 = {30 * 8, 	33 * 8, 	8 * 8};
const Size collision_34_30_4 = {34 * 8, 	30 * 8, 	8 * 8};
const Size collision_38_10_4 = {38 * 8, 	10 * 8, 	8 * 8};
const Size collision_42_18_4 = {42 * 8, 	18 * 8, 	8 * 8};
const Size collision_47_3_4 = 	{47 * 8, 	3 * 8, 		8 * 8};
const Size collision_48_2_4 = 	{48 * 8, 	2 * 8, 		8 * 8};
const Size collision_48_3_4 = 	{48 * 8, 	3 * 8, 		8 * 8};
const Size collision_48_4_4 = 	{48 * 8, 	4 * 8, 		8 * 8};
const Size collision_48_10_4 = {48 * 8, 	10 * 8, 	8 * 8};
const Size collision_48_18_4 = {48 * 8, 	18 * 8, 	8 * 8};
const Size collision_48_28_4 = {48 * 8, 	28 * 8, 	8 * 8};
const Size collision_49_5_4 = 	{49 * 8, 	5 * 8, 		8 * 8};
const Size collision_67_25_4 = {67 * 8, 	25 * 8, 	8 * 8};


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
			{0, 0, -__I_TO_FIX19_13(4 * 8)},

			// rotation modifier
			{0, 0, 0},

			// scale modifier
			{0, 0, 0},

			// if true this shape checks for collisions against other shapes
			false,

			/// layers in which I live
			kSolidLayer,

			/// layers to ignore when checking for collisions
			kNoLayer,
		};

		Shape shape = CollisionManager_createShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), &shapeDefinition);

		const Vector3D* myPosition = Entity_getPosition(__SAFE_CAST(Entity, this));
		const Rotation* myRotation = Entity_getRotation(__SAFE_CAST(Entity, this));
		const Scale* myScale = Entity_getScale(__SAFE_CAST(Entity, this));

		__VIRTUAL_CALL(Shape, position, shape, myPosition, myRotation, myScale, &this->size);

		VirtualList_pushBack(this->shapes, shape);
	}
}
