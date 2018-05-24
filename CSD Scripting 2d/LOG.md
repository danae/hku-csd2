This is my log for the CSD2d induvidual project.

## April 30 - May 6 ##

### Decided to use Java ###

At first I wanted to use C++, due to its low level access to hardware for low-latency audio output. I tried to install and test several C++ creative frameworks:

* [*JUCE*](https://juce.com/) (cross-platform library focused on audio and graphics)
* [*OpenFrameworks*](http://openframeworks.cc/) (Processing-like cross-platform library)
* [*Cinder*](https://libcinder.org/) (Same as OF, but different)

Downside to these three frameworks is that they require to be compiled with *Microsoft Visual Studio* and even when I installed it and configured the libraries, they won't compile (the strangest case was with OF, that required the C99 standard, but the VC++ compiler does not implement that standard).

Another pittfall was that the libraries claimed to be cross-platform, but to achieve that one must compile the code for each platform to be able to use it. When using Java one could compile the code once and execute it on all platforms that have a Java VM running.

I made this comparison table:

**C++**
* Pros:
  * Low-latency audio processing
  * Software can eventually be used as VST
* Cons:
  * Libraries require particular compilers
  * Cross-platform requires compiling on every platform
  * No garbage collection of pointers
  * *lambda* and *std::function* are not interchangeable and templates cannot accept pointers of subclasses

**Java**
* Pros:
  * Is cross-platform without extra coding
* Cons:
  * Requires *Java Runtime Environment* to run, which makes the language quite slow compared to C++

In the end I thus decided to use Java with *Processing* for graphics and *Beads* for audio output.
