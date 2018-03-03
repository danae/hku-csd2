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
  cout << patch->toString() << endl << endl;

  // Create a new synth based on the patch
  update(mtof(60));

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

  // Add commands to the prmpt
  prompt.add("add",[&](string command, vector<string> args) {
    if (args.size() == 1)
    {
      cout << "Do you want to add a (R)atio or a (F)ixed operator? ";
      switch (prompt.getChar())
      {
        case 'r':
        case 'R':
        default:
          cout << "You selected ratio" << endl;
          break;

        case 'f':
        case 'F':
          prompt.execute("addfixed");
          break;
      }
      cin.ignore(1);
    }

    return false;
  });

  // Add a command for adding ratio operators
  prompt.add("addratio",[&](string command, vector<string> args) {
    cout << "Enter the following parameters for your new fixed operator:" << endl;

    cout << "- Ratio (default 1.0): ";
    double ratio = prompt.getDouble(1.0);

    cout << "- Detune (default 0 Hz): ";
    double detune = prompt.getDouble(0);

    cout << "- Amplitude (default 1.0): ";
    double amplitude = prompt.getDouble(1.0);

    cout << "- Phase (default 0.0): ";
    double phase = prompt.getDouble(0.0);

    Operator* op = new RatioOperator(ratio,detune,amplitude,phase);
    patch->addOperator(op);
    update(mtof(60));

    cout << endl << patch->toString() << endl << endl;

    return false;
  });

  // Add a command for adding fixed operators
  prompt.add("addfixed",[&](string command, vector<string> args) {
    cout << "Enter the following parameters for your new fixed operator:" << endl;

    cout << "- Frequency (default 440 Hz): ";
    double frequency = prompt.getDouble(440);

    cout << "- Amplitude (default 1.0): ";
    double amplitude = prompt.getDouble(1.0);

    cout << "- Phase (default 0.0): ";
    double phase = prompt.getDouble(0.0);

    Operator* op = new FixedOperator(frequency,amplitude,phase);
    patch->addOperator(op);
    update(mtof(60));

    cout << endl << patch->toString() << endl << endl;

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
