#include <iostream>
#include <jack/jack.h>
#include <math.h>

#include "jack_module.h"
#include "Synthesizer.h"
#include "SineWave.h"

#define COUNT 3

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

  // Create a new synth
  Synthesizer *synth = new Synthesizer();

  // Add a sine wave
  double notes[COUNT] = {mtof(48),mtof(60),mtof(72)};
  for (int i = 0; i < COUNT; i ++)
  {
    cout << i << ": " << notes[i] << endl;
    synth->addOscillator(new SineWave(jack.getSamplerate(),notes[i]));
  }

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

  // End
  return 0;
}
