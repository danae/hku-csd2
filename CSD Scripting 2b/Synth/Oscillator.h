#ifndef OSCILLATOR_H
#define OSCILLATOR_H

// Sample rate
#define SAMPLE_RATE 256

// Oscillator class
class Oscillator
{
public:
  float frequency;
  float phase;
  int sample;

//public:
  // Constructor
  Oscillator(float _frequency, float _phase);

  // Destructor
  virtual ~Oscillator();

  // Return the frequency of the oscillator
  float getFrequency();

    // Return the phase of the oscillator
  float getPhase();

  // Increase the phase
  void tick();

  // Get the sample at the current phase
  virtual float getSample();
};

#endif // OSCILLATOR_H
