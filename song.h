#ifndef SONG_H
#define SONG_H

// Forward declaration of Artist, avoids circular includes
struct Artist;

typedef struct Song {
    int id;                         // Unique identifier
    char title[100];                // Title of the song
    int length_seconds;             // Duration in seconds
    int rating;                     // 1-10 scale rating
    char filepath[256];             // Path for playback
    
    struct Artist* artist_ptr;      // Pointer to the Artist object 
    struct Song* next;              // Next song in a playlist or database
} Song;

// --- Function Prototypes ---

// Creates a new song instance and returns a pointer to it
Song* create_song(int id, const char* title, int length, const char* path);

// Adds a song to a linked list (like a playlist or the main database)
void add_song_to_list(Song** head, Song* new_song);

// Updates the 10-point rating for a specific song
void rate_song(Song* song, int new_rating);

// Searches for a song by its title
Song* find_song_by_title(Song* head, const char* title);

// Frees the memory allocated for a song list
void free_song_list(Song* head);

// links a song to an artist
void link_song_to_artist(Song* song, struct Artist* artist);

// prints all the songs for a given rating
void print_songs_by_rating(Song* head, int target_rating);

// updates the file path for a song
void update_song_path(Song* song, const char* new_path);

#endif
