#ifndef __GameFunctions_H
#define __GameFunctions_H
/*******************************
Variables
*******************************/

//Game camera
camera cam;

//controls
u16 buttons;

/*********************************************
The map is a variable length array of bytes.
Byte 1 consists of a row type and a count of
objects. Each object is 3 bytes long. The next
entry will begin with a new row type and count.
The playable area is broken up into a cube of
16 sections/cells across each dimension. The x,y,z 
values are indexes to a cell of the cube.

Bytes:
Byte 1: LNibble = rowtype RNibble = Count
                  rowtypes: 0=empty,1=enemy,2=obstacle,3=help,4=friendly,5=boss
Byte 2: LNibble = x       RNibble = y
Byte 3: LNibble = z       RNibble = object number in corrisponding table
Byte 4: LNibble = pathNum RNibble = unused
**********************************************/
#define ROW_T_EMPTY    0x00  //A value of just zero means end of map. An empty row type with a count signifies an area with no objects
#define ROW_T_ENEMY    0x10
#define ROW_T_OBSTACLE 0x20
#define ROW_T_HELP     0x30
#define ROW_T_FRIENDLY 0x40
#define ROW_T_BOSS     0x50
typedef struct{
	u8* mapData;
} map;

/*******************************
Functions
*******************************/
/*********************************************************
System control functions
*********************************************************/
void screenControl();
void handleInput();
void vbInit();
void timeHnd(void);
/********************************************************/

/*********************************************************
Object functions
*********************************************************/
void initObjects();
void initEnemyTable();
void initObjectTable();

void setObjectRelative(object* o, object* parent);
void setObjectRelativeCamera(object* o);

void doMoveEnemy(object* o);
void doGroundEffects();
void doLaserFire(object* o, object* laser);
void doLevel1();
void doReadMapRow(map* m, u32 row);
/********************************************************/
void intro1();
void intro2();
void intro3();
void ending();

#endif
