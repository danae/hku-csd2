#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H

#include "Oscillator.h"

// Square wave class
class SquareWave : public Oscillator
{
public:
  // Constructor
  SquareWave(float _frequency, float _phase);

  // Destructor
  virtual ~SquareWave();

  // Get the sample at the current phase
  float getSample();
};

#endif // SQUAREWAVE_H
