#include "Synthesizer.h"
#include <cmath>

// Convert MIDI notes to frequencies
double Synthesizer::mtof(int note)
{
  return 440.0 * pow(2,(note - 57) / 12.0);
}

// Constructor
Synthesizer::Synthesizer()
{
}

// Destructor
Synthesizer::~Synthesizer()
{
}
