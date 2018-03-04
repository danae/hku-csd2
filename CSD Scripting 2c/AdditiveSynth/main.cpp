#include <iostream>
#include <vector>
#include <math.h>
#include <jack/jack.h>

#include "jack_module.h"
#include "Synthesizer.h"
#include "Patch.h"
#include "RatioOperator.h"
#include "FixedOperator.h"
#include "Prompt.h"

using namespace std;

// Global variables
JackModule jack; // Holds the Jack module for audio
Patch *patch = nullptr; // Holds the current patch
Synthesizer *synth = nullptr; // Holds the synthesizer converted from the patch

// Global variables for the UI
Prompt prompt; // Contains the UI functions
Operator* currentOp = nullptr; // Holds the currently selected operator
int currentNote = 60;

// Main function
int main(int argc, const char** argv)
{
  // Create a JackModule instance
  jack.init("AdditiveSynth");

  // Create a new patch
  patch = new Patch();

  // Create a callback for the Jack module
  jack.onProcess = [&synth](jack_default_audio_sample_t* inBuf, jack_default_audio_sample_t* outBuf, jack_nframes_t nframes)
  {
    for (uint32_t i = 0; i < nframes; i++)
    {
      // Check if the synth is already made
      if (synth != nullptr)
      {
        // Fill the buffer with the current sample value
        outBuf[i] = synth->calculate();
        synth->tick();
      }
      else
        outBuf[i] = 0;
    }

    return 0;
  };

  // Connect to Jack
  jack.autoConnect();

  // Add a command for a tutorial
  prompt.addCommand("help",[&](string command, vector<string> args) {
    cout << "Welcome to ADDITIVESYNTH, a command line tool to create an additive synthesis patch!" << endl;
    cout << "The following commands can be used to control the synthesizer:" << endl;
    cout << endl;
    cout << "list" << endl;
    cout << "  List the current patch and its operators and view which one is selected." << endl;
    cout << "getglobal <parameter>" << endl;
    cout << "  Get a global parameter of the patch and display it (detune, ratio)." << endl;
    cout << "setglobal <parameter> <value>" << endl;
    cout << "  Set a global parameter of the patch." << endl;
    cout << "addratio [ratio = 1] [detune = 0] [amplitude = 1] [phase = 0]" << endl;
    cout << "  Adds an ratio operator to the patch and select it." << endl;
    cout << "addfixed [frequency = 440] [amplitude = 1] [phase = 0]" << endl;
    cout << "  Adds a fixed operator to the patch and select it." << endl;
    cout << "select <index>" << endl;
    cout << "  Select an operator to modify." << endl;
    cout << "get <parameter>" << endl;
    cout << "  Get a parameter of the selected operator and display it (amplitude, detune, frequency, phase, ratio)." << endl;
    cout << "set <parameter> <value>" << endl;
    cout << "  Set a parameter of the selected operator." << endl;
    cout << "remove" << endl;
    cout << "  Remove the selected operator (this action cannot be undone)." << endl;
    cout << "reset" << endl;
    cout << "  Reset the patch, discarding changes." << endl;
    cout << "play [midi_note]" << endl;
    cout << "  Plays the synthesizer on the given note or continues the last note." << endl;
    cout << "pause" << endl;
    cout << "  Pauses the synthesizer." << endl;
    cout << "help" << endl;
    cout << "  Display this tutorial message." << endl;
    cout << "quit" << endl;
    cout << "  Quit the program, discarding changes in the patch." << endl;

    return false;
  });

  // Add a command to list the patch
  prompt.addCommand("list",[&](string command, vector<string> args) {
    cout << patch->toString(currentOp) << endl;

    return false;
  });

  // Add a command for adding ratio operators
  prompt.addCommand("addratio",[&](string command, vector<string> args) {
    // Get the arguments
    double ratio = 1.0;
    if (args.size() > 1)
      ratio = Prompt::stringToDouble(args[1],1.0);

    double detune = 0.0;
    if (args.size() > 2)
      detune = Prompt::stringToDouble(args[2],0.0);

    double amplitude = 1.0;
    if (args.size() > 3)
      amplitude = Prompt::stringToDouble(args[3],1.0);

    double phase = 0.0;
    if (args.size() > 4)
      phase = Prompt::stringToDouble(args[4],0.0);

    // Add the new operator
    Operator* op = new RatioOperator(ratio,detune,amplitude,phase);
    patch->addOperator(op);

    // Select the operator and list the current patch
    currentOp = op;
    prompt.execute("list");

    return false;
  });

  // Add a command for adding fixed operators
  prompt.addCommand("addfixed",[&](string command, vector<string> args) {
    // Get the arguments
    double frequency = 440;
    if (args.size() > 1)
      frequency = Prompt::stringToDouble(args[1],440);

    double amplitude = 1.0;
    if (args.size() > 2)
      amplitude = Prompt::stringToDouble(args[2],1.0);

    double phase = 0.0;
    if (args.size() > 3)
      phase = Prompt::stringToDouble(args[3],0.0);

    // Add the new operator
    Operator* op = new FixedOperator(frequency,amplitude,phase);
    patch->addOperator(op);

    // Select the operator and list the current patch
    currentOp = op;
    prompt.execute("list");

    return false;
  });

  // Add a command for selecting an operator
  prompt.addCommand("select",[&](string command, vector<string> args) {
    // Check if all required arguments are given
    if (args.size() < 2)
    {
      cout << "Usage: select <index>" << endl;
      return false;
    }

    // Check if there are any ops to select
    if (patch->operatorCount() == 0)
    {
      cout << "There are no operators to select; use the addratio and addfixed commands to add an operator" << endl;
      return false;
    }

    // Get the arguments
    int index = Prompt::stringToInt(args[1],0);

    // Check if the index is in the boundaries
    if (index < 0 || index >= patch->operatorCount())
    {
      cout << "The selected index is not valid; valid indices are 0 to " << (patch->operatorCount() - 1) << endl;
      return false;
    }

    // Select the operator and list the current patch
    currentOp = patch->getOperator(index);
    prompt.execute("list");

    return false;
  });

  // Add a command for getting parameters of the selected operator
  prompt.addCommand("get",[&](string command, vector<string> args) {
    // Check if all required arguments are given
    if (args.size() < 2)
    {
      cout << "Usage: get <parameter>" << endl;
      return false;
    }

    // Check if there is currently a selected operator
    if (currentOp == nullptr)
    {
      cout << "You have not selected an operator; use the select command to select an operator" << endl;
      return false;
    }

    // Get the arguments
    string parameter = args[1];

    // Print the value belonging to this parameter
    try
    {
      cout << parameter << " = " << currentOp->get(parameter) << endl;
    }
    catch (invalid_argument ex)
    {
      cout << "This operator does not have a parameter " << parameter << endl;
      return false;
    }

    return false;
  });

  // Add a command for getting global parameters
  prompt.addCommand("getglobal",[&](string command, vector<string> args) {
    // Check if all required arguments are given
    if (args.size() < 2)
    {
      cout << "Usage: getglobal <parameter>" << endl;
      return false;
    }

    // Get the arguments
    string parameter = args[1];

    // Print the value belonging to this parameter
    try
    {
      cout << parameter << " = " << patch->get(parameter) << endl;
    }
    catch (invalid_argument ex)
    {
      cout << "Patch does not have a parameter " << parameter << endl;
      return false;
    }

    return false;
  });

  // Add a command for setting parameters of the selected operator
  prompt.addCommand("set",[&](string command, vector<string> args) {
    // Check if all required arguments are given
    if (args.size() < 3)
    {
      cout << "Usage: set <parameter> <value>" << endl;
      return false;
    }

    // Check if there is currently a selected operator
    if (currentOp == nullptr)
    {
      cout << "You have not selected an operator; use the select command to select an operator" << endl;
      return false;
    }

    // Get the arguments
    string parameter = args[1];
    double value = Prompt::stringToDouble(args[2],0.0);

    // Set the parameter and print the new value
    try
    {
      currentOp->set(parameter,value);
      cout << parameter << " = " << value << endl;
    }
    catch (invalid_argument ex)
    {
      cout << "This operator does not have a parameter " << parameter << endl;
      return false;
    }
    catch (out_of_range ex)
    {
      cout << ex.what() << endl;
      return false;
    }

    return false;
  });

  // Add a command for gsetting global parameters
  prompt.addCommand("setglobal",[&](string command, vector<string> args) {
    // Check if all required arguments are given
    if (args.size() < 3)
    {
      cout << "Usage: set <parameter> <value>" << endl;
      return false;
    }

    // Get the arguments
    string parameter = args[1];
    double value = Prompt::stringToDouble(args[2],0.0);

    // Set the parameter and print the new value
    try
    {
      patch->set(parameter,value);
      cout << parameter << " = " << value << endl;
    }
    catch (invalid_argument ex)
    {
      cout << "Patch does not have a parameter " << parameter << endl;
      return false;
    }
    catch (out_of_range ex)
    {
      cout << ex.what() << endl;
      return false;
    }

    return false;
  });

  // Add a command for removing the selected operator
  prompt.addCommand("remove",[&](string command, vector<string> args) {
    // Check if there is currently a selected operator
    if (currentOp == nullptr)
    {
      cout << "You have not selected an operator; use the select command to select an operator" << endl;
      return false;
    }

    // Remove the current operator, reset the selected operator and list the current patch
    patch->removeOperator(currentOp);
    currentOp = nullptr;
    prompt.execute("list");

    return false;
  });

  // Add a command to reset the patch
  prompt.addCommand("reset",[&](string command, vector<string> args) {
    // Pause the synth
    prompt.execute("pause");

    // Reset the selected op
    currentOp = nullptr;

    // Reset the patch and list it
    patch->reset();
    prompt.execute("list");

    return false;
  });

  // Add a command to play the synthesizer
  prompt.addCommand("play",[&](string command, vector<string> args) {
    // Get the note to play if one is given
    if (args.size() > 1)
      currentNote = Prompt::stringToInt(args[1],60);

    // Create the synthesizer
    if (synth != nullptr)
      delete synth;
    synth = patch->convert(jack.getSamplerate(),Synthesizer::mtof(currentNote));

    return false;
  });

  // Add a command to pause the synthesizer
  prompt.addCommand("pause",[&](string command, vector<string> args) {
    // Delete the synthesizer
    if (synth != nullptr)
      delete synth;
    synth = nullptr;

    return false;
  });

  // Use the prompt to provice a user interface, but first print the tutorial
  prompt.execute("help");
  prompt.run();

  // Cleanup
  if (synth != nullptr)
    delete synth;
  if (patch != nullptr)
    delete patch;

  // End
  return 0;
}
