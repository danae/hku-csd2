#include "SineWave.h"
#include <cmath>

// Constructor
SineWave::SineWave(float _frequency, float _phase)
 : Oscillator(_frequency,_phase)
{
}

// Destructor
SineWave::~SineWave()
{
}

// Get the current sample at the current phase
float SineWave::getSample()
{
  // Get the current time in seconds
  float t = float(sample) / SAMPLE_RATE;

  // Calculate some variables
  float phase_rad = phase * M_PI * 2;
  float frequency_rad = frequency * M_PI * 2;

  // Return the sine of the angle
  return sin(frequency_rad * t + phase_rad);
}
