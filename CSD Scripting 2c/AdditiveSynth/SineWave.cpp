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
  return sin(phase * PI_2) * amplitude;
}
