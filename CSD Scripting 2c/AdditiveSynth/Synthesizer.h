#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include "Oscillator.h"
#include <vector>

class Synthesizer
{
  protected:
    // Variables
    std::vector<Oscillator*> oscillators;

  public:
    // Convert MIDI notes to frequencies
    static double mtof(int note);

    Synthesizer();
    ~Synthesizer();

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

#endif // SYNTHESIZER_H
