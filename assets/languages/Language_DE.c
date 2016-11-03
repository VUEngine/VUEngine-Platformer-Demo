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
 * form part of a valid UTF-8 byte sequence: £
 */

const char* const LANGUAGE_DE_STRINGS[] =
{
	/* General */

	/* STR_ARE_YOU_SURE */				"Bist Du sicher?",
	/* STR_AUTOMATIC_PAUSE */			"Automatische Pause",
	/* STR_BACK */						"Zurück",
	/* STR_CONTINUE */					"Fortsetzen",
	/* STR_CREDITS */					"Mitwirkende",
	/* STR_IMPORTANT */					"Wichtig",
	/* STR_LANGUAGE */					"Sprache",
	/* STR_LANGUAGE_SELECT */			"Sprachauswahl",
	/* STR_LEVEL */						"Level",
	/* STR_LEVEL_CONQUERED */			"Level gemeistert!",
	/* STR_LEVEL_DONE */				"Level geschafft!",
	/* STR_NEW_BEST */					"Neue Bestleistung!",
	/* STR_NEW_GAME */					"Neues Spiel",
	/* STR_NO */						"Nein",
	/* STR_OFF */						"Aus",
	/* STR_ON */						"An",
	/* STR_OPTIONS */					"Optionen",
	/* STR_PAUSE */						"Pause",
	/* STR_PRESS_START_BUTTON */		"Start-Knopf drücken",
	/* STR_PROGRESS_WILL_BE_ERASED */	"Dein kompletter Fortschritt wird gelöscht.",
	/* STR_QUIT_LEVEL */				"Level beenden",
	/* STR_SELECT */					"Auswählen",
	/* STR_TAKE_A_REST */				"Bitte mache eine Pause!",
	/* STR_YES */						"Ja",

	/* Splash Screens */

	/* STR_PRECAUTION_SCREEN_TEXT */	"   Lesen Sie vor dem\n\n Spielen die Anleitung\n\nund Sicherheitshinweise",
	/* STR_AUTO_PAUSE_EXPLANATION */	" Die Automatische Pause Funktion\nerinnert dich daran, das Spiel ca.\n  alle 30 Minuten zu pausieren",

	/* Levels */

	/* STR_LEVEL_1_NAME */				"Woohoo-Berge",
};

const LangROMDef LANGUAGE_DE =
{
	// Language Name
	"Deutsch",

	// Strings
	(const char**)LANGUAGE_DE_STRINGS
};

