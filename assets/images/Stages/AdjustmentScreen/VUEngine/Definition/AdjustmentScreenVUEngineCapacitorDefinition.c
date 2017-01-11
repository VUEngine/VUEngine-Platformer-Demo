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
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Image.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE AdjustmentScreenVUEngineCapacitorTiles[];
extern BYTE AdjustmentScreenVUEngineCapacitorMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    4,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    AdjustmentScreenVUEngineCapacitorTiles,
};

TextureROMDef ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_TX =
{
    // charset definition
    (CharSetDefinition*)&ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_CH,

    // bgmap definition
    AdjustmentScreenVUEngineCapacitorMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    0,
};

BgmapSpriteROMDef ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_IM_SPRITE_1 =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_TX,

        // transparent
		false,

		// displacement
        {
        	FTOFIX19_13(-116),
        	FTOFIX19_13(67),
        	FTOFIX19_13(-1),
        	FTOFIX19_13(0),
		},
    },

	// LOGOmap mode ( LOGOMAP, AFFINE, H-BIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_IM_SPRITE_2 =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_TX,

        // transparent
		false,

		// displacement
        {
        	FTOFIX19_13(83),
        	FTOFIX19_13(7),
        	FTOFIX19_13(-1),
        	FTOFIX19_13(0),
		},
    },

	// LOGOmap mode ( LOGOMAP, AFFINE, H-BIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_IM_SPRITE_3 =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&ADJUSTMENT_SCREEN_VUENGINE_CAPACITOR_TX,

        // transparent
		false,

		// displacement
        {
        	FTOFIX19_13(116),
        	FTOFIX19_13(-77),
        	FTOFIX19_13(-1),
        	FTOFIX19_13(0),
		},
    },

	// LOGOmap mode ( LOGOMAP, AFFINE, H-BIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};
