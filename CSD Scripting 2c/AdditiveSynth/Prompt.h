#ifndef PROMPT_H
#define PROMPT_H

#include <string>
#include <functional>
#include <map>
#include <vector>

typedef std::function<bool(std::string, std::vector<std::string>)> PromptFunction;

class Prompt
{
  protected:
    // Variables
    std::map<std::string, PromptFunction> commands;

  public:
    Prompt();
    virtual ~Prompt();

    // Add a command
    void add(std::string command, PromptFunction fn);

    // Execute a command
    bool execute(std::string line);

    // Get things from cin easily
    char getChar();
    std::string getLine();
    int getInteger(int defaultValue);
    double getDouble(double defaultValue);

    // Run the prompt loop
    void run();
};

#endif // PROMPT_H
