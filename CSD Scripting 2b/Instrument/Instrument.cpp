#include <iostream>
#include "Instrument.h"

// Constructor
Instrument::Instrument(std::string sound)
{
  this->sound = sound;
}

// Make a sound
void Instrument::makeSound()
{
  // Print the sound of the instruemnt
  std::cout << this->sound << std::endl;
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

// Play a tone
void Instrument::playTone()
{
  // Print a tone
  std::cout << "AAAAAA" << std::endl;
}
