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
    Synthesizer();
    virtual ~Synthesizer();

    // Oscillator management
    void addOscillator(Oscillator *oscillator);
    void removeOscillator(int index);
    Oscillator* getOscillator(int index);

    // Tick all oscillators
    void tick();

    // Calculate the sample for all oscillators
    double calculate();
};

#endif // SYNTHESIZER_H
