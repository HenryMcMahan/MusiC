#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#include "artist.h"

// Create a new song instance (not linked to artist)
Song* create_song(int id, const char* title, int length, const char* path) {
    Song* new_song = (Song*)malloc(sizeof(Song));
    if (new_song == NULL) return NULL;

    new_song->id = id;
    strncpy(new_song->title, title, 99);
    new_song->length_seconds = length;
    new_song->rating = 0; // Default rating
    strncpy(new_song->filepath, path, 255);
    
    new_song->artist_ptr = NULL; // Can be linked later
    new_song->next = NULL;

    return new_song;
}

// Add a song to a linked list
void add_song_to_list(Song** head, Song* new_song) {
    if (*head == NULL) {
        *head = new_song;
    } else {
        Song* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_song;
    }
}

// Update the rating (1-10 scale)
void rate_song(Song* song, int new_rating) {
    if (song != NULL && new_rating >= 1 && new_rating <= 10) {
        song->rating = new_rating;
    }
}

// Search for a song by title
Song* find_song_by_title(Song* head, const char* title) {
    Song* current = head;
    while (current != NULL) {
        // Returns 0 if the strings are an exact match
        if (strcmp(current->title, title) == 0) {
            return current; // Song found
        }
        current = current->next;
    }
    return NULL; // Song not found after checking entire list
}

// Free the memory for an entire song list
void free_song_list(Song* head) {
    Song* current = head;
    while (current != NULL) {
        Song* temp = current;
        current = current->next;
        free(temp);
    }
}

void link_song_to_artist(Song* song, struct Artist* artist) {
    if (song == NULL || artist == NULL) return;

    // Just set the back-reference
    song->artist_ptr = artist;
    
    // Do NOT call add_song_to_list here if to avoid loops
}

void print_songs_by_rating(Song* head, int target_rating) {
    // Validation check for the 1-10 scale
    if (target_rating < 1 || target_rating > 10) {
        printf("Invalid rating search. Please use a scale of 1-10.\n");
        return;
    }

    printf("\n--- Songs Rated %d/10 ---\n", target_rating);
    
    Song* current = head;
    int found_count = 0;

    // Traverse the list
    while (current != NULL) {
        if (current->rating == target_rating) {
            // Access artist name via the pointer if it's linked
            const char* artist_name = (current->artist_ptr != NULL) ? current->artist_ptr->name : "Unknown Artist";
            
            printf("[%d] Title: %-20s | Artist: %-20s | Length: %d seconds\n", 
                   current->id, current->title, artist_name, current->length_seconds);
            
            found_count++;
        }
        current = current->next;
    }

    // Handle the case where no songs match the criteria
    if (found_count == 0) {
        printf("No songs found with a rating of %d.\n", target_rating);
    }
    printf("---------------------------\n");
}