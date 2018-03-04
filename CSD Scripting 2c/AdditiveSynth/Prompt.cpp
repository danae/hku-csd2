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

// Get a line from cin
string Prompt::getLine()
{
  char line[128];
  cin.getline(line,128);
  return string(line);
}

// Constructor
Prompt::Prompt()
{
  this->beforeFunction = 0;
  this->afterFunction = 0;

  // Add the quit command
  addCommand("quit",[&](string command, vector<string> args) {
    return true;
  });

  // Add the help command
  addCommand("help",[&](string command, vector<string> args) {
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
void Prompt::addCommand(string command, PromptFunction fn)
{
  commands[command] = fn;
}

// Remove a command
void Prompt::removeCommand(string command)
{
  commands.erase(command);
}

// Set the before function
void Prompt::before(PromptEventFunction fn)
{
  beforeFunction = fn;
}

// Set the after function
void Prompt::after(PromptEventFunction fn)
{
  afterFunction = fn;
}

// Execute a command
bool Prompt::execute(string line)
{
  // Split the line
  vector<string> tokens = explode(line);

  // Search if there exists a command for the input
  auto command = tokens[0];
  auto it = commands.find(command);
  if (it != commands.end())
  {
    // Found the command, so excute it
    if (beforeFunction != 0)
      beforeFunction(command);

    bool result = it->second(command,tokens);

    if (afterFunction != 0)
      afterFunction(command);

    return result;
  }
  else
  {
    // Not found
    cout << "Undefined command " << command << ", enter 'help' to see a list of available commands" << endl;
    return false;
  }
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
