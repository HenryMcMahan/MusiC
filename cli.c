#include "cli.h"
#include "playback.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static const char* get_filename(const char* path) {
    const char* slash    = strrchr(path, '\\');
    const char* fwdslash = strrchr(path, '/');
    const char* last     = slash > fwdslash ? slash : fwdslash;
    return (last != NULL) ? last + 1 : path;
}

static void truncate_str(char* dest, const char* src, int max_len) {
    if ((int)strlen(src) <= max_len) {
        strncpy(dest, src, max_len);
        dest[max_len] = '\0';
    } else {
        strncpy(dest, src, max_len - 3);
        dest[max_len - 3] = '\0';
        strcat(dest, "...");
    }
}

static void print_song_card(Song* song) {
    int mins = song->length_seconds / 60;
    int secs = song->length_seconds % 60;
    const char* artist = song->artist_ptr ? song->artist_ptr->name : "Unknown Artist";

    char dur_buf[16];
    snprintf(dur_buf, sizeof(dur_buf), "%d:%02d", mins, secs);

    char pips[12] = "";
    for (int i = 0; i < 10; i++)
        strcat(pips, i < song->rating ? "#" : "-");
    char rating_buf[48];
    snprintf(rating_buf, sizeof(rating_buf), "[%s] %d/10", pips, song->rating);

    char title_buf[33], artist_buf[33], path_buf[33];
    truncate_str(title_buf,  song->title,                  32);
    truncate_str(artist_buf, artist,                       32);
    truncate_str(path_buf,   get_filename(song->filepath), 32);

    printf("\n");
    printf("  +------------------------------------------+\n");
    printf("  |  ** NOW PLAYING **   🎵      🎶          |\n");
    printf("  +------------------------------------------+\n");
    printf("  |  Title    : %-30s|\n", title_buf);
    printf("  |  Artist   : %-30s|\n", artist_buf);
    printf("  |  Duration : %-30s|\n", dur_buf);
    printf("  |  ID       : %-30d|\n", song->id);
    printf("  |  Rating   : %-30s|\n", rating_buf);
    printf("  |  File     : %-30s|\n", path_buf);
    printf("  +------------------------------------------+\n");
    printf("  |  Audio playing -- use Stop to end        |\n");
    printf("  +------------------------------------------+\n\n");
}

// ------------------------------------------------
//  Profile Menu
// ------------------------------------------------
static void profile_menu(Profile** head_ref) {
    int choice;
    char input_name[50];

    while (1) {
        printf("\n  === Profile Management ===\n\n");
        printf("  1. Create New Profile\n");
        printf("  2. View All Profiles\n");
        printf("  3. Delete Profile\n");
        printf("  4. Back to Main Menu\n");
        printf("\n  Select: ");

        if (scanf("%d", &choice) != 1) { clear_input_buffer(); continue; }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                printf("  Username: ");
                fgets(input_name, sizeof(input_name), stdin);
                input_name[strcspn(input_name, "\n")] = 0;
                Profile* p = create_profile(input_name);
                p->next = *head_ref;
                *head_ref = p;
                printf("  Profile '%s' created.\n", p->username);
                break;
            }
            case 2: {
                printf("\n  -- Profiles --\n");
                Profile* cur = *head_ref;
                if (!cur) printf("  No profiles yet.\n");
                while (cur) { printf("  - %s\n", cur->username); cur = cur->next; }
                break;
            }
            case 3:
                printf("  Username to delete: ");
                fgets(input_name, sizeof(input_name), stdin);
                input_name[strcspn(input_name, "\n")] = 0;
                delete_profile(head_ref, input_name);
                printf("  Deleted '%s'.\n", input_name);
                break;
            case 4:
                return;
            default:
                printf("  Invalid option.\n");
        }
    }
}

// ------------------------------------------------
//  Artist Menu
// ------------------------------------------------
static void artist_menu(Artist** head_ref) {
    int choice, input_id;
    char input_name[100];

    while (1) {
        printf("\n  === Artist Management ===\n\n");
        printf("  1. Add Artist\n");
        printf("  2. View All Artists\n");
        printf("  3. Back to Main Menu\n");
        printf("\n  Select: ");

        if (scanf("%d", &choice) != 1) { clear_input_buffer(); continue; }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                printf("  Artist ID: ");
                if (scanf("%d", &input_id) != 1) { clear_input_buffer(); break; }
                clear_input_buffer();
                printf("  Artist Name: ");
                fgets(input_name, sizeof(input_name), stdin);
                input_name[strcspn(input_name, "\n")] = 0;
                Artist* a = create_artist(input_id, input_name);
                add_artist_to_list(head_ref, a);
                printf("  Artist '%s' added.\n", input_name);
                break;
            }
            case 2: {
                printf("\n  -- Artists --\n");
                Artist* cur = *head_ref;
                if (!cur) printf("  No artists yet.\n");
                while (cur) {
                    printf("  [%d] %s\n", cur->id, cur->name);
                    cur = cur->next;
                }
                break;
            }
            case 3:
                return;
            default:
                printf("  Invalid option.\n");
        }
    }
}

// ------------------------------------------------
//  Song Menu
// ------------------------------------------------
static void song_menu(Song** song_head_ref, Artist* artist_head) {
    int choice;
    char input_title[100], input_path[256];
    int input_id, input_length, input_rating;

    while (1) {
        printf("\n  === Song Management ===\n\n");
        printf("  1. Add New Song\n");
        printf("  2. View All Songs\n");
        printf("  3. Rate a Song\n");
        printf("  4. Link Song to Artist\n");
        printf("  5. Update Song Filepath\n");
        printf("  6. Back to Main Menu\n");
        printf("\n  Select: ");

        if (scanf("%d", &choice) != 1) { clear_input_buffer(); continue; }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                printf("  Song ID: ");
                scanf("%d", &input_id); clear_input_buffer();
                printf("  Title: ");
                fgets(input_title, sizeof(input_title), stdin);
                input_title[strcspn(input_title, "\n")] = 0;
                printf("  Duration (seconds): ");
                scanf("%d", &input_length); clear_input_buffer();
                printf("  Filepath: ");
                fgets(input_path, sizeof(input_path), stdin);
                input_path[strcspn(input_path, "\n")] = 0;

                Song* s = create_song(input_id, input_title, input_length, input_path);

                printf("  Artist ID to link (0 to skip): ");
                int artist_id;
                if (scanf("%d", &artist_id) == 1 && artist_id != 0) {
                    Artist* par = find_artist_by_id(artist_head, artist_id);
                    if (par) { link_song_to_artist(s, par); printf("  Linked to: %s\n", par->name); }
                    else printf("  Artist not found. Song unlinked.\n");
                }
                clear_input_buffer();
                add_song_to_list(song_head_ref, s);
                printf("  Song '%s' added.\n", input_title);
                break;
            }
            case 2: {
                printf("\n");
                printf("  %-4s  %-25s  %-22s  %-6s  %s\n",
                       "ID", "Title", "Artist", "Rating", "Time");
                printf("  %-4s  %-25s  %-22s  %-6s  %s\n",
                       "----", "-------------------------",
                       "----------------------", "------", "----");
                Song* cur = *song_head_ref;
                if (!cur) { printf("  No songs yet.\n"); break; }
                while (cur) {
                    const char* aname = cur->artist_ptr ? cur->artist_ptr->name : "Unlinked";
                    int mins = cur->length_seconds / 60;
                    int secs = cur->length_seconds % 60;
                    char time_buf[8];
                    snprintf(time_buf, sizeof(time_buf), "%d:%02d", mins, secs);

                    char title_col[26], artist_col[23];
                    truncate_str(title_col,  cur->title, 25);
                    truncate_str(artist_col, aname,      22);

                    printf("  %-4d  %-25s  %-22s  %-6d  %s\n",
                           cur->id, title_col, artist_col, cur->rating, time_buf);
                    cur = cur->next;
                }
                break;
            }
            case 3: {
                printf("  Song title to rate: ");
                fgets(input_title, sizeof(input_title), stdin);
                input_title[strcspn(input_title, "\n")] = 0;
                Song* to_rate = find_song_by_title(*song_head_ref, input_title);
                if (to_rate) {
                    printf("  New rating (1-10): ");
                    scanf("%d", &input_rating); clear_input_buffer();
                    rate_song(to_rate, input_rating);
                    printf("  Rating updated.\n");
                } else printf("  Song not found.\n");
                break;
            }
            case 4: {
                printf("  Song title: ");
                fgets(input_title, sizeof(input_title), stdin);
                input_title[strcspn(input_title, "\n")] = 0;
                Song* to_link = find_song_by_title(*song_head_ref, input_title);
                if (to_link) {
                    printf("  Artist ID: ");
                    scanf("%d", &input_id); clear_input_buffer();
                    Artist* par = find_artist_by_id(artist_head, input_id);
                    if (par) { link_song_to_artist(to_link, par); printf("  Linked.\n"); }
                    else printf("  Artist not found.\n");
                } else printf("  Song not found.\n");
                break;
            }
            case 5: {
                printf("  Song title: ");
                fgets(input_title, sizeof(input_title), stdin);
                input_title[strcspn(input_title, "\n")] = 0;
                Song* to_update = find_song_by_title(*song_head_ref, input_title);
                if (to_update) {
                    printf("  New filepath: ");
                    fgets(input_path, sizeof(input_path), stdin);
                    input_path[strcspn(input_path, "\n")] = 0;
                    update_song_path(to_update, input_path);
                    printf("  Filepath updated.\n");
                } else printf("  Song not found.\n");
                break;
            }
            case 6:
                return;
            default:
                printf("  Invalid option.\n");
        }
    }
}

// ------------------------------------------------
//  Playback Menu
// ------------------------------------------------
static void playback_menu(Song* master_song_list) {
    int choice;
    char input_title[100];

    while (1) {
        printf("\n  === Playback ===\n\n");
        printf("  1. Play Song\n");
        printf("  2. Stop Playback\n");
        printf("  3. Back to Main Menu\n");
        printf("\n  Select: ");

        if (scanf("%d", &choice) != 1) { clear_input_buffer(); continue; }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                printf("  Song title: ");
                fgets(input_title, sizeof(input_title), stdin);
                input_title[strcspn(input_title, "\n")] = 0;
                Song* to_play = find_song_by_title(master_song_list, input_title);
                if (to_play) {
                    play_song(to_play);
                    print_song_card(to_play);
                } else {
                    printf("  Song not found.\n");
                }
                break;
            }
            case 2:
                stop_song();
                break;
            case 3:
                return;
            default:
                printf("  Invalid option.\n");
        }
    }
}

// ------------------------------------------------
//  Main Menu
// ------------------------------------------------
void run_main_menu(Song** song_list, Artist** artist_list, Profile** profile_list) {
    int choice;

    while (1) {
        printf("\n  === MusiC ===\n\n");
        printf("  1. Profile Management\n");
        printf("  2. Artist Management\n");
        printf("  3. Song Management\n");
        printf("  4. Playback\n");
        printf("  5. Save and Exit\n");
        printf("\n  Select: ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: profile_menu(profile_list); break;
            case 2: artist_menu(artist_list); break;
            case 3: song_menu(song_list, *artist_list); break;
            case 4: playback_menu(*song_list); break;
            case 5:
                printf("\n  Saving...\n");
                save_data(*artist_list, *song_list);
                free_song_list(*song_list);
                free_artist_list(*artist_list);
                free_profile_list(*profile_list);
                cleanup_audio_engine();
                printf("  Goodbye.\n");
                exit(0);
            default:
                printf("  Invalid option.\n");
        }
    }
}