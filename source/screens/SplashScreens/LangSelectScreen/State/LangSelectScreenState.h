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

#ifndef LANGUAGE_SELECTION_SCREEN_STATE_H_
#define LANGUAGE_SELECTION_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SplashScreenState.h>
#include <OptionsSelector.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define LangSelectScreenState_METHODS											\
	SplashScreenState_METHODS;							    					\

// declare the virtual methods which are redefined
#define LangSelectScreenState_SET_VTABLE(ClassName)								\
	SplashScreenState_SET_VTABLE(ClassName)				    					\
	__VIRTUAL_SET(ClassName, LangSelectScreenState, print);						\
	__VIRTUAL_SET(ClassName, LangSelectScreenState, processInput);				\

__CLASS(LangSelectScreenState);

#define LangSelectScreenState_ATTRIBUTES										\
														            			\
	/* inherits */																\
	SplashScreenState_ATTRIBUTES												\
																				\
	OptionsSelector languageSelector;											\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

LangSelectScreenState LangSelectScreenState_getInstance(void);


#endif