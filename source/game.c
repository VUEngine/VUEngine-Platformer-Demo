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

#include <I18n.h>
#include <text.h>
#include <lang_de.h>
#include <lang_en.h>

// include the game's states
#include <states.h>


//---------------------------------------------------------------------------------------------------------
// 											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern const u16 FontTiles[];


//---------------------------------------------------------------------------------------------------------
// 										  GAME'S MAIN LOOP
//---------------------------------------------------------------------------------------------------------

// Main game algorithm
// There should be no need to modify this.
int main(void)
{
	// register languages
	I18n_registerLanguage(I18n_getInstance(), Lang_EN);
	I18n_registerLanguage(I18n_getInstance(), Lang_DE);
	I18n_setLanguage(I18n_getInstance(), LANG_EN);

	// load custom font
	Printing_setFontDefinition((const u16*)FontTiles);

    // start the game
	// Game_start(Game_getInstance(), (State)SplashScreenState_getInstance());
	// for quick level testing comment the line above and uncomment the line below
	// Game_start(Game_getInstance(), (State)TitleScreenState_getInstance());
	Game_start(Game_getInstance(), (State)PlatformerLevelState_getInstance());
		
	// end program
	return true;
}