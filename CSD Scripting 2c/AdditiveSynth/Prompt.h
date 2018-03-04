#ifndef PROMPT_H
#define PROMPT_H

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <stdexcept>

// Use a simple name for the huge function
typedef std::function<bool(std::string, std::vector<std::string>)> PromptFunction;
typedef std::function<void(std::string)> PromptEventFunction;

typedef std::map<std::string, PromptFunction> PromptFunctionMap;

class Prompt
{
  protected:
    // Variables
    PromptFunctionMap commands;
    PromptEventFunction beforeFunction;
    PromptEventFunction afterFunction;

  public:
    Prompt();
    virtual ~Prompt();

    // Split string using a delimiter
    static std::vector<std::string> explode(const std::string str, const std::string delimiter = " ");

    // Convert string to numbers
    static int stringToInt(std::string str, int defaultValue);
    static double stringToDouble(std::string str, double defaultValue);

    // Get a line from cin
    static std::string getLine();

    // Command management
    void addCommand(std::string command, PromptFunction fn);
    void removeCommand(std::string command);

    // Set the before and after functions
    void before(PromptEventFunction fn);
    void after(PromptEventFunction fn);

    // Execute a command
    bool execute(std::string line);

    // Run the prompt loop
    void run();
};

#endif // PROMPT_H
