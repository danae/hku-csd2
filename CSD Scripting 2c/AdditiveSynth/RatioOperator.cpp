#include "RatioOperator.h"
#include "SineWave.h"

// Constructor
RatioOperator::RatioOperator(double ratio, double detune)
{
  this->ratio = ratio;
  this->detune = detune;
}

// Destructor
RatioOperator::~RatioOperator()
{
}

// Getters and setters
double RatioOperator::getRatio()
{
  return ratio;
}
void RatioOperator::setRatio(double ratio)
{
  this->ratio = ratio;
}
double RatioOperator::getDetune()
{
  return detune;
}
void RatioOperator::setDetune(double detune)
{
  this->detune = detune;
}

// Convert this operator to an oscillator with a base frequency
Oscillator* RatioOperator::convert(int sampleRate, double baseFrequency)
{
  // Calculate the frequency based on ratio and detune
  double frequency = baseFrequency * ratio + detune;

  // Return a new sine wave with the frequency
  return new SineWave(sampleRate,frequency);
}
