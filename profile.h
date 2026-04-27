#ifndef PROFILE_H
#define PROFILE_H

#include "song.h"
#include "artist.h"

typedef struct Profile {
    char username[50];
    struct Artist* saved_artists; // List of artists added by the user
    struct Song* saved_songs;     // List of songs added by the user
    struct Profile* next;         // For multiple user profiles
} Profile;

// --- Function Prototypes ---

// Creates a new user profile
Profile* create_profile(const char* username);

// Updates profile information (e.g., changing username)
void update_profile(Profile* profile, const char* new_username);

// Deletes a profile and frees its memory
void delete_profile(Profile** head, const char* username);

// Finds a profile by username
Profile* find_profile(Profile* head, const char* username);

// Frees a list of profiles
void free_profile_list(Profile* head);

// Adds a profile to a passed in list
void add_profile_to_list(Profile** head, Profile* new_profile);

#endif