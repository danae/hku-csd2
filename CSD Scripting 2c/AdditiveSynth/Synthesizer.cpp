#include "Synthesizer.h"
#include <algorithm>

using namespace std;

// Convert MIDI notes to frequencies
double Synthesizer::mtof(int note)
{
  return 440.0 * pow(2,(note - 57) / 12.0);
}

// Constructor
Synthesizer::Synthesizer()
{
}

// Destructor
Synthesizer::~Synthesizer()
{
  // Delete oscillators that are left over
  for (Oscillator* oscillator : oscillators)
    delete oscillator;
}

// Add an oscillator
void Synthesizer::addOscillator(Oscillator *oscillator)
{
  oscillators.push_back(oscillator);
}

// Remove an oscillator
void Synthesizer::removeOscillator(Oscillator *oscillator)
{
  oscillators.erase(remove(oscillators.begin(),oscillators.end(),oscillator),oscillators.end());
  delete oscillator;
}

// Get an oscillator in the vector
Oscillator* Synthesizer::getOscillator(int index)
{
  return oscillators[index];
}

// Tick all oscillators
void Synthesizer::tick()
{
  // Iterate over the oscillators and tick them
  for (Oscillator* oscillator : oscillators)
    oscillator->tick();
}

// Calculate the sample for all oscillators
double Synthesizer::calculate()
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
