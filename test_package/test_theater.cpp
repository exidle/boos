#include "../include/theater.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using boosapi::MovieItem;
using boosapi::Theater;

class TheaterFixture : public ::testing::Test {
public:
  Theater theater{"Theater 1", 2};
};

TEST_F(TheaterFixture, GetAvailableRooms) {
  std::vector<std::string> expected_rooms{"Room 1", "Room 2"};
  EXPECT_EQ(theater.getAvailableRooms(), expected_rooms);
}

TEST_F(TheaterFixture, GetRoom) {
  EXPECT_EQ(theater.getRoom("Room 1").getName(), "Room 1");
}

TEST_F(TheaterFixture, AssignMovie) {
  theater.assignMovie("Room 1", {"Movie 1", 1991});
  EXPECT_EQ(theater.getMovie("Room 1"), (MovieItem{"Movie 1", 1991}));

  EXPECT_TRUE(theater.hasMovie("Room 1"));
  EXPECT_FALSE(theater.hasMovie("Room 2"));
}
