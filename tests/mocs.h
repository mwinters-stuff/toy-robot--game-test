#pragma once

#include <gmock/gmock.h>

#include "robot.h"
#include "table.h"


class MockTable : public ToyRobotGame::Table {
public:
  MockTable(){};
  virtual ~MockTable(){};

  MOCK_METHOD(bool, placeRobot,
              (const int x, const int y, const ToyRobotGame::DirectionFacing facing),
              (override));
  MOCK_METHOD(bool, moveRobot, (), (override));
  MOCK_METHOD(bool, rotateRobot, (const ToyRobotGame::Rotate rotate), (override));
  MOCK_METHOD(std::string, reportRobotPosition, (), (override));
  MOCK_METHOD(int, getHeight, (), (override));
  MOCK_METHOD(int, getWidth, (), (override));
};

class MockRobot : public ToyRobotGame::Robot{
public:
  MockRobot(){};
  virtual ~MockRobot(){};

  MOCK_METHOD(bool, isPlaced, (), (override));
  MOCK_METHOD(int, getX, (), (override));
  MOCK_METHOD(int, getY, (), (override));
  MOCK_METHOD(ToyRobotGame::DirectionFacing, getFacing, (), (override));
  MOCK_METHOD(bool, place, (const int x, const int y, const ToyRobotGame::DirectionFacing facing), (override));
  MOCK_METHOD(bool, rotate, (const ToyRobotGame::Rotate rotate), (override));
  MOCK_METHOD(bool, move, (), (override));
  MOCK_METHOD(bool, checkMove, (const int maxx, const int maxy), (override));
  MOCK_METHOD(std::string, reportPosition, (), (override));
};

