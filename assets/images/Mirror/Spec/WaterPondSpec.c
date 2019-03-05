/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#include <Libgccvb.h>
#include <WaterPond.h>
#include <Box.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BgmapSpriteSpec LEVEL_1_MAIN_1_BACK_5_HBIAS_MASK_IM;

//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


BgmapSpriteROMSpec* const WATER_POND_EN_SPRITES[] =
{
//	(BgmapSpriteROMSpec*)&LEVEL_1_MAIN_1_BACK_5_HBIAS_MASK_IM,
	NULL
};

const u8 WATER_POND_WAVE_LUT[] =
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

ShapeROMSpec WATER_POND_EN_SHAPES[] =
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
		kSolidLayer,

		/// layers to ignore when checking for collisions
		kNoLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

PhysicalSpecificationROMSpec WATER_POND_EN_PHYSICAL_PROPERTIES =
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

WaterPondROMSpec WATER_POND_EN =
{
	{
		{
			// class allocator
			__TYPE(WaterPond),

			// behaviors 
			NULL,

			// sprites
			(SpriteSpec**)WATER_POND_EN_SPRITES,

			// collision shapes
			(ShapeSpec*)WATER_POND_EN_SHAPES,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{WATER_POND_WIDTH, WATER_POND_HEIGHT, 10},

			// gameworld's character's type
			kWaterPond,

			// physical specification
			(PhysicalSpecification*)&WATER_POND_EN_PHYSICAL_PROPERTIES,
		},

		// the starting point from where start to reflect data
		// relative to my position
		{-WATER_POND_WIDTH / 2 - 1, 0},

		// the starting point from where start to draw data
		// relative to my position
		{-WATER_POND_WIDTH / 2 - 1, 0},

		// width and height of the reflection
		WATER_POND_WIDTH, WATER_POND_HEIGHT,

		// mask to apply to the whole reflection
		0x00000000,

		// mask to apply to the mirrored image
		0xAAAAAAAA,

		// mask to apply to the image behind the reflection
		0x55555555,

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
