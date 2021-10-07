/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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

const PixelSize collision_2_28_4 = 	{2 * 8, 	28 * 8, 	8 * 8};
const PixelSize collision_2_64_4 = 	{2 * 8, 	64 * 8, 	8 * 8};
const PixelSize collision_3_2_4 = 	{3 * 8, 	2 * 8, 		8 * 8};
const PixelSize collision_4_2_4 = 	{4 * 8, 	2 * 8, 		8 * 8};
const PixelSize collision_4_4_4 = 	{4 * 8, 	4 * 8, 		8 * 8};
const PixelSize collision_4_8_4 = 	{4 * 8, 	8 * 8, 		8 * 8};
const PixelSize collision_6_4_4 = 	{6 * 8, 	4 * 8, 		8 * 8};
const PixelSize collision_6_2_4 = 	{6 * 8, 	2 * 8, 		8 * 8};
const PixelSize collision_8_3_4 = 	{8 * 8, 	3 * 8, 		8 * 8};
const PixelSize collision_8_4_4 = 	{8 * 8, 	4 * 8, 		8 * 8};
const PixelSize collision_8_20_4 = 	{8 * 8, 	20 * 8, 	8 * 8};
const PixelSize collision_12_4_4 = 	{12 * 8, 	4 * 8, 		8 * 8};
const PixelSize collision_12_12_4 = {12 * 8, 	12 * 8, 	8 * 8};
const PixelSize collision_14_6_4 = 	{14 * 8, 	6 * 8, 		8 * 8};
const PixelSize collision_14_18_4 = {14 * 8, 	18 * 8, 	8 * 8};
const PixelSize collision_16_2_4 = 	{16 * 8, 	2 * 8, 		8 * 8};
const PixelSize collision_18_6_4 = 	{18 * 8, 	6 * 8, 		8 * 8};
const PixelSize collision_20_2_4 = 	{20 * 8, 	2 * 8, 		8 * 8};
const PixelSize collision_20_6_4 = 	{20 * 8, 	6 * 8, 		8 * 8};
const PixelSize collision_20_32_4 = {20 * 8, 	32 * 8, 	8 * 8};
const PixelSize collision_28_8_4 = 	{28 * 8, 	8 * 8, 		8 * 8};
const PixelSize collision_28_16_4 = {28 * 8, 	16 * 8, 	8 * 8};
const PixelSize collision_32_14_4 = {32 * 8, 	14 * 8, 	8 * 8};
const PixelSize collision_32_4_4 = 	{32 * 8, 	4 * 8, 		8 * 8};
const PixelSize collision_30_33_4 = {30 * 8, 	33 * 8, 	8 * 8};
const PixelSize collision_34_30_4 = {34 * 8, 	30 * 8, 	8 * 8};
const PixelSize collision_38_10_4 = {38 * 8, 	10 * 8, 	8 * 8};
const PixelSize collision_42_18_4 = {42 * 8, 	18 * 8, 	8 * 8};
const PixelSize collision_44_3_4 = 	{44 * 8 + 2, 	3 * 8, 		8 * 8};
const PixelSize collision_48_2_4 = 	{48 * 8, 	2 * 8, 		8 * 8};
const PixelSize collision_48_3_4 = 	{48 * 8, 	3 * 8, 		8 * 8};
const PixelSize collision_48_4_4 = 	{48 * 8, 	4 * 8, 		8 * 8};
const PixelSize collision_48_10_4 = {48 * 8, 	10 * 8, 	8 * 8};
const PixelSize collision_48_18_4 = {48 * 8, 	18 * 8, 	8 * 8};
const PixelSize collision_48_28_4 = {48 * 8, 	28 * 8, 	8 * 8};
const PixelSize collision_45_5_4 = 	{45 * 8, 	5 * 8, 		8 * 8};
const PixelSize collision_62_25_4 = {62 * 8, 	25 * 8, 	8 * 8};


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Collision::constructor(EntitySpec* inGameEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(inGameEntitySpec, internalId, name);
}

// class's destructor
void Collision::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// set extra info
void Collision::setExtraInfo(void* extraInfo)
{
	NM_ASSERT(NULL != extraInfo, "Collision::setExtraInfo: null extraInfo");

	this->size = Size::getFromPixelSize(*((PixelSize*)extraInfo));
}

void Collision::initialTransform(Transformation* environmentTransform, uint32 recursive)
{
	Base::initialTransform(this, environmentTransform, recursive);

	if(!this->shapes)
	{
		this->shapes = new VirtualList();

		ShapeSpec shapeSpec =
		{
			// class allocator
			__TYPE(Box),

			// size
			PixelSize::getFromSize(this->size),

			// displacement modifier
			{0, 0, -1, 0},

			// rotation modifier
			{0, 0, 0},

			// scale modifier
			{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

			// if true this shape checks for collisions against other shapes
			false,

			/// layers in which I live
			kLayerSolid,

			/// layers to ignore when checking for collisions
			kLayerNone,
		};

		Shape shape = CollisionManager::createShape(Game::getCollisionManager(Game::getInstance()), SpatialObject::safeCast(this), &shapeSpec);

		const Vector3D* myPosition = Entity::getPosition(this);
		const Rotation* myRotation = Entity::getRotation(this);
		const Scale* myScale = Entity::getScale(this);

		Shape::position(shape, myPosition, myRotation, myScale, &this->size);

		VirtualList::pushBack(this->shapes, shape);
	}
}
