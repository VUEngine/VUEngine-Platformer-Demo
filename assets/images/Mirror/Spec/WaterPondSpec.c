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

#include <Libgccvb.h>
#include <BgmapSprite.h>
#include <WaterPond.h>
#include <Box.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BgmapSpriteSpec Level1Main1Back5HbiasMaskEntity;

//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


BgmapSpriteROMSpec* const WaterPondSprites[] =
{
//	(BgmapSpriteROMSpec*)&Level1Main1Back5HbiasMaskEntity,
	NULL
};

const uint8 WATER_POND_WAVE_LUT[] =
{
	0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 2, 2, 2, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 2, 2, 2, 1, 1, 1,
};

//#define WATER_POND_WIDTH 				175
//#define WATER_POND_WIDTH 				240
#define WATER_POND_WIDTH 				92
//#define WATER_POND_WIDTH 				124
#define WATER_POND_HEIGHT 				32
#define WATER_POND_REFLECTION_WIDTH		WATER_POND_WIDTH
#define WATER_POND_REFLECTION_HEIGHT	12
#define WAVING_THROTTLE					__F_TO_FIX10_6(0.8f)

ShapeROMSpec WaterPondShapes[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{WATER_POND_WIDTH, WATER_POND_HEIGHT, 10},

		// displacement (x, y, z, p)
		{0, WATER_POND_HEIGHT / 2, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kLayerSolid,

		/// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

PhysicalSpecificationROMSpec WaterPondPhysicalProperties =
{
	// mass
	__F_TO_FIX10_6(0),

	// friction
	__F_TO_FIX10_6(1.0f),

	// bounciness
	__F_TO_FIX10_6(0),

	// maximum velocity
	{__I_TO_FIX10_6(100), __I_TO_FIX10_6(100), __I_TO_FIX10_6(100)},

	// maximum speed
	__I_TO_FIX10_6(0)
};

WaterPondROMSpec WaterPondEntity =
{
	{
		{
			// class allocator
			__TYPE(WaterPond),

			// children
			NULL,

			// behaviors
			NULL,

			// extra
			NULL,

			// sprites
			(SpriteSpec**)WaterPondSprites,

			// use z displacement in projection
			false,
			
			/// meshes
			(WireframeSpec**)NULL,

			// collision shapes
			(ShapeSpec*)WaterPondShapes,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{WATER_POND_WIDTH, WATER_POND_HEIGHT, 10},

			// gameworld's character's type
			kTypeWaterPond,

			// physical specification
			(PhysicalSpecification*)&WaterPondPhysicalProperties,
		},

		// the starting point from where start to reflect data
		// relative to my position
		{-WATER_POND_WIDTH / 2 - 1, 0},

		// the starting point from where start to draw data
		// relative to my position
		{-WATER_POND_WIDTH / 2 - 1, 0},

		// width and height of the reflection
		WATER_POND_WIDTH, WATER_POND_HEIGHT,

		// mask to apply to the mirrored image
		0xAAAAAAAA,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// reflect parallax info
		false,

		// axis for image reversing
		0,

		// pointer to table of vertical displacements
		// if no displacement, leave as NULL
		//NULL,
		WATER_POND_WAVE_LUT,

		// number of wave lut entries
		12 * 5,

		// fix10_6 throttle for the waving
		WAVING_THROTTLE,

		// parallax displacement applied to the reflection
		WATERFALLS_PARALLAX_DISPLACEMENT * 2,

		// flatten up/down
		false, true,

		// border masks: top, bottom, left, right
		0x00000001,
		0x00000000,
		0xC0000000,
		0x00000003,

		// noise passes
		0
	},

	// throttle increment
	__F_TO_FIX10_6(0.5f),

	// throttle increment duration
	1500,

	// throttle increment duration step
	5,

	// surface height
	2,

	// wave amplitude factor
	__F_TO_FIX10_6(1.5f),
};
