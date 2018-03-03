#ifndef PATCH_H
#define PATCH_H

#include "Operator.h"
#include "Synthesizer.h"
#include "Oscillator.h"
#include <string>

class Patch
{
  public:
    // Variables
    std::vector<Operator*> operators;

  public:
    Patch();
    virtual ~Patch();

    // Operator management
    void addOperator(Operator *op);
    void removeOperator(int index);
    Operator* getOperator(int index);

    // Convert this patch to a synthesizer so it can be audible
    Synthesizer* convert(int sampleRate, double baseFrequency);

    // Create a string representation for this Patch
    std::string toString();
};

#endif // PATCH_H
