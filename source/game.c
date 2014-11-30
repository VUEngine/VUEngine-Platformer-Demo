/* VbJaEngine: bitmap graphics engine for the Nintendo Virtual Boy 
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

// include VbJaEngine's Game class
#include <Game.h>

// include the Game's objects
#include <objects.h>
#include <macros.h>

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 										GAME'S MAIN LOOP
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// Main game algorithm
// There should be no need
// to modify this.
int main(void){
	
	// don't forget to define the START_LEVEL macro in
	// common.h (default: TitleScreen) which is the state set
	// after the normal splash screen sequence

	// start the game at state
	 Game_start(Game_getInstance(), (State)SplashScreen_getInstance());
	// for quick level testing comment the line above
	// and uncomment the line below
	// Game_start(Game_getInstance(), (State)TitleScreen_getInstance());
	// Game_start(Game_getInstance(), (State)GameLevel_getInstance());
		
	// end program
	return true;
}