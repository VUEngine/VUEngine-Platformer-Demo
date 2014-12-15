#ifndef CONFIG_H_
#define CONFIG_H_


//---------------------------------------------------------------------------------------------------------
// 							  VBJAENGINE'S CUSTOM CONFIGURATION
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											DEBUGGING
//---------------------------------------------------------------------------------------------------------

#define __DEBUG_TOOLS
#define __PRINT_FRAMERATE


//---------------------------------------------------------------------------------------------------------
// 											EDITORS
//---------------------------------------------------------------------------------------------------------

#define __STAGE_EDITOR
#define __ANIMATION_EDITOR


//---------------------------------------------------------------------------------------------------------
// 										OPTICS / PROJECTION
//---------------------------------------------------------------------------------------------------------

// screen width in pixels
#define __SCREEN_WIDTH							384

// screen height in pixels
#define __SCREEN_HEIGHT							224

// z position of the screen
#define __ZZERO									0

// game world limit to unload entities
#define __Z_GAME_LIMIT							__ZZERO - 30

// lower posible z coordinate
#define __ZLOWLIMIT 							-200

// distance from player's eyes to the virtual screen
#define __DISTANCE_EYE_SCREEN					384

// maximun view distance (deep)
#define __MAX_VIEW_DISTANCE						512
// always use a power of 2 as the maximun view distance, and update
// the number of bits to make projection faster
#define __MAX_VIEW_DISTANCE_POW					9

//distance between eyes
#define __BASE_FACTOR							768

// player's eyes's horizontal position
#define __HVPC									192

// player's eyes's vertical position
#define __VVPC									112

// zoom factor to distortoine zooming
#define __ZOOM_FACTOR							0.2f

// parallax values are divide by this factor to control it's strenght
#define __PARALLAX_CORRECTION_FACTOR			20


//---------------------------------------------------------------------------------------------------------
// 										FRAME RATE CONTROL
//---------------------------------------------------------------------------------------------------------

// determine whether frame rate is capped or not
#define __CAP_FPS						1

// clock resolution
#define __TIMER_RESOLUTION				10

// target frames per second
// must be a muliple of 50 to being able to use a timer resolution
// greater than 1
// if finer control is needed, change timer resolution to 1
#define __TARGET_FPS 					50

// target frames per second
#define __OPTIMUM_FPS 					__TARGET_FPS

// target frames per second
#define __MINIMUM_GOOD_FPS 				(__TARGET_FPS - 3)

#define __MILISECONDS_IN_SECOND			1000

// set animation delays as if they are 60 FPS,
// and multiply by this factor
#define __FPS_ANIM_FACTOR 	(__TARGET_FPS / (float)__OPTIMUM_FPS)

//seconds that must elapse to call rest state... in seconds (15 minutes)
#define __REST_DELAY 		900


//---------------------------------------------------------------------------------------------------------
// 										MEMORY POOL
//---------------------------------------------------------------------------------------------------------

#define __MEMORY_POOLS	9

//each block size
#define __BLOCK_512B 		512
#define __BLOCK_256B 		256
#define __BLOCK_192B 		192
#define __BLOCK_128B 		128
#define __BLOCK_100B 		100		// Used by images
#define __BLOCK_64B 		64		// Used mainly by Sprites
#define __BLOCK_48B 		48		// Used mainly by Telegrams
#define __BLOCK_32B 		32		// Used mainly by CharGroups
#define __BLOCK_28B 		28		// Virtual nodes are 24 bytes long so a 32b block is too much
#define __BLOCK_16B 		16
#define __POOL_512B_SIZE 	(__BLOCK_512B * 0)
#define __POOL_256B_SIZE 	(__BLOCK_256B * 0)
#define __POOL_192B_SIZE 	(__BLOCK_192B * 10)
#define __POOL_128B_SIZE 	(__BLOCK_128B * 24)
#define __POOL_100B_SIZE 	(__BLOCK_100B * 64)
#define __POOL_64B_SIZE 	(__BLOCK_64B * 32)
#define __POOL_48B_SIZE 	(__BLOCK_48B * 16)
#define __POOL_32B_SIZE 	(__BLOCK_32B * 64)
#define __POOL_28B_SIZE 	(__BLOCK_28B * 512)

#ifdef __DEBUG_TOOLS
#define __POOL_16B_SIZE 	(__BLOCK_16B * 512)
#else
#define __POOL_16B_SIZE 	(__BLOCK_16B * 128)
#endif

#define __MIN_BLOCK 		__BLOCK_16B


//---------------------------------------------------------------------------------------------------------
// 										CHAR MANAGEMENT
//---------------------------------------------------------------------------------------------------------

#define __CHAR_SEGMENTS					4

// number of chargroups per char segment
#define __CHAR_GRP_PER_SEG				32

// number of chargroups per char segment
#define __CHAR_SEGMENT_SIZE 			16

// number of chars per char segment
#define __CHAR_SEGMENT_TOTAL_CHARS 		512


//---------------------------------------------------------------------------------------------------------
// 										SPRITE MANAGEMENT
//---------------------------------------------------------------------------------------------------------

// basically the number of WORLDS
#define __TOTAL_LAYERS			32


//---------------------------------------------------------------------------------------------------------
// 										TEXTURE MANAGEMENT
//---------------------------------------------------------------------------------------------------------

//bgmaps to use (leave 2 bgmaps to allocate param table)
#define __NUM_BGMAPS 					10

//number of bgmap definitions in each bgmap segment
#define __NUM_MAPS_PER_SEG 				16

// printing area
#define __PRINTING_BGMAP 				(__NUM_BGMAPS + 1)
#define __PRINTING_BGMAP_X_OFFSET		0
#define __PRINTING_BGMAP_Y_OFFSET		5
#define __PRINTING_BGMAP_Z_OFFSET		__ZZERO
#define __PRINTABLE_BGMAP_AREA 			(64 * 28)

#define __PALLET_MASK					0x0600
#define __WORLD_LAYER_MASK				0x01F0
#define __SEGMENT_MASK					0x000F

#define __PALLET_MASK_DISP				0x09 /* 6 */
#define __WORLD_LAYER_MASK_DISP			0x04 /* 1 */
#define __SEGMENT_MASK_DISP				0x00 /* 0 */


//---------------------------------------------------------------------------------------------------------
// 										PARAM TABLE
//---------------------------------------------------------------------------------------------------------

// param table for affine and hbias render
#define __PARAMEND 					0x0003D7FF

// param table initial address
// To increase param table's size, decrease PARAMBase in libgccvb/video.h
#define __PARAMINI 					(PARAMBase)

// Number of the power of 2 to multiply by the number of rows of a given bgmap to allocate space
#define __PARAM_SPACE_FACTOR		1


//---------------------------------------------------------------------------------------------------------
// 										WORLD'S CAPACITY
//---------------------------------------------------------------------------------------------------------

// padd to determine if a character must be loaded/unloaded load pad must always be lower than unload pad!
#define __ENTITY_LOAD_PAD 			20
#define __ENTITY_UNLOAD_PAD 		30

// since there are 32 layers, that's the theoretical limit of entities to display
#define __STREAMING_AMPLITUDE		32

// number of sprites per entity
#define __MAX_SPRITES_PER_ENTITY 	4


//---------------------------------------------------------------------------------------------------------
// 										PHYSICS
//---------------------------------------------------------------------------------------------------------

// define it to make the collision system inform your entities if they can fall
#define __GRAVITY_WORLD

// physical friction
#define __NO_FRICTION 				0.0f
#define __FLOOR_FRICTION 			10.0f
#define __AIR_FRICTION 				50.0f

#define __GRAVITY					980

#define __MAX_SHAPES_PER_LEVEL		32
#define __MAX_BODIES_PER_LEVEL		32


//---------------------------------------------------------------------------------------------------------
// 										SOUND
//---------------------------------------------------------------------------------------------------------

// channels per bgms
#define __BGM_CHANNELS			2

// channels per fx
#define __FX_CHANNELS			1

// simultaneous bgms
#define __BGMS					1

// simultaneous fx
#define __FXS					2

#define __TOTAL_SOUNDS			(__BGMS + __FXS)
#define __LEFT_EAR_CENTER		96
#define __RIGHT_EAR_CENTER		288


//---------------------------------------------------------------------------------------------------------
// 										COLOR PALETS
//---------------------------------------------------------------------------------------------------------

#define __PRINTING_PALLETE		3

#define __GPLT0VALUE  			0xE4	/* Set all eight palettes to: 11100100 */
#define __GPLT1VALUE  			0xE0	/* (i.e. "Normal" dark to light progression.) */
#define __GPLT2VALUE  			0xF0
#define __GPLT3VALUE  			0xEA
#define __JPLT0VALUE  			0xE4
#define __JPLT1VALUE  			0xE4
#define __JPLT2VALUE  			0xE4
#define __JPLT3VALUE  			0xE4

#define	__BKCOL					0x00

#define __BRTA					0x00
#define __BRTB					0x00
#define __BRTC					0x00


//---------------------------------------------------------------------------------------------------------
// 										MISCELLANEOUS
//---------------------------------------------------------------------------------------------------------

#define __EXCEPTION_COLUMN	1
#define __EXCEPTION_LINE	0


#endif