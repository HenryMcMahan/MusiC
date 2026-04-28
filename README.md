# MusiC

A command-line music management and playback system written in C.  
MusiC allows users to create profiles, manage artists and songs, organize playlists, and play music directly from the terminal.

---

## Project Overview

**Project Title:** MusiC  
**Group Members:** Henry McMahan, Mukhtar Mohamed  

### Description
MusiC is a command-line interface (CLI) application developed in C that allows users to navigate and manage a database of songs.

Each user profile contains:
- Artists
- Songs
- Playlists
- Ratings

Users manually add or upload songs to the system. If the proper audio files are provided, the program supports playback directly from the terminal. MusiC also includes additional music-player-style features such as song ratings and playlists.

### Group Responsibilities
- Henry McMahan — Core functionality and main program logic  
- Mukhtar Mohamed — Navigation layout and terminal print formatting  
- Version control managed using Git  

---

## Key Features and Functionalities

### 1. Profile Management (10 pts)
- Create, update, and delete user profiles  
- Profiles store:
  - Artists  
  - Songs  
  - Playlists  
  - Ratings  

---

### 2. Artist Management (10 pts)
- Create, update, and delete artists  
- Artists are linked to songs  
- Artists can be:
  - Manually added to a profile  
  - Automatically created when adding a song  

---

### 3. Song Management (10 pts)
- Create, update, and delete songs  
- Each song contains:
  - Artist  
  - Title  
  - Length  
- Songs can optionally link to real audio files for playback  

---

### 4. Song Rating System (10 pts)
- Songs are rated on a 10-point scale  
- Ratings can be displayed:
  - Highest to lowest  
  - Lowest to highest  
  - By specific rating value (e.g., all songs rated 10)  

---

### 5. Playlists / Folders (10 pts)
- Create custom playlists for organizing songs  
- Playlists function like separate folders/files  
- Songs can belong to:
  - Artists  
  - Playlists  

---

### 6. Local Storage (10 pts)
- All data is stored locally in text files:
  - User profiles  
  - Artists  
  - Songs  
  - Playlists  
- Users can upload audio files for playback support  

---

### 7. Playback System (20 pts)
- Play songs directly within the terminal  
- Requires an uploaded audio file  
- Uses an external C audio library to enable playback  

---

### 8. Feature Printouts (10 pts)
- Visually structured terminal output  
- Clean formatting for:
  - Profiles  
  - Artists  
  - Songs  
  - Playlists  
  - Local files  

---

### 9. Terminal Visualizer (10 pts)
- Displays an animation or visualizer during playback  
- May or may not sync with the music  

---

## Bonus Feature (5 pts)

**Real-Time Lyrics Display**
- If a song has an associated lyric file, lyrics can be displayed in real time during playback.

---

## Technologies Used

- Language: C  
- Interface: Command Line (Terminal)  
- Storage: Local text files  
- Version Control: Git  

## For Compiling
gcc -o main main.c profile.c song.c artist.c storage.c playback.c cli.c -lwinmm -lm

## How to Use
To use the program, first download the files and compile the program using the line above. Once compiled the program can be run with ./main
The program has a example set of artists and songs loaded in. Songs and Artists can be added in any manner, but it probably makes more sense to 
add the artists first and then add songs.

The program is navigated in the terminal with entering numbers. Names need to match exactly when trying to look up songs.
Pressing 4 from the main menu will enter the playback mode. You need a .wav file to playback the song and the file needs to be properly linked in order
for the song to playback. File paths can be absolute, or use a relative path and put songs in the Music_Files folder. 
Once played the song plays once and the menu can be used in the background. Once the song is done it will not play again.
