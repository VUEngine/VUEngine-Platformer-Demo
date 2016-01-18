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

#include <states.h>


//---------------------------------------------------------------------------------------------------------
// 										  GAME'S MAIN LOOP
//---------------------------------------------------------------------------------------------------------

int main(void)
{
    // start the game
	Game_start(Game_getInstance(), __SAFE_CAST(GameState, PlatformerLevelState_getInstance()));
//	Game_start(Game_getInstance(), __SAFE_CAST(GameState, TitleScreenState_getInstance()));
    
	// end program
	return true;
}
