#include "../include/seat.h"
#include <gtest/gtest.h>

TEST(SeatTest, test_to_string) {
  EXPECT_EQ("A1", boosapi::to_string(boosapi::SeatType{'A', 1}));
  EXPECT_EQ("B2", boosapi::to_string(boosapi::SeatType{'B', 2}));
  EXPECT_EQ("C3", boosapi::to_string(boosapi::SeatType{'C', 3}));
}

TEST(SeatTest, test_from_string) {
  EXPECT_EQ((boosapi::SeatType{'A', 1}), boosapi::from_string("A1"));
  EXPECT_EQ((boosapi::SeatType{'B', 2}), boosapi::from_string("B2"));
  EXPECT_EQ((boosapi::SeatType{'C', 3}), boosapi::from_string("C3"));
}

TEST(SeatTest, test_from_string_invalid) {
  EXPECT_THROW(boosapi::from_string("AA"), std::invalid_argument);
  EXPECT_THROW(boosapi::from_string("1"), std::invalid_argument);
}
