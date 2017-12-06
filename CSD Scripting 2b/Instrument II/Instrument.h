#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>
using namespace std;

// Instrument class
class Instrument
{
private:
  // Variables
  string type;
  string name;
  string sound;
  string pitchRange;

public:
  // Constructor
  Instrument(string type, string name, string sound, string pitchRange);

  // Make a sound
  void makeSound();

  // Make multiple sounds
  void makeMultipleSounds(int numTimes);
};

#endif // INSTRUMENT_H
