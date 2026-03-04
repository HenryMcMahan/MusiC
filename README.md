# MusiC
A command line program written in C that will allow users to store a music file system. They will be able to play songs from the terminal if they have the correct files.

Project Overview
Group Members: Henry McMahan, Mukhtar Mohamed
Project Title: MusiC
Description: This will be a command line interface developed in C that will allow a user to
navigate a database of songs. User profiles will have artists and songs tied to them that the
user will manually add or upload to the program. They will be able to use it as a sort of
music playing software if they have the proper files for songs, and it will also have other
nice features for a music player such as song ratings and playlists.
Group Responsibilities: Henry will focus on the main code, and Mukhtar will focus on the
navigation layout and printouts to the command line. Code will be managed from a git
repository.
------------------------------------------------------------------------------------------------------------------
Key Features and Functionalities
2.1 Profile Management (10 pts)
Users can create, update, and delete a profile. They have artists, songs, playlists, and
ratings associated with their account.
2.2 Artist Management (10 pts)
Users can create, update, and delete artists. Artists have songs linked to them and can be
manually added to a profile or added when a song is added.
2.3 Song Management (10 pts)
Users can create, update, and delete songs stored in the system. All songs will have a
artist, title, and length associated with them. The songs can also be linked to real audio
files for playback.
2.4 Song Rating (10pts)
All songs can be rated on a 10-point scale. Ratings are grouped by points and can be
printed out highest to lowest, lowest to highest, or for a certain number (example: print out
all songs rated at a 10).
2.5 Playlists / Folders (10 pts)
Songs can be grouped not just by artists but also by separate playlists or folders for easier
management. Each playlist is like a separate file
2.6 Local Storage (10 pts)
User profiles, artists, songs, and playlists are stored locally in text files in the system.
Users can also upload a file or put a file in a folder for playback.
2.7 Playback (20 pts)
Users can play back songs in the command line interface. To play a song, the user must
upload a file to enable playback. This is something that will take more research, but it looks
like there is a library that can enable playback of songs.
2.8 Feature Printouts (10 pts)
Each feature will have extensive printouts detailing things about the feature in a way that is
visually pleasing in the terminal. Printouts will be for things like the Profile, Artists, Songs,
Playlists, and Local Files.
2.9 Visualizer During Playback (10 pts)
Some sort of animation or visualizer will play in the terminal when a song is playing. This
might or might not be synced to the music playing.
Bonus Feature (5 pts)
When a song is playing, lyrics can be printed to the terminal in real time if there is an
associated lyric file for the song.
