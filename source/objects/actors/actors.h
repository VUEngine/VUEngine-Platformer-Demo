/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#ifndef ACTORS_H_
#define ACTORS_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "Cannon/Cannon.h"
#include "CannonBall/CannonBall.h"
#include "Hero/Hero.h"
#include "MovingEnemy/MovingEnemy.h"
#include "MovingEntity/MovingEntity.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition HERO_AC;
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