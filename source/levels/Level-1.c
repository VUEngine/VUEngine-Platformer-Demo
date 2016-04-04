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


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <PlatformerLevelState.h>
#include <Languages.h>


//---------------------------------------------------------------------------------------------------------
// 											    DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL_1_MAIN_SMALL_ROOM_EXIT_DOOR_EP;


//---------------------------------------------------------------------------------------------------------
// 												LEVEL DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerLevelROMDef LEVEL_1_LV =
{
	// starting entry point
	(StageEntryPointDefinition*)&LEVEL_1_MAIN_SMALL_ROOM_EXIT_DOOR_EP,

    // id
    1,

    // identifier
    "1-1",

    // name
    (void*)STR_LEVEL_1_NAME,
};