#include "playback.h"
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

int init_audio_engine() {
    printf("Audio engine ready.\n");
    return 1;
}

void play_song(Song* song) {
    if (song == NULL || strlen(song->filepath) == 0) {
        printf("  Error: No filepath for this song.\n");
        return;
    }
    BOOL result = PlaySound(song->filepath, NULL, SND_FILENAME | SND_ASYNC);
    if (!result) {
        printf("  Playback failed. Check the file exists and is a .wav file.\n");
    }
}

void stop_song() {
    PlaySound(NULL, NULL, 0);
    printf("  Playback stopped.\n");
}

void cleanup_audio_engine() {
    stop_song();
}