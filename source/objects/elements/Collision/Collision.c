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
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include "Collision.h"


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

VBVec3D collision_2_28_1 = 	{2 * 8, 	28 * 8, 	1 * 8};
VBVec3D collision_2_64_1 = 	{2 * 8, 	64 * 8, 	1 * 8};
VBVec3D collision_3_2_1 = 	{3 * 8, 	2 * 8, 		1 * 8};
VBVec3D collision_4_2_1 = 	{4 * 8, 	2 * 8, 		1 * 8};
VBVec3D collision_4_4_1 = 	{4 * 8, 	4 * 8, 		1 * 8};
VBVec3D collision_4_8_1 = 	{4 * 8, 	8 * 8, 		1 * 8};
VBVec3D collision_6_4_1 = 	{6 * 8, 	4 * 8, 		1 * 8};
VBVec3D collision_7_2_1 = 	{7 * 8, 	2 * 8, 		1 * 8};
VBVec3D collision_8_3_1 = 	{8 * 8, 	3 * 8, 		1 * 8};
VBVec3D collision_8_4_1 = 	{8 * 8, 	4 * 8, 		1 * 8};
VBVec3D collision_8_20_1 = 	{8 * 8, 	20 * 8, 	1 * 8};
VBVec3D collision_12_4_1 = 	{12 * 8, 	4 * 8, 		1 * 8};
VBVec3D collision_12_12_1 = {12 * 8, 	12 * 8, 	1 * 8};
VBVec3D collision_14_6_1 = 	{14 * 8, 	6 * 8, 		1 * 8};
VBVec3D collision_14_18_1 = {14 * 8, 	18 * 8, 	1 * 8};
VBVec3D collision_16_2_1 = 	{16 * 8, 	2 * 8, 		1 * 8};
VBVec3D collision_18_6_1 = 	{18 * 8, 	6 * 8, 		1 * 8};
VBVec3D collision_20_2_1 = 	{20 * 8, 	2 * 8, 		1 * 8};
VBVec3D collision_20_6_1 = 	{20 * 8, 	6 * 8, 		1 * 8};
VBVec3D collision_20_32_1 = {20 * 8, 	32 * 8, 	1 * 8};
VBVec3D collision_28_8_1 = 	{28 * 8, 	8 * 8, 		1 * 8};
VBVec3D collision_28_16_1 = {28 * 8, 	16 * 8, 	1 * 8};
VBVec3D collision_32_14_1 = {32 * 8, 	14 * 8, 	1 * 8};
VBVec3D collision_32_4_1 = 	{32 * 8, 	4 * 8, 		1 * 8};
VBVec3D collision_30_33_1 = {30 * 8, 	33 * 8, 	1 * 8};
VBVec3D collision_34_30_1 = {34 * 8, 	30 * 8, 	1 * 8};
VBVec3D collision_38_10_1 = {38 * 8, 	10 * 8, 	1 * 8};
VBVec3D collision_42_18_1 = {42 * 8, 	18 * 8, 	1 * 8};
VBVec3D collision_47_3_1 = 	{47 * 8, 	3 * 8, 		1 * 8};
VBVec3D collision_48_2_1 = 	{48 * 8, 	2 * 8, 		1 * 8};
VBVec3D collision_48_3_1 = 	{48 * 8, 	3 * 8, 		1 * 8};
VBVec3D collision_48_4_1 = 	{48 * 8, 	4 * 8, 		1 * 8};
VBVec3D collision_48_10_1 = {48 * 8, 	10 * 8, 	1 * 8};
VBVec3D collision_48_18_1 = {48 * 8, 	18 * 8, 	1 * 8};
VBVec3D collision_48_28_1 = {48 * 8, 	28 * 8, 	1 * 8};
VBVec3D collision_49_5_1 = 	{49 * 8, 	5 * 8, 		1 * 8};
VBVec3D collision_67_25_1 = {67 * 8, 	25 * 8, 	1 * 8};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Collision, InanimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Collision, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Collision, inanimatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void Collision_constructor(Collision this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(InanimatedInGameEntity, inanimatedInGameEntityDefinition, id, internalId, name);
}

// class's destructor
void Collision_destructor(Collision this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// set size
void Collision_setExtraInfo(Collision this, void* extraInfo)
{
	ASSERT(this, "Collision::setExtraInfo: null this");

	VBVec3D* size = (VBVec3D*)extraInfo;
	this->size.x = size->x;
	this->size.y = size->y;
	this->size.z = size->z;

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);
}
