Skeleton VB GPL source release				24 October 2008
==================================

This file contains the following sections:

LICENSE
GENERAL NOTES
COMPILING ON WIN32
COMPILING ON GNU/LINUX


LICENSE
=======

Copyright (C) 2008 Jorge Eremiev
jorgech3@gmail.com

See GPL-license.txt for the GNU GENERAL PUBLIC LICENSE

-----------------------------------------------------------------------------

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.



GENERAL NOTES
=============

Description: 
	
	Platform demo of a game created using the VBJaEngine to show off
	some of the engine's capabilities. 


A short summary of the file layout:

source/			   		Skeleton VB source code
source/game/objects/	Definition and implementation of the different graphics, objects, IA, worlds			


For more documentation go to:

http://www.vr32.de/modules/dokuwiki/doku.php?id=vbjaengine_programmer_s_guide


COMPILING ON WIN32
==================

Requirements: 

	· Minimal Linux environment (i.e: CygWin)
	
	· GCCVB 4.4.2 for V810 



1. Create an environment variable called VBJAENGINE which must point to the VBJaEngine's folder.

2. To compile the execute the following command inside the game's folder:

	$ make

	This will compile the engine and the game, the executable is placed in the output/ folder.


COMPILING ON GNU/LINUX
==================

Requirements: 

	· GCCVB 4.4.2 for V810 


1. Create a CygWin environment variable called VBJAENGINE which must point to the VBJaEngine's folder.

2. To compile the execute the following command inside the game's folder:

	$ make

	This will compile the engine and the game, the executable is placed in the output/ folder.



ACKNOWLEDGMENTS
==================

	· Christian Radke (KR155E), for helping me with most of the demo's graphics, design, debbuging, etc.
	
	
==================  

V810 is a trade mark of NEC.
Mario is a trade mark of Nintendo.
Virtual Boy is a trade mark of Nintendo.

Jorge Eremiev is in no way affiliated with either of these parties.