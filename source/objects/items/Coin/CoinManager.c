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

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <CoinManager.h>
#include <Coin.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

#define CoinManager_ATTRIBUTES													\
																				\
	/* super's attributes */													\
	Object_ATTRIBUTES;															\
																				\
	/* allocated sprites */														\
	VirtualList coins;															\

__CLASS_DEFINITION(CoinManager, Object);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

// class constructor 
static void CoinManager_constructor(CoinManager this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// a singleton
__SINGLETON(CoinManager);

//class constructor
static void CoinManager_constructor(CoinManager this)
{
	ASSERT(this, "CoinManager::constructor: null this");

	__CONSTRUCT_BASE();

	this->coins = __NEW(VirtualList);
}

// class destructor
void CoinManager_destructor(CoinManager this)
{
	ASSERT(this, "CoinManager::destructor: null this");

	if(this->coins) 
	{
		__DELETE(this->coins);
		
		this->coins = NULL;
	}
	
	// allow a new construct
	__SINGLETON_DESTROY;
}

// register coin
void CoinManager_registerCoin(CoinManager this, Coin coin)
{
	ASSERT(this, "CoinManager::registerCoin: null this");

	if(!VirtualList_find(this->coins, coin))
	{
		Coin firstCoin = (Coin)VirtualList_back(this->coins);
		
		if(firstCoin)
		{
			VirtualList firstCoinSprites = Entity_getSprites(__UPCAST(Entity, firstCoin));
			
			Sprite firstCoinSprite = __UPCAST(Sprite, VirtualList_front(firstCoinSprites));
	
			if(firstCoinSprite) 
			{			
				s8 currentFrame = Sprite_getActualFrame(firstCoinSprite);
				s8 frameDelay = Sprite_getFrameDelay(firstCoinSprite);
				
				VirtualList coinSprites = Entity_getSprites(__UPCAST(Entity, coin));
				
				VirtualNode node = VirtualList_begin(coinSprites);
				
				for (; node; node = VirtualNode_getNext(node))
				{
					Sprite coinSprite = __UPCAST(Sprite, VirtualNode_getData(node));
					Sprite_setActualFrame(coinSprite, currentFrame);
					Sprite_setFrameDelay(coinSprite, frameDelay);
	 			}
			}
		}
		
		VirtualList_pushBack(this->coins, coin);
	}
}

// remove coin
void CoinManager_removeCoin(CoinManager this, Coin coin)
{
	ASSERT(this, "CoinManager::removeCoin: null this");

	VirtualList_removeElement(this->coins, coin);
}