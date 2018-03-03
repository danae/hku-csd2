#ifndef RATIOOPERATOR_H
#define RATIOOPERATOR_H

#include "Operator.h"
#include "Oscillator.h"

class RatioOperator : public Operator
{
  protected:
    // Variables
    double ratio;
    double detune;

  public:
    RatioOperator(double ratio = 1.0, double detune = 0.0);
    virtual ~RatioOperator();

    // Getters and setters
    double getRatio();
    void setRatio(double ratio);
    double getDetune();
    void setDetune(double detune);

    // Convert this operator to an oscillator with a base frequency
    Oscillator* convert(int sampleRate, double baseFrequency);
};

#endif // RATIOOPERATOR_H
