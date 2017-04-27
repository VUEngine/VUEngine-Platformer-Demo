/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef HOT_AIR_M_BGMAP_SPRITE_H_
#define HOT_AIR_M_BGMAP_SPRITE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HotAirMBgmapSprite_METHODS(ClassName)															\
		MBgmapSprite_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define HotAirMBgmapSprite_SET_VTABLE(ClassName)														\
		MBgmapSprite_SET_VTABLE(ClassName)																\
		__VIRTUAL_SET(ClassName, HotAirMBgmapSprite, render);											\

#define HotAirMBgmapSprite_ATTRIBUTES																	\
		MBgmapSprite_ATTRIBUTES																			\
		/**
		 * @var Sprite 					lavaSprite
		 * @brief						sprite to follow
		 * @memberof 					HotAirMBgmapSprite
		 */																								\
		Sprite lavaSprite;																				\
		/**
		 * @var Sprite 					sprite
		 * @brief						reference Sprite
		 * @memberof 					HotAirMBgmapSprite
		 */																								\
		Sprite referenceSprite;																			\
		/**
		 * @var Sprite 					sprite
		 * @brief						reference Sprite
		 * @memberof 					HotAirMBgmapSprite
		 */																								\
		const HotAirMBgmapSpriteDefinition* hotAirMBgmapSpriteDefinition;

__CLASS(HotAirMBgmapSprite);

typedef struct HotAirMBgmapSpriteDefinition
{
	// super class definition
	MBgmapSpriteDefinition mBgmapSpriteDefinition;

	// name of the owner of the reference sprite
	char* referenceSpriteOwnerName;

} HotAirMBgmapSpriteDefinition;

typedef const HotAirMBgmapSpriteDefinition HotAirMBgmapSpriteROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(HotAirMBgmapSprite, const HotAirMBgmapSpriteDefinition* hotAirMBgmapSpriteDefinition, Object);

void HotAirMBgmapSprite_constructor(HotAirMBgmapSprite this, const HotAirMBgmapSpriteDefinition* hotAirMBgmapSpriteDefinition, Object owner);
void HotAirMBgmapSprite_destructor(HotAirMBgmapSprite this);
void HotAirMBgmapSprite_render(HotAirMBgmapSprite this);
s16 HotAirMBgmapSprite_lavaHotAir(HotAirMBgmapSprite this);


#endif
