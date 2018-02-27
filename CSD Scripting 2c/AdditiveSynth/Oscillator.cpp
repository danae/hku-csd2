#include "Oscillator.h"

// Constructor
Oscillator::Oscillator(double sampleRate, double frequency, double amplitude = 1.0, double phase = 0.0)
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
  // Calculate the new phase
  phase += frequency / sampleRate;
  if (phase >= 1)
    phase -= 1;
}
