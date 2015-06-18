/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
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
 */

const LangROMDef LANGUAGE_FR =
{
    // Language Name
    "Français",

    // Strings
    {
        /* Splash Screens */

        //STR_PRECAUTION_SCREEN_TITLE:
        "Important:",
        //STR_PRECAUTION_SCREEN_TEXT:
        "Prenez conaissance de la\n\nnotice et des précautions\n\na prendre avant de jouer",
        //STR_AUTOMATIC_PAUSE:
        "Pause Automatique",
        //STR_AUTOMATIC_PAUSE_EXPLANATION:
        "  La fonction Pause automatique va\nvous rappelerez de prendre une pause\n  de jeu chaque 30 minutes environ",
        //STR_AUTOMATIC_PAUSE_TEXT:
        "Se il vous plaît, prendre un repos!",
        //STR_ON:
        "Activé",
        //STR_OFF:
        "Desactivé",
        //STR_LANGUAGE_SELECT:
        "Choix de la langue",

        /* Level Names */

        //STR_LEVEL:
        "Niveau",
        //STR_LEVEL_1_1_NAME:
        "Woohoo Hills",
        //STR_LEVEL_1_3_NAME:
        "Upwards Spiral",
    },
};