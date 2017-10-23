import colorama

# Class for choosing/selecting things in a terminal
class Selector:
  # Constructor
  # Options is a list of strings
  def __init__(self, options):
    self.options = options
    
  # Let the user choose an option
  def select(self):
    # Print the header
    print(colorama.Fore.BLACK + colorama.Back.GREEN + "What would you like to do next?")
    
    # Print all options
    for index, option in enumerate(self.options):
      print("  %d. %s" % (index + 1,option))
      
    # Wait for input
    inputInt = None
    while inputInt == None:
      try:
        # Retrieve the input
        inputStr = input("Enter your choice: ")
        inputInt = int(inputStr)
        if inputInt <= 0 or inputInt > len(self.options):
          raise ValueError
        break
      except ValueError:
        print(colorama.Fore.RED + "  Invalid choice, please try again.")
        inputInt = None
        
    # Return the index of the selected option
    return inputInt