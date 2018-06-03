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

  // Create a JackModule instance
  //jack.init("LoopMachine"); // use program name as JACK client name
  //jack.autoConnect();

  //std::thread filterThread(filter);

  // Run the prompt
  prompt.run();

  // Stop the filter thread
  //filterThread.join();

  // Stop the JackModule
  //jack.end();

  // End
  return 0;
}
