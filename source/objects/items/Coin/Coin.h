/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef COIN_H_
#define COIN_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Collectable.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const CollectableSpec CoinSpec;
typedef const CoinSpec CoinROMSpec;

class Coin : Collectable
{
	void constructor(AnimatedEntitySpec* spec, int16 internalId, const char* const name);
	override void collect();
}


#endif
