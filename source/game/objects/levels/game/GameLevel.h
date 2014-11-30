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
#ifndef GAME_LEVEL_H_
#define GAME_LEVEL_H_

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
#define GameLevel_METHODS									\
	Level_METHODS;									

// declare the virtual methods which are redefined
#define GameLevel_SET_VTABLE(ClassName)						\
	Level_SET_VTABLE(ClassName)								\
	__VIRTUAL_SET(ClassName, GameLevel, enter);				\
	__VIRTUAL_SET(ClassName, GameLevel, execute);			\
	__VIRTUAL_SET(ClassName, GameLevel, exit);				\
	__VIRTUAL_SET(ClassName, GameLevel, pause);				\
	__VIRTUAL_SET(ClassName, GameLevel, resume);			\
	__VIRTUAL_SET(ClassName, GameLevel, handleMessage);		\


__CLASS(GameLevel);

#define GameLevel_ATTRIBUTES			\
										\
	/* inherits */						\
	Level_ATTRIBUTES					\
										\
	/* to allow moving the screen */	\
	u8 mode: 4;							\




enum GameLevelMessageTypes{
	
	kHeroDied = kLastEngineMessage + 1, // 16
	kHeroFall,
	kSetUpLevel,	//18
	kShowUpLevel,	//19
	kStartLevel,	// 20
	kHideStartUpMessage, //21
	kTakeCoin, //22
};

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 										PUBLIC INTERFACE
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// setup the init focus screen
GameLevel GameLevel_getInstance(void);

#endif /*GAME_LEVEL_H_*/
