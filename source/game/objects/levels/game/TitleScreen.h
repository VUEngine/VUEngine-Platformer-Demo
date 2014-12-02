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
#ifndef TITLE_SCREEN_H_
#define TITLE_SCREEN_H_

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include <Level.h>

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DECLARATION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// declare the virtual methods
#define TitleScreen_METHODS										\
	Level_METHODS;												\
	__VIRTUAL_DEC(update);					\

// declare the virtual methods which are redefined
#define TitleScreen_SET_VTABLE(ClassName)						\
	Level_SET_VTABLE(ClassName)									\
	__VIRTUAL_SET(ClassName, TitleScreen, enter);				\
	__VIRTUAL_SET(ClassName, TitleScreen, exit);				\
	__VIRTUAL_SET(ClassName, TitleScreen, update);				\
	__VIRTUAL_SET(ClassName, TitleScreen, handleMessage);		\


__CLASS(TitleScreen);

#define TitleScreen_ATTRIBUTES			\
										\
	/* inherits */						\
	Level_ATTRIBUTES					\
										\
	/* to allow moving the screen */	\
	u8 mode: 4;							\
	u32 lastTime;



/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 										PUBLIC INTERFACE
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// setup the init focus screen
TitleScreen TitleScreen_getInstance(void);


#endif /*TITLE_SCREEN_H_*/
