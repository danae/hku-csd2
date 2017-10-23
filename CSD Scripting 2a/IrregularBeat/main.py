from sampler import Sampler
from sequencer import Sequencer
from selector import Selector

import random
import re
import colorama

# Create a list of default values for user settings
defaults = {
  "samples": ["assets/808-Kick.wav","assets/808-Snare.wav","assets/808-OH.wav"],
  "timeSignature": "4/4",
  "bpm": 120,
  "fileName": "export.mid"
}

# Parse a time signature string
# Returns a tuple of beats and beatUnit for a string
def time_signature(timeSignature):
  # Create a RegEx pattern and find it
  match = re.match("(\\d+)/([1248])",timeSignature)
  
  # If no match
  if not match:
    # Return None, because error
    return None
  else:
    # Otherwise parse the expression
    try:
      # Get the match groups
      beats = int(match.group(1))
      beatUnit = int(match.group(2))
      # Return them in a tuple
      return (beats,beatUnit)
    except ValueError:
      # Not an integer
      return None
       
# Initialize a sampler with user input settings
def init_sampler():
  # Create a sampler to store the samples
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
  while True:
    timeSignatureInput = input("  Enter the time signature (%s): " % defaults["timeSignature"])
    timeSignature = time_signature(timeSignatureInput or defaults["timeSignature"])
    if timeSignature:
      break
    else:
      print(colorama.Fore.RED + "  Invalid time signature, make sure you use the format '7/8'. Please try again.")
  
  # Ask for the bpm to use
  while True:
    try:
      bpmInput = input("  Enter the desired BPM (%d): " % defaults["bpm"])
      bpm = int(bpmInput or defaults["bpm"])
      break
    except ValueError:
      print(colorama.Fore.RED + "  Invalid number, please try again.")
  
  # Create a new sequencer and return it
  return Sequencer.generate_irregular_beat(bpm,timeSignature[0],timeSignature[1]);
  
# Export a sequence as MIDI file with user input settings
def export_midi(seq):
  # Print a newline
  print("")
  
  # Print the header
  print(colorama.Fore.BLACK + colorama.Back.GREEN + "Save the beat to a MIDI file (press ENTER for the default value)")

  # Ask for the time signature to use
  fileName = input("  Enter the file to save (%s): " % defaults["fileName"])
  
  # Export the MIDI file
  if not seq.export_midi(fileName or defaults["fileName"]):
    print(colorama.Fore.RED + "  Could not write to the selected file, please try again.")
  else:
    print (colorama.Fore.GREEN + "  Saved file successfully!")
    
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
  while True:
    # Play the sequence using the sampler
    seq.play(sampler)
    
    # Print a newline
    print("")
  
    # Options to continue, function returns the selected option
    option = Selector(["Save the beat to a MIDI file","Replay the current beat","Generate a new beat","Exit the application"]).select()
    if option == 1:
      # Save the beat to a MIDI file
      export_midi(seq)
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
