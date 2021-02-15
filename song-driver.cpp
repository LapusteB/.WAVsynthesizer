#include <string>
using namespace std;

#include "song.h"
#include "wavfilewriter.h"

const string INPUT_FILE = "menuet.txt";
const string OUTPUT_FILE = "output.wav";

int main()
{
  //Read in song from file and print
  Song Song(INPUT_FILE);
  cout << Song << endl;

  //Write the song to a WAV file
  WAVFileWriter writer(OUTPUT_FILE);
  writer.setSong(Song);
  writer.writeToFile();

  return 0;
}