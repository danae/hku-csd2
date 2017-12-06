#ifndef KEYS_H
#define KEYS_H

#include <string>
#include "Instrument.h"
using namespace std;

// Keys class
class Keys : public Instrument
{
public:
  Keys(string name, string sound, string pitchRange);
};

#endif // KEYS_H
