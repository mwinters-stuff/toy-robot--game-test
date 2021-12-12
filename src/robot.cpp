#include "robot.h"
#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> directionfacingStrings = {"North","East", "South","West"};

using namespace ToyRobotGame;

// initial position of robot is not placed.
Robot::Robot(): x(-1),y(-1),facing(DF_NORTH), moveChecked(false){

}

// place robot, if not already.
bool Robot::place(const int x, const int y,const  DirectionFacing facing){
  if(!isPlaced()){
    this->x = x;
    this->y = y;
    this->facing = facing;
    std::cout << "Robot placed at " << x << "," << y << "," << directionfacingStrings[facing] << "." << std::endl;
    return true;
  }
  std::cout << "Robot has already been placed." << std::endl;
  return false;
}

// rotate robot left or right if placed.
bool Robot::rotate(const Rotate rotate){
  if(!isPlaced()){
    std::cout << "Robot has not been placed and can not rotate." << std::endl;
    return false;
  }
  switch(rotate){
    case R_LEFT:
      rotateLeft();
      break;
    case R_RIGHT:
      rotateRight();
      break;
  }
  std::cout << "Robot now facing " << directionfacingStrings[facing] << "." << std::endl;
  return true;
}


void Robot::rotateLeft(){
  std::cout << "Robot rotating Left." << std::endl;
  switch(facing){
    case DF_NORTH:
      facing = DF_WEST;
      break;
    case DF_EAST:
      facing = DF_NORTH;
      break;
    case DF_SOUTH:
      facing = DF_EAST;
      break;
    case DF_WEST:
      facing = DF_SOUTH;
      break;
  }
}

void Robot::rotateRight(){
  std::cout << "Robot rotating Right." << std::endl;
  switch(facing){
    case DF_NORTH:
      facing = DF_EAST;
      break;
    case DF_EAST:
      facing = DF_SOUTH;
      break;
    case DF_SOUTH:
      facing = DF_WEST;
      break;
    case DF_WEST:
      facing = DF_NORTH;
      break;
  }
}

// move robot if placed and checked, once moved reset moveChecked
bool Robot::move(){
  if(!isPlaced()){
    std::cout << "Robot has not been placed and can not move." << std::endl;
    return false;
  }
  if(!moveChecked){
    std::cout << "Robot move has not been checked, and can not move." << std::endl;
    return false;
  }

  calculateMove(x,y);
  std::cout << "Robot moved to " << x << "," << y << "." << std::endl;

  moveChecked = false;
  return true;
}

// check the next move is valid within 0,0,maxx,maxy.
bool Robot::checkMove(const int maxx, const int maxy){
  int newX;
  int newY;

  calculateMove(newX, newY);

  moveChecked = newX >= 0 && newY >= 0 && newX < maxx && newY < maxy;
  return moveChecked;
}

// calculate position the robot will be in
// after a move in the facing direction, passing
// back the new position.
void Robot::calculateMove(int& newx, int& newy){
  newx = x;
  newy = y;
  switch(facing){
    case DF_NORTH:
      newy++;
      break;
    case DF_EAST:
      newx++;
      break;
    case DF_SOUTH:
      newy--;
      break;
    case DF_WEST:
      newx--;
      break;
  }
}


// report the robot position.
std::string Robot::reportPosition(){
  if(!isPlaced()){
    return "Not placed on table";
  }
  std::stringstream sstream;
  sstream << x << "," << y << "," << directionfacingStrings[facing]; 
  return sstream.str();
}
