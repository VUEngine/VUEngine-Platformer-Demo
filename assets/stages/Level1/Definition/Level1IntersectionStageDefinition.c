/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Stage.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <VIPManager.h>
#include <Fonts.h>
#include <Hero.h>

//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP;
extern BrightnessRepeatROMDef EDGE_FADE_OUT_BRIGHTNESS_REPEAT;
extern u16 KRISSE_BGM[][2];

extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition COLLISIONS_CONTAINER_ENTITY;

extern EntityDefinition COIN_AG;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition COLLISION_TOP_CL;
extern EntityDefinition DOOR_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition LEVEL_1_INTERSECTION_MAIN_IM;
extern EntityDefinition SAW_BLADE_H8_AC;
extern EntityDefinition TORCH_AG;
extern EntityDefinition TORCH_LIGHT_AG;

extern CharSetDefinition LEVEL_1_INTERSECTION_BACK_CH;
extern CharSetDefinition LEVEL_1_INTERSECTION_MAIN_BACK_CH;
extern CharSetDefinition LEVEL_1_INTERSECTION_MAIN_CH;

extern VBVec3D collision_2_28_1;
extern VBVec3D collision_7_2_1;
extern VBVec3D collision_14_18_1;
extern VBVec3D collision_28_8_1;
extern VBVec3D collision_48_2_1;


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_1_INTERSECTION_MAIN_ENTITIES[] =
{
	{&LEVEL_1_INTERSECTION_MAIN_IM,	{FTOFIX19_13(0), 	FTOFIX19_13(-16), 	FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_INTERSECTION_MAIN_COLLISIONS[] =
{
	// bottom floor
	{&COLLISION_CL,				{FTOFIX19_13(0),	FTOFIX19_13(72),	FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_2_1, false},
	// top ceiling
	{&COLLISION_CL,				{FTOFIX19_13(0),	FTOFIX19_13(-104),	FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_2_1, false},
	// right ceiling/floor
	{&COLLISION_CL,				{FTOFIX19_13(136),	FTOFIX19_13(24),	FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_14_18_1, false},
	// top left wall
	{&COLLISION_CL,				{FTOFIX19_13(-144), FTOFIX19_13(-72),	FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_28_8_1, false},
	// left ceiling/floor
	{&COLLISION_CL,				{FTOFIX19_13(-80),	FTOFIX19_13(-16),	FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_28_8_1, false},
	// top one way floor
	{&COLLISION_TOP_CL,			{FTOFIX19_13(56),	FTOFIX19_13(-40),	FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_7_2_1, false},
	// bottom one way floor
	{&COLLISION_TOP_CL,			{FTOFIX19_13(56),	FTOFIX19_13(16),	FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_7_2_1, false},
	// outermost left wall
	{&COLLISION_CL,				{FTOFIX19_13(-184), FTOFIX19_13(0),		FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_2_28_1, false},
	// outermost right wall
	{&COLLISION_CL,				{FTOFIX19_13(184),	FTOFIX19_13(0),		FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&collision_2_28_1, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_INTERSECTION_STAGE_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition

	{&MANAGED_ENTITY,				{FTOFIX19_13(192),	FTOFIX19_13(112),	FTOFIX19_13(LAYER_0 - 1.1f)}, 	0, NULL, (struct PositionedEntity*)LEVEL_1_INTERSECTION_MAIN_ENTITIES, NULL, false},
	{&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),	FTOFIX19_13(111),	FTOFIX19_13(LAYER_0)}, 	0, NULL, (struct PositionedEntity*)LEVEL_1_INTERSECTION_MAIN_COLLISIONS, NULL, false},

	{&HERO_AC,						{FTOFIX19_13(32),	FTOFIX19_13(159),	FTOFIX19_13(LAYER_0)}, 	0, HERO_NAME, NULL, NULL, false},

	{&DOOR_AG,						{FTOFIX19_13(176),	FTOFIX19_13(47),	FTOFIX19_13(LAYER_0_DOORS)}, 0, "UpperEntryDoor", NULL, NULL, false},

	{&TORCH_LIGHT_AG,				{FTOFIX19_13(200),	FTOFIX19_13(43),	FTOFIX19_13(0)}, 		0, NULL, NULL, NULL, false},
	{&TORCH_AG,						{FTOFIX19_13(200),	FTOFIX19_13(44),	FTOFIX19_13(LAYER_0)}, 	0, NULL, NULL, NULL, false},

	{&DOOR_AG,						{FTOFIX19_13(32),	FTOFIX19_13(159),	FTOFIX19_13(LAYER_0_DOORS)}, 0, "LowerEntryDoor", NULL, NULL, false},

	{&TORCH_LIGHT_AG,				{FTOFIX19_13(56),	FTOFIX19_13(155),	FTOFIX19_13(0)}, 		0, NULL, NULL, NULL, false},
	{&TORCH_AG,						{FTOFIX19_13(56),	FTOFIX19_13(156),	FTOFIX19_13(LAYER_0)}, 	0, NULL, NULL, NULL, false},

	{&SAW_BLADE_H8_AC,				{FTOFIX19_13(130),	FTOFIX19_13(174),	FTOFIX19_13(LAYER_0_ENEMIES)}, 0, NULL, NULL, NULL, false},

	{&TORCH_LIGHT_AG,				{FTOFIX19_13(200),	FTOFIX19_13(155),	FTOFIX19_13(0)}, 		0, NULL, NULL, NULL, false},
	{&TORCH_AG,						{FTOFIX19_13(200),	FTOFIX19_13(156),	FTOFIX19_13(LAYER_0)}, 	0, NULL, NULL, NULL, false},

	{&COIN_AG,						{FTOFIX19_13(240),	FTOFIX19_13(104),	FTOFIX19_13(LAYER_0_ITEMS)}, 46, NULL, NULL, NULL, false},
	{&COIN_AG,						{FTOFIX19_13(256),	FTOFIX19_13(104),	FTOFIX19_13(LAYER_0_ITEMS)}, 47, NULL, NULL, NULL, false},

	{&TORCH_LIGHT_AG,				{FTOFIX19_13(328),	FTOFIX19_13(43),	FTOFIX19_13(0)}, 		0, NULL, NULL, NULL, false},
	{&TORCH_AG,						{FTOFIX19_13(328),	FTOFIX19_13(44),	FTOFIX19_13(LAYER_0)}, 	0, NULL, NULL, NULL, false},
	{&DOOR_AG,						{FTOFIX19_13(352),	FTOFIX19_13(47),	FTOFIX19_13(LAYER_0_DOORS)}, 0, NULL, NULL, (void*)&LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_INTERSECTION_STAGE_ST_UI_CHILDREN[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(215), FTOFIX19_13(-4)}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const LEVEL_1_INTERSECTION_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMDef* const LEVEL_1_INTERSECTION_STAGE_ST_CHARSETS[] =
{
	&LEVEL_1_INTERSECTION_BACK_CH,
	&LEVEL_1_INTERSECTION_MAIN_BACK_CH,
	&LEVEL_1_INTERSECTION_MAIN_CH,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------



StageROMDef LEVEL_1_INTERSECTION_STAGE_ST =
{
	// level
	{
		// size
		{
			// x
			__SCREEN_WIDTH,
			// y
			__SCREEN_HEIGHT,
			// z
			__SCREEN_DEPTH,
		},

		// screen's initial position inside the game world
		{
			// x
			ITOFIX19_13(0),
			// y
			ITOFIX19_13(0),
			// z
			ITOFIX19_13(0)
		},
	},

	// streaming
	{
		// minimum free ms in the current game frame to allow streaming to quick in
		5,
		// load padding
		40,
		// unload padding
		16,
		// streaming amplitude
		24,
		// particle removal delay cycles
		0,
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		__TARGET_FPS / 10,

		// maximum number of texture's rows to write each time the texture writing is active
		12,

		// maximum number of rows to compute on each call to the affine functions
		16,

		// colors config
		{
			// background color
			__COLOR_BLACK,

			// brightness
			// these values times the repeat values specified in the column table (max. 16) make the final
			// brightness values on the respective regions of the screen. maximum brightness is 128.
			{
				// dark red
				2,
				// medium red
				4,
				// bright red
				8,
			},

			// brightness repeat
			(BrightnessRepeatDefinition*)&EDGE_FADE_OUT_BRIGHTNESS_REPEAT,
		},

		// palettes' config
		{
			{
				// bgmap palette 0
				__BGMAP_PALETTE_0,
				// bgmap palette 1
				__BGMAP_PALETTE_1,
				// bgmap palette 2
				__BGMAP_PALETTE_2,
				// bgmap palette 3
				__BGMAP_PALETTE_3,
			},
			{
				// object palette 0
				__OBJECT_PALETTE_0,
				// object palette 1
				__OBJECT_PALETTE_1,
				// object palette 2
				__OBJECT_PALETTE_2,
				// object palette 3
				__OBJECT_PALETTE_3,
			},
		},

		// bgmap segments configuration
		// number of segments reserved for the param table
		1,

		// obj segments sizes (must total 1024)
		{
			// __spt0
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt1
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt2
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt3
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
		},

		// obj segments z coordinates
		// Note that each SPT's z coordinate much be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
		{
			// __spt0
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt1
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt2
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt3
			FTOFIX19_13(LAYER_0_PARTICLES),
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			ITOFIX19_13(__DISTANCE_EYE_SCREEN),
			// distance from left to right eye (depth sensation)
			ITOFIX19_13(__BASE_FACTOR),
			// horizontal view point center
			ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
			// vertical view point center
			ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER),
		},
	},

	// physics
	{
		// gravity
		{
			ITOFIX19_13(0),
			ITOFIX19_13(__GRAVITY),
			ITOFIX19_13(0)
		},

		// friction
		FTOFIX19_13(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)LEVEL_1_INTERSECTION_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)LEVEL_1_INTERSECTION_STAGE_ST_CHARSETS,

		// textures to preload
		(StageTextureEntryDefinition*)NULL,

		// background music
		(const u16 (*)[])KRISSE_BGM,
	},

	// entities
	{
		// ui
		{
			LEVEL_1_INTERSECTION_STAGE_ST_UI_CHILDREN,
			__TYPE(UiContainer),
		},

		// children
		LEVEL_1_INTERSECTION_STAGE_ST_CHILDREN,
	},
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL_1_INTERSECTION_MAIN_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_INTERSECTION_STAGE_ST,

	// name of the entity to start at
	"UpperEntryDoor",

	// offset from entry point (x, y, z)
	{0, 0, FTOFIX19_13(-SORT_INCREMENT)},
};

StageEntryPointROMDef LEVEL_1_INTERSECTION_LOWER_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_INTERSECTION_STAGE_ST,

	// name of the entity to start at
	"LowerEntryDoor",

	// offset from entry point (x, y, z)
	{0, 0, FTOFIX19_13(-SORT_INCREMENT)},
};
