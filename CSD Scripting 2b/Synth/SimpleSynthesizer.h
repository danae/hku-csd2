#ifndef SIMPLE_SYNTHESIZER_H
#define SIMPLE_SYNTHESIZER_H

#include "Synthesizer.h"
#include "Oscillator.h"

// Simple synthesizer class
class SimpleSynthesizer : public Synthesizer
{
private:
  Oscillator* oscillator;

public:
  // Constructor
  SimpleSynthesizer(Oscillator* _oscillator);

  // Destructor
  virtual ~SimpleSynthesizer();

  // Process function
  void process(float audioBuffer[], int audioBufferLen);
};

#endif // SIMPLESYNTHESIZER_H
