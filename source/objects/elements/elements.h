/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#ifndef ELEMENTS_H_
#define ELEMENTS_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "Door/Door.h"
#include "HideLayer/HideLayer.h"
#include "GUI/GUI.h"
#include "Hint/Hint.h"

#include "textures.h"
#include "charsets.h"


//---------------------------------------------------------------------------------------------------------
// 											  DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition GUI_AG;
extern EntityDefinition GUI_OVERWORLD_AG;

extern EntityDefinition CLOCK_AG;

extern EntityDefinition DOOR_AG;
extern EntityDefinition DOOR_BACK_AG;
extern EntityDefinition LAYER_SWITCH_DOOR_AG;
extern EntityDefinition GOAL_DOOR_AG;
extern EntityDefinition KEY_DOOR_AG;
extern EntityDefinition LAYER_SWITCH_DOOR_BACK_AG;
extern EntityDefinition AFFINE_DOOR_AG;

extern EntityDefinition LAVA_IG;
extern EntityDefinition LAVA_TOP_AG;
extern EntityDefinition LAVA_TRIGGER_IG;

extern EntityDefinition HIDE_LAYER_10x7_AG;

extern EntityDefinition HINT_MC;


#endif
