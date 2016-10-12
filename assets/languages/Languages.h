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

#ifndef LANGUAGES_H_
#define LANGUAGES_H_


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

enum LanguageIdentifiers
{
    LANG_EN,
    LANG_DE,
    LANG_ES,
    LANG_FR,
};

enum LanguageStrings
{
    /* Splash Screens */
	STR_PRECAUTION_SCREEN_TITLE,
	STR_PRECAUTION_SCREEN_TEXT,
	STR_AUTOMATIC_PAUSE,
	STR_AUTOMATIC_PAUSE_EXPLANATION,
    STR_AUTOMATIC_PAUSE_TEXT,
    STR_PAUSE,
    STR_ON,
    STR_OFF,
    STR_LANGUAGE_SELECT,
    STR_PRESS_START_BUTTON,

    /* Levels */
    STR_LEVEL,
    STR_LEVEL_DONE,
    STR_LEVEL_CONQUERED,
    STR_LEVEL_1_NAME,
    STR_NEW_BEST,
};


#endif
