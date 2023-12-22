/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef TEST_COG_WHEEL_H_
#define TEST_COG_WHEEL_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define COG_WHEEL_ROTATION_DELAY 200


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const EntitySpec TestCogWheelSpec;
typedef const TestCogWheelSpec TestCogWheelROMSpec;

class TestCogWheel : Entity
{
	void constructor(EntitySpec* spec, int16 internalId, const char* const name);
	override void ready(bool recursive);
	override bool handleMessage(Telegram telegram);
}


#endif
