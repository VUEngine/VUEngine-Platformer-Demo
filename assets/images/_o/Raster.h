
//{{BLOCK(Raster)

//======================================================================
//
//	Raster, 512x512@2, 
//	+ 2 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 8192 = 8224
//
//	Time-stamp: 2014-12-02, 15:14:04
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_RASTER_H
#define GRIT_RASTER_H

#define RasterTilesLen 32
extern const unsigned char RasterTiles[32];

#define RasterMapLen 8192
extern const unsigned char RasterMap[8192];

#endif // GRIT_RASTER_H

//}}BLOCK(Raster)
