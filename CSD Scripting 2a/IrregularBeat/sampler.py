import simpleaudio;

# Sampler class, extends list
class Sampler(list):
  # Create a sample from a file name and append it to the list
  def append_file(self, sampleFile):
    try:
      # Try to load the sample
      sample = simpleaudio.WaveObject.from_wave_file(sampleFile)
      # Add the sample to the list
      self.append(sample)
      # Function succeeded
      return True
    except FileNotFoundError:
      # Function failed
      return False
