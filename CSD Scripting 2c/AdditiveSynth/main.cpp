#include <iostream>
#include <vector>
#include <math.h>
#include <jack/jack.h>

#include "jack_module.h"
#include "Synthesizer.h"
#include "SineWave.h"
#include "Patch.h"
#include "RatioOperator.h"
#include "FixedOperator.h"
#include "Prompt.h"

using namespace std;

// Global variables
JackModule jack; // Holds the Jack module for audio
Patch *patch = nullptr; // Holds the current patch
Synthesizer *synth = nullptr; // Holds the synthesizer converted from the patch
Prompt prompt; // Contains the UI functions

// Convert MIDI notes to frequency
double mtof(int midiNote)
{
  return 440.0 * pow(2,(midiNote - 57) / 12.0);
}

// Update the synthesizer to the current patch
void update(double frequency)
{
  synth = patch->convert(jack.getSamplerate(),frequency);
}

// Main function
int main(int argc, const char** argv)
{
  // Create a JackModule instance
  jack.init("AdditiveSynth");

  // Create a new patch
  patch = new Patch();
  cout << patch->toString() << endl;

  // Create a new synth based on the patch
  update(mtof(60));

  // Create a callback for the Jack module
  jack.onProcess = [&synth](jack_default_audio_sample_t* inBuf, jack_default_audio_sample_t* outBuf, jack_nframes_t nframes)
  {
    for(uint32_t i = 0; i < nframes; i++)
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

  // Add a command for adding ratio operators
  prompt.add("addratio",[&](string command, vector<string> args) {
    // Usage: addratio <ratio> [detune = 0.0] [amplitude = 1.0] [phase = 0.0]
    if (args.size() < 2)
    {
      cout << "Usage: addratio <ratio = 1.0> [detune = 0.0] [amplitude = 1.0] [phase = 0.0]" << endl;
    }
    else
    {
      // Get the arguments
      double ratio = Prompt::stringToDouble(args[1],1.0);

      double detune = 0.0;
      if (args.size() > 2)
        detune = Prompt::stringToDouble(args[2],0.0);

      double amplitude = 1.0;
      if (args.size() > 3)
        amplitude = Prompt::stringToDouble(args[3],1.0);

      double phase = 1.0;
      if (args.size() > 4)
        phase = Prompt::stringToDouble(args[4],1.0);

      // Add the new operator
      Operator* op = new RatioOperator(ratio,detune,amplitude,phase);
      patch->addOperator(op);
      update(mtof(60));

      cout << patch->toString() << endl;
    }

    return false;
  });

  // Add a command for adding fixed operators
  prompt.add("addfixed",[&](string command, vector<string> args) {
    // Usage: addratio <ratio> [detune = 0.0] [amplitude = 1.0] [phase = 0.0]
    if (args.size() < 2)
    {
      cout << "Usage: addfixed <frequency = 440> [amplitude = 1.0] [phase = 0.0]" << endl;
    }
    else
    {
      // Get the arguments
      double frequency = Prompt::stringToDouble(args[1],440);

      double amplitude = 1.0;
      if (args.size() > 2)
        amplitude = Prompt::stringToDouble(args[2],1.0);

      double phase = 1.0;
      if (args.size() > 3)
        phase = Prompt::stringToDouble(args[3],1.0);

      // Add the new operator
      Operator* op = new FixedOperator(frequency,amplitude,phase);
      patch->addOperator(op);
      update(mtof(60));

      cout << patch->toString() << endl;
    }

    return false;
  });

  // Use the prompt to provice a user interface
  prompt.run();

  // Cleanup
  if (synth != nullptr)
    delete synth;
  if (patch != nullptr)
    delete patch;

  // End
  return 0;
}
