#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>

// Instrument class
class Instrument
{
private:
  // Variables
  std::string sound;

public:
  // Constructor
  Instrument(std::string sound);

  // Make a sound
  void makeSound();

  // Make multiple sounds
  void makeMultipleSounds(int numTimes);

  // Play a tone
  void playTone();
};

#endif // INSTRUMENT_H
