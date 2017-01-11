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

#ifndef ELEMENTS_H_
#define ELEMENTS_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "Door/Door.h"
#include "HideLayer/HideLayer.h"
#include "Gui/Gui.h"
#include "Hint/Hint.h"

#include "textures.h"
#include "charsets.h"


//---------------------------------------------------------------------------------------------------------
// 											  DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition GUI_AG;
extern EntityDefinition GUI_OVERWORLD_AG;

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

extern EntityDefinition COLLISION_CL;
extern EntityDefinition COLLISION_TOP_CL;
extern EntityDefinition COLLISION_HIT_CL;


#endif
