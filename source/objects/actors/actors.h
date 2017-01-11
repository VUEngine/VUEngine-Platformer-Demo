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

#ifndef ACTORS_H_
#define ACTORS_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "textures.h"
#include "charsets.h"

#include "Cannon/Cannon.h"
#include "Cannon/CannonBall.h"
#include "Hero/Hero.h"
#include "MovingEntity/MovingEntity.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition HERO_AC;
extern EntityDefinition HERO_IDLE_AG;
extern EntityDefinition HERO_SLEEPING_AG;
extern EntityDefinition HERO_BANDANA_AG;
extern EntityDefinition CAMERA_BOUNDING_BOX_IG;
extern EntityDefinition SAW_BLADE_V3_AC;
extern EntityDefinition SAW_BLADE_H3_AC;
extern EntityDefinition SAW_BLADE_H8_AC;
extern EntityDefinition CANNON_AC;
extern EntityDefinition CANNON_BALL_AC;
extern EntityDefinition MOVING_PLATFORM_V6_AC;
extern EntityDefinition SNAIL_4_AC;
extern EntityDefinition SNAIL_8_AC;


#endif
