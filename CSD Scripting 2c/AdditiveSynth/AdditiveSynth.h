#ifndef ADDITIVESYNTH_H
#define ADDITIVESYNTH_H

#include "Synthesizer.h"
#include "Oscillator.h"
#include <vector>

class AdditiveSynth : public Synthesizer
{
  protected:
    // Variables
    std::vector<Oscillator*> oscillators;

  public:
    AdditiveSynth();
    ~AdditiveSynth();

    // Oscillator management
    void addOscillator(Oscillator *oscillator);
    void removeOscillator(Oscillator* oscillator);
    Oscillator* getOscillator(int index);

    // Remove all oscillators
    void reset();

    // Tick all oscillators
    void tick();

    // Calculate the sample for all oscillators
    double calculate();
};

#endif // ADDITIVESYNTH_H
