#include "Prompt.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Split string using a delimiter
vector<string> Prompt::explode(const string str, const string delimiter)
{
  vector<string> vec;

  // Create a copy of the string
  string strc(str);

  // Iteratively search for the delimiter
  size_t pos = 0;
  while ((pos = strc.find(delimiter)) != string::npos)
  {
    vec.push_back(strc.substr(0,pos));
    strc.erase(0,pos + delimiter.length());
  }

  // Add the last past
  vec.push_back(strc);

  return vec;
}

// Convert string to integer
int Prompt::stringToInt(string str, int defaultValue)
{
  try
  {
    // Check if the string is empty
    if (str.empty())
      return defaultValue;

    // Otherwise convert
    else
      return stoi(str);
  }
  catch (invalid_argument ex)
  {
    cout << "The string \"" << str << "\" could not be converted to an integer, using defaut value " << defaultValue << " instead" << endl;
    return defaultValue;
  }
}

// Convert string to double
double Prompt::stringToDouble(string str, double defaultValue)
{
  try
  {
    // Check if the string is empty
    if (str.empty())
      return defaultValue;

    // Otherwise convert
    else
      return stod(str);
  }
  catch (invalid_argument ex)
  {
    cout << "The string \"" << str << "\" could not be converted to an integer, using defaut value " << defaultValue << " instead" << endl;
    return defaultValue;
  }
}

// Constructor
Prompt::Prompt()
{
  // Add the quit command
  add("quit",[&](string command, vector<string> args) {
    return true;
  });

  // Add the help command
  add("help",[&](string command, vector<string> args) {
    cout << "Available commands: ";

    for (auto c : commands)
      cout << c.first << " ";
    cout << endl;

    return false;
  });
}

// Destructor
Prompt::~Prompt()
{
}

// Add a command
void Prompt::add(string command, PromptFunction fn)
{
  commands[command] = fn;
}

// Execute a command
bool Prompt::execute(string line)
{
  // Split the line
  vector<string> tokens = explode(line);

  // Search if there exists a command for the input
  auto it = commands.find(tokens[0]);
  if (it != commands.end())
  {
    // Found the command, so excute it
    return it->second(tokens[0],tokens);
  }
  else
  {
    // Not found
    cout << "Undefined command " << tokens[0] << ", enter 'help' to see a list of available commands" << endl;
    return false;
  }
}

// Get a line from cin
string Prompt::getLine()
{
  char line[128];
  cin.getline(line,128);
  return string(line);
}

// Run the prompt loop
void Prompt::run()
{
  // Main loop
  while (true)
  {
    // Wait for user input
    cout << endl << "> ";

    // Get the line the user has entered and split it
    string input = getLine();

    // Execute the line and exit if the result is true
    if (execute(input))
      break;
  }
}
