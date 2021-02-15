#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "song.h"
#include "wavfilewriter.h"


Note::Note(string str)
{

string p;
int flat, sharp, period, oct;
char dur;
int size, length;

  //flat = str.find("b");
  //sharp = str.find("#");
  period = str.find(".");
  size = str.size();


 if (period == -1)//no period
    {
      switch(size){
        case 3://Bb3e
          length = 1;
          p = str.substr(0, length);
          break;
        default://G2q
          length = 2;
          p = str.substr(0, length);
          break;
        }
    } else if(size == 4)
    {
      switch(size)
      {
        case 4://Bb3h.
        length = 1;
        p = str.substr(0, length);
        break;
        default:
        length = 2;
        p = str.substr(0, length);
        break;
      }
    }

oct = str.at(length) - '0'; 
 octave = oct;
 length++;
 dur = str.at(length);



//---------------start setting struct------------//

    if(p == "R")
      pitch = REST;
    else if(p == "C")
      pitch = C;
    else if(p == "D")
      pitch = D;
    else if(p == "E")
      pitch = E;
    else if(p == "F")
      pitch = F;
    else if(p == "G")
      pitch = G;
    else if(p == "A")
      pitch = A;
    else if(p == "B")
      pitch = B;
    else if(p == "C#" || p == "Db")
      pitch = Db;
    else if(p == "D#" || p == "Eb")
      pitch = Eb;
    else if(p == "F#" || p == "Gb")
      pitch = Gb;
    else if(p == "G#" || p == "Ab")
      pitch = Ab;
    else if(p == "A#" || p == "Bb")
      pitch = Bb;

  if(dur == 'q')
    duration = 1;
  if(dur == 'h')
    duration = 2;
  if(dur == 'w')
  duration = 4;
  if(dur == 'e')
  duration = 0.5;
  if(dur == 's')
  duration = 0.25;
  if(period != -1)
  {
    duration *= 1.5;
  }

}


Voice::Voice(const string& str, double vol, instrument_t instr)
{
clear();
setVolume(vol);
setInstrument(instr);

    istringstream iss(str);
    string line;
    while(iss>>line)
    {
    
    Note note(line);
    addNote(note);
    }



}


Song::Song(const string& file)
{
Note notes;
unsigned bpm;
string line;
ifstream in(file);
in>>bpm;
//bpm = tempo;
setTempo(bpm);

   
while(!(in.eof()))
{

  //clear(); --- this will play only one line
  //in.clear(); -- same here

    getline(in, line);
    Voice Voice(line);
    addVoice(Voice);
  

}
in.close();

}
//print notes like text
ostream& operator<<(ostream& out, const Note& Note)
{
    if(Note.getPitch() == REST)
        out<<"R";
    else if(Note.getPitch() == A)
        out<<"A";
    else if(Note.getPitch() == B)
        out<<"B";
    else if(Note.getPitch() == C)
        out<<"C";
    else if(Note.getPitch() == D)
        out<<"D";
    else if(Note.getPitch() == E)
        out<<"E";
    else if(Note.getPitch() == F)
        out<<"F";
    else if(Note.getPitch() == G)
        out<<"G";
    else if(Note.getPitch() == Ab)
        out<<"Ab";
    else if(Note.getPitch() == Bb)
        out<<"Bb";

    else if(Note.getPitch() == Db)
        out<<"Db";
    else if(Note.getPitch() == Eb)
        out<<"Eb";
  
    else if(Note.getPitch() == Gb)
        out<<"Gb";

    out << Note.getOctave();
//----------Duration Data--------//

    if(Note.getDuration() == 1)
        out<<'g';
    if(Note.getDuration() == 2)
        out <<'h';
    if(Note.getDuration() == 4)
        out<<'w';
    if(Note.getDuration() == 0.5)
        out<<'e';
    if(Note.getDuration() == 0.25)
        out<<'s';
    if(Note.getDuration() == 1.5)
        out<<"g.";
    if(Note.getDuration() == 3)
        out<<"h.";
    if(Note.getDuration() == 6)
        out<<"w.";
    if(Note.getDuration() == 0.75)
        out<<"e.";
    if(Note.getDuration() == 0.375)
        out<<"s.";
    return out;
}

//print voices
ostream& operator<<(ostream& out, const Voice& v)
{
    vector<Note> vec = v.getNotes();
    for(int i = 0; i<vec.size(); i++)
      out << vec[i] <<" ";
    
    return out;
}

//print songs
ostream& operator<<(ostream& out, const Song& s)
{
    unsigned temp = s.getTempo();
    out << temp << endl;
    vector<Voice> Vvec = s.getVoices();
    for(int i=0; i<Vvec.size(); i++)
    {
        out<<Vvec[i]<<endl;
    }
    return out;
}



