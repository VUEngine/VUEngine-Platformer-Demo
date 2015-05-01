/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

InanimatedInGameEntityROMDef COLLISION_2x28x48 =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            NULL,
        },

        // collision detection gap (up, down, left, right)
        {0, 0, 0, 0},

        // in game type
        kSolid,

        // if 0, width and height will be inferred from the texture's size
    	// width
    	2 * 8,

    	// height
    	28 * 8,

    	// Depth
    	48 * 8
    },

    // friction FTOFIX19_13
    FTOFIX19_13(40),

    // elasticity FTOFIX19_13
    FTOFIX19_13(1.0f),

    // register shape
    true,
};