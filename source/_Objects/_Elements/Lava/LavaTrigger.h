/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LAVA_TRIGGER_H_
#define LAVA_TRIGGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef EntitySpec LavaTriggerSpec;
typedef const LavaTriggerSpec LavaTriggerROMSpec;

class LavaTrigger : Entity
{
	void constructor(EntitySpec* spec, int16 internalId, const char* const name);
	override bool handleMessage(Telegram telegram);
}


#endif
