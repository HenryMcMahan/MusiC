#ifndef PLAYBACK_H
#define PLAYBACK_H

#include "song.h"
#include <stdint.h>

int init_audio_engine();
void play_song(Song* song);
void stop_song();
void cleanup_audio_engine();

#endif