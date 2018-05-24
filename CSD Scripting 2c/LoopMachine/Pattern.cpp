#include "Pattern.h"
#include <sstream>

using namespace std;

// Constructor
Pattern::Pattern(unsigned int numBars)
{
  setStatus(PatternStatus::IDLE);
  setNumBars(numBars);
}

// Destructor
Pattern::~Pattern()
{
}

// Getters and setters
PatternStatus Pattern::getStatus()
{
  return status;
}
void Pattern::setStatus(PatternStatus status)
{
  this->status = status;
}
unsigned int Pattern::getNumBars()
{
  return numBars;
}
void Pattern::setNumBars(unsigned int numBars)
{
  this->numBars = numBars;
}

// Convert to string
string Pattern::toString()
{
  stringstream ss;

  switch (status)
  {
    case PatternStatus::IDLE:
    default:
      ss << " IDLE  ";
      break;
    case PatternStatus::QUEUED_FOR_PLAYING:
      ss << "[PLAY️] ";
      break;
    case PatternStatus::PLAYING:
      ss << " PLAY  ";
      break;
    case PatternStatus::QUEUED_FOR_RECORDING:
      ss << "[REC]  ";
      break;
    case PatternStatus::RECORDING:
      ss << " REC   ";
      break;
  }

  for (int i = 0; i < numBars; i ++)
    ss << "|~~~~";
  ss << "|";

  return ss.str();
}
