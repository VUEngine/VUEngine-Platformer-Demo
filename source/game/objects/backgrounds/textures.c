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

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include <Texture.h>

#include "chars.h"
#include "maps.h"


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												DEFINITIONS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

extern const u16 FontTiles[];


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef FLOOR0_TX = {
		// Chargroup
		{
			// chDefinition,				 
			FLOOR0_CH,	
			
			// numChars,
			10,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		FLOOR0_MP,
		
		// cols (max 48)
		28,
		
		// rows (max 28)
		4,
		
		//pallet number,
		1
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef FLOOR1_TX = {
		// Chargroup
		{
			// chDefinition,				 
			FLOOR1_CH,	
			
			// numChars,
			10,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		FLOOR1_MP,
		
		// cols (max 48)
		6,
		
		// rows (max 28)
		4,
		
		//pallet number,
		1
};



TextureROMDef FLOOR2_TX = {
		// Chargroup
		{
			// chDefinition,				 
			FLOOR2_CH,	
			
			// numChars,
			11,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		FLOOR2_MP,
		
		// cols (max 48)
		14,
		
		// rows (max 28)
		12,
		
		//pallet number,
		1
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureDefinition PIPE0_TX = {
		// Chargroup
		{
			// chDefinition,				 
			PIPE0_CH,	
			
			// numChars,
			16,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		PIPE0_MP,
		
		// cols (max 48)
		4,
		
		// rows (max 28)
		5,
		
		//pallet number,
		1
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureDefinition PIPE1_TX = {
		// Chargroup
		{
			// chDefinition,				 
			PIPE1_CH,	
			
			// numChars,
			17,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		PIPE1_MP,
		
		// cols (max 48)
		7,
		
		// rows (max 28)
		4,
		
		//pallet number,
		1
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureDefinition WALL0_TX = {
		// Chargroup
		{
			// chDefinition,				 
			WALL0_CH,	
			
			// numChars,
			9,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		WALL0_MP,
		
		// cols (max 48)
		4,
		
		// rows (max 28)
		3,
		
		//pallet number,
		1
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef POLE0_TX = {
		// Chargroup
		{
			// chDefinition,				 
			POLE0_CH,	
			
			// numChars,
			4,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		POLE0_MP,
		
		// cols (max 48)
		2,
		
		// rows (max 28)
		13,
		
		//pallet number,
		1
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef GATE0_TX = {
		// Chargroup
		{
			// chDefinition,				 
			GATE0_CH,	
			
			// numChars,
			1,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		GATE0_MP,
		
		// cols (max 48)
		2,
		
		// rows (max 28)
		2,
		
		//pallet number,
		0
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef GOAL0_TX = {
		// Chargroup
		{
			// chDefinition,				 
			GOAL0_CH,	
			
			// numChars,
			11,
			
			// allocation type
			__NO_ANIMATED
		},
		
		// bgmap definition
		GOAL0_MP,
		
		// cols (max 48)
		16,
		
		// rows (max 28)
		24,
		
		//pallet number,
		1
};
