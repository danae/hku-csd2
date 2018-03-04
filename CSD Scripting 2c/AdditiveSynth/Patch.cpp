#include "Patch.h"
#include <sstream>
#include <algorithm>

using namespace std;

// Constructor
Patch::Patch()
{
}

// Destructor
Patch::~Patch()
{
  // Delete operators that are left over
  reset();
}

// Add an operator
void Patch::addOperator(Operator *op)
{
  operators.push_back(op);
}

// Remove an operator
void Patch::removeOperator(Operator *op)
{
  operators.erase(remove(operators.begin(),operators.end(),op),operators.end());
  delete op;
}

// Get an operator in the vector
Operator* Patch::getOperator(int index)
{
  return operators[index];
}

// Remove all operators
void Patch::reset()
{
  for (Operator* op : operators)
    delete op;
  operators.clear();
}

// Convert this patch to a synthesizer so it can be audible
Synthesizer* Patch::convert(int sampleRate, double baseFrequency)
{
  Synthesizer *synth = new Synthesizer();

  // Iterate over all operators and convert them to oscillators
  for (Operator *op : operators)
    synth->addOscillator(op->convert(sampleRate,baseFrequency));

  // Return the synthesizer
  return synth;
}

void Patch::convert(Synthesizer *synthesizer, int sampleRate, double baseFrequency)
{
  synthesizer->reset();
  for (Operator *op : operators)
    synthesizer->addOscillator(op->convert(sampleRate,baseFrequency));
}

// Create a string representation for this operator
string Patch::toString(Operator* current)
{
  stringstream ss;

  // Print current patch info
  ss << "Current patch contains " << operators.size() << " operators:";

  // Print all operators
  for (int i = 0; i < operators.size(); i ++)
  {
    Operator *op = operators[i];
    ss << endl;

    // If the op is selected, print an arrow
    if (current == op)
      ss << "--> ";
    else
      ss << "    ";

    // Print the op string
    ss << i << ". " << op->toString();
  }

  return ss.str();
}
