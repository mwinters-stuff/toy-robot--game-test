#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "table.h"

namespace ToyRobotGame{

typedef std::function<bool(std::vector<std::string> parameters)> commandFunction;

class Game{
  public:
    // creates the game, injecting an instance of Table
    Game(std::shared_ptr<Table> tableInstance);
    virtual ~Game(){}

    // called with a line of input
    bool doCommandString(const std::string line);

  private:
    std::shared_ptr<Table> table;


    bool placeCommand(std::vector<std::string> parameters);
    bool rotateCommand(std::vector<std::string> parameters);
    bool moveCommand(std::vector<std::string> parameters);
    bool reportCommand(std::vector<std::string> parameters);

    // maps commands to the above methods.
    std::map<std::string, commandFunction> commandFunctions
      {
        { "PLACE", [&](std::vector<std::string> parameters) {
          return placeCommand(parameters);
        }},
        { "ROTATE", [&](std::vector<std::string> parameters) {
          return rotateCommand(parameters);
        }},
        { "MOVE", [&](std::vector<std::string> parameters) {
          return moveCommand(parameters);
        }},
        { "REPORT", [&](std::vector<std::string> parameters) {
          return reportCommand(parameters);
        }},

      };

};

}