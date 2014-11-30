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

extern const u16 ASCII_CH[];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef PRECAUTION_TX = {
		// Chargroup
		{
				// chDefinition,				 
				PRECAUTION_CH,	
				
				// numChars,
				96,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		PRECAUTION_MP,
		
		// cols (max 48)
		48,
		
		// rows (max 28)
		28,
		
		//pallet number,
		0
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef PVBCC_LEFT_TX = {
		
		// Chargroup
		{
				// chDefinition,				 
				PVBCC_CHARSET_LEFT,	
				
				// numChars,
				238,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		PVBCC_MAP_LEFT,
		
		// cols (max 48)
		48,
		
		// rows (max 28)
		28,
		
		//pallet number,
		0
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef PVBCC_RIGHT_TX = {
		
		// Chargroup
		{
				// chDefinition,				 
				PVBCC_CHARSET_RIGHT,	
				
				// numChars,
				235,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		PVBCC_MAP_RIGHT,
		
		// cols (max 48)
		48,
		
		// rows (max 28)
		28,
		
		//pallet number,
		0
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef PVB_LEFT_TX = {
		// Chargroup
		{
				// chDefinition,				 
				PVB_LEFT_CH,	
				
				// numChars,
				81,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		PVB_LEFT_MP,
		
		// cols (max 48)
		48,
		
		// rows (max 28)
		28,
		
		//pallet number,
		0
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef PVB_RIGHT_TX = {
		// Chargroup
		{
				// chDefinition,				 
				PVB_RIGHT_CH,	
				
				// numChars,
				81,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		PVB_RIGHT_MP,
		
		// cols (max 48)
		48,
		
		// rows (max 28)
		28,
		
		//pallet number,
		0
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef VBJAE_LEFT_TX = {
		// Chargroup
		{
				// chDefinition,				 
				VBJAE_LEFT_CH,	
				
				// numChars,
				97,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		VBJAE_LEFT_MP,
		
		// cols (max 48)
		19,
		
		// rows (max 28)
		11,
		
		//pallet number,
		0
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureROMDef VBJAE_RIGHT_TX = {
		// Chargroup
		{
				// chDefinition,				 
				VBJAE_RIGHT_CH,	
				
				// numChars,
				97,
				
				// allocation type
				__NO_ANIMATED
		},
		
		// bgmap definition
		VBJAE_RIGHT_MP,
		
		// cols (max 48)
		19,
		
		// rows (max 28)
		11,
		
		//pallet number,
		0
};
