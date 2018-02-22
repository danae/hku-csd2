#include "SineWave.h"

// Constructor
SineWave::SineWave(float frequency, float amplitude, float phaseOffset)
{
  this->frequency = frequency;
  this->amplitude = amplitude;
  this->phaseOffset = phaseOffset;
}

// Destructor
SineWave::~SineWave()
{
}

// Getters and setters
float SineWave::getFrequency()
{
  return frequency;
}
void SineWave::setFrequency(float value)
{
  frequency = value;
}
float SineWave::getAmplitude()
{
  return amplitude;
}
void SineWave::setAmplitude(float value)
{
  amplitude = value;
}
float SineWave::getPhaseOffset()
{
  return phaseOffset;
}
void SineWave::setPhaseOffset(float value)
{
  phaseOffset = value;
}
