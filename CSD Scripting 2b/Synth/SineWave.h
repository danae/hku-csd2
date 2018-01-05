#ifndef SINEWAVE_H
#define SINEWAVE_H

#include "Oscillator.h"

// Sine wave class
class SineWave : public Oscillator
{
public:
  // Constructor
  SineWave(float _frequency, float _phase);

  // Destructor
  virtual ~SineWave();

  // Get the sample at the current phase
  float getSample();
};

#endif // SINEWAVE_H
