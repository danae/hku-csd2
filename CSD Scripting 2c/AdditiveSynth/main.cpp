#include <iostream>
#include <jack/jack.h>

#include "jack_module.h"
#include "Synthesizer.h"
#include "SineWave.h"

using namespace std;

int main(int argc, const char** argv)
{
  // Create a JackModule instance
  JackModule jack;

  // Init the Jack module
  jack.init("AdditiveSynth");

  // Create a new synthesizer
  Synthesizer *synth = new Synthesizer();

  // Add a sine wave
  for (int i = 0; i < 16; i ++)
    synth->addOscillator(new SineWave(jack.getSamplerate(),440 * i));

  // Create a callback for the Jack module
  jack.onProcess = [&synth](jack_default_audio_sample_t* inBuf, jack_default_audio_sample_t* outBuf, jack_nframes_t nframes)
  {
    for(int i = 0; i < nframes; i++)
    {
      outBuf[i] = synth->calculate();
      synth->tick();
    }

    return 0;
  };

  // Connect to Jack
  jack.autoConnect();

  // Main loop
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
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

  // End
  return 0;
}
