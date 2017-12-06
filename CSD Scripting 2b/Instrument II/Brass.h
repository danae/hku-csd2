#ifndef BRASS_H
#define BRASS_H

#include <string>
#include "Instrument.h"
using namespace std;

// Brass class
class Brass: public Instrument
{
public:
  // Constructor
  Brass(string name, string sound, string pitchRange);
};

#endif // BRASS_H
