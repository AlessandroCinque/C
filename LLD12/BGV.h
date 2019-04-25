
//{{BLOCK(BGV)

//======================================================================
//
//	BGV, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 10 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 320 + 2048 = 2880
//
//	Time-stamp: 2018-02-12, 13:25:24
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BGV_H
#define GRIT_BGV_H

#define BGVTilesLen 320
extern const unsigned short BGVTiles[160];

#define BGVMapLen 2048
extern const unsigned short BGVMap[1024];

#define BGVPalLen 512
extern const unsigned short BGVPal[256];

#endif // GRIT_BGV_H

//}}BLOCK(BGV)
