#ifndef PROMPT_H
#define PROMPT_H

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <stdexcept>

// Use a simple name for the huge function
typedef std::function<bool(std::string, std::vector<std::string>)> PromptFunction;

class Prompt
{
  protected:
    // Variables
    std::map<std::string, PromptFunction> commands;

  public:
    Prompt();
    virtual ~Prompt();

    // Split string using a delimiter
    static std::vector<std::string> explode(const std::string str, const std::string delimiter = " ");

    // Convert string to numbers
    static int stringToInt(std::string str, int defaultValue);
    static double stringToDouble(std::string str, double defaultValue);

    // Add a command
    void add(std::string command, PromptFunction fn);

    // Execute a command
    bool execute(std::string line);

    // Get a line from cin
    std::string getLine();

    // Run the prompt loop
    void run();
};

#endif // PROMPT_H
