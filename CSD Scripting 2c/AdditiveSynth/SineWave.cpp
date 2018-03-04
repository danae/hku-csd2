#include "SineWave.h"
#include <math.h>

// Constructor
SineWave::SineWave(int sampleRate, double frequency, double amplitude, double phase) :
  Oscillator(sampleRate,frequency,amplitude,phase)
{
}

// Destructor
SineWave::~SineWave()
{
}

// Calculate the sample based on the phase and the base frequency
double SineWave::calculate()
{
  // Check if the frequency is not 0, otherwise just return 0 to prevent DC offset
  if (frequency == 0)
    return 0.0;

  return sin(phase * PI_2) * amplitude;
}
