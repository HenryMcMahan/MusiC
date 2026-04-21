#ifndef ARTIST_H
#define ARTIST_H

// Forward declaration of Song (so songs linked to Artists)
struct Song;

typedef struct Artist {
    int id;
    char name[100];
    struct Song* head_song; // Pointer to the first song by this artist 
    struct Artist* next;    // Pointer to the next artist in the database
} Artist;

// Function prototypes
Artist* create_artist(int id, const char* name);
void add_artist_to_list(Artist** head, Artist* new_artist);
void save_artists_to_file(Artist* head, const char* filename);

#endif