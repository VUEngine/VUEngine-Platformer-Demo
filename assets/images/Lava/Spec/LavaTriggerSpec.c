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

#include <Entity.h>
#include <LavaTrigger.h>
#include <Box.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ShapeROMSpec LavaTriggerShapes[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{2 * 8, 12 * 8, 1 * 8},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kLayerTriggers,

		/// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

LavaTriggerROMSpec LavaTriggerEntity =
{
	// class allocator
	__TYPE(LavaTrigger),

	// children 
	NULL,

	// behaviors 
	NULL,

	// extra info 
	NULL,

	// sprites
	NULL,

	// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec**)NULL,

	// collision shapes
	(ShapeSpec*)LavaTriggerShapes,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{4 * 8, 2 * 8, 4},

	// gameworld's character's type
	kTypeLavaTrigger,

	// physical specification
	(PhysicalSpecification*)NULL,
};
