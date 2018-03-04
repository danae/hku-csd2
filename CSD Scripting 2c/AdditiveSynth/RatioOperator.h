#ifndef RATIOOPERATOR_H
#define RATIOOPERATOR_H

#include "Operator.h"
#include "Oscillator.h"
#include <string>

class RatioOperator : public Operator
{
  protected:
    // Variables
    double ratio;
    double detune;

  public:
    RatioOperator(double ratio, double detune = 0.0, double amplitude = 1.0, double phase = 0.0);
    virtual ~RatioOperator();

    // Getters and setters
    double getRatio();
    void setRatio(double ratio);
    double getDetune();
    void setDetune(double detune);

    // Dynamic getter and setter for the prompt
    double get(std::string parameter);
    void set(std::string parameter, double value);

    // Convert this operator to an oscillator with a base frequency
    Oscillator* convert(int sampleRate, double baseFrequency);

    // Create a string representation for this operator
    std::string toString();
};

#endif // RATIOOPERATOR_H
