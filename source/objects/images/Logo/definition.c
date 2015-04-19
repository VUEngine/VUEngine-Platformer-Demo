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
extern BYTE PlatformerDemoLogoOutlineLTiles[];
extern BYTE PlatformerDemoLogoOutlineLMap[];
extern BYTE PlatformerDemoLogoOutlineRTiles[];
extern BYTE PlatformerDemoLogoOutlineRMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef LOGO_L_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        168,

        // allocation type
        __NO_ANIMATED,

        // char definition
        PlatformerDemoLogoLTiles,
    },

    // bgmap definition
    PlatformerDemoLogoLMap,

    // cols (max 64)
    36,

    // rows (max 64)
    7,

    // number of frames
    1,

   // palette number
    0,
};

TextureROMDef LOGO_R_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        165,

        // allocation type
        __NO_ANIMATED,

        // char definition
        PlatformerDemoLogoRTiles,
    },

    // bgmap definition
    PlatformerDemoLogoRMap,

    // cols (max 64)
    36,

    // rows (max 64)
    7,

    // number of frames
    1,

    // palette number
    0,
};

TextureROMDef LOGO_OUTLINE_L_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        90,

        // allocation type
        __NO_ANIMATED,

        // char definition
        PlatformerDemoLogoOutlineLTiles,
    },

    // bgmap definition
    PlatformerDemoLogoOutlineLMap,

    // cols (max 64)
    36,

    // rows (max 64)
    7,

    // number of frames
    1,

   // palette number
    1,
};

TextureROMDef LOGO_OUTLINE_R_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        91,

        // allocation type
        __NO_ANIMATED,

        // char definition
        PlatformerDemoLogoOutlineRTiles,
    },

    // bgmap definition
    PlatformerDemoLogoOutlineRMap,

    // cols (max 64)
    36,

    // rows (max 64)
    7,

    // number of frames
    1,

    // palette number
    1,
};

BSpriteROMDef LOGO_L_IM_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&LOGO_L_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_LON,

	// parallax displacement
	0		
};

BSpriteROMDef LOGO_R_IM_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&LOGO_R_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_RON,

	// parallax displacement
	0		
};

BSpriteROMDef LOGO_OUTLINE_L_IM_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&LOGO_OUTLINE_L_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_LON,

	// parallax displacement
	0		
};

BSpriteROMDef LOGO_OUTLINE_R_IM_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&LOGO_OUTLINE_R_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_RON,

	// parallax displacement
	0		
};

BSpriteROMDef* const LOGO_IM_SPRITES[] =
{
	&LOGO_OUTLINE_L_IM_SPRITE,
	&LOGO_OUTLINE_R_IM_SPRITE,
	&LOGO_L_IM_SPRITE,
	&LOGO_R_IM_SPRITE,
	NULL
};

ImageROMDef LOGO_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)LOGO_IM_SPRITES,
};


TextureROMDef SUPER_AWESOME_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        38,

        // allocation type
        __NO_ANIMATED,

        // char definition
        SuperAwesomeTiles,
    },

    // bgmap definition
    SuperAwesomeMap,

    // cols (max 64)
    19,

    // rows (max 64)
    2,

    // number of frames
    1,

    // palette number
    1,
};

BSpriteROMDef SUPER_AWESOME_IM_L_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&SUPER_AWESOME_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_LON,

	// parallax displacement
	0		
};

BSpriteROMDef SUPER_AWESOME_IM_R_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&SUPER_AWESOME_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_RON,

	// parallax displacement
	0		
};

BSpriteROMDef* const SUPER_AWESOME_IM_SPRITES[] =
{
	&SUPER_AWESOME_IM_L_SPRITE,
	&SUPER_AWESOME_IM_R_SPRITE,
	NULL
};

ImageROMDef SUPER_AWESOME_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)SUPER_AWESOME_IM_SPRITES,
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

    // cols (max 64)
    16,

    // rows (max 64)
    4,

    // number of frames
    1,

    // palette number
    0,
};

BSpriteROMDef VBJAENGINE_IM_L_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&VBJAENGINE_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_LON,

	// parallax displacement
	0		
};

BSpriteROMDef VBJAENGINE_IM_R_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&VBJAENGINE_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_RON,

	// parallax displacement
	0		
};

BSpriteROMDef* const VBJAENGINE_IM_SPRITES[] =
{
	&VBJAENGINE_IM_L_SPRITE,
	&VBJAENGINE_IM_R_SPRITE,
	NULL
};

ImageROMDef VBJAENGINE_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)VBJAENGINE_IM_SPRITES,
};