#ifndef SINEWAVE_H
#define SINEWAVE_H

class SineWave
{
  private:
    // Variables
    float frequency;
    float amplitude;
    float phaseOffset;

  public:
    // Constructor
    SineWave(float frequency, float amplitude = 1.0f, float phaseOffset = 0.0f);

    // Destructor
    virtual ~SineWave();

    // Getters ans setters
    float getFrequency();
    void setFrequency(float value);
    float getAmplitude();
    void setAmplitude(float value);
    float getPhaseOffset();
    void setPhaseOffset(float value);
};

#endif // SINEWAVE_H
