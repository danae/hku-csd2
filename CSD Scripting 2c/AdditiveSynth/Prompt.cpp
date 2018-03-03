#include "Prompt.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

// Split string using a delimiter
vector<string> explode(const string str, const string delimiter = " ")
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

// Get a char from cin
char Prompt::getChar()
{
  char character = cin.get();
  cin.ignore(1);
  return character;
}

// Get a line from cin
string Prompt::getLine()
{
  char line[128];
  cin.getline(line,128);
  return string(line);
}

// Get an interger from cin
int Prompt::getInteger(int defaultValue = 0)
{
  string line = getLine();
  if (line == "")
    return defaultValue;
  else
    return atoi(line.c_str());
}

// Get a double from cin
double Prompt::getDouble(double defaultValue)
{
  string line = getLine();
  if (line == "")
    return defaultValue;
  else
    return atof(line.c_str());
}

// Run the prompt loop
void Prompt::run()
{
  // Main loop
  while (true)
  {
    // Wait for user input
    cout << "> ";

    // Get the line the user has entered and split it
    string input = getLine();

    // Execute the line and exit if the result is true
    if (execute(input))
      break;
  }
}
