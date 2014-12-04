
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

#ifndef COMMON_IMAGE_CHARS_H_
#define COMMON_IMAGE_CHARS_H_
/* This file must have an extern definition of every char */ 
/*---------------------------------INCLUDES--------------------------------*/
#include <libgccvb.h>
/*-------------------------------PROTOTYPES--------------------------------*/
extern const u16 FontTiles[];

extern BYTE PVB_LEFT_CH[];
extern BYTE PVB_RIGHT_CH[];
extern BYTE PRECAUTION_CH[];
extern BYTE VBJAE_LEFT_CH[];
extern BYTE VBJAE_RIGHT_CH[];
extern BYTE PVBCC_CHARSET_LEFT[];
extern BYTE PVBCC_CHARSET_RIGHT[];
extern BYTE PRECAUTION_CH[];

#endif /*COMMON_IMAGE_CHARS_H_*/


