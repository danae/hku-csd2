#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

class Synthesizer
{
  public:
    // Convert MIDI notes to frequencies
    static double mtof(int note);

    Synthesizer();
    virtual ~Synthesizer();

    // Tick the synthesizer
    virtual void tick() = 0;

    // Calculate the sample
    virtual double calculate() = 0;
};

#endif // SYNTHESIZER_H
