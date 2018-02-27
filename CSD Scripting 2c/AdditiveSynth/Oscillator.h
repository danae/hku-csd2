#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#define PI_2 6.28318530717959

class Oscillator
{
  protected:
    // Variables
    double sampleRate;
    double frequency;
    double amplitude;
    double phase;

  public:
    // Constructor
    Oscillator(double sampleRate, double frequency, double amplitude, double phase);

    // Destructor
    virtual ~Oscillator();

    // Getters and setters
    double getFrequency();
    double getAmplitude();
    double getPhase();

    // Tick the oscillator
    void tick();

    // Calculate the sample based on the phase
    virtual double calculate() = 0;
};

#endif // OSCILLATOR_H
