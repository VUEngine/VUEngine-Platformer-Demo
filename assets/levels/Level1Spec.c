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

extern StageEntryPointROMSpec Level1MainMainEntryPoint;

extern Sound Soundtrack01;

SoundROM* const Level1Sounds[] =
{
	&Soundtrack01,
	NULL,
};

//---------------------------------------------------------------------------------------------------------
//												LEVEL DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerLevelROMSpec Level1 =
{
	// starting entry point
	(StageEntryPointSpec*)&Level1MainMainEntryPoint,

	// id
	1,

	// identifier
	"1-1",

	// name
	(void*)kStringLevel1Name,

	// slogan
	(void*)kStringLevel1Slogan,
};
