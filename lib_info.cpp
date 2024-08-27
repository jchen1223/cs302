// Name: Jeffrey Chen
// Date: 8/26/2024
// Overview:

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
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

// replace underscore function
// https://www.quora.com/How-do-you-replace-a-character-in-a-string-in-C#:~:text=Using%20Loop%20%3A,character%20you%20want%20to%20replace.&text=std%3A%3Acout%20%3C%3C%20str%20%3C,%2F%2F%20Output%3A%20Hella%2C%20warld!&text=To%20replace%20a%20character%20in%20a%20C%2B%2B%20string%2C%20use%20the,specific%20index%20using%20array%20notation.
void replaceUnderscore(string &string) {
  replace(string.begin(), string.end(), '_', ' ');
}

std::string convertTimeToString(int intTime) {
  int remainingMinutes = intTime / 60;
  int remainingSeconds = intTime % 60;

  stringstream minutesStream;
  stringstream secondsStream;

  // for the minutes portion
  minutesStream << remainingMinutes;
  string minutes = minutesStream.str();

  secondsStream << std::setw(2) << setfill('0') << remainingSeconds;
  string seconds = secondsStream.str();

  return minutes + ":" + seconds;
}

int convertTimeToInt(string stringTime) {
  // find to find the colon position, substr to make a seperate string, stoi to
  // convert integer
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
  string file;
  cout << "lib_info ";
  cin >> file;

  // connects to the file
  std::ifstream infile;
  std::string line;
  infile.open(file);

  // while it is able to read the entire line
  while (getline(infile, line)) {
    // Title	Time (m:ss)	Artist	Album	Genre	Track

    stringstream ss(line);
    string temp;

    // instances a new Song struct
    Song *song = new Song();
    ss >> temp;
    replaceUnderscore(temp);
    song->title = temp;

    ss >> temp;

    // convert the time from string to int
    int time = convertTimeToInt(temp);
    song->time = time;

    // skips everything to get to the track
    for (int i = 0; i < 3; i++) {
      getline(ss, temp, ' ');
    }
    ss >> song->track;
  }

  infile.close();
  return 0;
}
