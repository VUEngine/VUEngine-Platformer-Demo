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

#include <Entity.h>
#include <LavaTrigger.h>
#include <Cuboid.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ShapeROMDef LAVA_TRIGGER_IG_SHAPES[] =
{
	// type, size, displacement
	{__TYPE(Cuboid), {2 * 8, 12 * 8, 1 * 8}, {ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)}, false},
	{NULL, {0, 0, 0}, {0, 0, 0}, false}
};

LavaTriggerROMDef LAVA_TRIGGER_IG =
{
	// the class allocator
	__TYPE(LavaTrigger),

	// the sprites list
	(SpriteROMDef**)NULL,

	// shapes to register
	(ShapeDefinition*)LAVA_TRIGGER_IG_SHAPES,

	// if 0, width and height will be inferred from the first sprite's texture's size
	{4 * 8, 2 * 8, 4},

	// gameworld's character's type
	kMovingPlatform,

	// physical specification
	(PhysicalSpecification*)NULL,
};
