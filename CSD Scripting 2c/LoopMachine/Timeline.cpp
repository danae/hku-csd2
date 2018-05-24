#include "Timeline.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Constructor
Timeline::Timeline(unsigned int beatsPerMinute, unsigned int beatsPerBar)
{
  setBeatsPerMinute(beatsPerMinute);
  setBeatsPerBar(beatsPerBar);

  this->currentBeat = 0;
}

// Destructor
Timeline::~Timeline()
{
  // Delete all patterns that are left over
  reset();
}

// Reset the time line
void Timeline::reset()
{
  // Delete and dereference all patterns
  for (Pattern* pattern : patterns)
    delete pattern;
  patterns.clear();
}

// Getters and setters
unsigned int Timeline::getBeatsPerMinute()
{
  return beatsPerMinute;
}
void Timeline::setBeatsPerMinute(unsigned int beatsPerMinute)
{
  this->beatsPerMinute = beatsPerMinute;
}
unsigned int Timeline::getBeatsPerBar()
{
  return beatsPerBar;
}
void Timeline::setBeatsPerBar(unsigned int beatsPerBar)
{
  this->beatsPerBar = beatsPerBar;
}

// Add a pattern
void Timeline::addPattern(Pattern* pattern)
{
  patterns.push_back(pattern);
}

// Remove a pattern
void Timeline::removePattern(Pattern* pattern)
{
  patterns.erase(remove(patterns.begin(),patterns.end(),pattern),patterns.end());
  delete pattern;
}

// Get a pattern
Pattern* Timeline::getPattern(int index)
{
  if (index < 0 || index >= patterns.size())
    throw out_of_range("Pattern index out of range");

  return patterns[index];
}

// Return the number of patterns
int Timeline::patternCount()
{
  return patterns.size();
}

// Tick one beat forward
void Timeline::beat()
{
  currentBeat ++;

  if (currentBeat % beatsPerBar == 0)
  {
    // Entering a new bar
  }
}

// Convert to string
string Timeline::toString()
{
  stringstream ss;
  ss << "Timeline (" << beatsPerMinute << " bpm, " << beatsPerBar << " beats per bar)" << endl;

  for (Pattern* pattern : patterns)
    ss << pattern->toString() << endl;

  return ss.str();
}
