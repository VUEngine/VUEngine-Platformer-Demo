
//{{BLOCK(gui)

//======================================================================
//
//	gui, 512x512@2, 
//	+ 20 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 320 + 8192 = 8512
//
//	Time-stamp: 2014-12-02, 15:34:22
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GUI_H
#define GRIT_GUI_H

#define guiTilesLen 320
extern const unsigned char guiTiles[320];

#define guiMapLen 8192
extern const unsigned char guiMap[];

#endif // GRIT_GUI_H

//}}BLOCK(gui)
