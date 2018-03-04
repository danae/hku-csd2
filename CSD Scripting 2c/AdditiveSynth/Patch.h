#ifndef PATCH_H
#define PATCH_H

#include "Operator.h"
#include "Synthesizer.h"
#include "Oscillator.h"
#include <string>
#include <vector>

class Patch
{
  protected:
    // Variables
    double globalRatio;
    double globalDetune;
    std::vector<Operator*> operators;

  public:
    Patch(double globalRatio = 1.0, double globalDetune = 0.0);
    ~Patch();

    // Getters and setters
    double getGlobalRatio();
    void setGlobalRatio(double globalRatio);
    double getGlobalDetune();
    void setGlobalDetune(double globalDetune);

    // Dynamic getter and setter for the prompt
    double get(std::string parameter);
    void set(std::string parameter, double value);

    // Operator management
    void addOperator(Operator *op);
    void removeOperator(Operator *op);
    Operator* getOperator(int index);
    int operatorCount();

    // Remove all operators
    void reset();

    // Convert this patch to a synthesizer so it can be audible
    Synthesizer* convert(int sampleRate, double baseFrequency);

    // Create a string representation for this Patch
    std::string toString(Operator* current = nullptr);
};

#endif // PATCH_H
