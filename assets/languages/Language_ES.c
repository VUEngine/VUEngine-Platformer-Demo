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
 * The following character is meant to prevent editors from loading this file as UTF-8, since it doesn't
 * form part of a valid UTF-8 byte sequence: �
 */

const char* const LANGUAGE_ES_STRINGS[] =
{
	/* General */

	/* STR_ARE_YOU_SURE: */				"�Est�s seguro?",
	/* STR_AUTOMATIC_PAUSE: */			"Pausa Automatica", //"Pausa Autom�tica",
	/* STR_BACK: */						"Espalda",
	/* STR_CONTINUE: */					"Continuar",
	/* STR_CREDITS: */					"Cr�ditos",
	/* STR_IMPORTANT: */				"Importante",
	/* STR_LANGUAGE: */					"Idioma",
	/* STR_LANGUAGE_SELECT: */			"Seleccionar Idioma",
	/* STR_LEVEL: */					"Nivel",
	/* STR_LEVEL_CONQUERED: */			"�Nivel conquistado!",
	/* STR_LEVEL_DONE: */				"�Nivel completo!",
	/* STR_NEW_BEST: */					"Conjunto de r�cord",
	/* STR_NEW_GAME: */					"Nuevo Juego",
	/* STR_NO: */						"No",
	/* STR_OFF: */						"Apagado",
	/* STR_ON: */						"Encendido",
	/* STR_OPTIONS: */					"Opciones",
	/* STR_PAUSE: */					"Pausa",
	/* STR_PRESS_START_BUTTON: */		"Presionar Start",
	/* STR_PROGRESS_WILL_BE_ERASED: */	"Esto eliminar� todo tu progreso.",
	/* STR_QUIT_LEVEL: */				"Dejar De Nivel",
	/* STR_SELECT: */					"Seleccionar",
	/* STR_TAKE_A_REST: */				"�Por favor, t�mese un descanso!",
	/* STR_YES: */						"S�",

	/* Splash Screens */

	/* STR_PRECAUTION_SCREEN_TEXT: */	"     Lea los libros de\n\nInstrucciones y precauciones\n\n       antes de jugar",
	/* STR_AUTO_PAUSE_EXPLANATION: */	" La funci�n autom�tica de pausa le\nrecordar� que debe tomar un descanso\n  de jugar approx. cada 30 minutos",

	/* Levels */

	/* STR_LEVEL_1_NAME: */				"Woohoo Hills",
};

const LangROMDef LANGUAGE_ES =
{
	// Language Name
	"Espa�ol",

	// Strings
	(const char**)LANGUAGE_ES_STRINGS
};
