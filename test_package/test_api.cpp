#include "../include/boosapi.h"
#include <gtest/gtest.h>

TEST(BoosAPITest, test_get_theaters) {
  boosapi::BoosAPI api;

  auto const movie = api.getAllMovies()[0];
  EXPECT_EQ(api.getTheaters(movie).size(), 2);
}

TEST(BoosAPITest, test_get_rooms) {
  boosapi::BoosAPI api;

  auto const movie = api.getAllMovies()[0];
  EXPECT_EQ(api.getRooms("Theater 1", movie).size(), 1);
  EXPECT_EQ(api.getRooms("Theater 2", movie).size(), 0);
  EXPECT_EQ(api.getRooms("Theater 4", movie).size(), 3);
}

TEST(BoosAPITest, test_available_seats) {
  boosapi::BoosAPI api;

  EXPECT_EQ(api.getAvailableSeats("Theater 1", "Room 1").size(), 20);
  EXPECT_EQ(api.getAvailableSeats("Theater 3", "Room 2").size(), 20);
}

TEST(BoosAPITest, test_book_seat) {
  boosapi::BoosAPI api;

  EXPECT_TRUE(api.bookSeat("Theater 1", "Room 1", {'A', 1}));
  EXPECT_FALSE(api.bookSeat("Theater 1", "Room 1", {'A', 1}));
  EXPECT_EQ(api.getAvailableSeats("Theater 1", "Room 1").size(), 19);
}
