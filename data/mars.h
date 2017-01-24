
//{{BLOCK(mars)

//======================================================================
//
//	mars, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 716 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 45824 + 2048 = 48384
//
//	Time-stamp: 2017-01-18, 18:11:22
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MARS_H
#define GRIT_MARS_H

#define marsTilesLen 45824
extern const unsigned int marsTiles[11456];

#define marsMapLen 2048
extern const unsigned short marsMap[1024];

#define marsPalLen 512
extern const unsigned short marsPal[256];

#endif // GRIT_MARS_H

//}}BLOCK(mars)
