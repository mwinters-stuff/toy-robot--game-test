#include <cassert>
#include <iostream>
#include "table.h"

using namespace ToyRobotGame;

// initialise table, assert if parameters are invalid.
Table::Table(int width, int height, std::shared_ptr<Robot> robotInstance): width(width), height(height), robot(robotInstance){
  assert(robotInstance);
  assert(width > 0 && height > 0);
}

// place a robot on the table, if the given position is within the table.
bool Table::placeRobot(const int x, const int y, const DirectionFacing facing){
  if(x < 0 || y < 0 || x >= width || y >= height){
    std::cout << "Can not place robot off the table." << std::endl;
    return false;
  }
  return robot->place(x,y,facing);
}

// move the robot, unless it is not placed on the table
// or the move would be off the table.
bool Table::moveRobot(){
  if(!robot->isPlaced()){
    std::cout << "Robot has not been placed and can not move." << std::endl;
    return false;
  }
  if(robot->checkMove(width,height)){
    return robot->move();
  }
  std::cout << "Robot refuses to move off the table." << std::endl;
  return false;
}

// pass on the rotate direction.
bool Table::rotateRobot(const Rotate rotate){
  return robot->rotate(rotate);
}

// get robot position.
std::string Table::reportRobotPosition(){
  return robot->reportPosition();
}