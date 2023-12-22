/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef HINT_H_
#define HINT_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

enum HintTypes
{
	kEnterHint = 0,
	kPickUpHint,
	kTypeKeyHint
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class Hint : AnimatedEntity
{
	/* the current hint type to show */
	uint8 type;
	/* name of the animation to play */
	char* languageAnimName;

	void constructor(AnimatedEntitySpec* spec, int16 internalId, const char* const name);
	void open(uint8 hintType);
	void close();
	void onCloseDone(Object eventFirer);
	void onHintOpened(Object eventFirer);
	override void resume();
	override bool handleMessage(void* telegram);
}


#endif
