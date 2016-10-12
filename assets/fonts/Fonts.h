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

#ifndef FONTS_H_
#define FONTS_H_


//---------------------------------------------------------------------------------------------------------
// 											  INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Printing.h>
#include <CharSet.h>


//---------------------------------------------------------------------------------------------------------
// 											  DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern CharSetDefinition PLATFORMER_DEFAULT_FONT_CH;
extern CharSetDefinition PLATFORMER_GUI_FONT_CH;
extern CharSetDefinition PLATFORMER_LARGE_FONT_CH;

extern FontDefinition PLATFORMER_DEFAULT_FONT;
extern FontDefinition PLATFORMER_GUI_FONT;
extern FontDefinition PLATFORMER_LARGE_FONT;


#endif
