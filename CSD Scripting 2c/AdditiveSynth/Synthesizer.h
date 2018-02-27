#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <vector>
#include "Oscillator.h"

class Synthesizer
{
  protected:
    // Variables
    std::vector<Oscillator*> oscillators;

  public:
    // Constructor
    Synthesizer();

    // Destructor
    virtual ~Synthesizer();

    // Add an oscillator
    void addOscillator(Oscillator *oscillator);

    // Tick all oscillators
    void tick();

    // Calculate the sample for all oscillators
    double calculate();
};

#endif // SYNTHESIZER_H
