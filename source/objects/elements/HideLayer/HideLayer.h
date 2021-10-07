/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef HIDE_LAYER_H_
#define HIDE_LAYER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define HIDE_LAYER_OVERLAPPING_CHECK_DELAY	100


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const AnimatedEntitySpec HideLayerSpec;
typedef const HideLayerSpec HideLayerROMSpec;

class HideLayer : AnimatedEntity
{
	/* is hide layer currently being overlapped by hero? */
	bool currentlyOverlappingHero;

	void constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name);
	void setOverlapping();
	void unsetOverlapping();
}


#endif
