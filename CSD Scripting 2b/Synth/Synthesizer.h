#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

// Synthesizer class
class Synthesizer
{
public:
  // Constructor
  Synthesizer();

  // Destructor
  virtual ~Synthesizer();

  // Process function
  virtual void process(float audioBuffer[], int audioBufferLen);
};

#endif // SYNTHESIZER_H
