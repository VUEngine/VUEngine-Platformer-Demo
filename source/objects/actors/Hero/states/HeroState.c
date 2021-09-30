/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "HeroState.h"
#include <VirtualList.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HeroState::constructor()
{
	// construct base
	Base::constructor();
}

// class's destructor
void HeroState::destructor()
{
	// destroy base
	Base::destructor();
}

void HeroState::onKeyHold(void* owner __attribute__ ((unused)), const UserInput* userInput __attribute__ ((unused)))
{
}
