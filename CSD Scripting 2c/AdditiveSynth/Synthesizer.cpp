#include "Synthesizer.h"

using namespace std;

// COnstructor
Synthesizer::Synthesizer()
{
}

// Destructor
Synthesizer::~Synthesizer()
{
  // Delete oscillators that are left over
  for (vector<Oscillator*>::iterator it = oscillators.begin(); it != oscillators.end(); ++ it)
    delete *it;
}

// Add an oscillator
void Synthesizer::addOscillator(Oscillator *oscillator)
{
  oscillators.push_back(oscillator);
}

// Tick all oscillators
void Synthesizer::tick()
{
  // Iterate over the oscillators and tick them
  for (vector<Oscillator*>::iterator it = oscillators.begin(); it != oscillators.end(); ++ it)
    (*it)->tick();
}

// Calculate the sample for all oscillators
double Synthesizer::calculate()
{
  // Initialize a new sample
  double result = 0.0;

  // Iterate over the oscillators and add the sample of the oscillator to the result
  for (vector<Oscillator*>::iterator it = oscillators.begin(); it != oscillators.end(); ++ it)
    result += (*it)->calculate();

  // Divide the result by the number of oscillators, so the output is max 1.0
  result /= oscillators.size();

  // Return the result
  return result;
}
