#include "AdditiveSynth.h"
#include <algorithm>

using namespace std;

// Constructor
AdditiveSynth::AdditiveSynth()
{
}

// Destructor
AdditiveSynth::~AdditiveSynth()
{
  // Delete oscillators that are left over
  reset();
}

// Add an oscillator
void AdditiveSynth::addOscillator(Oscillator *oscillator)
{
  oscillators.push_back(oscillator);
}

// Remove an oscillator
void AdditiveSynth::removeOscillator(Oscillator *oscillator)
{
  oscillators.erase(remove(oscillators.begin(),oscillators.end(),oscillator),oscillators.end());
  delete oscillator;
}

// Get an oscillator in the vector
Oscillator* AdditiveSynth::getOscillator(int index)
{
  return oscillators[index];
}

// Remove all oscillators
void AdditiveSynth::reset()
{
  for (Oscillator* oscillator : oscillators)
    delete oscillator;
  oscillators.clear();
}

// Tick all oscillators
void AdditiveSynth::tick()
{
  // Iterate over the oscillators and tick them
  for (Oscillator* oscillator : oscillators)
    oscillator->tick();
}

// Calculate the sample for all oscillators
double AdditiveSynth::calculate()
{
  // Check if there are any oscillators, otherwise just return 0 to prevent DC offset
  if (oscillators.empty())
    return 0.0;

  // Initialize a new sample
  double result = 0.0;

  // Iterate over the oscillators and add the sample of the oscillator to the result
  for (Oscillator* oscillator : oscillators)
    result += oscillator->calculate();

  // Divide the result by the number of oscillators, so the output is max 1.0
  result /= oscillators.size();

  // Return the result
  return result;
}
