import simpleaudio as sa;
import time;
import random;
import colorama;

# Create a list of default values for user settings
defaults = {
  "samples": ["assets/808-Kick.wav","assets/808-Snare.wav","assets/808-OH.wav"],
  "bpm": 120
}

# Option class for selecting things in the terminal
class Option:
  # Constructor
  # Options is a list of strings
  def __init__(self, options):
    self.options = options
    
  # Let the user choose an option
  def choose(self):
    # Print the header
    print(colorama.Fore.BLACK + colorama.Back.GREEN + "What would you like to do next?")
    # Print all options
    for index, option in enumerate(self.options):
      print("  %d. %s" % (index + 1,option))
    # Wait for input
    inputInt = None
    while inputInt == None:
      try:
        inputStr = input("Enter your choice: ")
        inputInt = int(inputStr)
        if inputInt <= 0 or inputInt > len(self.options):
          raise ValueError
        break
      except ValueError:
        print("Invalid")
        inputInt = None
    # Return the index of the selected option
    return inputInt

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
  def generate_irregular_beat(cls, bpm, length):
    # Generate a list of pattern lengths
    patterns = generate_patterns(length)
        
    # Create an empty event list
    events = []
        
    # Generate a kick and snare pattern using the lengths
    eventPosition = 0
    for pattern in patterns:
      # Append a kick event at the start of the pattern
      events.append((eventPosition,0))
      
      # Append a snare event at a random position in the pattern
      snarePosition = random.randrange(1,pattern)
      events.append((eventPosition + snarePosition,1))
      
      # Fill the gaps with hats
      for hatPosition in range(pattern):
        if hatPosition != snarePosition:
          events.append((eventPosition + hatPosition,2))
    
      # Increase the event position
      eventPosition += pattern
    
    # Return a new sequencer with the event list
    return cls.create_from_indexes(events,bpm)
    
# Recursively generates a list of patterns
def generate_patterns(length):
  if length == 2:
    # Add a 2-pattern
    return [2]
  elif length == 3:
    # Add a 3-pattern
    return [3]
  elif length == 4:
    # Add a 4-pattern or two 2-patterns
    return random.choice([[4],[2,2]])
  elif length == 5:
    # Add a 2-3 or 3-2
    return random.choice([[2,3],[3,2]])
  else:
    # Add a random pattern
    currentLength = random.choice([2,3,4])
    return [currentLength] + generate_patterns(length - currentLength)
   
# Generate a new beat with user input settings   
def generate_beat():
  # Print a newline
  print("")
  
  # Print the header
  print(colorama.Fore.BLACK + colorama.Back.GREEN + "Enter the settings for the new beat (press ENTER for the default value)")

  # Ask for the time signature to use
  try:
    timeSignatureInput = input("  Enter the time signature (7/8): ")
  except ValueError:
    pass
  
  # Ask for the bpm to use
  try:
    bpmInput = input("  Enter the desired BPM (%d): " % defaults["bpm"])
    bpm = int(bpmInput or defaults["bpm"])
  except ValueError:
    print("Invalid input, using default BPM")
    bpm = defaults["bpm"]
  
  # Create a new sequencer and return it
  beats = random.randrange(5,10)
  return Sequencer.generate_irregular_beat(bpm,beats);
  
# Initialize a sampler with user input settings
def init_sampler():
  # Create a list to store the samples
  sampler = Sampler()
  
  # Print a newline
  print("")
  
  # Print the header
  print(colorama.Fore.BLACK + colorama.Back.GREEN + "Enter the settings to configure the script (press ENTER for the default value)")

  # Ask for the samples to use
  for i in range(3):
    while True:
      # Ask for the sample to use and append it to the list
      sampleFile = input("  Enter the path to sample #%d (%s): " % (i + 1, defaults["samples"][i]))
      if sampler.append_file(sampleFile or defaults["samples"][i]):
        break
      else:
        print(colorama.Fore.RED + "  Could not find the file! Please try again.")
        
  # Return the sampler
  return sampler

# Main function
def main():    
  # Initialize colorama
  colorama.init(autoreset=True)

  # Print welcome message
  print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "  ___                       _          ___           _               ")
  print(colorama.Fore.GREEN + colorama.Style.BRIGHT + " |_ _|_ _ _ _ ___ __ _ _  _| |__ _ _ _| _ ) ___ __ _| |_   _ __ _  _ ")
  print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "  | || '_| '_/ -_) _` | || | / _` | '_| _ \/ -_) _` |  _|_| '_ \ || |")
  print(colorama.Fore.GREEN + colorama.Style.NORMAL + " |___|_| |_| \___\__, |\_,_|_\__,_|_| |___/\___\__,_|\__(_) .__/\_, |")
  print(colorama.Fore.GREEN + colorama.Style.NORMAL + "                 |___/                                    |_|   |__/ ")
  print("")
  print("  Generate beats with 2-3-4-patterns in irregular time signatures")
  print("  Created by dengsn (https://github.com/dengsn)")
  
  # Initialize the sampler
  sampler = init_sampler()
  
  # Initialize a new beat
  seq = generate_beat()

  # Main loop
  notInterrupted = True
  while notInterrupted:
    # Play the sequence using the sampler
    seq.play(sampler)
    
    # Print a newline
    print("")
  
    # Options
    option = Option(["Save the beat to a MIDI file","Replay the current beat","Generate a new beat","Exit the application"]).choose()
    if option == 1:
      # Save the beat to a MIDI file
      pass
    elif option == 2:
      # Replay the current beat -> just pass
      pass
    elif option == 3:
      # Generate a new beat
      seq = generate_beat()
    elif option == 4:
      # Exit the application
      break
  
  # Deinitialize colorama
  colorama.deinit()
    
# Execute the main function if not importing the script
if __name__ == "__main__":
  main()
  