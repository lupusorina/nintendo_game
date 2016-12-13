
//{{BLOCK(cosmos)

//======================================================================
//
//	cosmos, 256x256@8, 
//	+ palette 120 entries, not compressed
//	+ 1021 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 240 + 65344 + 2048 = 67632
//
//	Time-stamp: 2016-12-12, 12:13:01
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_COSMOS_H
#define GRIT_COSMOS_H

#define cosmosTilesLen 65344
extern const unsigned int cosmosTiles[16336];

#define cosmosMapLen 2048
extern const unsigned short cosmosMap[1024];

#define cosmosPalLen 240
extern const unsigned short cosmosPal[120];

#endif // GRIT_COSMOS_H

//}}BLOCK(cosmos)
