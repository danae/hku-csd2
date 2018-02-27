#ifndef SINEWAVE_H
#define SINEWAVE_H

#include "Oscillator.h"

class SineWave : public Oscillator
{
  public:
    // Constructor
    SineWave(double sampleRate, double frequency, double amplitude = 1.0f, double phase = 0.0f);

    // Destructor
    virtual ~SineWave();

    // Calculate the sample based on the phase
    double calculate();
};

#endif // SINEWAVE_H
