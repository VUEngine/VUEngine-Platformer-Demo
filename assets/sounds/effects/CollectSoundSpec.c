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


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


const uint16 JumpTrack[] =
{
  A_4, B_4, E_5, HOLD, ENDSOUND,
  80, 80, 80, 1, 1,
  15, 15, 15, 15 , 0,
};

SoundChannelConfigurationROM JumpSoundChannel1Configuration =
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
	0x01,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	SineWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM JumpSoundChannel1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&JumpSoundChannel1Configuration,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)JumpTrack
	}
};


SoundChannelROM* JumpSoundChannels[] =
{
	&JumpSoundChannel1,
	NULL
};

SoundROM JumpSound =
{
	/// Name
	"Collect sound",

	/// Play in loop
	false,

	/// Target timer resolution in us
	500,

	/// Tracks
	(SoundChannel**)JumpSoundChannels
};