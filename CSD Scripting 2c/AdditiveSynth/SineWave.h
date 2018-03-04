#ifndef SINEWAVE_H
#define SINEWAVE_H

#include "Oscillator.h"

class SineWave : public Oscillator
{
  public:
    SineWave(int sampleRate, double frequency, double amplitude = 1.0, double phase = 0.0);
    ~SineWave();

    // Calculate the sample based on the phase
    double calculate();
};

#endif // SINEWAVE_H
