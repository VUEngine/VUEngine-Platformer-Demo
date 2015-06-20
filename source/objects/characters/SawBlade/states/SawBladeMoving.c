/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------
#include <Game.h>
#include <InGameEntity.h>
#include <MessageDispatcher.h>
#include <Prototypes.h>

#include <EnemyDead.h>
#include <Hero.h>
#include <SawBlade.h>

#include "SawBladeMoving.h"
#include "SawBladeIdle.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void SawBladeMoving_constructor(SawBladeMoving this);
void SawBladeMoving_destructor(SawBladeMoving this);
void SawBladeMoving_enter(SawBladeMoving this, void* owner);
void SawBladeMoving_execute(SawBladeMoving this, void* owner);
void SawBladeMoving_exit(SawBladeMoving this, void* owner);
bool SawBladeMoving_handleMessage(SawBladeMoving this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(SawBladeMoving, State);
__SINGLETON(SawBladeMoving);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void SawBladeMoving_constructor(SawBladeMoving this)
{
	// construct base
	__CONSTRUCT_BASE();
}

// class's destructor
void SawBladeMoving_destructor(SawBladeMoving this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void SawBladeMoving_enter(SawBladeMoving this, void* owner)
{
	SawBlade_startMovement((SawBlade)owner);
	
	AnimatedInGameEntity_playAnimation(__GET_CAST(AnimatedInGameEntity, owner), "Spin");
}

// state's execute
void SawBladeMoving_execute(SawBladeMoving this, void* owner)
{	
	// if not waiting
	if(!Enemy_getActionTime((Enemy)owner))
    {
		// update movement
		SawBlade_move((SawBlade)owner);		
	}
	else
    {
		// if wait time elapsed
		if(SAW_BLADE_WAIT_DELAY < Clock_getTime(Game_getInGameClock(Game_getInstance())) - Enemy_getActionTime((Enemy)owner))
		{
			// start movement in opposite direction
			SawBlade_startMovement((SawBlade)owner);
		}
	}
	
}

// state's exit
void SawBladeMoving_exit(SawBladeMoving this, void* owner)
{
}

// state's on message
bool SawBladeMoving_handleMessage(SawBladeMoving this, void* owner, Telegram telegram)
{
	int message = Telegram_getMessage(telegram);

	switch(message)
    {
		case kCollision:
		{
			VirtualList collidingObjects = __GET_CAST(VirtualList, Telegram_getExtraInfo(telegram));
			ASSERT(collidingObjects, "SawBladeMoving::handleMessage: null collidingObjects");

			VirtualNode node = NULL;
			
			// this will place the shape in the owner's position
			for(node = VirtualList_begin(collidingObjects); node; node = VirtualNode_getNext(node))
            {
				InGameEntity inGameEntity = __GET_CAST(InGameEntity, VirtualNode_getData(node));
				
				switch(InGameEntity_getInGameType(inGameEntity))
                {
					case kHero:
					
						// ok, i hit him
						//Hero_takeHit((Hero)inGameEntity, Entity_getPosition(__GET_CAST(Entity, owner)));
						return true;
						break;
						
					case kSolid:
						
						return true;
						break;
				}
			}
		}
        break;
	}

	return false;
}