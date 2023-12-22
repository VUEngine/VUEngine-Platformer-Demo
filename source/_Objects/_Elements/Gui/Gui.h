/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef GUI_H_
#define GUI_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define GUI_ICON_FONT	"PlatformerGui"
#define GUI_TEXT_FONT	"AstonishS"
#define GUI_X_POS		0
#define GUI_Y_POS		26


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class Gui : AnimatedEntity
{
	void constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name);
	void printClock();
	void printBestTime();
	void printCoins();
	void printEnergy();
	void printKey();
	void printLevel();
	void printAll();
	override bool handlePropagatedMessage(int message);
}


#endif
