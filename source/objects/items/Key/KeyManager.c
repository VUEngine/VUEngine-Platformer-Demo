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

#include <KeyManager.h>
#include <Key.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

#define KeyManager_ATTRIBUTES													\
																				\
	/* super's attributes */													\
	Object_ATTRIBUTES;															\
																				\
	/* allocated sprites */														\
	VirtualList keys;															\

__CLASS_DEFINITION(KeyManager, Object);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

// class constructor 
static void KeyManager_constructor(KeyManager this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// a singleton
__SINGLETON(KeyManager);

//class constructor
static void KeyManager_constructor(KeyManager this)
{
	__CONSTRUCT_BASE();

	this->keys = __NEW(VirtualList);
}

// class destructor
void KeyManager_destructor(KeyManager this)
{
	ASSERT(this, "KeyManager::destructor: null this");

	if(this->keys)
	{
		__DELETE(this->keys);
		
		this->keys = NULL;
	}
	
	// allow a new construct
	__SINGLETON_DESTROY;
}

// register key
void KeyManager_registerKey(KeyManager this, Key key)
{
	ASSERT(this, "KeyManager::registerKey: null this");

	if(!VirtualList_find(this->keys, key))
	{
		Key firstKey = (Key)VirtualList_back(this->keys);
		
		if(firstKey)
		{
			VirtualList firstKeySprites = Entity_getSprites(__UPCAST(Entity, firstKey));
			
			AnimatedSprite firstKeySprite = __UPCAST(AnimatedSprite, VirtualList_front(firstKeySprites));
	
			if(firstKeySprite)
			{			
				s8 currentFrame = AnimatedSprite_getActualFrame(firstKeySprite);
				s8 frameDelay = AnimatedSprite_getFrameDelay(firstKeySprite);
				
				VirtualList keySprites = Entity_getSprites(__UPCAST(Entity, key));
				
				VirtualNode node = VirtualList_begin(keySprites);
				
				
				for (; node; node = VirtualNode_getNext(node))
				{
					AnimatedSprite keySprite = __UPCAST(AnimatedSprite, VirtualNode_getData(node));
					AnimatedSprite_setActualFrame(keySprite, currentFrame);
					AnimatedSprite_setFrameDelay(keySprite, frameDelay);
	 			}
			}
		}
		
		VirtualList_pushBack(this->keys, key);
	}
}

// remove key
void KeyManager_removeKey(KeyManager this, Key key)
{
	ASSERT(this, "KeyManager::removeKey: null this");

	VirtualList_removeElement(this->keys, key);
}