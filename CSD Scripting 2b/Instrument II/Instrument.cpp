#include <iostream>
#include <typeinfo>
#include "Instrument.h"
using namespace std;

// Constructor
Instrument::Instrument(string type, string name, string sound, string pitchRange)
{
  this->type = type;
  this->name = name;
  this->sound = sound;
  this->pitchRange = pitchRange;
}

// Make a sound
void Instrument::makeSound()
{
  // Print the name, sound of the instrument
  cout << "<" << this->name << " (" << this->type << ") with pitch range " << this->pitchRange << "> " << this->sound << endl;
}

// Make multiple sounds
void Instrument::makeMultipleSounds(int numTimes)
{
  // Loop for numTimes
  for (int i = 0; i < numTimes; i ++)
  {
    // Make sound
    this->makeSound();
  }
}
