#include "Operator.h"

// Constructor
Operator::Operator(double amplitude, double phase)
{
  this->amplitude = amplitude;
  this->phase = phase;
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
  this->amplitude = amplitude;
}
double Operator::getPhase()
{
  return phase;
}
void Operator::setPhase(double phase)
{
  this->phase = phase;
}
