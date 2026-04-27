#include <stdio.h>
#include "artist.h"
#include "song.h"
#include "profile.h"
#include "storage.h"
#include "playback.h"
#include "cli.h"

int main() {
    Artist*  master_artist_list  = NULL;
    Song*    master_song_list    = NULL;
    Profile* master_profile_list = NULL;

    printf("Initializing MusiC...\n");
    load_data(&master_artist_list, &master_song_list);
    init_audio_engine();

    run_main_menu(&master_song_list, &master_artist_list, &master_profile_list);

    return 0;
}