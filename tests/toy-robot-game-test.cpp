#include <gmock/gmock-spec-builders.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <regex>
#include <vector>


#include "toy-robot-game.h"
#include "mocs.h"

using ::testing::Eq;
using ::testing::Return;
using namespace ToyRobotGame;

namespace{



TEST(ToyRobotGameTest, CommandsInvalid) {
  auto mockTable = std::make_shared<MockTable>();

  Game game(mockTable);

  ASSERT_FALSE(game.doCommandString(""));
  ASSERT_FALSE(game.doCommandString("BOB"));
  ASSERT_FALSE(game.doCommandString("JOE"));
  ASSERT_FALSE(game.doCommandString("HARRY PLACE 3,4,NORTH"));
}

TEST(ToyRobotGameTest, CommandPlaceRobot) {
  auto mockTable = std::make_shared<MockTable>();

  Game game(mockTable);

  testing::InSequence s1;

  EXPECT_CALL(*mockTable, placeRobot(Eq(3), Eq(4), Eq(DF_NORTH)))
      .Times(1)
      .WillOnce(Return(true));
  ASSERT_TRUE(game.doCommandString("PLACE 3,4,NORTH"));

  EXPECT_CALL(*mockTable, placeRobot(Eq(2), Eq(1), Eq(DF_SOUTH)))
      .Times(1)
      .WillOnce(Return(true));
  ASSERT_TRUE(game.doCommandString("PLACE 2,1,SOUTH"));

  EXPECT_CALL(*mockTable, placeRobot(Eq(0), Eq(0), Eq(DF_EAST)))
      .Times(1)
      .WillOnce(Return(true));
  ASSERT_TRUE(game.doCommandString("PLACE 0,0,EAST"));

  EXPECT_CALL(*mockTable, placeRobot(Eq(1), Eq(0), Eq(DF_WEST)))
      .Times(1)
      .WillOnce(Return(true));
  ASSERT_TRUE(game.doCommandString("PLACE 1 0 WEST")); // spaces ok too..

  EXPECT_CALL(*mockTable, placeRobot(Eq(10), Eq(10), Eq(DF_WEST)))
      .Times(1)
      .WillOnce(Return(false));
  ASSERT_FALSE(game.doCommandString("PLACE 10 10 WEST")); // false from table.

  ASSERT_FALSE(game.doCommandString("PLACE 0 0 FAST")); // bad direction

  ASSERT_FALSE(game.doCommandString("PLACE")); // no parameters

  ASSERT_FALSE(game.doCommandString("PLACE 1")); // not enough parameters

  ASSERT_FALSE(game.doCommandString("PLACE 2 3")); // not enough parameters

  ASSERT_FALSE(game.doCommandString("PLACE 1 3 4")); // pad parameter

  ASSERT_FALSE(game.doCommandString("PLACE a,b,c")); // bad parameters

  ASSERT_FALSE(game.doCommandString("PLACEa,b,c")); // bad format
}

TEST(ToyRobotGameTest, CommandMoveRobot) {
  auto mockTable = std::make_shared<MockTable>();

  Game game(mockTable);

  EXPECT_CALL(*mockTable, moveRobot()).Times(1).WillOnce(Return(true));
  ASSERT_TRUE(game.doCommandString("MOVE"));

  EXPECT_CALL(*mockTable, moveRobot()).Times(1).WillOnce(Return(false));
  ASSERT_FALSE(game.doCommandString("MOVE"));

  ASSERT_FALSE(game.doCommandString("MOVEasdasdasdsad"));

  ASSERT_FALSE(game.doCommandString("MOVE extra words"));
}

TEST(ToyRobotGameTest, CommandRotateRobot) {
  auto mockTable = std::make_shared<MockTable>();

  Game game(mockTable);

  EXPECT_CALL(*mockTable, rotateRobot(R_LEFT)).Times(1).WillOnce(Return(true));
  ASSERT_TRUE(game.doCommandString("ROTATE LEFT"));

  EXPECT_CALL(*mockTable, rotateRobot(R_RIGHT)).Times(1).WillOnce(Return(true));
  ASSERT_TRUE(game.doCommandString("ROTATE RIGHT"));

  EXPECT_CALL(*mockTable, rotateRobot(R_LEFT)).Times(1).WillOnce(Return(false));
  ASSERT_FALSE(game.doCommandString("ROTATE LEFT"));

  EXPECT_CALL(*mockTable, rotateRobot(R_RIGHT))
      .Times(1)
      .WillOnce(Return(false));
  ASSERT_FALSE(game.doCommandString("ROTATE RIGHT"));

  ASSERT_FALSE(game.doCommandString("ROTATE"));

  ASSERT_FALSE(game.doCommandString("ROTATELEFT"));

  ASSERT_FALSE(game.doCommandString("ROTATE bbbb"));
}

TEST(ToyRobotGameTest, CommandReportRobotPosition) {
  auto mockTable = std::make_shared<MockTable>();

  Game game(mockTable);

  EXPECT_CALL(*mockTable, reportRobotPosition())
      .Times(1)
      .WillOnce(Return("robot position"));
  ASSERT_TRUE(game.doCommandString("REPORT"));

  ASSERT_FALSE(game.doCommandString("REPORTsadsdasd"));
  ASSERT_FALSE(game.doCommandString("REPORT sadsdasd"));
}
}