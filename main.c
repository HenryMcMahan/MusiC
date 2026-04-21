#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artist.h"
#include "song.h"

// --- Data Structures ---

// Represents a user profile
//typedef struct Profile {
//    char username[50];
//    Song* saved_songs; 
    // Additional pointers for playlists can be added here
//} Profile;


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
	
	// Save artists to file
	save_artists_to_file(artist_list, "output.txt");

    // Clean up memory before exiting
    Artist* current = artist_list;
    while (current != NULL) {
        Artist* temp = current;
        current = current->next;
        free(temp);
    }
	printf("Test complete. Memory cleared.\n");
}

void songTest() {
	printf("\n--- Starting MusiC Song Management Test ---\n");

    // 1. Setup: Create a master list and a test artist
    Song* master_song_list = NULL;
    Artist* test_artist = create_artist(1, "Machine Girl");

    // 2. Create and Add Songs: id, title, length (sec), path
    Song* s1 = create_song(101, "Necro Culture Vulture", 221, "music/track1.mp3");
    Song* s2 = create_song(102, "Dread Architect", 301, "music/track2.mp3");
    Song* s3 = create_song(103, "PoPiPo", 181, "music/track3.mp3");

    add_song_to_list(&master_song_list, s1);
    add_song_to_list(&master_song_list, s2);
    add_song_to_list(&master_song_list, s3);

    // 3. Link songs to the artist
    link_song_to_artist(s1, test_artist);
    link_song_to_artist(s2, test_artist);

    // 4. Test Search Functionality
    printf("Searching for 'PoPiPo'...\n");
    Song* found = find_song_by_title(master_song_list, "PoPiPo");
    if (found != NULL) {
        printf("Found! Song ID: %d, Path: %s\n", found->id, found->filepath);
    } else {
        printf("Song not found.\n");
    }

    // 5. Test Rating System
    rate_song(s1, 10);
    rate_song(s2, 8);
    rate_song(s3, 10);

    // Print all songs with a specific rating 
    print_songs_by_rating(master_song_list, 10);

    // 6. Cleanup Memory
    free_song_list(master_song_list);
    free(test_artist);
    
    printf("--- Song Test Complete. Memory Cleared. ---\n");
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
				songTest();
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