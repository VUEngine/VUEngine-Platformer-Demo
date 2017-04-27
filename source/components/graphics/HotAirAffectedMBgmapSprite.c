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


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HotAirAffectedMBgmapSprite.h>
#include <Optics.h>
#include <Screen.h>
#include <BgmapTexture.h>
#include <Game.h>
#include <Entity.h>
#include <ParamTableManager.h>
#include <debugConfig.h>


//---------------------------------------------------------------------------------------------------------
//											 CLASS' MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

/**
 * @class	HotAirAffectedMBgmapSprite
 * @extends BgmapSprite
 * @brief	Sprite which holds a texture and a drawing specification.
 */
__CLASS_DEFINITION(HotAirAffectedMBgmapSprite, MBgmapSprite);
__CLASS_FRIEND_DEFINITION(Texture);
__CLASS_FRIEND_DEFINITION(BgmapTexture);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

// globals
extern const VBVec3D* _screenPosition;
extern Optical* _optical;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(HotAirAffectedMBgmapSprite, const HotAirAffectedMBgmapSpriteDefinition* hotAirAffectedMBgmapSpriteDefinition, Object owner)
__CLASS_NEW_END(HotAirAffectedMBgmapSprite, hotAirAffectedMBgmapSpriteDefinition, owner);

/**
 * Class constructor
 *
 * @memberof							HotAirAffectedMBgmapSprite
 * @public
 *
 * @param this							Function scope
 * @param mBgmapSpriteDefinition		Definition to use
 * @param owner							Sprite's owner
 */
void HotAirAffectedMBgmapSprite_constructor(HotAirAffectedMBgmapSprite this, const HotAirAffectedMBgmapSpriteDefinition* hotAirAffectedMBgmapSpriteDefinition, Object owner)
{
	__CONSTRUCT_BASE(MBgmapSprite, (MBgmapSpriteDefinition*)hotAirAffectedMBgmapSpriteDefinition, owner);
}

/**
 * Class destructor
 *
 * @memberof		HotAirAffectedMBgmapSprite
 * @public
 *
 * @param this		Function scope
 */
void HotAirAffectedMBgmapSprite_destructor(HotAirAffectedMBgmapSprite this)
{
	ASSERT(this, "HotAirAffectedMBgmapSprite::destructor: null this");

	// destroy the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

/**
 * Write WORLD data to DRAM
 *
 * @memberof		HotAirAffectedMBgmapSprite
 * @public
 *
 * @param this		Function scope
 */
void HotAirAffectedMBgmapSprite_render(HotAirAffectedMBgmapSprite this)
{
	ASSERT(this, "HotAirAffectedMBgmapSprite::render: null this");

	MBgmapSprite_render(__SAFE_CAST(MBgmapSprite, this));

	static WorldAttributes* worldPointer = NULL;
	worldPointer = &_worldAttributesBaseAddress[this->worldLayer];
	worldPointer->head = __WORLD_OFF;
}
