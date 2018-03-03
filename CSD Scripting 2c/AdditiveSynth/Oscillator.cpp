#include "Oscillator.h"

// Constructor
Oscillator::Oscillator(int sampleRate, double frequency, double amplitude, double phase)
{
  this->sampleRate = sampleRate;
  this->frequency = frequency;
  this->amplitude = amplitude;
  this->phase = phase;
}

// Destructor
Oscillator::~Oscillator()
{
}

// Getters and setters
int Oscillator::getSampleRate()
{
  return sampleRate;
}
double Oscillator::getFrequency()
{
  return frequency;
}
double Oscillator::getAmplitude()
{
  return amplitude;
}
double Oscillator::getPhase()
{
  return phase;
}

// Tick the Oscillator
void Oscillator::tick()
{
// Calculate the new phase and vind it between 0-1
  phase += frequency / sampleRate;
  while (phase > 1.0)
    phase -= 1.0;
}
