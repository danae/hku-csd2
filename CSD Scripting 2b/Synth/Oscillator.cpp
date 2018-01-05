#include "Oscillator.h"

// Constructor
Oscillator::Oscillator(float _frequency)
{
  frequency = _frequency;
  phase = 0.0f;
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

// Increase the phase
void Oscillator::tick()
{

}

// Get the current sample
float Oscillator::getSample()
{
  return 0.0f;
}
