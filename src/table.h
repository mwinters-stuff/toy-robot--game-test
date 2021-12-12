#pragma once

// Table, owns a robot and the width/hgith of the table, forwards commands
// to the robot.

#include <memory>

#include "robot.h"

namespace ToyRobotGame{

class Table{
  public:
    // default constructor for test mocs.
    Table(){};
    // table of width/height injecting robot instance.
    Table(int width, int height, std::shared_ptr<Robot> robotInstance);

    // forwards commands to the robot from the game.
    virtual bool placeRobot(const int x, const int y, const DirectionFacing facing);
    virtual bool moveRobot();
    virtual bool rotateRobot(const Rotate rotate);
    virtual std::string reportRobotPosition();

    // getters
    virtual int getHeight(){return height;}
    virtual int getWidth(){return width;}

  private:
    int width;
    int height;
    std::shared_ptr<Robot> robot;
};
}