#include "SimpleSynthesizer.h"

// Constructor
SimpleSynthesizer::SimpleSynthesizer(Oscillator* _oscillator)
 : Synthesizer()
{
  oscillator = _oscillator;
}

// Destructor
SimpleSynthesizer::~SimpleSynthesizer()
{
}

// Process function
void SimpleSynthesizer::process(float audioBuffer[], int audioBufferLen)
{
  // Loop as many times as the audio buffer has space
  for (int i = 0; i < audioBufferLen; i ++)
  {
    // Add the sample to the buffer
    audioBuffer[i] = oscillator->getSample();

    // Tick the oscillator
    oscillator->tick();
  }
}
