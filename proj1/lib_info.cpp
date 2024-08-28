// Name: Jeffrey Chen
// Partner: Aidan Feyerherm
// Date: 8/27/2024
// Overview: Using maps to track multiple structs or objects to
// lexicographically print everything. Citation:
// https://www.geeksforgeeks.org/references-in-cpp/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

using namespace std;

struct Song {
  std::string title;
  int time;
  int track;
};

struct Album {
  std::map<int, Song> songs;
  std::string name;
  int time;
  int nsongs;
};

struct Artist {
  std::map<std::string, Album> albums;
  std::string name;
  int time;
  int nsongs;
};

// Replace underscore function
// https://www.quora.com/How-do-you-replace-a-character-in-a-string-in-C#:~:text=std%3A%3Acout%20%3C%3C%20str%20%3C,%2F%2F%20Output%3A%20Hella%2C%20warld!&text=Mar%2026-,In%20C%2B%2B%2C%20you%20can%20replace%20a%20character%20in%20a,using%20the%20find%20(%20)%20function.
void replaceUnderscore(string &str) {
  replace(str.begin(), str.end(), '_', ' ');
}

std::string convertTimeToString(int intTime) {
  int remainingMinutes = intTime / 60;
  int remainingSeconds = intTime % 60;

  stringstream minutesStream;
  stringstream secondsStream;

  minutesStream << remainingMinutes;
  string minutes = minutesStream.str();

  secondsStream << std::setw(2) << setfill('0') << remainingSeconds;
  string seconds = secondsStream.str();

  return minutes + ":" + seconds;
}

int convertTimeToInt(string stringTime) {
  int colon = stringTime.find(":");
  string stringMinutes = stringTime.substr(0, colon);
  string stringSeconds = stringTime.substr(colon + 1);
  int minutes = stoi(stringMinutes);
  int seconds = minutes * 60;
  int additionalSeconds = stoi(stringSeconds);
  seconds += additionalSeconds;
  return seconds;
}

int main(int argc, char *argv[]) {
  string filename = argv[1];
  ifstream infile(filename);

  string line;

  // When the struct or object inside the map reaches end of lifetime (or hits
  // end of scope), a map creates a copy of the object or struct and thus is why
  // we are able to track it and do not need new keyword. The map manages the
  // lifetime of its elements independently of the variables used to insert
  // those elements
  map<string, Artist> listOfArtists;
  map<string, Album> listOfAlbums;

  while (getline(infile, line)) {
    stringstream ss(line);

    // Parse the line into string variables
    string title, time, artistName, albumName, genre, track;

    ss >> title >> time >> artistName >> albumName >> genre >> track;

    // Remove the Underscore
    replaceUnderscore(title);
    replaceUnderscore(artistName);
    replaceUnderscore(albumName);

    Song song;
    song.title = title;
    song.track = stoi(track);
    song.time = convertTimeToInt(time);

    // If the artist isn't logged, create one and add it to the list.
    // All artists (key) is mapped to their own respective structs (the value).
    if (listOfArtists.find(artistName) == listOfArtists.end()) {
      Artist artist;
      artist.name = artistName;
      artist.nsongs = 0;
      artist.time = 0;
      listOfArtists[artistName] = artist;
    }

    // Creates a reference to the artist
    // A reference is similar to a pointer but it can be modified
    Artist &artist = listOfArtists[artistName];
    // If the album isn't logged, create one and add it to the list.
    if (artist.albums.find(albumName) == artist.albums.end()) {
      Album album;
      album.name = albumName;
      album.nsongs = 0;
      album.time = 0;
      artist.albums[albumName] = album;
    }

    Album &album = artist.albums[albumName];
    album.songs[song.track] = song;
    album.nsongs += 1;
    album.time += song.time;

    artist.nsongs += 1;
    artist.time += song.time;
  }

  // Print all artists, albums, and songs.
  // It0, Iterator 0, iterates through the list of artists.
  // It1, Iterator 1, iterates through the list of albums.
  // It2, Iterator 2, iterates through the songs in the album
  for (map<string, Artist>::const_iterator it0 = listOfArtists.begin();
       it0 != listOfArtists.end(); ++it0) {
    // Accessing the first and second members of the map iterator, it0->first is
    // the artist name, it0->second is the object.
    cout << it0->first << ": " << it0->second.nsongs << ", "
         << convertTimeToString(it0->second.time) << endl;

    // Iterate over albums of the current artist, it1->first is the album name,
    // it1->second is the object.
    for (map<string, Album>::const_iterator it1 = it0->second.albums.begin();
         it1 != it0->second.albums.end(); ++it1) {
      cout << "        " << it1->first << ": " << it1->second.nsongs << ", "
           << convertTimeToString(it1->second.time) << endl;

      // Iterate over songs of the current album, it2->first is the song name,
      // it2->second is the object.
      for (map<int, Song>::const_iterator it2 = it1->second.songs.begin();
           it2 != it1->second.songs.end(); ++it2) {
        cout << "                " << it2->first << ". " << it2->second.title
             << ": " << convertTimeToString(it2->second.time) << endl;
      }
    }
  }

  return 0;
}
