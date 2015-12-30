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

#ifndef SAW_BLADE_IDLE_H_
#define SAW_BLADE_IDLE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <StateMachine.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define SawBladeIdle_METHODS									\
	State_METHODS;									

// declare the virtual methods which are redefined
#define SawBladeIdle_SET_VTABLE(ClassName)						\
State_SET_VTABLE(ClassName)										\
	__VIRTUAL_SET(ClassName, SawBladeIdle, enter);				\
	__VIRTUAL_SET(ClassName, SawBladeIdle, execute);			\
	__VIRTUAL_SET(ClassName, SawBladeIdle, exit);				\
	__VIRTUAL_SET(ClassName, SawBladeIdle, handleMessage);		\
	
__CLASS(SawBladeIdle);

#define SawBladeIdle_ATTRIBUTES									\
																\
	/* inherits */												\
	State_ATTRIBUTES


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

SawBladeIdle SawBladeIdle_getInstance();


#endif