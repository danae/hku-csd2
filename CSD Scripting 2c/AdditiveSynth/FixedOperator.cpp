#include "FixedOperator.h"
#include "SineWave.h"
#include <sstream>
#include <stdexcept>

using namespace std;

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
  if (frequency <= 0.0)
    throw out_of_range("frequency must be higher than 0");

  return frequency;
}
void FixedOperator::setFrequency(double frequency)
{
  this->frequency = frequency;
}

// Dynamic getter for the prompt
double FixedOperator::get(string parameter)
{
  if (parameter == "frequency")
    return getFrequency();
  else
    // Call the parent function
    return Operator::get(parameter);
}

// Dynamic setter for the prompt
void FixedOperator::set(string parameter, double value)
{
  if (parameter == "frequency")
    setFrequency(value);
  else
    // Call the parent function
    Operator::set(parameter,value);
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
  ss << "Fixed operator (frequency = " << frequency << " Hz, amplitude = " << amplitude << ", phase = " << phase << ")";
  return ss.str();
}
