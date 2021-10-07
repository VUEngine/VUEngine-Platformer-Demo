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

#include <PlatformerLevelState.h>
#include <Languages.h>
#include <SoundWrapper.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMSpec LEVEL_1_MAIN_MAIN_EP;

extern Sound SOUNDTRACK_01;

SoundROM* const LEVEL_1_SOUNDS[] =
{
	&SOUNDTRACK_01,
	NULL,
};

//---------------------------------------------------------------------------------------------------------
//												LEVEL DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerLevelROMSpec LEVEL_1_LV =
{
	// starting entry point
	(StageEntryPointSpec*)&LEVEL_1_MAIN_MAIN_EP,

	// id
	1,

	// identifier
	"1-1",

	// name
	(void*)STR_LEVEL_1_NAME,

	// slogan
	(void*)STR_LEVEL_1_SLOGAN,
};
