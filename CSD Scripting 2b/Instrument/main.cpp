#include <iostream>
#include "Instrument.h"

using namespace std;

int main()
{
  Instrument* instrument = new Instrument("Toet!");

  std::cout << "Maak een geluid:" << std::endl;
  instrument->makeSound();

  std::cout << "Maak 10 geluiden:" << std::endl;
  instrument->makeMultipleSounds(10);

  std::cout << "Speel een toon:" << std::endl;
  instrument->playTone();

  delete instrument;
  instrument = null;
  return 0;
}
