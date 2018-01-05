#include <iostream>

#include "Oscillator.h"
#include "Synthesizer.h"
#include "SimpleSynthesizer.h"

using namespace std;

int main()
{
  // Create an audio buffer
  float audioBuffer[256] = {0.0f};

  // Create a new Oscillator
  Oscillator* oscillator = new Oscillator(440.0f);

  // Create a synthesizer with the oscillator
  Synthesizer* synthesizer = new SimpleSynthesizer(oscillator);

  // Process
  synthesizer->process(audioBuffer,256);

  // Print the result
  for (int i = 0; i < 256; i ++)
  {
    std::cout << i << ": " << audioBuffer[i] << std::endl;
  }

  // Delete resources
  delete synthesizer;
  delete oscillator;

 // Return
  return 0;
}
