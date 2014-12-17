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
#include <InvisibleInGameEntity.h>
#include <macros.h>

//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Floor16x8LTiles[];
extern BYTE Floor16x8LMap[];
extern BYTE Floor16x8RTiles[];
extern BYTE Floor16x8RMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef FLOOR_16x8_L_TX =
{
    {
        // number of chars
        13,

        // allocation type
        __NO_ANIMATED,

        // char definition
        Floor16x8LTiles,
    },

    // bgmap definition
    Floor16x8LMap,

    // cols (max 48)
    17,

    // rows (max 28)
    9,

    // palette number
    1,
};

TextureROMDef FLOOR_16x8_R_TX =
{
    {
        // number of chars
        14,

        // allocation type
        __NO_ANIMATED,

        // char definition
        Floor16x8RTiles,
    },

    // bgmap definition
    Floor16x8RMap,

    // cols (max 48)
    17,

    // rows (max 28)
    9,

    // palette number
    1,
};

SpriteROMDef FLOOR_16x8_BG_SPRITES[] =
{
	{
		// texture definition
		(TextureDefinition*)&FLOOR_16x8_L_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,
		
		// parallax displacement
		-1,
	},
	{
		// texture definition
		(TextureDefinition*)&FLOOR_16x8_R_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,

		// parallax displacement
		-1,
	},
};

InanimatedInGameEntityROMDef FLOOR_16x8_BG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            __SPRITE_ARRAY(FLOOR_16x8_BG_SPRITES),
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 4, 8},

        // in game type
        kSolid,

        // deep
        20,
    },

    // friction FTOFIX19_13
    FTOFIX19_13(0.5f),

    // elasticity FTOFIX19_13
    FTOFIX19_13(1.0f),

    // register shape
    true,
};

InvisibleInGameEntityROMDef FLOOR_48x2x48 =
{
	{
	    {
	        {
	            __TYPE(InvisibleInGameEntity),
	            NULL,
	        },
	
	        // collision detection gap (up, down, left, right)
	        {0, 0, 0, 0},
	
	        // in game type
	        kSolid,
	
	        // deep
	        0,
	    },
	
	    // friction FTOFIX19_13
	    FTOFIX19_13(0.5f),
	
	    // elasticity FTOFIX19_13
	    FTOFIX19_13(1.0f),
	
	    // register shape
	    true,
	},
	
	// width
	48 * 8,
	// height
	2 * 8,
	// deep
	48 * 8,
};

InvisibleInGameEntityROMDef FLOOR_2x28x48 =
{
	{
	    {
	        {
	            __TYPE(InvisibleInGameEntity),
	            NULL,
	        },
	
	        // collision detection gap (up, down, left, right)
	        {0, 0, 0, 0},
	
	        // in game type
	        kSolid,
	
	        // deep
	        0,
	    },
	
	    // friction FTOFIX19_13
	    FTOFIX19_13(0.5f),
	
	    // elasticity FTOFIX19_13
	    FTOFIX19_13(1.0f),
	
	    // register shape
	    true,
	},
	
	// width
	2 * 8,
	// height
	28 * 8,
	// deep
	48 * 8,
};

InvisibleInGameEntityROMDef FLOOR_48x28x2 =
{
	{
	    {
	        {
	            __TYPE(InvisibleInGameEntity),
	            NULL,
	        },
	
	        // collision detection gap (up, down, left, right)
	        {0, 0, 0, 0},
	
	        // in game type
	        kSolid,
	
	        // deep
	        0,
	    },
	
	    // friction FTOFIX19_13
	    FTOFIX19_13(0.5f),
	
	    // elasticity FTOFIX19_13
	    FTOFIX19_13(1.0f),
	
	    // register shape
	    true,
	},
	
	// width
	48 * 8,
	// height
	28 * 8,
	// deep
	2 * 8,
};