#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artist.h"

// Create a new artist instance in memory
Artist* create_artist(int id, const char* name) {
    Artist* new_artist = (Artist*)malloc(sizeof(Artist));
    if (new_artist == NULL) return NULL; // Safety check

    new_artist->id = id;
    strncpy(new_artist->name, name, 99);
    new_artist->head_song = NULL; // Initially, no songs are linked 
    new_artist->next = NULL;
    
    return new_artist;
}

// Add that artist to the database (linked list)
void add_artist_to_list(Artist** head, Artist* new_artist) {
    if (*head == NULL) {
        *head = new_artist; // This is the first artist in the system
    } else {
        Artist* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; // Find the end of the list
        }
        temp->next = new_artist;
    }
}

// Saves list of all artists to a text file
void save_artists_to_file(Artist* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return;

    Artist* current = head;
    while (current != NULL) {
        // Save ID and Name to a text file 
        fprintf(file, "%d,%s\n", current->id, current->name);
        current = current->next;
    }

    fclose(file);
}