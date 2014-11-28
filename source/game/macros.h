#ifndef MACROS_H_
#define MACROS_H_

//delay to don't allow the player to bypass logo's screen
#define SHOWDELAY	2000

/* */
#define FADE_DELAY		15

#define LAYER_INCREMENT					50
#define PLAYABLE_LAYER_INCREMENT		15
#define LAYER_0 0
#define PLAYABLE_LAYER_0 (LAYER_0 + PLAYABLE_LAYER_INCREMENT)
#define BACKGROUND_LAYER_0 (PLAYABLE_LAYER_0 + PLAYABLE_LAYER_INCREMENT)
#define LAYER_1 (LAYER_0 + LAYER_INCREMENT)
#define PLAYABLE_LAYER_1 (LAYER_1 + PLAYABLE_LAYER_INCREMENT)
#define BACKGROUND_LAYER_1 (PLAYABLE_LAYER_1 + PLAYABLE_LAYER_INCREMENT)
#define LAYER_2 (LAYER_1 + LAYER_INCREMENT)
#define PLAYABLE_LAYER_2 (LAYER_2 + PLAYABLE_LAYER_INCREMENT)
#define BACKGROUND_LAYER_2 (PLAYABLE_LAYER_2 + PLAYABLE_LAYER_INCREMENT)
#define LAYER_3 (LAYER_2 + LAYER_INCREMENT)
#define PLAYABLE_LAYER_3 (LAYER_3 + PLAYABLE_LAYER_INCREMENT)
#define BACKGROUND_LAYER_3 (PLAYABLE_LAYER_3 + PLAYABLE_LAYER_INCREMENT)
#define LAYER_4 (LAYER_3 + LAYER_INCREMENT)

#define TOTAL_GAME_LAYERS 	5


#define SCREEN_CENTER_X		384/2
#define SCREEN_CENTER_Y		224/2

#define DEAD_VELOCITY_Y			ITOFIX19_13(70)
#define DEAD_ACCELERATION_Y		ITOFIX19_13(10)
#define DEAD_VELOCITY_Z			ITOFIX19_13(20)
#define DEAD_ACCELERATION_Z		ITOFIX19_13(10)

enum HeroVbTypes{
	kHero = 1,
	kKoopa,
	kPiranhaPlant,
	kSawBlade,
	kSolid,
	kFloor,
	kGoal,
	kGate,
	kBridge,
	kCoin,
};


#define GAMEWORLD_MODES		4 

enum GameWorldModes {
	
	kPlaying = 1,
	kShowingUp,
	kSettingUp,
	kStartPlaying,
	kPaused,
	kMovingScreen,
	kMovingPerspective,
};

#endif /*MACROS_H_*/
