
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "mocs.h"

using ::testing::Return;
using ::testing::Eq;
using ::testing::InSequence;
using namespace ToyRobotGame;

namespace {

TEST(TableTest, TableCreate){
  auto mockRobot = std::make_shared<MockRobot>();
  Table table(123,456,mockRobot);


  ASSERT_EQ(table.getWidth(), 123);
  ASSERT_EQ(table.getHeight(), 456);


}

TEST(TableTest, PlaceRobot){
  auto mockRobot = std::make_shared<MockRobot>();
  Table table(5,5,mockRobot);
  
  EXPECT_CALL(*mockRobot, place(Eq(2),Eq(4), Eq(DF_WEST))).Times(1).WillOnce(Return(true));

  ASSERT_TRUE(table.placeRobot(2,4,DF_WEST));

  EXPECT_CALL(*mockRobot, place(Eq(2),Eq(4), Eq(DF_EAST))).Times(1).WillOnce(Return(false));
  ASSERT_FALSE(table.placeRobot(2,4,DF_EAST));

  ASSERT_FALSE(table.placeRobot(-1,-2,DF_EAST));
  ASSERT_FALSE(table.placeRobot(7,8,DF_EAST));

}


TEST(TableTest, MoveRobot){
  auto mockRobot = std::make_shared<MockRobot>();
  Table table(5,5,mockRobot);

  {
    InSequence s1;
    EXPECT_CALL(*mockRobot, isPlaced()).Times(1).WillOnce(Return(false));

    ASSERT_FALSE(table.moveRobot());

    EXPECT_CALL(*mockRobot, isPlaced()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*mockRobot, checkMove(Eq(5),Eq(5))).Times(1).WillOnce(Return(false));
    ASSERT_FALSE(table.moveRobot());
  }

  {
    InSequence s1;
    EXPECT_CALL(*mockRobot, isPlaced()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*mockRobot, checkMove(Eq(5),Eq(5))).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockRobot, move()).Times(1).WillOnce(Return(false));

    ASSERT_FALSE(table.moveRobot());
  }

  {
    InSequence s1;
    EXPECT_CALL(*mockRobot, isPlaced()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*mockRobot, checkMove(Eq(5),Eq(5))).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockRobot, move()).Times(1).WillOnce(Return(true));

    ASSERT_TRUE(table.moveRobot());
  }
}

TEST(TableTest, RotateRobot){
  auto mockRobot = std::make_shared<MockRobot>();
  Table table(5,5,mockRobot);
  
  EXPECT_CALL(*mockRobot, rotate(Eq(R_LEFT))).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*mockRobot, rotate(Eq(R_RIGHT))).Times(1).WillOnce(Return(false));

  ASSERT_FALSE(table.rotateRobot(R_LEFT));
  ASSERT_FALSE(table.rotateRobot(R_RIGHT));

  EXPECT_CALL(*mockRobot, rotate(Eq(R_LEFT))).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*mockRobot, rotate(Eq(R_RIGHT))).Times(1).WillOnce(Return(true));

  ASSERT_TRUE(table.rotateRobot(R_LEFT));
  ASSERT_TRUE(table.rotateRobot(R_RIGHT));
}

TEST(TableTest, ReportRobotPosition){
  auto mockRobot = std::make_shared<MockRobot>();
  Table table(5,5,mockRobot);
  
  EXPECT_CALL(*mockRobot, reportPosition()).Times(1).WillOnce(Return(std::string("reported position")));

  ASSERT_EQ(table.reportRobotPosition(), "reported position");

}

}