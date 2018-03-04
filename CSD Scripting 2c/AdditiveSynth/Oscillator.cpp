#include "Oscillator.h"
#include <stdexcept>

using namespace std;

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
double Oscillator::getFrequency()
{
  return frequency;
}
void Oscillator::setFrequency(double frequency)
{
  if (frequency <= 0.0)
    throw out_of_range("frequency must be higher than 0");

  this->frequency = frequency;
}
double Oscillator::getAmplitude()
{
  return amplitude;
}
void Oscillator::setAmplitude(double amplitude)
{
  if (amplitude < 0.0 || amplitude > 1.0)
    throw out_of_range("amplitude must be between 0 and 1");

  this->amplitude = amplitude;
}
double Oscillator::getPhase()
{
  return phase;
}
void Oscillator::setPhase(double phase)
{
  if (phase < 0.0 || phase > 1.0)
    throw out_of_range("phase must be between 0 and 1");

  this->phase = phase;
}

// Tick the Oscillator
void Oscillator::tick()
{
// Calculate the new phase and vind it between 0-1
  phase += frequency / sampleRate;
  while (phase > 1.0)
    phase -= 1.0;
}
