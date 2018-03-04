#ifndef PATCH_H
#define PATCH_H

#include "Operator.h"
#include "Synthesizer.h"
#include "Oscillator.h"
#include <string>
#include <vector>

class Patch
{
  public:
    // Variables
    std::vector<Operator*> operators;

    Patch();
    ~Patch();

    // Operator management
    void addOperator(Operator *op);
    void removeOperator(Operator *op);
    Operator* getOperator(int index);

    // Remove all operators
    void reset();

    // Convert this patch to a synthesizer so it can be audible
    Synthesizer* convert(int sampleRate, double baseFrequency);

    // Create a string representation for this Patch
    std::string toString(Operator* current = nullptr);
};

#endif // PATCH_H
