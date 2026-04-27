#ifndef STORAGE_H
#define STORAGE_H

#include "artist.h"
#include "song.h"
#include "profile.h"

// --- Save Functions ---
void save_data(Artist* artist_list, Song* song_list);

// --- Load Functions ---
// These take double pointers so they can update the lists in main()
void load_data(Artist** artist_list, Song** song_list);

#endif