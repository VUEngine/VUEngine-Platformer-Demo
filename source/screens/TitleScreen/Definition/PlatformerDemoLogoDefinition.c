/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Image.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

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
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        168,

        // allocation type
        __NOT_ANIMATED,

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
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        165,

        // allocation type
        __NOT_ANIMATED,

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
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        90,

        // allocation type
        __NOT_ANIMATED,

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
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        91,

        // allocation type
        __NOT_ANIMATED,

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

BgmapSpriteROMDef LOGO_L_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&LOGO_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_LON,
};

BgmapSpriteROMDef LOGO_R_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&LOGO_R_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_RON,
};

BgmapSpriteROMDef LOGO_OUTLINE_L_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&LOGO_OUTLINE_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 1},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_LON,
};

BgmapSpriteROMDef LOGO_OUTLINE_R_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&LOGO_OUTLINE_R_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 1},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_RON,
};

BgmapSpriteROMDef* const LOGO_IM_SPRITES[] =
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