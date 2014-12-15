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

#include <Image.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE VBJaEngineLogoLTiles[];
extern BYTE VBJaEngineLogoRTiles[];
extern BYTE VBJaEngineLogoLMap[];
extern BYTE VBJaEngineLogoRMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef VBJAENGINE_LOGO_L_TX =
{
    {
        // number of chars
        69,

        // allocation type
        __NO_ANIMATED,

        // char definition
        VBJaEngineLogoLTiles,
    },

    // bgmap definition
    VBJaEngineLogoLMap,

    // cols (max 48)
    17,

    // rows (max 28)
    9,

    // palette number
    0,
};

TextureROMDef VBJAENGINE_LOGO_R_TX =
{
    {
        // number of chars
        68,

        // allocation type
        __NO_ANIMATED,

        // char definition
        VBJaEngineLogoRTiles,
    },

    // bgmap definition
    VBJaEngineLogoRMap,

    // cols (max 48)
    17,

    // rows (max 28)
    9,

    // palette number
    0,
};

SpriteROMDef VBJAENGINE_LOGO_IM_SPRITES[] =
{
	{
		// texture definition
		(TextureDefinition*)&VBJAENGINE_LOGO_L_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,

		// parallax displacement
		0,
	},
	{
		// texture definition
		(TextureDefinition*)&VBJAENGINE_LOGO_R_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,

		// parallax displacement
		0,
	},
};

ImageROMDef VBJAENGINE_LOGO_IM =
{
	__TYPE(Image),
	__SPRITE_ARRAY(VBJAENGINE_LOGO_IM_SPRITES),
};