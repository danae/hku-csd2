import simpleaudio as sa;
import time;
import random;

# Sampler class, extends list
class Sampler(list):
  # Create a sample from a file name and append it to the list
  def append_file(self, sampleFile):
    try:
      # Try to load the sample
      sample = sa.WaveObject.from_wave_file(sampleFile)
      # Add the sample to the list
      self.append(sample)
      # Function succeeded
      return True
    except FileNotFoundError:
      # Function failed
      return False

# Sequencer class
class Sequencer:
  # Constructor
  # Events is a list of tuples (event time in s, sample)
  def __init__(self, events=[]):
    self.events = events
    
  # Plays the sequence (blocking method)
  def play(self, sampler):  
    # Copy the event list for re-usage and sort them by time
    events = self.events[:]
    events.sort()
    
    # If there are no events, then just return
    if not events:
      return
    
    # Retrieve the first event if there is any
    event = events.pop(0)
    
    # Get the start time
    startTime = time.time();
    
    # Play the sequence as long as there are events
    while True:
      # Retrieve the current time
      currentTime = time.time()
      # Check if the time of the event is passed
      if currentTime - startTime >= event[0]:
        # Play the sample of the event
        sampler[event[1]].play()
        # If there are more events
        if events:
          # Get the next event
          event = events.pop(0)
        # Otherwise stop the loop
        else:
          break
    
      # Otherwise wait for a short moment
      else:
        time.sleep(0.001)
        
  # Create a sequence from an index-based list
  @classmethod
  def create_from_indexes(cls, events, bpm=120):
    # Calculate the duration of a 16th note
    quarterNoteDuration = 60.0 / bpm
    sixteenthNoteDuration = quarterNoteDuration / 4.0
    
    # Map the event list to durations
    events = [(event[0] * sixteenthNoteDuration, event[1]) for event in events]
    
    # Return a new sequencer with the event list
    return cls(events)
  
  # Generate an irregular sequence
  @classmethod 
  def generate(cls, bpm, beats, beatsPerBar=4):
    events = [(i,0) for i in range(0,beats,2)] + [(i,1) for i in range(0,beats,2)]
    
    # Return a new sequencer with the event list
    return cls.create_from_indexes(events,bpm)

# Main function
def main():    
  # Print welcome message
  print("""
  ___                       _          ___           _               
 |_ _|_ _ _ _ ___ __ _ _  _| |__ _ _ _| _ ) ___ __ _| |_   _ __ _  _ 
  | || '_| '_/ -_) _` | || | / _` | '_| _ \/ -_) _` |  _|_| '_ \ || |
 |___|_| |_| \___\__, |\_,_|_\__,_|_| |___/\___\__,_|\__(_) .__/\_, |
                 |___/                                    |_|   |__/ 
  """)
  
  # Create a list of default values for user settings
  defaults = {
    "samples": ["assets/808-Kick.wav","assets/808-Snare.wav","assets/808-OH.wav"],
    "bpm": 120
  }

  # Create a list to store the samples
  samples = Sampler()

  # Ask for the samples to use
  print("Enter the following settings to configure the script (press ENTER for the default value)")
  for i in range(3):
    while True:
      # Ask for the sample to use and append it to the list
      sampleFile = input("- Enter the path to sample #%d (%s): " % (i + 1, defaults["samples"][i]))
      if samples.append_file(sampleFile or defaults["samples"][i]):
        break
      else:
        print("Could not fild the file! Please try again.")

  # Ask for the bpm to use
  try:
    bpmInput = input("- Enter the desired BPM (%d): " % defaults["bpm"])
    bpm = int(bpmInput or defaults["bpm"])
  except ValueError:
    print("Invalid input, using default BPM")
    bpm = defaults["bpm"]

  # Main loop
  notInterrupted = True
  while notInterrupted:
    # Create a new sequencer
    seq = Sequencer.generate(bpm,5);

    # Play the sequence
    seq.play(samples)
  
    # Ask for input
    if input("Enter someting to quit: "):
      exit()
    
# Execute the main function if not importing the script
if __name__ == "__main__":
  main()
  