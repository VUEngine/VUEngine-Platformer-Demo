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

const LangROMDef LANGUAGE_DE =
{
    // Language Name
    "Deutsch",

    // Strings
    {
        /* Splash Screens */

        //STR_PRECAUTION_SCREEN_TITLE:
        "Wichtig:",
        //STR_PRECAUTION_SCREEN_TEXT:
        "   Lesen Sie vor dem\n\n Spielen die Anleitung\n\nund Sicherheitshinweise",
        //STR_AUTOMATIC_PAUSE:
        "Automatische Pause",
        //STR_AUTOMATIC_PAUSE_EXPLANATION:
        " Die Automatische Pause Funktion\nerinnert dich daran, das Spiel ca.\n  alle 30 Minuten zu pausieren",
        //STR_AUTOMATIC_PAUSE_TEXT:
        "Bitte mache eine Pause!",
        //STR_PAUSE:
        "Pause",
        //STR_ON:
        "An",
        //STR_OFF:
        "Aus",
        //STR_LANGUAGE_SELECT:
        "Sprachauswahl",

        /* Level Names */

        //STR_LEVEL:
        "Level",
        //STR_LEVEL_1_NAME:
        "Woohoo-Berge",
    },
};