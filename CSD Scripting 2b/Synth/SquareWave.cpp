#include "SquareWave.h"
#include <cmath>

// Constructor
SquareWave::SquareWave(float _frequency, float _phase)
 : Oscillator(_frequency,_phase)
{
}

// Destructor
SquareWave::~SquareWave()
{
}

// Get the current sample at the current phase
float SquareWave::getSample()
{
  // Get the current time in seconds
  float t = float(sample) / SAMPLE_RATE;

  // Calculate some variables
  float phase_rad = phase * M_PI * 2;
  float frequency_rad = frequency * M_PI * 2;

  // Calculate the sine of the angle
  float sine = sin(frequency_rad * t + phase_rad);

  // Return the sign of the sine
  return (sine > 0) - (sine < 0);
}
