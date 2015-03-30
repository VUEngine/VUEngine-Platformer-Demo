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

#include <fonts.h>
#include <I18n.h>
#include <lang.h>
#include <lang_de.h>
#include <lang_en.h>
#include <states.h>


//---------------------------------------------------------------------------------------------------------
// 										  GAME'S MAIN LOOP
//---------------------------------------------------------------------------------------------------------

int main(void)
{
	// register languages
	I18n_registerLanguage(I18n_getInstance(), &LANG_EN);
	I18n_registerLanguage(I18n_getInstance(), &LANG_DE);
	I18n_setActiveLanguageByName(I18n_getInstance(), "English");

	// register fonts
	Printing_registerFont(Printing_getInstance(), &PLATFORMER_DEFAULT_FONT);
	Printing_registerFont(Printing_getInstance(), &PLATFORMER_GUI_FONT);
	//Printing_registerFont(Printing_getInstance(), &PLATFORMER_LARGE_FONT);

    // redefine splash screens
    VBJaEPrecautionScreenState_setPrecautionString(VBJaEPrecautionScreenState_getInstance(), I18n_getText(I18n_getInstance(), STR_PRECAUTION));
    VBJaELangSelectScreenState_setTitleString(VBJaELangSelectScreenState_getInstance(), I18n_getText(I18n_getInstance(), STR_LANGUAGE_SELECT));
    VBJaEAutoPauseSelectScreenState_setExplanationString(VBJaEAutoPauseSelectScreenState_getInstance(), I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE_EXPLANATION));
    VBJaEAutoPauseSelectScreenState_setTitleString(VBJaEAutoPauseSelectScreenState_getInstance(), I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE));
    VBJaEAutoPauseSelectScreenState_setOnString(VBJaEAutoPauseSelectScreenState_getInstance(), I18n_getText(I18n_getInstance(), STR_ON));
    VBJaEAutoPauseSelectScreenState_setOffString(VBJaEAutoPauseSelectScreenState_getInstance(), I18n_getText(I18n_getInstance(), STR_OFF));
	VBJaESplashScreenState_setNextstate(VBJaESplashScreenState_getInstance(), __UPCAST(GameState, TitleScreenState_getInstance()));

    // start the game
	//Game_start(Game_getInstance(), __UPCAST(GameState, VBJaEPrecautionScreenState_getInstance()));
    //Game_start(Game_getInstance(), __UPCAST(GameState, TitleScreenState_getInstance()));
	Game_start(Game_getInstance(), __UPCAST(GameState, PlatformerLevelState_getInstance()));

	// end program
	return true;
}
