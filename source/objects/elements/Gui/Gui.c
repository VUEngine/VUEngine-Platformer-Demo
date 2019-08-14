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
#include <Hero.h>
#include <EventManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern CharSetSpec GUI_CH;
extern CharSetSpec GUI_BANDANA_CH;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Gui::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, id, internalId, name);

	// add event listeners
	Object::addEventListener(Object::safeCast(PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), Object::safeCast(this), (EventListener)Gui::onSecondChange, kEventSecondChanged);
	Object::addEventListener(Object::safeCast(EventManager::getInstance()), Object::safeCast(this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::addEventListener(Object::safeCast(EventManager::getInstance()), Object::safeCast(this), (EventListener)Gui::onCoinTaken, kEventCoinTaken);
	Object::addEventListener(Object::safeCast(EventManager::getInstance()), Object::safeCast(this), (EventListener)Gui::onKeyTaken, kEventKeyTaken);
	Object::addEventListener(Object::safeCast(EventManager::getInstance()), Object::safeCast(this), (EventListener)Gui::onPowerUp, kEventPowerUp);
}

// class's destructor
void Gui::destructor()
{
	// remove event listeners
	Object::removeEventListener(Object::safeCast(PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), Object::safeCast(this), (EventListener)Gui::onSecondChange, kEventSecondChanged);
	Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)Gui::onHitTaken, kEventHitTaken);
	Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)Gui::onCoinTaken, kEventCoinTaken);
	Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)Gui::onKeyTaken, kEventKeyTaken);
	Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)Gui::onPowerUp, kEventPowerUp);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// print elapsed time to gui
void Gui::printClock()
{
	Clock::print(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()), GUI_X_POS + 36, GUI_Y_POS, GUI_TEXT_FONT);
}

// print best time to gui
void Gui::printBestTime()
{
	u32 bestTime = ProgressManager::getCurrentLevelBestTime(ProgressManager::getInstance());

	if(bestTime)
	{
		Clock clock = new Clock();
		Clock::setTimeInMilliSeconds(clock, bestTime);
		Clock::print(clock, GUI_X_POS + 42, GUI_Y_POS + 1, NULL);
		delete clock;
	}
	else
	{
		Printing::text(Printing::getInstance(), "--:--", GUI_X_POS + 42, GUI_Y_POS + 1, "Platformer");
	}
}

// print number of coins to gui
void Gui::printCoins()
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
	Printing::text(Printing::getInstance(), "00/64", GUI_X_POS + 11, GUI_Y_POS, GUI_TEXT_FONT);
	Printing::int(Printing::getInstance(), coins, printPos, GUI_Y_POS, GUI_TEXT_FONT);
}

// print hero's energy to gui
void Gui::printEnergy()
{
	Printing::text(Printing::getInstance(), "\x21\x21\x21", GUI_X_POS + 4, GUI_Y_POS, GUI_ICON_FONT);
	u8 i;
	ASSERT(Hero::getInstance(), "Gui::printEnergy: null hero");

	for(i=0; i < Hero::getEnergy(Hero::getInstance()); i++)
	{
		Printing::text(Printing::getInstance(), "\x22", GUI_X_POS + 4 + i, GUI_Y_POS, GUI_ICON_FONT);
	}
}

// print keys icon to gui
void Gui::printKey()
{
	if(Hero::hasKey(Hero::getInstance()))
	{
		Printing::text(Printing::getInstance(), "\x23\x24", GUI_X_POS + 21, GUI_Y_POS, GUI_ICON_FONT);
	}
	else
	{
		Printing::text(Printing::getInstance(), "  ", GUI_X_POS + 21, GUI_Y_POS, GUI_ICON_FONT);
	}
}

// print current level to gui
void Gui::printLevel()
{
	PlatformerLevelSpec* platformerLevelSpec = PlatformerLevelState::getCurrentLevelSpec(PlatformerLevelState::getInstance());
	Printing::text(Printing::getInstance(), platformerLevelSpec->identifier, GUI_X_POS + 29, GUI_Y_POS, GUI_TEXT_FONT);
}

// update sprite, e.g. after collecting a power-up
void Gui::updateSprite()
{
	CharSet charSet = Texture::getCharSet(Sprite::getTexture(Sprite::safeCast(VirtualList::front(this->sprites))), true);

	CharSetSpec* charSetSpec = NULL;

	switch(Hero::getPowerUp(Hero::getInstance()))
	{
		case kPowerUpBandana:

			charSetSpec = &GUI_BANDANA_CH;
			break;

		default:
		case kPowerUpNone:

			charSetSpec = &GUI_CH;
			break;
	}

	CharSet::setCharSetSpec(charSet, charSetSpec);
	CharSet::rewrite(charSet);
}

// print current level to gui
void Gui::printAll()
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
void Gui::onSecondChange(Object eventFirer __attribute__ ((unused)))
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
void Gui::onHitTaken(Object eventFirer __attribute__ ((unused)))
{
	Gui::printEnergy(this);
}

// handle event
void Gui::onCoinTaken(Object eventFirer __attribute__ ((unused)))
{
	Gui::printCoins(this);
}

// handle event
void Gui::onKeyTaken(Object eventFirer __attribute__ ((unused)))
{
	Gui::printKey(this);
}

// handle event
void Gui::onPowerUp(Object eventFirer __attribute__ ((unused)))
{
	Gui::updateSprite(this);
}

bool Gui::handlePropagatedMessage(int message)
{
	switch(message)
	{
		case kLevelSetUp:
		case kLevelResumed:

			Gui::printAll(this);
			break;
	}

	return false;
}
