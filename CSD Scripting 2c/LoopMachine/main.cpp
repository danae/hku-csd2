#include <iostream>
#include <string>
#include <thread>

#include "Timeline.h"
#include "Pattern.h"
#include "Prompt.h"
#include "jack_module.h"

using namespace std;

// Main time line object
Timeline* timeline;

// Objects for the modules
Prompt prompt;
JackModule jack;

// Main function
int main()
{
  // Create the main time line
  timeline = new Timeline(120,4);
  timeline->addPattern(new Pattern(2));
  timeline->addPattern(new Pattern(4));
  timeline->getPattern(1)->setStatus(PatternStatus::QUEUED_FOR_RECORDING);

  cout << timeline->toString() << endl;

  // Create a JackModule instance
  jack.init("LoopMachine"); // use program name as JACK client name
  jack.autoConnect();

  //std::thread filterThread(filter);
  thread audioThread([&] {

  });

  // Add a command to play the timeline
  prompt.addCommand("play",[&](string command, vector<string> args) {
    return false;
  });

  // Create a thread for the prompt
  prompt.run();

  // Stop the threads and modules
  audioThread.join();
  jack.end();

  // Cleanup
  delete timeline;

  // End
  return 0;
}
