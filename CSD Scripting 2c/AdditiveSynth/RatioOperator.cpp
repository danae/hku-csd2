#include "RatioOperator.h"
#include "SineWave.h"
#include <sstream>

using namespace std;

// Constructor
RatioOperator::RatioOperator(double ratio, double detune, double amplitude, double phase) :
  Operator(amplitude,phase)
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

// Dynamic getter for the prompt
double RatioOperator::get(string parameter)
{
  if (parameter == "ratio")
    return getRatio();
  else if (parameter == "detune")
    return getDetune();
  else
    // Call the parent function
    return Operator::get(parameter);
}

// Dynamic setter for the prompt
void RatioOperator::set(string parameter, double value)
{
  if (parameter == "ratio")
    setRatio(value);
  else if (parameter == "detune")
    setDetune(value);
  else
    // Call the parent function
    Operator::set(parameter,value);
}

// Convert this operator to an oscillator with a base frequency
Oscillator* RatioOperator::convert(int sampleRate, double baseFrequency)
{
  // Calculate the frequency based on ratio and detune
  double frequency = baseFrequency * ratio + detune;

  // Return a new sine wave with the frequency
  return new SineWave(sampleRate,frequency,amplitude,phase);
}

// Create a string representation for this operator
std::string RatioOperator::toString()
{
  std::stringstream ss;
  ss << "Ratio operator (ratio = " << ratio << ", detune = " << detune << " Hz, amplitude = " << amplitude << ", phase = " << phase << ")";
  return ss.str();
}
