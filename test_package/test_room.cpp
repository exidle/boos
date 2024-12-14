#include "../include/room.h"
#include <gtest/gtest.h>

class RoomFixture : public ::testing::Test {
public:
  boosapi::Room room{"Room 1", 13};
};

TEST_F(RoomFixture, get_available_seats) {
  EXPECT_EQ(room.getAvailableSeats().size(), 13);
}

TEST_F(RoomFixture, book_seat) {
  EXPECT_TRUE(room.bookSeat(boosapi::SeatType{'A', 1}));
  EXPECT_FALSE(room.bookSeat(boosapi::SeatType{'A', 1}));

  EXPECT_EQ(room.getAvailableSeats().size(), 12);
  EXPECT_EQ(room.getBookedSeats().size(), 1);
}

TEST_F(RoomFixture, name) { EXPECT_EQ(room.getName(), "Room 1"); }
