#include "Pattern.h"

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
