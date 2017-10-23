from sampler import Sampler
from sequencer import Sequencer
from selector import Selector

import random
import colorama

# Create a list of default values for user settings
defaults = {
  "samples": ["assets/808-Kick.wav","assets/808-Snare.wav","assets/808-OH.wav"],
  "bpm": 120
}
      
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
        print(colorama.Fore.RED + "  Could not find the file, please try again.")
        
  # Return the sampler
  return sampler
   
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
  while True:
    try:
      bpmInput = input("  Enter the desired BPM (%d): " % defaults["bpm"])
      bpm = int(bpmInput or defaults["bpm"])
      break
    except ValueError:
      print(colorama.Fore.RED + "  Invalid input, please try again.")
  
  # Create a new sequencer and return it
  beats = random.randrange(5,10)
  return Sequencer.generate_irregular_beat(bpm,beats);
    
# Print the welcome message
def welcome_message():
  print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "  ___                       _          ___           _               ")
  print(colorama.Fore.GREEN + colorama.Style.BRIGHT + " |_ _|_ _ _ _ ___ __ _ _  _| |__ _ _ _| _ ) ___ __ _| |_   _ __ _  _ ")
  print(colorama.Fore.GREEN + colorama.Style.BRIGHT + "  | || '_| '_/ -_) _` | || | / _` | '_| _ \/ -_) _` |  _|_| '_ \ || |")
  print(colorama.Fore.GREEN + colorama.Style.NORMAL + " |___|_| |_| \___\__, |\_,_|_\__,_|_| |___/\___\__,_|\__(_) .__/\_, |")
  print(colorama.Fore.GREEN + colorama.Style.NORMAL + "                 |___/                                    |_|   |__/ ")
  print("")
  print(colorama.Fore.BLACK + colorama.Style.BRIGHT + "  Generate beats with 2-3-4-patterns in irregular time signatures")
  print(colorama.Fore.BLACK + colorama.Style.BRIGHT + "  Created by dengsn (https://github.com/dengsn)")
 

# Main function
def main():    
  # Initialize colorama
  colorama.init(autoreset=True)

  # Print welcome message
  welcome_message() 
 
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
  
    # Options to continue
    option = Selector(["Save the beat to a MIDI file","Replay the current beat","Generate a new beat","Exit the application"]).select()
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
  