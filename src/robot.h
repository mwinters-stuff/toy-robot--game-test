#pragma once

// robot class, the robot knows where it is and what direction it is facing.
// The calls are made to the robot to place/rotate and move it.

#include <string>

namespace ToyRobotGame{

enum DirectionFacing {
  DF_NORTH,
  DF_EAST,
  DF_SOUTH,
  DF_WEST,
};

enum Rotate{
  R_LEFT,
  R_RIGHT
};


class Robot{
  public:
    Robot();
    virtual ~Robot(){}

    // true if robot has been placed, false if not.
    virtual bool isPlaced(){ return x >= 0 && y >= 0; }
    
    // getters
    virtual int getX(){return x;}
    virtual int getY(){return y;}
    virtual DirectionFacing getFacing(){return facing;}

    // call to place robot at position and facing direction.
    // location should have already been checked to see if is on the table.
    // fails if already placed.
    virtual bool place(const int x, const int y, const DirectionFacing facing);
    
    // rotate the robot, fails if robot is not placed.
    virtual bool rotate(const Rotate rotate);

    // move the robot by one in the direction facing, or fails
    // if the robot is not placed, or the move has not been checked first.
    virtual bool move();

    // call to first check if the robot can move in its direction within 
    // the maxx and maxy boundries.
    virtual bool checkMove(const int maxx, const int maxy);

    // returns a string reporting the robots position.
    virtual std::string reportPosition();

    
  private:
    // robots position, -1 if not placed.
    int x;
    int y;
    DirectionFacing facing;

    // true if the move has been checked, false if not.
    bool moveChecked;

    // rotates the robot left to a new facingDirection
    void rotateLeft();
    // rotates the robot right to a new facingDirection
    void rotateRight();

    // calculate the next move, returning new x and y position
    void calculateMove(int& newx, int& newy);
};

}
