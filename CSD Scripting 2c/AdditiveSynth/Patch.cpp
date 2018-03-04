#include "Patch.h"
#include "AdditiveSynth.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Constructor
Patch::Patch(double globalRatio, double globalDetune)
{
  setGlobalRatio(globalRatio);
  setGlobalDetune(globalDetune);
}

// Destructor
Patch::~Patch()
{
  // Delete operators that are left over
  reset();
}

// Getters and setters
double Patch::getGlobalRatio()
{
  return globalRatio;
}
void Patch::setGlobalRatio(double globalRatio)
{
  if (globalRatio <= 0.0)
    throw out_of_range("ratio must be higher than 0");

  this->globalRatio = globalRatio;
}
double Patch::getGlobalDetune()
{
  return globalDetune;
}
void Patch::setGlobalDetune(double globalDetune)
{
  this->globalDetune = globalDetune;
}

// Dynamic getter for the prompt
double Patch::get(string parameter)
{
  if (parameter == "ratio")
    return getGlobalRatio();
  else if (parameter == "detune")
    return getGlobalDetune();
  else
    throw invalid_argument(parameter);
}

// Dynamic setter for the prompt
void Patch::set(string parameter, double value)
{
  if (parameter == "ratio")
    setGlobalRatio(value);
  else if (parameter == "detune")
    setGlobalDetune(value);
  else
    throw invalid_argument(parameter);
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

// Return the number of operators
int Patch::operatorCount()
{
  return operators.size();
}

// Get an operator in the vector
Operator* Patch::getOperator(int index)
{
  return operators[index];
}

// Remove all operators
void Patch::reset()
{
  // Delete and dereference all operators
  for (Operator* op : operators)
    delete op;
  operators.clear();

  // Reset the global variables
  setGlobalRatio(1.0);
  setGlobalDetune(0.0);
}

// Convert this patch to a synthesizer so it can be audible
Synthesizer* Patch::convert(int sampleRate, double baseFrequency)
{
  AdditiveSynth *synth = new AdditiveSynth();

  // Calculate the frequency
  double appliedBaseFrequency = baseFrequency * globalRatio + globalDetune;

  // Iterate over all operators and convert them to oscillators
  for (Operator *op : operators)
    synth->addOscillator(op->convert(sampleRate,appliedBaseFrequency));

  // Return the synthesizer
  return synth;
}

// Create a string representation for this operator
string Patch::toString(Operator* current)
{
  stringstream ss;

  // Print current patch info
  ss << "Current patch (global ratio = " << globalRatio << ", global detune = " << globalDetune << " Hz) contains " << operators.size() << " operators";

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
