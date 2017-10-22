import simpleaudio as sa;
import time;
import random;

# Sequencer class
class Sequencer:
  # Constructor
  # Events is a list of tuples (event time in s, index of sample)
  def __init__(self, events=[]):
    self.events = events
    
  # Plays the sequence
  def play(self, bpm=120):
    # Calculate the duration of a 16th note
    duration = 15 / bpm
  
    # Copy the event list for re-usage and sort them in time
    events = self.events[:]
    events.sort()
    
    # Map the sequence index to duration in s
    events = [(event[0] * duration,event[1]) for event in events]
  
    # Retrieve the first event
    event = events.pop(0)

    # Play the sequence
    startTime = time.time();
    while True:
      # Retrieve the current time
      currentTime = time.time()      
      # Check if the time of the event is passed
      if currentTime - startTime >= event[0]:
        # Get the sample to play
        sample = samples[event[1]].play()
        # If there are events left
        if events:
          # Retrieve the next event
          event = events.pop(0)
        else:
          # Wait for the sample to finish
          #sample.wait_done()
          # Break out of the loop
          break
    
      # Otherwise wait for a short moment
      else:
        time.sleep(0.001)

# Create a list of default values for user inputs
defaults = {
  "samples": ["assets/808-Kick.wav","assets/808-Snare.wav","assets/808-OH.wav"],
  "bpm": 120
}

# Create a list to store the samples
samples = []

# Ask for the samples to use
for i in range(3):
  try:
    # Ask for the sample to use and append it to the list
    sampleFile = input("Enter the path to sample #%d (%s): " % (i + 1, defaults["samples"][i]))
    samples.append(sa.WaveObject.from_wave_file(sampleFile or defaults["samples"][i]))
  except FileNotFoundError:
    # File not found, so use the default sample
    print("File not found, using default sample")
    samples.append(sa.WaveObject.from_wave_file(defaults["samples"][i]))

# Ask for the bpm to use
try:
  bpmInput = input("Enter the desired BPM (%d): " % defaults["bpm"])
  bpm = int(bpmInput or defaults["bpm"])
except ValueError:
  print("Invalid input, using default BPM")
  bpm = defaults["bpm"]

# Create lists with the moments (in 16th) at which we should play the samples
sequence1 = [0, 2, 4, 8, 11]
sequence2 = [3, 6, 10]
sequence3 = [9, 13]

notInterrupted = True
while notInterrupted:
  # Create a new sequencer
  seq = Sequencer()

  # Add the events to the sequencer
  seq.events = seq.events + [(i,0) for i in sequence1]
  seq.events = seq.events + [(i,1) for i in sequence2]
  seq.events = seq.events + [(i,2) for i in sequence3]
  
  # Play the sequence
  seq.play(bpm)
  
  # Ask for input
  input("Would you like to save this beat Y/N (N)? ")