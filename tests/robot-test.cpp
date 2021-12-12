
#include "robot.h"
#include <gtest/gtest.h>

using namespace ToyRobotGame;

namespace{
TEST(RobotTest, RobotNotPlaced) {
  Robot robot;

  ASSERT_FALSE(robot.rotate(R_LEFT));
  ASSERT_FALSE(robot.move());
  ASSERT_FALSE(robot.checkMove(5, 5));
}

TEST(RobotTest, PlaceRobot) {
  Robot robot;

  ASSERT_TRUE(robot.place(4, 2, DF_SOUTH));

  ASSERT_EQ(robot.getX(), 4);
  ASSERT_EQ(robot.getY(), 2);
  ASSERT_EQ(robot.getFacing(), DF_SOUTH);

  // attempting to place robot a second time fails
  ASSERT_FALSE(robot.place(2, 1, DF_NORTH));

  ASSERT_EQ(robot.getX(), 4);
  ASSERT_EQ(robot.getY(), 2);
  ASSERT_EQ(robot.getFacing(), DF_SOUTH);
}

TEST(RobotTest, RotateRobotLeft) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_NORTH));

  ASSERT_TRUE(robot.rotate(R_LEFT));
  ASSERT_EQ(robot.getFacing(), DF_WEST);

  ASSERT_TRUE(robot.rotate(R_LEFT));
  ASSERT_EQ(robot.getFacing(), DF_SOUTH);

  ASSERT_TRUE(robot.rotate(R_LEFT));
  ASSERT_EQ(robot.getFacing(), DF_EAST);

  ASSERT_TRUE(robot.rotate(R_LEFT));
  ASSERT_EQ(robot.getFacing(), DF_NORTH);
}

TEST(RobotTest, RotateRobotRight) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_NORTH));

  ASSERT_TRUE(robot.rotate(R_RIGHT));
  ASSERT_EQ(robot.getFacing(), DF_EAST);

  ASSERT_TRUE(robot.rotate(R_RIGHT));
  ASSERT_EQ(robot.getFacing(), DF_SOUTH);

  ASSERT_TRUE(robot.rotate(R_RIGHT));
  ASSERT_EQ(robot.getFacing(), DF_WEST);

  ASSERT_TRUE(robot.rotate(R_RIGHT));
  ASSERT_EQ(robot.getFacing(), DF_NORTH);
}

TEST(RobotTest, CheckMoveNorthInsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_NORTH));

  ASSERT_TRUE(robot.checkMove(5, 5));
}

TEST(RobotTest, MoveNorthInsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_NORTH));

  ASSERT_TRUE(robot.checkMove(5, 5));
  ASSERT_TRUE(robot.move());

  ASSERT_EQ(robot.getX(), 2);
  ASSERT_EQ(robot.getY(), 3);
}

TEST(RobotTest, CheckMoveNorthOutsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 4, DF_NORTH));

  ASSERT_FALSE(robot.checkMove(5, 5));
}

TEST(RobotTest, MoveNorthOutsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 4, DF_NORTH));

  ASSERT_FALSE(robot.checkMove(5, 5));
  ASSERT_FALSE(robot.move());

  ASSERT_EQ(robot.getX(), 2);
  ASSERT_EQ(robot.getY(), 4);
}

TEST(RobotTest, CheckMoveEastInsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_EAST));

  ASSERT_TRUE(robot.checkMove(5, 5));
}

TEST(RobotTest, MoveEastInsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_EAST));

  ASSERT_TRUE(robot.checkMove(5, 5));
  ASSERT_TRUE(robot.move());

  ASSERT_EQ(robot.getX(), 3);
  ASSERT_EQ(robot.getY(), 2);
  
}


TEST(RobotTest, CheckMoveEastOutsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(4, 3, DF_EAST));

  ASSERT_FALSE(robot.checkMove(5, 5));
}

TEST(RobotTest, MoveEastOutsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(4, 3, DF_EAST));

  ASSERT_FALSE(robot.checkMove(5, 5));
  ASSERT_FALSE(robot.move());

  ASSERT_EQ(robot.getX(), 4);
  ASSERT_EQ(robot.getY(), 3);
}

TEST(RobotTest, CheckMoveSouthInsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_SOUTH));

  ASSERT_TRUE(robot.checkMove(5, 5));
}

TEST(RobotTest, MoveSouthInsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_SOUTH));

  ASSERT_TRUE(robot.checkMove(5, 5));
  ASSERT_TRUE(robot.move());

  ASSERT_EQ(robot.getX(), 2);
  ASSERT_EQ(robot.getY(), 1);
}


TEST(RobotTest, CheckMoveSouthOutsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 0, DF_SOUTH));

  ASSERT_FALSE(robot.checkMove(5, 5));
}

TEST(RobotTest, MoveSouthOutsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 0, DF_SOUTH));

  ASSERT_FALSE(robot.checkMove(5, 5));
  ASSERT_FALSE(robot.move());

  ASSERT_EQ(robot.getX(), 2);
  ASSERT_EQ(robot.getY(), 0);
}

TEST(RobotTest, CheckMoveWestInsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_WEST));

  ASSERT_TRUE(robot.checkMove(5, 5));
}

TEST(RobotTest, MoveWestInsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_WEST));

  ASSERT_TRUE(robot.checkMove(5, 5));
  ASSERT_TRUE(robot.move());

  ASSERT_EQ(robot.getX(), 1);
  ASSERT_EQ(robot.getY(), 2);
}

TEST(RobotTest, CheckMoveWestOutsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(0, 3, DF_WEST));

  ASSERT_FALSE(robot.checkMove(5, 5));
}

TEST(RobotTest, MoveWestOutsideBounds) {
  Robot robot;

  ASSERT_TRUE(robot.place(0, 3, DF_WEST));

  ASSERT_FALSE(robot.checkMove(5, 5));
  ASSERT_FALSE(robot.move());

  ASSERT_EQ(robot.getX(), 0);
  ASSERT_EQ(robot.getY(), 3);
}

TEST(RobotTest, MoveRobotUnchecked) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_NORTH));

  ASSERT_FALSE(robot.move());

  ASSERT_EQ(robot.getX(), 2);
  ASSERT_EQ(robot.getY(), 2);
}

TEST(RobotTest, MoveRobotChecked) {
  Robot robot;

  ASSERT_TRUE(robot.place(2, 2, DF_NORTH));

  ASSERT_TRUE(robot.checkMove(5, 5));

  ASSERT_TRUE(robot.move());
}

TEST(RobotTest, ReportPosition){
  Robot robot;

  ASSERT_EQ(robot.reportPosition(), "Not placed on table");

  ASSERT_TRUE(robot.place(2, 3, DF_NORTH));

  ASSERT_EQ(robot.reportPosition(), "2,3,North");
  
  ASSERT_TRUE(robot.rotate(R_RIGHT));
  ASSERT_EQ(robot.reportPosition(), "2,3,East");

  ASSERT_TRUE(robot.rotate(R_RIGHT));
  ASSERT_EQ(robot.reportPosition(), "2,3,South");

  ASSERT_TRUE(robot.rotate(R_RIGHT));
  ASSERT_EQ(robot.reportPosition(), "2,3,West");

}
}