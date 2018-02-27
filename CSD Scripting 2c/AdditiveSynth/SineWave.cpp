#include "SineWave.h"

#include <math.h>

// Constructor
SineWave::SineWave(double sampleRate, double frequency, double amplitude, double phaseOffset) :
  Oscillator(sampleRate,frequency,amplitude,phase)
{
}

// Destructor
SineWave::~SineWave()
{
}

// Calculate the sample based on the phase
double SineWave::calculate()
{
  return sin(phase * PI_2) * amplitude;
}
