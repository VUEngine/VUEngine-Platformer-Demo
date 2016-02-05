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

const LangROMDef LANGUAGE_ES =
{
    // Language Name
    "Español",

    // Strings
    {
        /* Splash Screens */

        //STR_PRECAUTION_SCREEN_TITLE:
        "Importante:",
        //STR_PRECAUTION_SCREEN_TEXT:
        "     Lea los libros de\nInstrucciones y precauciones\n       antes de jugar",
        //STR_AUTOMATIC_PAUSE:
        "Pausa Automática",
        //STR_AUTOMATIC_PAUSE_EXPLANATION:
        " La función automática de pausa le\nrecordará que debe tomar un descanso\n  de jugar approx. cada 30 minutos",
        //STR_AUTOMATIC_PAUSE_TEXT:
        "¡Por favor, tómese un descanso!",
        //STR_PAUSE:
        "Pausa",
        //STR_ON:
        "Encendido",
        //STR_OFF:
        "Apagado",
        //STR_LANGUAGE_SELECT:
        "Seleccionar Idioma",
        // STR_PRESS_START_BUTTON:
        "Press Start Button",

        /* Levels */

        //STR_LEVEL:
        "Nivel",
        //STR_LEVEL_DONE:
        "Level Completed!",
        //STR_LEVEL_1_NAME:
        "Woohoo Hills",
    },
};