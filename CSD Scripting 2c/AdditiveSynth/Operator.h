#ifndef OPERATOR_H
#define OPERATOR_H

#include "Oscillator.h"

class Operator
{
  public:
    Operator();
    virtual ~Operator();

    // Convert this operator to an oscillator with a base frequency
    virtual Oscillator* convert(int sampleRate, double baseFrequency) = 0;
};

#endif // OPERATOR_H
