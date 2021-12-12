#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "robot.h"
#include "toy-robot-game.h"
#include "string-funcs.h"

using namespace ToyRobotGame;

// command parameter strings to enum values
std::map<std::string,Rotate> rotateParameters {
  {"LEFT", R_LEFT},
  {"RIGHT", R_RIGHT}
};

std::map<std::string,DirectionFacing> facingParameters {
  {"NORTH", DF_NORTH},
  {"EAST", DF_EAST},
  {"SOUTH", DF_SOUTH},
  {"WEST", DF_WEST}
};

// create game with Table Instance.
Game::Game(std::shared_ptr<Table> tableInstance)
    : table(tableInstance) {
  assert(tableInstance);
}

// takes a line of input and calls the appropriate method.
bool Game::doCommandString(const std::string line) {
  if (line.empty()) {
    return false;
  }

  // split to command and parameters
  auto splitcommand = utils::split(line);
  if(splitcommand.empty() || splitcommand.size() > 2){
    return false;
  }

  // if there is a parameter string, split it into strings
  std::vector<std::string> parameters;
  std::string command = splitcommand.front();
  if(splitcommand.front() != splitcommand.back()){
    parameters = utils::tokenize(splitcommand.back());
  }

  // if the command string is valid call the method.
  if(commandFunctions.count(command) > 0){
    return commandFunctions[command](parameters);
  }else{
    std::cout << "Error: \"" << command << "\" is not a valid command." << std::endl;
  }

  return false;
}

// PLACE command, takex the x,y,direction and passes it to the table
// any problems converting integers or the direction is not correct
// are errors.
bool Game::placeCommand(std::vector<std::string> parameters){
  if(parameters.size() == 3){
    std::string directionstr = parameters[2];

    try{
      int x = std::stoi(parameters[0]);
      int y = std::stoi(parameters[1]);
      if(facingParameters.count(parameters[2])){
        return table->placeRobot(x, y, facingParameters[parameters[2]]);
      }
      std::cout << "PLACE: " << parameters[2] << " is not a valid direction." << std::endl;
      return false;
    }catch(std::invalid_argument e){
      std::cout << "PLACE: Invalid Argument: " << e.what() << std::endl;
    }catch(std::out_of_range e){
      std::cout << "PLACE: Out Of Range: " << e.what() << std::endl;
    }
    return false;
  }
  std::cout << "PLACE: invalid number of parameters in command. "  << std::endl;

  return false;
}

// ROTATE command, LEFT or RIGHT. if parameter is not LEFT or RIGHT that is 
// an error. Pass correct rotation to table.
bool Game::rotateCommand(std::vector<std::string> parameters){
  if(parameters.size() == 1){
    if(rotateParameters.count(parameters.front())){
      return table->rotateRobot(rotateParameters[parameters.front()]);
    }
    std::cout << "ROTATE: " << parameters.front() << " is not a valid rotation." << std::endl;
    return false;
  }
  std::cout << "ROTATE: invalid number of parameters in command. "  << std::endl;
  return false;
}

// MOVE command, needs no parameters, pass to table.
bool Game::moveCommand(std::vector<std::string> parameters){
  if(parameters.empty()){
    return table->moveRobot();
  }
  std::cout << "MOVE: invalid number of parameters in command. "  << std::endl;
  return false;
}

// REPORT command, no parameters, get position string from the table.
bool Game::reportCommand(std::vector<std::string> parameters){
  if(parameters.empty()){
    std::cout << "Robot reports: " << table->reportRobotPosition() << std::endl;
    return true;
  } 
  return false;
}

