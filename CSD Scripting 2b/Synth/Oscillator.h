#ifndef OSCILLATOR_H
#define OSCILLATOR_H

// Oscillator class
class Oscillator
{
private:
  float frequency;
  float phase;

public:
  // Constructor
  Oscillator(float _frequency);

  // Destructor
  virtual ~Oscillator();

  // Return the frequency of the oscillator
  float getFrequency();

    // Return the phase of the oscillator
  float getPhase();

  // Increase the phase
  void tick();

  // Generate the sample at the current phase
  virtual float getSample();
};

#endif // OSCILLATOR_H
