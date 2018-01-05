#include <iostream>

#include "Oscillator.h"
#include "SineWave.h"
#include "SquareWave.h"
#include "Synthesizer.h"
#include "SimpleSynthesizer.h"

using namespace std;

int main()
{
  // Create an audio buffer
  float audioBuffer[256] = {0.0f};

  // Create a sine wave oscillator
  Oscillator* sineWave = new SineWave(440.0f,0.0f);

  // Create a sine wave synthesizer
  Synthesizer* sineSynth = new SimpleSynthesizer(sineWave);

  // Process the sine wave
  cout << "Processing sine wave:" << endl;
  sineSynth->process(audioBuffer,256);
  for (int i = 0; i < 256; i ++)
    cout << i << ": " << audioBuffer[i] << endl;


    // Create a square wave oscillator
  Oscillator* squareWave = new SquareWave(440.0f,0.0f);

  // Create a square wave synthesizer
  Synthesizer* squareSynth = new SimpleSynthesizer(squareWave);

  // Process the sine wave
  cout << "Processing square wave:" << endl;
  squareSynth->process(audioBuffer,256);
  for (int i = 0; i < 256; i ++)
    cout << i << ": " << audioBuffer[i] << endl;


  // Delete resources
  delete sineSynth;
  delete sineWave;
  delete squareSynth;
  delete squareWave;

 // Return
  return 0;
}
