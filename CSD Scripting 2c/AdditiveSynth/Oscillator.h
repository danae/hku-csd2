#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#define PI_2 6.28318530717959

class Oscillator
{
  protected:
    // Variables
    int sampleRate;

    double frequency;
    double amplitude;
    double phase;

  public:
    Oscillator(int sampleRate, double frequency, double amplitude = 1.0, double phase = 0.0);
    virtual ~Oscillator();

    // Getters and setters
    double getFrequency();
    void setFrequency(double frequency);
    double getAmplitude();
    void setAmplitude(double amplitude);
    double getPhase();
    void setPhase(double phase);

    // Tick the oscillator
    void tick();

    // Calculate the sample based on the phase
    virtual double calculate() = 0;
};

#endif // OSCILLATOR_H
