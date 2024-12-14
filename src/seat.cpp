#include "seat.h"

namespace boosapi {

std::string to_string(SeatType seat) {
  return std::string(1, seat.letter) + std::to_string(seat.number);
}

SeatType from_string(const std::string &str) {
  return SeatType{str[0], std::stoi(str.substr(1))};
}

bool operator==(const SeatType &lhs, const SeatType &rhs) {
  return lhs.letter == rhs.letter && lhs.number == rhs.number;
}

bool operator<(const SeatType &lhs, const SeatType &rhs) {
  return lhs.letter < rhs.letter ||
         (lhs.letter == rhs.letter && lhs.number < rhs.number);
}

void SeatType::swap(SeatType &other) {
  std::swap(letter, other.letter);
  std::swap(number, other.number);
}
} // namespace boosapi
