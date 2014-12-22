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

#ifndef TITLE_SCREEN_STATE_H_
#define TITLE_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define TitleScreenState_METHODS										\
	GameState_METHODS;											    			\

// declare the virtual methods which are redefined
#define TitleScreenState_SET_VTABLE(ClassName)							\
	GameState_SET_VTABLE(ClassName)								    			\
	__VIRTUAL_SET(ClassName, TitleScreenState, enter);					\
	__VIRTUAL_SET(ClassName, TitleScreenState, exit);					\
	__VIRTUAL_SET(ClassName, TitleScreenState, execute);				\
	__VIRTUAL_SET(ClassName, TitleScreenState, handleMessage);			\


__CLASS(TitleScreenState);

#define TitleScreenState_ATTRIBUTES							        	\
														            			\
	/* inherits */																\
	GameState_ATTRIBUTES														\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

TitleScreenState TitleScreenState_getInstance(void);


#endif