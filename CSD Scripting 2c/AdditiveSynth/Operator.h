#ifndef OPERATOR_H
#define OPERATOR_H

#include "Oscillator.h"

class Operator
{
  protected:
    // Variables
    double amplitude;
    double phase;

  public:
    Operator(double amplitude = 1.0, double phase = 0.0);
    virtual ~Operator();

    // Getters and setters
    double getAmplitude();
    void setAmplitude(double amplitude);
    double getPhase();
    void setPhase(double phase);

    // Convert this operator to an oscillator with a base frequency
    virtual Oscillator* convert(int sampleRate, double baseFrequency) = 0;
};

#endif // OPERATOR_H
