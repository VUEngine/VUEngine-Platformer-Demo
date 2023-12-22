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
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------


const uint16 Soundtrack01Track1[] =
{
	PAU, PAU, PAU, PAU, F_4, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, C_4, PAU, PAU, PAU, F_4, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, C_4, PAU, PAU, PAU, F_4, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, PAU, ENDSOUND,
	30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

const uint16 Soundtrack01Track2[] =
{
	PAU, PAU, PAU, PAU, F_5, PAU, PAU, D_4, F_6, PAU, E_3, F_5, PAU, C_4, F_6, PAU, F_5, PAU, C_4, PAU, F_5, PAU, PAU, D_4, F_6, PAU, E_4, F_5, PAU, C_4, F_6, PAU, F_5, PAU, C_4, PAU, F_6, F_5, PAU, D_4, PAU, PAU, E_4, PAU, PAU, C_4, PAU, PAU, C_4, PAU, C_4, PAU, F_4, PAU, PAU, D_4, PAU, PAU, E_4, PAU, PAU, C_4, PAU, PAU, C_4, PAU, C_4, PAU, ENDSOUND,
	30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

SoundChannelConfigurationROM Soundtrack01Channel1Configuration =
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
	0x30,

	/// SxEV1
	0x01,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	PianoWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelConfigurationROM Soundtrack01Channel2Configuration =
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
	0x30,

	/// SxEV1
	0x01,

	/// SxFQH
	0x00,

	/// SxFQL
	0x00,

	/// Ch. 5 only
	0x00,

	/// Waveform data pointer
	ViolinWaveForm,

	/// kChannelNormal, kChannelModulation, kChannelNoise
	kChannelNormal,

	/// Volume
	__SOUND_LR
};

SoundChannelROM Soundtrack01Channel1 =
{
	/// Configuration
	(SoundChannelConfiguration*)&Soundtrack01Channel1Configuration,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)Soundtrack01Track1
	}
};


SoundChannelROM Soundtrack01Channel2 =
{
	/// Configuration
	(SoundChannelConfiguration*)&Soundtrack01Channel2Configuration,

	/// Length (PCM)
	0,

	/// Sound track
	{
		(const uint8*)Soundtrack01Track2
	}
};

SoundChannelROM* Soundtrack01Channels[] =
{
	&Soundtrack01Channel1,
	&Soundtrack01Channel2,
	NULL
};

SoundROMSpec Soundtrack01 =
{
	/// Name
	"some soundtrack",

	/// Play in loop
	true,

	/// Target timer resolution in us
	5000,

	/// Tracks
	(SoundChannel**)Soundtrack01Channels
};