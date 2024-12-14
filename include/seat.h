#pragma once

#include <string>

namespace boosapi {

struct SeatType {
  char letter;
  int number;
  void swap(SeatType &other);
  SeatType &operator=(SeatType &rhs) {
    swap(rhs);
    return *this;
  }
};

std::string to_string(SeatType seat);
SeatType from_string(const std::string &str);
bool operator==(const SeatType &lhs, const SeatType &rhs);
bool operator<(const SeatType &lhs, const SeatType &rhs);
} // namespace boosapi
