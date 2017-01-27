/*
 * audio.c
 *
 *  Created on: Jan 26, 2017
 *      Author: tardyantoine
 *
 *      Handles audio
 */

#include "audio.h"

// ===== AUDIO IMPLEMENTATIONS =================================================
// Init ausio
void audio_init()
{
	//Init the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);
	//Load module
	mmLoad(MOD_TETRISMIX);
}

// Play music
void audio_start_music()
{
	//Start playing music in a loop
	mmStart(MOD_TETRISMIX, MM_PLAY_LOOP);
	//Set module volume to 512 (range 0...1024) using the function mmSetVolume(...)
	mmSetModuleVolume(512);
}

// Stop music
void audio_pause_music()
{
	//Set module volume to 0 (range 0...1024) using the function mmSetVolume(...)
	mmPause();
}

// Restart music
void audio_restart_music()
{
	//Set module volume to 0 (range 0...1024) using the function mmSetVolume(...)
	mmResume();
}

// Stops music
void audio_stop_music()
{
	mmStop();
}

