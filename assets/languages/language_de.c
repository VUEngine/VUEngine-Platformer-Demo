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

#ifdef __CUSTOM_LANGUAGES

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to enable usage
 * of the full extended ASCII character including special characters of European languages.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <I18n.h>


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const LangROMDef LANGUAGE_DE =
{
    // Language Name
    "Deutsch",

    // Strings
    {
        /* Splash Screens */
        "            Wichtig:\n\n  Lesen Sie vor dem Spielen die\n\nAnleitung und Sicherheitshinweise", //STR_PRECAUTION_SCREEN
        "Automatische Pause", //STR_AUTOMATIC_PAUSE
        " Die Automatische Pause Funktion\nerinnert dich daran, das Spiel ca.\n  alle 30 Minuten zu pausieren", //STR_AUTOMATIC_PAUSE_EXPLANATION
        "Sprachauswahl", //STR_LANGUAGE_SELECT
        "An", //STR_ON
        "Aus", //STR_OFF

        /* Level Names */
        "Level", //STR_LEVEL
        "Woohoo-Berge", //STR_LEVEL_1_1_NAME
        "Aufw�rtsspirale", //STR_LEVEL_1_3_NAME
    },
};


#endif