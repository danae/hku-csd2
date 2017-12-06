import pyaudio

settings = {
  'width': 2,
  'channels': 1,
  'sampleRate': 44100,
  'framesPerBuffer': 256
}

# Audio callback function
def audioCallback(in_data, frame_count, time_info, status):
  pass
  
# Main function
def main():
  name = input("Name: ")
  print("Hello, %s!" % name)

# Execute the main function  
if __name__ == "__main__":
  main()