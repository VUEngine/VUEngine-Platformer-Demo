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


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <InanimatedInGameEntity.h>
#include <Collision.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

InanimatedInGameEntityROMDef COLLISION_HIT_CL =
{
    {
        {
            __TYPE(Collision),
            NULL,
        },

        // collision detection gap (up, down, left, right)
        {2, 0, 0, 0},

        // in game type
        kHit,

        // width
        // if 0, width and height will be inferred from the texture's size
    	64,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	64,

    	// depth
    	64
    },

    // friction
    FTOFIX19_13(FLOOR_FRICTION),

    // elasticity
    FTOFIX19_13(FLOOR_ELASTICITY),

    // register shape
    false,
};