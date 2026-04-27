#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

// ==========================================
//                 SAVING
// ==========================================

void save_data(Artist* artist_list, Song* song_list) {
    // 1. Save Artists
    FILE* a_file = fopen("artists.txt", "w");
    if (a_file != NULL) {
        Artist* curr_a = artist_list;
        while (curr_a != NULL) {
            fprintf(a_file, "%d,%s\n", curr_a->id, curr_a->name);
            curr_a = curr_a->next;
        }
        fclose(a_file);
    }

    // 2. Save Songs (Saving the Artist ID as a 'Foreign Key')
    FILE* s_file = fopen("songs.txt", "w");
    if (s_file != NULL) {
        Song* curr_s = song_list;
        while (curr_s != NULL) {
            // Determine the linked artist ID (use 0 if none)
            int artist_id = (curr_s->artist_ptr != NULL) ? curr_s->artist_ptr->id : 0;
            
            fprintf(s_file, "%d,%s,%d,%d,%s,%d\n", 
                    curr_s->id, 
                    curr_s->title, 
                    curr_s->length_seconds, 
                    curr_s->rating, 
                    curr_s->filepath,
                    artist_id); // The Foreign Key
                    
            curr_s = curr_s->next;
        }
        fclose(s_file);
    }
    printf("Data successfully saved to disk.\n");
}

// ==========================================
//                 LOADING
// ==========================================

void load_data(Artist** artist_list, Song** song_list) {
    char line[256];

    // 1. Load Artists FIRST (songs depend on them)
    FILE* a_file = fopen("artists.txt", "r");
    if (a_file != NULL) {
        int id;
        char name[100];
        // Read lines and parse by comma
        while (fgets(line, sizeof(line), a_file)) {
            // %[^,\n] means read characters until a comma or newline is hit
            if (sscanf(line, "%d,%99[^,\n]", &id, name) == 2) {
                Artist* new_artist = create_artist(id, name);
                add_artist_to_list(artist_list, new_artist);
            }
        }
        fclose(a_file);
    }

    // 2. Load Songs and Relink them
    FILE* s_file = fopen("songs.txt", "r");
    if (s_file != NULL) {
        int id, length, rating, artist_id;
        char title[100], path[256];
        
        while (fgets(line, sizeof(line), s_file)) {
            if (sscanf(line, "%d,%99[^,],%d,%d,%255[^,],%d", 
                       &id, title, &length, &rating, path, &artist_id) == 6) {
                
                // Create the raw song object
                Song* new_song = create_song(id, title, length, path);
                new_song->rating = rating;
                
                // Rebuild the pointer connection!
                if (artist_id != 0) {
                    Artist* parent_artist = find_artist_by_id(*artist_list, artist_id);
                    if (parent_artist != NULL) {
                        // Use your existing link function to re-establish the connection
                        link_song_to_artist(new_song, parent_artist); 
                    }
                }
                
                // Add to master list
                add_song_to_list(song_list, new_song);
            }
        }
        fclose(s_file);
    }
    printf("Data successfully loaded from disk.\n");
}