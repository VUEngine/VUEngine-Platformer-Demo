/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include "Gui.h"
#include <PlatformerLevelState.h>
#include <ProgressManager.h>
#include <EventManager.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Gui::printAll(Gui this);
static void Gui::onSecondChange(Gui this, Object eventFirer);
static void Gui::onHitTaken(Gui this, Object eventFirer);
static void Gui::onCoinTaken(Gui this, Object eventFirer);
static void Gui::onKeyTaken(Gui this, Object eventFirer);
static void Gui::onPowerUp(Gui this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern CharSetDefinition GUI_CH;
extern CharSetDefinition GUI_BANDANA_CH;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other



// class's constructor
void Gui::constructor(Gui this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntityDefinition, id, internalId, name);

	// add event listeners
	Object::addEventListener(__SAFE_CAST(Object, PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), __SAFE_CAST(Object, this), (EventListener)Gui::onSecondChange, kEventSecondChanged);
	Object::addEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::addEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui::onCoinTaken, kEventCoinTaken);
	Object::addEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui::onKeyTaken, kEventKeyTaken);
	Object::addEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui::onPowerUp, kEventPowerUp);
}

// class's destructor
void Gui::destructor(Gui this)
{
	// remove event listeners
	Object::removeEventListener(__SAFE_CAST(Object, PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), __SAFE_CAST(Object, this), (EventListener)Gui::onSecondChange, kEventSecondChanged);
	Object::removeEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::removeEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui::onCoinTaken, kEventCoinTaken);
	Object::removeEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui::onKeyTaken, kEventKeyTaken);
	Object::removeEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)Gui::onPowerUp, kEventPowerUp);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void Gui::ready(Gui this, bool recursive)
{
	ASSERT(this, "Gui::ready: null this");

	// call base
	Base::ready(this, recursive);
}

// print elapsed time to gui
void Gui::printClock(Gui this __attribute__ ((unused)))
{
	Clock::print(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()), GUI_X_POS + 36, GUI_Y_POS, GUI_FONT);
}

// print best time to gui
void Gui::printBestTime(Gui this __attribute__ ((unused)))
{
	u32 bestTime = ProgressManager::getCurrentLevelBestTime(ProgressManager::getInstance());

	if(bestTime)
	{
		Clock clock = __NEW(Clock);
		Clock::setTimeInMilliSeconds(clock, bestTime);
		Clock::print(clock, GUI_X_POS + 42, GUI_Y_POS + 1, NULL);
		__DELETE(clock);
	}
	else
	{
		Printing::text(Printing::getInstance(), "--:--", GUI_X_POS + 42, GUI_Y_POS + 1, NULL);
	}
}

// print number of coins to gui
void Gui::printCoins(Gui this __attribute__ ((unused)))
{
	u8 coins = ProgressManager::getCurrentLevelNumberOfCollectedCoins(ProgressManager::getInstance());

	// bound to 64
	if(coins > 64)
	{
		coins = 64;
	}

	// compute x position
	u8 printPos = GUI_X_POS + (coins >= 10) ? 11 : 12;

	// print
	Printing::text(Printing::getInstance(), "00/64", GUI_X_POS + 11, GUI_Y_POS, GUI_FONT);
	Printing::int(Printing::getInstance(), coins, printPos, GUI_Y_POS, GUI_FONT);
}

// print hero's energy to gui
void Gui::printEnergy(Gui this __attribute__ ((unused)))
{
	Printing::text(Printing::getInstance(), "\x7B\x7B\x7B", GUI_X_POS + 4, GUI_Y_POS, GUI_FONT);
	u8 i;
	ASSERT(Hero::getInstance(), "Gui::printEnergy: null hero");

	for(i=0; i < Hero::getEnergy(Hero::getInstance()); i++)
	{
		Printing::text(Printing::getInstance(), "\x60", GUI_X_POS + 4 + i, GUI_Y_POS, GUI_FONT);
	}
}

// print keys icon to gui
void Gui::printKey(Gui this __attribute__ ((unused)))
{
	if(Hero::hasKey(Hero::getInstance()))
	{
		Printing::text(Printing::getInstance(), "\x7E\x7F", GUI_X_POS + 21, GUI_Y_POS, GUI_FONT);
	}
	else
	{
		Printing::text(Printing::getInstance(), "  ", GUI_X_POS + 21, GUI_Y_POS, GUI_FONT);
	}
}

// print current level to gui
void Gui::printLevel(Gui this __attribute__ ((unused)))
{
	PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState::getCurrentLevelDefinition(PlatformerLevelState::getInstance());
	Printing::text(Printing::getInstance(), platformerLevelDefinition->identifier, GUI_X_POS + 29, GUI_Y_POS, GUI_FONT);
}

// update sprite, e.g. after collecting a power-up
void Gui::updateSprite(Gui this)
{
	CharSet charSet = Texture::getCharSet(Sprite::getTexture(__SAFE_CAST(Sprite, VirtualList::front(this->sprites))), true);

	CharSetDefinition* charSetDefinition = NULL;

	switch(Hero::getPowerUp(Hero::getInstance()))
	{
		case kPowerUpBandana:

			charSetDefinition = &GUI_BANDANA_CH;
			break;

		default:
		case kPowerUpNone:

			charSetDefinition = &GUI_CH;
			break;
	}

	CharSet::setCharSetDefinition(charSet, charSetDefinition);
	CharSet::rewrite(charSet);
}

// print current level to gui
void Gui::printAll(Gui this)
{
	// calls Gui::updateSprite, which modifies Sprites. These are not yet available in the entity's
	// construction phase, so we need to utilize the ready method.
	Gui::updateSprite(this);

	Gui::printClock(this);
	Gui::printBestTime(this);
	Gui::printCoins(this);
	Gui::printEnergy(this);
	Gui::printKey(this);
	Gui::printLevel(this);
}

// handle event
static void Gui::onSecondChange(Gui this, Object eventFirer __attribute__ ((unused)))
{
#ifdef __DEBUG_TOOLS
	if(!Game::isInSpecialMode(Game::getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!Game::isInSpecialMode(Game::getInstance()))
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game::isInSpecialMode(Game::getInstance()))
#endif

	Gui::printClock(this);
}

// handle event
static void Gui::onHitTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui::printEnergy(this);
}

// handle event
static void Gui::onCoinTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui::printCoins(this);
}

// handle event
static void Gui::onKeyTaken(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui::printKey(this);
}

// handle event
static void Gui::onPowerUp(Gui this, Object eventFirer __attribute__ ((unused)))
{
	Gui::updateSprite(this);
}

bool Gui::handlePropagatedMessage(Gui this, int message)
{
	ASSERT(this, "Gui::handlePropagatedMessage: null this");

	switch(message)
	{
		case kLevelSetUp:
		case kLevelResumed:

			Gui::printAll(this);
			break;
	}

	return false;
}
