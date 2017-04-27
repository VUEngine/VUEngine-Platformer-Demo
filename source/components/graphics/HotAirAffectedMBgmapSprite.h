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

#ifndef HOT_AIR_AFFECTED_M_BGMAP_SPRITE_H_
#define HOT_AIR_AFFECTED_M_BGMAP_SPRITE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HotAirAffectedMBgmapSprite_METHODS(ClassName)													\
		MBgmapSprite_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define HotAirAffectedMBgmapSprite_SET_VTABLE(ClassName)												\
		MBgmapSprite_SET_VTABLE(ClassName)																\
		__VIRTUAL_SET(ClassName, HotAirAffectedMBgmapSprite, render);											\

#define HotAirAffectedMBgmapSprite_ATTRIBUTES															\
		MBgmapSprite_ATTRIBUTES																			\

__CLASS(HotAirAffectedMBgmapSprite);

typedef MBgmapSpriteDefinition HotAirAffectedMBgmapSpriteDefinition;
typedef const HotAirAffectedMBgmapSpriteDefinition HotAirAffectedMBgmapSpriteROMDef;


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(HotAirAffectedMBgmapSprite, const HotAirAffectedMBgmapSpriteDefinition* hotAirAffectedMBgmapSpriteDefinition, Object);

void HotAirAffectedMBgmapSprite_constructor(HotAirAffectedMBgmapSprite this, const HotAirAffectedMBgmapSpriteDefinition* hotAirAffectedMBgmapSpriteDefinition, Object owner);
void HotAirAffectedMBgmapSprite_destructor(HotAirAffectedMBgmapSprite this);
void HotAirAffectedMBgmapSprite_render(HotAirAffectedMBgmapSprite this);


#endif
