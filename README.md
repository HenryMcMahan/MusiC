# MusiC

A command-line music management and playback system written in C.  
MusiC allows users to create profiles, manage artists and songs, organize playlists, and play music directly from the terminal.

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

---
Each user profile contains:
- Artists
- Songs
- Playlists
- Ratings

Users manually add or upload songs to the system. If the proper audio files are provided, the program supports playback directly from the terminal. MusiC also includes additional music-player-style features such as song ratings and playlists.

## Technologies Used

- Language: C  
- Interface: Command Line (Terminal)  
- Storage: Local text files  
- Version Control: Git  
