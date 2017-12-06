#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include "Instrument.h"
using namespace std;

// Strings class
class Strings: public Instrument
{
public:
  // Constructor
  Strings(string name, string sound, string pitchRange);
};

#endif // STRINGS_H
