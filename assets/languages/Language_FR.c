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

const char* const LANGUAGE_FR_STRINGS[] =
{
	/* General */

	/* STR_ARE_YOU_SURE */				"Es tu s�r?",
	/* STR_AUTOMATIC_PAUSE */			"Pause Automatique",
	/* STR_BACK */						"Arri�re",
	/* STR_CONTINUE */					"Continuer",
	/* STR_CREDITS */					"Cr�dits",
	/* STR_IMPORTANT */					"Important",
	/* STR_LANGUAGE */					"Langue",
	/* STR_LANGUAGE_SELECT */			"Choix de la langue",
	/* STR_LEVEL */						"Niveau",
	/* STR_LEVEL_CONQUERED */			"Niveau conquis!",
	/* STR_LEVEL_DONE */				"Niveau termin�!",
	/* STR_NEW_BEST */					"Set Record!",
	/* STR_NEW_GAME */					"Nouveau Jeu",
	/* STR_NO */						"Non",
	/* STR_OFF */						"Desactiv�",
	/* STR_ON */						"Activ�",
	/* STR_OPTIONS */					"Options",
	/* STR_PAUSE */						"Pause",
	/* STR_PRESS_START_BUTTON */		"Appuyer sur Start",
	/* STR_PROGRESS_WILL_BE_ERASED */	"Tout v�tre progr�s sera effac�.",
	/* STR_QUIT_LEVEL */				"Quitter Niveau",
	/* STR_SELECT */					"S�lectionner",
	/* STR_TAKE_A_REST */				"Se il vous pla�t, prendre un repos!",
	/* STR_YES */						"Oui",

	/* Splash Screens */

	/* STR_PRECAUTION_SCREEN_TEXT */	"Prenez conaissance de la\n\nnotice et des pr�cautions\n\na prendre avant de jouer",
	/* STR_AUTO_PAUSE_EXPLANATION */	"  La fonction Pause automatique va\nvous rappelerez de prendre une pause\n  de jeu chaque 30 minutes environ",

	/* Levels */

	/* STR_LEVEL_1_NAME */				"Woohoo Hills",
};

const LangROMDef LANGUAGE_FR =
{
	// Language Name
	"Fran�ais",

	// Strings
	(const char**)LANGUAGE_FR_STRINGS
};
