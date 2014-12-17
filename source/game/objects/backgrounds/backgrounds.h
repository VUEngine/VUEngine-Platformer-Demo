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

#ifndef BACKGROUNDS_H_
#define BACKGROUNDS_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include "texture.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition TREE_BG_FRONT_SB;
extern EntityDefinition TREE_BG_BACK_SB;
extern EntityDefinition VBJAENGINE_BG_SB;
extern EntityDefinition CLOUDS_SB;

extern EntityDefinition FLOOR_4x10_BG;
extern EntityDefinition FLOOR_16x8_BG;
extern EntityDefinition FLOOR_4x3_FLOAT_BG;
extern EntityDefinition FLOOR_2x2_BLOCK_BG;

extern EntityDefinition FLOOR_48x2x48;
extern EntityDefinition FLOOR_2x28x48;
extern EntityDefinition FLOOR_48x28x2;

extern EntityDefinition MOUND_1_IM;
extern EntityDefinition MOUND_2_IM;


#endif