#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "profile.h"

Profile* create_profile(const char* username) {
    Profile* new_profile = (Profile*)malloc(sizeof(Profile));
    if (new_profile == NULL) return NULL;

    strncpy(new_profile->username, username, 49);
    new_profile->saved_artists = NULL;
    new_profile->saved_songs = NULL;
    new_profile->next = NULL;
    
    return new_profile;
}

void update_profile(Profile* profile, const char* new_username) {
    if (profile != NULL) {
        strncpy(profile->username, new_username, 49);
    }
}

void delete_profile(Profile** head, const char* username) {
    Profile* temp = *head;
    Profile* prev = NULL;

    while (temp != NULL && strcmp(temp->username, username) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return; // Profile not found

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    // In a full implementation should also free saved_songs/artists
    free(temp);
}

Profile* find_profile(Profile* head, const char* username) {
    Profile* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void free_profile_list(Profile* head) {
    Profile* current = head;
    Profile* next_node;

    while (current != NULL) {
        // 1. Save the pointer to the next node before freeing the current one
        next_node = current->next;

        // 2. Clear the username
        // free dynamic memory here if added later

        // 3. Free the actual profile struct
        free(current);

        // 4. Move to the next node in the sequence
        current = next_node;
    }
    
    printf("All profile memory has been successfully cleared.\n");
}

void add_profile_to_list(Profile** head, Profile* new_profile) {
    // 1. Safety check to ensure we aren't adding a NULL pointer
    if (new_profile == NULL) return;

    // 2. If the list is empty, make the new profile the head
    if (*head == NULL) {
        *head = new_profile;
    } else {
        // 3. Otherwise, traverse to the last node
        Profile* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // 4. Link the last node to the new profile
        current->next = new_profile;
    }
    // Ensure the new tail points to NULL
    new_profile->next = NULL;
}
