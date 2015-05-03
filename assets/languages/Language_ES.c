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


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

/*
 * IMPORTANT: Ensure that this file is encoded in Windows-1252 or ISO-8859-1 ("ANSI") to make use
 * of the full extended ASCII character set including special characters of European languages.
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
        //STR_ON:
        "Encendido",
        //STR_OFF:
        "Apagado",
        //STR_LANGUAGE_SELECT:
        "Seleccionar Idioma",

        /* Level Names */

        //STR_LEVEL:
        "Nivel",
        //STR_LEVEL_1_1_NAME:
        "Woohoo Hills",
        //STR_LEVEL_1_3_NAME:
        "Upwards Spiral",
    },
};