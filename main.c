#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artist.h"

// --- Data Structures ---

// Represents a user profile
typedef struct Profile {
    char username[50];
    Song* saved_songs; 
    // Additional pointers for playlists can be added here
} Profile;


// --- CLI Interface ---
void print_main_menu() {
    printf("\n=== MusiC CLI ===\n");
    printf("1. Profile Management\n");
    printf("2. Artist Management\n");
    printf("3. Song Management\n");
    printf("4. Playback System\n");
    printf("5. Exit\n");
    printf("Select an option: ");
}

// A simple print function for testing purposes.
void test_print_artists(Artist* head) {
    printf("\n--- Current Artist Database ---\n");
    if (head == NULL) {
        printf("The database is currently empty.\n");
        return;
    }

    Artist* current = head;
    while (current != NULL) {
        printf("ID: %d | Name: %s\n", current->id, current->name);
        current = current->next;
    }
    printf("-------------------------------\n");
}

void artistTest() {
	// Initialize the head of your artist list to NULL
    Artist* artist_list = NULL;
	printf("Starting MusiC Test...\n");

    // Create and add the first artist
    Artist* a1 = create_artist(1, "Death's Dynamic Shroud");
    if (a1 != NULL) {
        add_artist_to_list(&artist_list, a1);
        printf("Added: %s\n", a1->name);
    }

    // Create and add a second artist
    Artist* a2 = create_artist(2, "HEALTH");
    if (a2 != NULL) {
        add_artist_to_list(&artist_list, a2);
        printf("Added: %s\n", a2->name);
    }

    // Print the list to verify the links are correct
    test_print_artists(artist_list);

    // Clean up memory before exiting
    Artist* current = artist_list;
    while (current != NULL) {
        Artist* temp = current;
        current = current->next;
        free(temp);
    }
	printf("Test complete. Memory cleared.\n");
}

int main() {
    int choice = 0;
    
    // Main application loop
    while (1) {
        print_main_menu();
        
        // Read user input safely
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer if the user types a character instead of a number
            while(getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        // Handle navigation 
        switch (choice) {
            case 1:
                printf("\n--- Profile Management ---\n");
                // Call profile functions here
                break;
            case 2:
                printf("\n--- Artist Management ---\n");
                // Call artist functions here
				artistTest();
                break;
            case 3:
                printf("\n--- Song Management ---\n");
                // Call song functions here
                break;
            case 4:
                printf("\n--- Playback System ---\n");
                // Call miniaudio integration here
                break;
            case 5:
                printf("\nExiting MusiC. Saving data...\n");
                // Call file saving routines here
                return 0;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
    return 0;
}