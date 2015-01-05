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

#include <MBackground.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE TestBGTiles[];
extern BYTE TestBG1Map[];
extern BYTE TestBG2Map[];
extern BYTE TestBG3Map[];
extern BYTE TestBG4Map[];
extern BYTE TestBG5Map[];
extern BYTE TestBG6Map[];
extern BYTE TestBG7Map[];
extern BYTE TestBG8Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


TextureROMDef TEST_BG_1_TX =
{
    {
        // number of chars
        71,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TestBGTiles,
    },

    // bgmap definition
    TestBG1Map,

    // cols (max 48)
    64,

    // rows (max 28)
    64,

    // palette number
    0,
};

TextureROMDef TEST_BG_2_TX =
{
    {
        // number of chars
        71,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TestBGTiles,
    },

    // bgmap definition
    TestBG2Map,

    // cols (max 48)
    64,

    // rows (max 28)
    64,

    // palette number
    0,
};

TextureROMDef TEST_BG_3_TX =
{
    {
        // number of chars
        71,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TestBGTiles,
    },

    // bgmap definition
    TestBG3Map,

    // cols (max 48)
    64,

    // rows (max 28)
    64,

    // palette number
    0,
};

TextureROMDef TEST_BG_4_TX =
{
    {
        // number of chars
        71,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TestBGTiles,
    },

    // bgmap definition
    TestBG4Map,

    // cols (max 48)
    64,

    // rows (max 28)
    64,

    // palette number
    0,
};

TextureROMDef TEST_BG_5_TX =
{
    {
        // number of chars
        71,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TestBGTiles,
    },

    // bgmap definition
    TestBG5Map,

    // cols (max 48)
    64,

    // rows (max 28)
    64,

    // palette number
    0,
};

TextureROMDef TEST_BG_6_TX =
{
    {
        // number of chars
        71,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TestBGTiles,
    },

    // bgmap definition
    TestBG6Map,

    // cols (max 48)
    64,

    // rows (max 28)
    64,

    // palette number
    0,
};

TextureROMDef TEST_BG_7_TX =
{
    {
        // number of chars
        71,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TestBGTiles,
    },

    // bgmap definition
    TestBG7Map,

    // cols (max 48)
    64,

    // rows (max 28)
    64,

    // palette number
    0,
};

TextureROMDef TEST_BG_8_TX =
{
    {
        // number of chars
        71,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TestBGTiles,
    },

    // bgmap definition
    TestBG8Map,

    // cols (max 48)
    64,

    // rows (max 28)
    64,

    // palette number
    0,
};

TextureROMDef* TEST_BG_TEXTURES[] = 
{
	(TextureDefinition*)&TEST_BG_1_TX,
	(TextureDefinition*)&TEST_BG_2_TX,
	(TextureDefinition*)&TEST_BG_3_TX,
	(TextureDefinition*)&TEST_BG_4_TX,
	(TextureDefinition*)&TEST_BG_5_TX,
	(TextureDefinition*)&TEST_BG_6_TX,
	(TextureDefinition*)&TEST_BG_7_TX,
	(TextureDefinition*)&TEST_BG_8_TX,
	NULL
};

MSpriteROMDef TEST_BG_SPRITES[] =
{
	{
		{
			// sprite's type
			__TYPE(MSprite),
	
			// texture definition
			NULL,
			
			// bgmap mode (BGMAP, AFFINE or H-BIAS)
			WRLD_BGMAP,
			
			// display mode
			WRLD_ON,
	
			// parallax displacement
			0,
		},
		
		(TextureDefinition**)TEST_BG_TEXTURES,
		
		// SCX/SCY
		WRLD_1x2,
	},
	{{NULL, NULL, 0, 0, 0}, NULL, 0}
};

MBackgroundROMDef TEST_BG =
{
	__TYPE(MBackground),
	TEST_BG_SPRITES,
};