#include "Oscillator.h"

// Constructor
Oscillator::Oscillator(float _frequency, float _phase)
{
  frequency = _frequency;
  phase = _phase;
  sample = 0;
}

// Destructor
Oscillator::~Oscillator()
{
}

// Return the frequency of the oscillator
float Oscillator::getFrequency()
{
  return frequency;
}

// Return the phase of the oscillator
float Oscillator::getPhase()
{
  return phase;
}

// Increase the sample number
void Oscillator::tick()
{
  sample++;
}

// Get the current sample at the current phase
float Oscillator::getSample()
{
  return 0.0f;
}
