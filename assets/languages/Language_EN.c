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

#include <I18n.h>


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to make use
 * of the full extended ASCII character set including special characters of European languages.
 *
 * The following character is meant to prevent editors to load this file as UTF-8, since it doesn't
 * form part of a valid UTF-8 byte sequence: £
 */

const char* const LANGUAGE_EN_STRINGS[] =
{
	/* General */

    //STR_YES:
    "Yes",
    //STR_NO:
    "No",
    //STR_ON:
    "On",
    //STR_OFF:
    "Off",
    //STR_ARE_YOU_SURE:
    "Are you sure?",

    /* Splash Screens */

    //STR_PRECAUTION_SCREEN_TITLE:
    "Important",
    //STR_PRECAUTION_SCREEN_TEXT:
    "Read Instruction and\n\nPrecaution Booklets\n\n  before operating",
    //STR_AUTOMATIC_PAUSE:
    "Automatic Pause",
    //STR_AUTOMATIC_PAUSE_EXPLANATION:
    "The Automatic Pause feature will\nremind you to take a break from\nplaying approx. every 30 minutes",
    //STR_AUTOMATIC_PAUSE_TEXT:
    "Please take a rest!",
    //STR_LANGUAGE_SELECT:
    "Language\nSelect",

    /* Title Screen */

    //STR_PRESS_START_BUTTON:
    "Press Start Button",
	//STR_MAIN_MENU_CONTINUE:
	"Continue",
	//STR_MAIN_MENU_NEW_GAME:
	"New Game",
	//STR_MAIN_MENU_OPTIONS:
	"Options",
	//STR_MAIN_MENU_CREDITS:
	"Credits",
	//STR_ALL_PROGRESS_WILL_BE_ERASED:
	"This will erase all your progress.",

	/* Pause Screen */

    //STR_PAUSE:
    "Pause",
	//STR_PAUSE_SCREEN_CONTINUE:
	"Continue",
	//STR_PAUSE_SCREEN_OPTIONS:
	"Options",
	//STR_PAUSE_SCREEN_QUIT_LEVEL:
	"Quit Level",

    /* Levels */

    //STR_LEVEL:
    "Level",
    //STR_LEVEL_DONE:
    "Level Completed!",
    //STR_LEVEL_CONQUERED:
    "Level Conquered!",
    //STR_LEVEL_1_NAME:
    "Woohoo Hills",
    //STR_NEW_BEST:
    "New Best!",
};

const LangROMDef LANGUAGE_EN =
{
    // Language Name
    "English",

    // Strings
    (const char**)LANGUAGE_EN_STRINGS
};
