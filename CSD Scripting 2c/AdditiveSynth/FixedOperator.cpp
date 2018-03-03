#include "FixedOperator.h"
#include "SineWave.h"
#include <sstream>

// Constructor
FixedOperator::FixedOperator(double frequency, double amplitude, double phase) :
  Operator(amplitude,phase)
{
  this->frequency = frequency;
}

// Destructor
FixedOperator::~FixedOperator()
{
}

// Getters and setters
double FixedOperator::getFrequency()
{
  return frequency;
}
void FixedOperator::setFrequency(double frequency)
{
  this->frequency = frequency;
}

// Convert this operator to an oscillator with a base frequency
Oscillator* FixedOperator::convert(int sampleRate, double baseFrequency)
{
  // The base frequency is ignored since the frequency is already fixed
  // Return a new sine wave with the frequency
  return new SineWave(sampleRate,frequency,amplitude,phase);
}

// Create a string representation for this operator
std::string FixedOperator::toString()
{
  std::stringstream ss;
  ss << "Fixed operator (freq = " << frequency << " Hz, amplitude = " << amplitude << ")";
  return ss.str();
}
