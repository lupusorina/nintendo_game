/*
 * audio.h
 *
 *  Created on: Jan 26, 2017
 *      Author: tardyantoine
 *
 *      Handles audio
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

// ===== AUDIO PROTOTYPES ======================================================
void audio_init();			// Init music
void audio_start_music();	// Play music from beginning
void audio_stop_music();	// Stops music
void audio_pause_music();	// Pause music
void audio_restart_music();	// Restart music

#endif /* AUDIO_H_ */
