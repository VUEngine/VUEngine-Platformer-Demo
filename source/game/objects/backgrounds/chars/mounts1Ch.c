#include <libgccvb.h>
const BYTE MOUNTS1_CH[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x40,0x00,0x90,0x00,0x24,	/*Char0*/
	0x00,0x00,0x00,0x55,0x50,0xa9,0x54,0x55,
	0x55,0x55,0xff,0xff,0x55,0x55,0x56,0x55,	/*Char1*/
	0x55,0x55,0x55,0x55,0xaa,0xaa,0x55,0x55,
	0x55,0x55,0xbf,0xaa,0x55,0x55,0x55,0x55,	/*Char2*/
	0x00,0x00,0x55,0x00,0x6a,0x01,0x55,0x15,
	0x55,0x55,0xfa,0xff,0x55,0x55,0x55,0x55,	/*Char3*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x01,0x40,0x05,0x90,0x15,0x24,	/*Char4*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x01,0x00,0x05,0x00,0x15,0x00,	/*Char5*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,	/*Char6*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,	/*Char7*/
	0x00,0xf4,0x00,0x25,0x00,0x89,0x00,0xfd,
	0x00,0x89,0x01,0x25,0x05,0x89,0x15,0x25,	/*Char8*/
	0xff,0xbf,0x56,0x55,0x55,0x55,0xff,0xae,
	0x55,0x55,0x56,0x55,0x55,0x55,0x56,0x55,	/*Char9*/
	0xab,0xaa,0x55,0x55,0x55,0x55,0xaa,0xaa,
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,	/*Char10*/
	0xaa,0xfa,0x55,0x55,0x55,0x55,0xaa,0xaa,
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,	/*Char11*/
	0x1f,0xf4,0x55,0x25,0x55,0x89,0x7f,0xfd,
	0x55,0x89,0x55,0x25,0x55,0x89,0x55,0x25,	/*Char12*/
	0x1f,0x00,0x55,0x00,0x55,0x00,0x7f,0x40,
	0x55,0x90,0x55,0x24,0x55,0xf4,0x55,0x25,	/*Char13*/
	0x50,0xa9,0x54,0x55,0x55,0x55,0xff,0xff,
	0x55,0x55,0x56,0x55,0xff,0xbf,0x56,0x55,	/*Char14*/
	0xaa,0xaa,0x55,0x55,0x55,0x55,0xbf,0xaa,
	0x55,0x55,0x55,0x55,0xab,0xaa,0x55,0x55,	/*Char15*/
	0x6a,0x01,0x55,0x15,0x55,0x55,0xfa,0xff,
	0x55,0x55,0x55,0x55,0xaa,0xfa,0x55,0x55,	/*Char16*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,
	0x05,0x00,0x15,0x00,0x1f,0x00,0x55,0x00,	/*Char17*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,
	0x00,0x54,0x00,0x55,0x40,0xff,0x90,0x55,	/*Char18*/
	0x00,0x00,0x00,0x55,0x55,0x55,0xa9,0xaa,
	0x55,0x55,0x55,0x55,0xff,0xbf,0x55,0x55,	/*Char19*/
	0x00,0x00,0x55,0x00,0x55,0x55,0xaa,0x6a,
	0x55,0x55,0x55,0x55,0xaa,0xfa,0x55,0x55,	/*Char20*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,
	0x15,0x00,0x55,0x00,0xff,0x01,0x55,0x05,	/*Char21*/
	0x00,0xf4,0x00,0x25,0x00,0x89,0x00,0xfd,
	0x00,0x89,0x00,0x25,0x00,0x89,0x00,0x25,	/*Char22*/
	0x1f,0xfd,0x55,0xfd,0x55,0x89,0x7f,0x25,
	0x55,0x89,0x55,0x25,0x55,0x89,0x55,0xfd,	/*Char23*/
	0xef,0xaa,0xbf,0xab,0x55,0x55,0x56,0x55,
	0x55,0x55,0x56,0x55,0x55,0x55,0xbf,0xab,	/*Char24*/
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0x55,0x55,0x55,0x55,0x55,0x55,0xaa,0xaa,	/*Char25*/
	0x7a,0xfd,0x7e,0xfd,0x55,0x89,0x55,0x25,
	0x55,0x89,0x55,0x25,0x55,0x89,0x7e,0xfd,	/*Char26*/
	0x7a,0x89,0x7e,0xfd,0x55,0x89,0x55,0x25,
	0x55,0x89,0x55,0x25,0x55,0xfd,0x7e,0xfd,	/*Char27*/
	0x55,0x55,0xff,0xae,0x55,0x55,0x56,0x55,
	0x55,0x55,0x56,0x55,0xef,0xaa,0xbf,0xab,	/*Char28*/
	0x55,0x55,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0x55,0x55,0x55,0x55,0xaa,0xaa,0xaa,0xaa,	/*Char29*/
	0x55,0x00,0x7f,0x00,0x55,0x00,0x55,0x00,
	0x55,0x00,0x55,0x00,0x7a,0x00,0x7e,0x00,	/*Char30*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x55,0x50,0xa9,0x54,0x55,	/*Char31*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x55,0x55,0x55,0x55,0xaa,0xaa,0x55,0x55,	/*Char32*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x55,0x00,0x6a,0x01,0x55,0x15,	/*Char33*/
	0x24,0x56,0xf4,0xff,0x25,0x56,0x89,0x55,
	0xfd,0xff,0x89,0x55,0x25,0x56,0x89,0x55,	/*Char34*/
	0x55,0x55,0xbf,0xab,0x55,0x55,0x55,0x55,
	0xae,0xaa,0x55,0x55,0x55,0x55,0x55,0x55,	/*Char35*/
	0x55,0x55,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0x55,0x55,0x55,0x55,0x55,0x55,	/*Char36*/
	0x55,0x15,0xfa,0x1f,0x55,0x55,0x55,0x55,
	0xaa,0x7f,0x55,0x55,0x55,0x55,0x55,0x55,	/*Char37*/
	0x00,0xfd,0x00,0xfd,0x00,0x89,0x00,0x25,
	0x00,0x89,0x00,0x25,0x00,0x89,0x00,0xfd,	/*Char38*/
	0x7a,0x89,0x7e,0x25,0x55,0x89,0x55,0x25,
	0x55,0x89,0x55,0xfd,0x55,0xfd,0x7e,0x89,	/*Char39*/
	0x55,0x55,0x56,0x55,0x55,0x55,0x56,0x55,
	0x55,0x55,0xbf,0xab,0xef,0xaa,0x55,0x55,	/*Char40*/
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
	0x55,0x55,0xaa,0xaa,0xaa,0xaa,0x55,0x55,	/*Char41*/
	0x55,0x00,0x55,0x40,0x55,0x90,0x55,0x24,
	0x55,0xf4,0x7e,0x25,0x7a,0x89,0x55,0xfd,	/*Char42*/
	0x55,0x55,0xff,0xff,0x55,0x55,0x56,0x55,
	0xff,0xbf,0x56,0x55,0x55,0x55,0xff,0xae,	/*Char43*/
	0x55,0x55,0xbf,0xaa,0x55,0x55,0x55,0x55,
	0xab,0xaa,0x55,0x55,0x55,0x55,0xaa,0xaa,	/*Char44*/
	0x55,0x55,0xfa,0xff,0x55,0x55,0x55,0x55,
	0xaa,0xfa,0x55,0x55,0x55,0x55,0xaa,0xaa,	/*Char45*/
	0x00,0x00,0x01,0x00,0x05,0x00,0x15,0x00,
	0x1f,0x00,0x55,0x00,0x55,0x00,0x7f,0x00,	/*Char46*/
	0x25,0x56,0xfd,0xef,0xfd,0xbf,0x89,0x55,
	0x25,0x56,0x89,0x55,0x25,0x56,0x89,0x55,	/*Char47*/
	0x55,0x55,0xaa,0xaa,0xab,0xaa,0x55,0x55,
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,	/*Char48*/
	0x55,0x55,0xaa,0x7a,0xaa,0x7e,0x55,0x55,
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,	/*Char49*/
	0xef,0xaa,0x55,0x55,0x56,0x55,0x55,0x55,
	0x56,0x55,0x55,0x55,0xbf,0xab,0xef,0xaa,	/*Char50*/
	0x7a,0xfd,0x55,0x89,0x55,0x25,0x55,0x89,
	0x55,0x25,0x55,0x89,0x7e,0xfd,0x7a,0xfd,	/*Char51*/
	0x7a,0x25,0x55,0x89,0x55,0x25,0x55,0x89,
	0x55,0xfd,0x55,0xfd,0x7e,0xfd,0x7a,0x89,	/*Char52*/
	0x56,0x55,0x55,0x55,0x56,0x55,0x55,0x55,
	0xbf,0xab,0xef,0xaa,0x6b,0x56,0x55,0x55,	/*Char53*/
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
	0xaa,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,	/*Char54*/
	0x55,0x89,0x55,0x25,0x55,0x89,0x55,0x25,
	0x7e,0xfd,0x7a,0xfd,0x55,0x89,0x55,0x25,	/*Char55*/
	0x55,0x55,0x56,0x55,0x55,0x55,0x56,0x55,
	0xef,0xaa,0xbf,0xab,0x55,0x55,0x56,0x55,	/*Char56*/
	0x55,0x00,0x55,0x00,0x55,0x00,0x55,0x00,
	0x7a,0x00,0x7e,0x00,0x55,0x00,0x55,0x00,	/*Char57*/
	0xfd,0xbf,0xfd,0xef,0x89,0x55,0x25,0x56,
	0x89,0x55,0x25,0x56,0x89,0x55,0xfd,0xbf,	/*Char58*/
	0xab,0xaa,0xaa,0xaa,0x55,0x55,0x55,0x55,
	0x55,0x55,0x55,0x55,0x55,0x55,0xab,0xaa,	/*Char59*/
	0xaa,0x7e,0xaa,0x7a,0x55,0x55,0x55,0x55,
	0x55,0x55,0x55,0x55,0x55,0x55,0xaa,0x7e,	/*Char60*/
	0x6b,0x56,0x55,0x55,0x56,0x55,0x55,0x55,
	0x56,0x55,0x55,0x55,0xbf,0xab,0xef,0xaa,	/*Char61*/
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
	0x55,0x55,0x55,0x55,0xaa,0xaa,0xaa,0xaa,	/*Char62*/
	0x55,0xfd,0x55,0x89,0x55,0x25,0x55,0x89,
	0x55,0x25,0x55,0x89,0x7e,0xfd,0x7a,0xfd,	/*Char63*/
	0x69,0xfd,0x55,0x89,0x55,0x25,0x55,0x89,
	0x55,0x25,0x55,0x89,0x7e,0xfd,0x7a,0xfd,	/*Char64*/
	0x69,0x25,0x55,0x89,0x55,0x25,0x55,0x89,
	0x55,0xfd,0x55,0xfd,0x7e,0xfd,0x7a,0xa9,	/*Char65*/
	0x55,0x89,0x55,0x25,0x55,0x89,0x55,0xfd,
	0x7e,0xfd,0x7a,0x89,0x55,0x25,0x55,0x89,	/*Char66*/
	0x55,0x55,0x56,0x55,0x55,0x55,0xbf,0xab,
	0xef,0xaa,0x55,0x55,0x56,0x55,0x55,0x55,	/*Char67*/
	0x55,0x55,0x55,0x55,0x55,0x55,0xaa,0xaa,
	0xaa,0xaa,0x55,0x55,0x55,0x55,0x55,0x55,	/*Char68*/
	0x55,0x00,0x55,0x00,0x55,0x00,0x7e,0x00,
	0x7a,0x00,0x55,0x00,0x55,0x00,0x55,0x00,	/*Char69*/
	0xfd,0xef,0xfd,0x6b,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char70*/
	0xaa,0xaa,0x56,0x55,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char71*/
	0xaa,0xaa,0x55,0x55,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char72*/
	0xaa,0x7a,0x55,0x55,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char73*/
	0x00,0xfd,0x00,0xa9,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char74*/
	0x6b,0x56,0x55,0x55,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char75*/
	0x55,0xfd,0x55,0xa9,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char76*/
	0x69,0xfd,0x55,0xa9,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char77*/
	0x69,0x55,0x55,0x55,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char78*/
	0x55,0x25,0x55,0x89,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char79*/
	0x56,0x55,0x55,0x55,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char80*/
	0x55,0x00,0x55,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char81*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*Char82*/
	
0};
