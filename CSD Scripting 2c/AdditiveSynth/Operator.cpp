#include "Operator.h"
#include <stdexcept>

using namespace std;

// Constructor
Operator::Operator(double amplitude, double phase)
{
  setAmplitude(amplitude);
  setPhase(phase);
}

// Desctructor
Operator::~Operator()
{
}

// Getters and setters
double Operator::getAmplitude()
{
  return amplitude;
}
void Operator::setAmplitude(double amplitude)
{
  if (amplitude < 0.0 || amplitude > 1.0)
    throw out_of_range("amplitude must be between 0 and 1");

  this->amplitude = amplitude;
}
double Operator::getPhase()
{
  return phase;
}
void Operator::setPhase(double phase)
{
  if (phase < 0.0 || phase > 1.0)
    throw out_of_range("phase must be between 0 and 1");

  this->phase = phase;
}

// Dynamic getter for the prompt
double Operator::get(string parameter)
{
  if (parameter == "amplitude")
    return getAmplitude();
  else if (parameter == "phase")
    return getPhase();
  else
    throw invalid_argument(parameter);
}

// Dynamic setter for the prompt
void Operator::set(string parameter, double value)
{
  if (parameter == "amplitude")
    setAmplitude(value);
  else if (parameter == "phase")
    setPhase(value);
  else
    throw invalid_argument(parameter);
}
