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

#include <libgccvb.h>
#include <WaterPond.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BgmapSpriteDefinition LEVEL_1_MAIN_1_BACK_5_HBIAS_MASK_IM;

//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


BgmapSpriteROMDef* const WATER_EN_SPRITES[] =
{
//	(BgmapSpriteROMDef*)&LEVEL_1_MAIN_1_BACK_5_HBIAS_MASK_IM,
	NULL
};

const u8 WATER_WAVE_LUT[] =
{
	0, 0, 1, 1, 2, 2, 1, 1,
	0, 0, 1, 1, 2, 2, 1, 1,
	0, 0, 1, 1, 2, 2, 1, 1,
	0, 0, 1, 1, 2, 2, 1, 1,
	0, 0, 1, 1, 2, 2, 1, 1,
};

//#define WATER_WIDTH 				175
//#define WATER_WIDTH 				240
#define WATER_WIDTH 				78
#define WATER_HEIGHT 				16
//#define WATER_HEIGHT 				8
#define WATER_REFLECTION_WIDTH		WATER_WIDTH
#define WATER_REFLECTION_HEIGHT		4
#define WAVING_THROTTLE				FTOFIX19_13(1)


WaterPondROMDef WATER_EN =
{
	{
		{
			__TYPE(WaterPond),
			(SpriteROMDef**)WATER_EN_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{0, 0, 0, 0},

		// in game type
		kLava,

		// width
		// if 0, width and height will be inferred from the texture's size
		WATER_WIDTH,

		// height
		// if 0, width and height will be inferred from the texture's size
		WATER_HEIGHT,

		// depth
		4
	},

	// the starting point from where start to reflect data
	// relative to my position
	{ITOFIX19_13(-WATER_WIDTH / 2), FTOFIX19_13(0), 0, 0},

	// the starting point from where start to draw data
	// relative to my position
	{ITOFIX19_13(-WATER_WIDTH / 2), FTOFIX19_13(0), 0, 0},

	// width and height of the reflection
	WATER_WIDTH, WATER_HEIGHT,

	// mask to apply to the mirrored image
	0xAAAAAAAA,

	// mask to apply to the image behind the reflection
	0xEEEEEEEE,

	// transparent
	false,

	// reflect parallax info
	true,

	// axis for image reversing
	0,

	// pointer to table of vertical displacements
	// if no displacement, leave as NULL
	//NULL,
	WATER_WAVE_LUT,

	// number of wave lut entries
	8*5,

	// fix19_13 throttle for the waving
	WAVING_THROTTLE,

	// parallax displacement applied to the reflection
	0,

	// flatten up/down
	false, true
};


ReflectiveEntityROMDef WATER_REFLECTION_EN =
{
	{
		{
			__TYPE(ReflectiveEntity),
			(SpriteROMDef**)WATER_EN_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{0, 0, 0, 0},

		// in game type
		kLava,

		// width
		// if 0, width and height will be inferred from the texture's size
		WATER_REFLECTION_WIDTH,

		// height
		// if 0, width and height will be inferred from the texture's size
		WATER_REFLECTION_HEIGHT,

		// depth
		4
	},

	// the starting point from where start to reflect data
	// relative to my position
	{ITOFIX19_13(-WATER_REFLECTION_WIDTH / 2), ITOFIX19_13(-WATER_REFLECTION_HEIGHT - 25), 0, 0},

	// the starting point from where start to draw data
	// relative to my position
	{ITOFIX19_13(-WATER_REFLECTION_WIDTH / 2), ITOFIX19_13(0), 0, 0},

	// width and height of the reflection
	WATER_REFLECTION_WIDTH, WATER_REFLECTION_HEIGHT,

	// mask to apply to the mirrored image
	0xFFFFFFFF,

	// mask to apply to the image behind the reflection
	0xFFFFFFFF,

	// transparent
	true,

	// reflect parallax info
	false,

	// axis for image reversing
	__YAXIS,

	// pointer to table of vertical displacements
	// if no displacement, leave as NULL
	//NULL,
	WATER_WAVE_LUT,

	// number of wave lut entries
	8*5,

	// fix19_13 throttle for the waving
	WAVING_THROTTLE,

	// parallax displacement applied to the reflection
	-1,

	// flatten up/down
	false, false
};
