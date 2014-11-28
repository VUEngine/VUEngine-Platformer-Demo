/* VbJaEngine: bitmap graphics engine for the Nintendo Virtual Boy 
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


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include <Game.h>
#include <CollisionManager.h>
#include <GameWorld.h>
#include <MessageDispatcher.h>
#include <Screen.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>

#include <objects.h>
#include "Coin.h"

#include <GameLevel.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											 CLASS'S MACROS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// Coin.c

// A Coin!
__CLASS_DEFINITION(Coin); 

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// always call these to macros next to each other
__CLASS_NEW_DEFINITION(Coin, __PARAMETERS(AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID))
__CLASS_NEW_END(Coin, __ARGUMENTS(animatedInGameEntityDefinition, ID));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
void Coin_constructor(Coin this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, __ARGUMENTS(animatedInGameEntityDefinition, ID));

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), (Entity)this, kCuboid);

	// play spinning animation
	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Spin");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
void Coin_destructor(Coin this)
{
	// delete the super object
	__DESTROY_BASE(AnimatedInGameEntity);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// process a collision
u8 Coin_processCollision(Coin this, Telegram telegram) 
{
	Shape_setActive(this->shape, false);
	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Taken");
					


					
	int message = Telegram_getMessage(telegram);
	InGameEntity inGameEntity = (InGameEntity) Telegram_getExtraInfo(telegram);
	
	/*
	if((message == kCollision) && (InGameEntity_getInGameType(inGameEntity)) == kHero)) {
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Taken");
	}*/

	return false;
}
