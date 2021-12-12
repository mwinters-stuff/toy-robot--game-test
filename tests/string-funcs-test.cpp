#include "string-funcs.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using ::testing::ElementsAre;



TEST(StringFuncs, tokenize) {
  EXPECT_THAT(utils::tokenize("command"), ElementsAre("command"));

  EXPECT_THAT(utils::tokenize("command parameter1 parameter2"),
              ElementsAre("command", "parameter1", "parameter2"));

  EXPECT_THAT(utils::tokenize("command parameter1,parameter2"),
              ElementsAre("command", "parameter1", "parameter2"));

  EXPECT_THAT(utils::tokenize("command parameter1,parameter2"),
              ElementsAre("command", "parameter1", "parameter2"));

}

TEST(StringFuncs, SplitTest){
  EXPECT_THAT(utils::split("command"), ElementsAre("command"));

  EXPECT_THAT(utils::split("command parameter1 parameter2"),
              ElementsAre("command", "parameter1 parameter2"));

  EXPECT_THAT(utils::split("command parameter1,parameter2"),
              ElementsAre("command", "parameter1,parameter2"));
}