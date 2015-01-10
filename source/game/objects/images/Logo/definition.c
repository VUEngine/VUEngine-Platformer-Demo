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

extern BYTE SuperAwesomeTiles[];
extern BYTE SuperAwesomeMap[];
extern BYTE VBJaEngineLogoTiles[];
extern BYTE VBJaEngineLogoMap[];
extern BYTE PlatformerDemoLogoLTiles[];
extern BYTE PlatformerDemoLogoLMap[];
extern BYTE PlatformerDemoLogoRTiles[];
extern BYTE PlatformerDemoLogoRMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef LOGO_LEFT_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        175,

        // allocation type
        __NO_ANIMATED,

        // char definition
        PlatformerDemoLogoLTiles,
    },

    // bgmap definition
    PlatformerDemoLogoLMap,

    // cols (max 48)
    34,

    // rows (max 28)
    7,

    // palette number
    0,
};

TextureROMDef LOGO_RIGHT_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        174,

        // allocation type
        __NO_ANIMATED,

        // char definition
        PlatformerDemoLogoRTiles,
    },

    // bgmap definition
    PlatformerDemoLogoRMap,

    // cols (max 48)
    34,

    // rows (max 28)
    7,

    // palette number
    0,
};

SpriteROMDef LOGO_IM_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&LOGO_LEFT_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,

		// parallax displacement
		0,
	},
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&LOGO_RIGHT_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,

		// parallax displacement
		0,
	},
	{NULL, NULL, 0, 0, 0}
};

ImageROMDef LOGO_IM =
{
	__TYPE(Image),
	LOGO_IM_SPRITES,
};


TextureROMDef SUPER_AWESOME_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        39,

        // allocation type
        __NO_ANIMATED,

        // char definition
        SuperAwesomeTiles,
    },

    // bgmap definition
    SuperAwesomeMap,

    // cols (max 48)
    19,

    // rows (max 28)
    2,

    // palette number
    0,
};

SpriteROMDef SUPER_AWESOME_IM_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&SUPER_AWESOME_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,

		// parallax displacement
		0,
	},
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&SUPER_AWESOME_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,
	},
	{NULL, NULL, 0, 0, 0}
};

ImageROMDef SUPER_AWESOME_IM =
{
	__TYPE(Image),
	SUPER_AWESOME_IM_SPRITES,
};


TextureROMDef VBJAENGINE_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        56,

        // allocation type
        __NO_ANIMATED,

        // char definition
        VBJaEngineLogoTiles,
    },

    // bgmap definition
    VBJaEngineLogoMap,

    // cols (max 48)
    16,

    // rows (max 28)
    4,

    // palette number
    0,
};

SpriteROMDef VBJAENGINE_IM_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&VBJAENGINE_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_LON,
	},
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&VBJAENGINE_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_RON,
	},
	{NULL, NULL, 0, 0, 0}
};

ImageROMDef VBJAENGINE_IM =
{
	__TYPE(Image),
	VBJAENGINE_IM_SPRITES,
};