#include "Patch.h"
#include <vector>

using namespace std;

// Constructor
Patch::Patch()
{
}

// Destructor
Patch::~Patch()
{
  // Delete operators that are left over
  for (vector<Operator*>::iterator it = operators.begin(); it != operators.end(); ++ it)
    delete *it;
}

// Add an operator
void Patch::addOperator(Operator *op)
{
  operators.push_back(op);
}

// Remove an operator
void Patch::removeOperator(int index)
{
  operators.erase(operators.begin() + index);
}

// Get an operator in the vector
Operator* Patch::getOperator(int index)
{
  return operators.at(index);
}

// Convert this patch to a synthesizer so it can be audible
Synthesizer* Patch::convert(int sampleRate, double baseFrequency)
{
  Synthesizer *synth = new Synthesizer();

  // Iterate over all operators and convert them to oscillators
  for (vector<Operator*>::iterator it = operators.begin(); it != operators.end(); ++ it)
    synth->addOscillator((*it)->convert(sampleRate,baseFrequency));

  // Return the synthesizer
  return synth;
}
