import simpleaudio as sa;
import time;
import random;

# Create a list to store the samples
samples = []

# Create a list with the default samples to use
defaultSampleFiles = ["assets/808-Kick.wav","assets/808-Snare.wav","assets/808-OH.wav"]

# Ask for the three samples to use
for i in range(3):
  try:
    sampleFile = input("Enter the path to sample #%d (%s): " % (i + 1, defaultSampleFiles[i]))
    samples.append(sa.WaveObject.from_wave_file(sampleFile or defaultSampleFiles[i]))
  except FileNotFoundError:
    print("File not found, using default sample")
    samples.append(sa.WaveObject.from_wave_file(defaultSampleFiles[i]))

# Variables
bpm = 120
quarterNoteDuration = 60 / bpm
sixteenthNoteDuration = quarterNoteDuration / 4.0
beatsPerMeasure = 3
measureDuration = beatsPerMeasure  * quarterNoteDuration

# Create a list to store the events
events = []
#create lists with the moments (in 16th) at which we should play the samples
sequence1 = [0, 2, 4, 8, 11]
sequence2 = [3, 6, 10]
sequence3 = [9, 13]

#transform the sixteenthNoteSequece to an eventlist with time values
for sixteenNoteIndex in sequence1:
  events.append((sixteenNoteIndex * sixteenthNoteDuration, 0))

#transform the sixteenthNoteSequece to an eventlist with time values
for sixteenNoteIndex in sequence2:
  events.append((sixteenNoteIndex * sixteenthNoteDuration, 1))

#transform the sixteenthNoteSequece to an eventlist with time values
for sixteenNoteIndex in sequence3:
  events.append((sixteenNoteIndex * sixteenthNoteDuration, 2))

#NOTE: The line below is essential to enable a correct playback of the events
events.sort()

#display the event list
print(events)

# Return the first event
event = events.pop(0)

#retrieve the startime: current time
startTime = time.time()
keepPlaying = True
#play the sequence
while keepPlaying:
  #retrieve current time
  currentTime = time.time()
  #check if the event's time (which is at index 0 of event) is passed
  if(currentTime - startTime >= event[0]):
    #play sample -> sample index is at index 1
    sample = samples[event[1]].play()
    #if there are events left in the events list
    if events:
      #retrieve the next event
      event = events.pop(0)
    else:
      #list is empty, stop loop
      sample.wait_done()
      keepPlaying = False
  else:
    #wait for a very short moment
    time.sleep(0.001)