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

#ifndef GAME_EVENTS_H_
#define GAME_EVENTS_H_

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Events.h>


//---------------------------------------------------------------------------------------------------------
// 											 DEFINITIONS
//---------------------------------------------------------------------------------------------------------


enum GameEvents
{
    kEventScreenFocused = kLastEngineEvent + 1,

    kEventKeyPressed,
    kEventKeyReleased,
    kEventKeyHold,

    kEventHitTaken,
    kEventCoinTaken,
    kEventKeyTaken,
    kEventPowerUp,
    kEventHeroDied,
    kEventLevelStarted,
    kEventLevelCompleted,

};

#endif
