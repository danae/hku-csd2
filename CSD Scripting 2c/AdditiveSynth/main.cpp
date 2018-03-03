#include <iostream>
#include <jack/jack.h>
#include <math.h>

#include "jack_module.h"
#include "Synthesizer.h"
#include "SineWave.h"
#include "Patch.h"
#include "RatioOperator.h"

using namespace std;

// Convert MIDI notes to frequency
double mtof(int midiNote)
{
  return 440.0 * pow(2,(midiNote - 57) / 12.0);
}

// Main function
int main(int argc, const char** argv)
{
  // Create a JackModule instance
  JackModule jack;
  jack.init("AdditiveSynth");

  // Create a new patch
  Patch* patch = new Patch();

  // Add operators
  patch->addOperator(new RatioOperator(1.0));
  patch->addOperator(new RatioOperator(1.5));
  patch->addOperator(new RatioOperator(2.0,-20));

  // Create a new synth based on the patch
  Synthesizer *synth = patch->convert(jack.getSamplerate(),mtof(48));

  // Create a callback for the Jack module
  jack.onProcess = [&synth](jack_default_audio_sample_t* inBuf, jack_default_audio_sample_t* outBuf, jack_nframes_t nframes)
  {
    for(int i = 0; i < nframes; i++)
    {
      // Check if the synth is already made
      if (synth != nullptr)
      {
        // Fill the buffer with the current sample value
        outBuf[i] = synth->calculate();
        synth->tick();
      }
    }

    return 0;
  };

  // Connect to Jack
  jack.autoConnect();

  // Main loop
  std::cout << "Press 'q' when you want to quit the program.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        break;
    }
  }

  // Cleanup
  delete synth;
  delete patch;

  // End
  return 0;
}
