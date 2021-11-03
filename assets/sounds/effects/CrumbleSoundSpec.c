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

#include <SoundManager.h>
#include <WaveForms.h>
#include <WaveForms.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


const uint16 CrumbleTrack[] =
{
  A_4, B_4, E_5, HOLD, A_4, B_4, E_5, HOLD, A_4, B_4, E_5, HOLD, ENDSOUND,
  100, 80, 100, 1, 100, 80, 100, 1, 100, 80, 100, 1, 1,
  15, 15, 15, 15 , 15, 15, 15, 15 , 15, 15, 15, 15 , 0,
  1, 4, 1, 2 , 1, 4, 1, 2 , 1, 4, 1, 2 , 0
};

SoundChannelConfigurationROM CRUMBLE_SND_CHANNEL_1_CONFIGURATION =
{
	/// kMIDI, kPCM
	kMIDI,

	/// SxINT
	0x9F,

	/// Volume SxLRV
	0xFF,

	/// SxRAM (this is overrode by the SoundManager)
	0x00,

	/// SxEV0
	0x80,

	/// SxEV1
	0x00,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	SawtoothWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNoise,

	/// Volume
	__SOUND_LR
};

SoundChannelROM CRUMBLE_SND_CHANNEL_1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&CRUMBLE_SND_CHANNEL_1_CONFIGURATION,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)CrumbleTrack
	}
};


SoundChannelROM* CRUMBLE_SND_CHANNELS[] =
{
	&CRUMBLE_SND_CHANNEL_1,
	NULL
};

SoundROM CRUMBLE_SND =
{
	/// Name
	"Fire sound",

	/// Play in loop
	false,

	/// Target timer resolution in us
	5000,

	/// Tracks
	(SoundChannel**)CRUMBLE_SND_CHANNELS
};