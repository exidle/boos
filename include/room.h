#pragma once

#include "seat.h"
#include <string>
#include <vector>

namespace boosapi {

constexpr auto DEFAULT_CAPACITY = 20;

struct Impl;
//
// Theater's room identified by name
class Room {
public:
  // Create a room named name with capacity seats
  explicit Room(std::string name, size_t capacity = DEFAULT_CAPACITY);
  ~Room();

  Room &operator=(const Room &other) = delete;
  Room(const Room &other) = delete;

  Room &operator=(Room &&other) noexcept {
    std::swap(this->name, other.name);
    std::swap(this->impl, other.impl);
    return *this;
  }

  Room(Room &&other) noexcept
      : name(std::move(other.name)), impl(std::move(other.impl)) {}

  // Book a seat
  // return true if successful
  bool bookSeat(SeatType seat);

  // Get available seats
  std::vector<SeatType> getAvailableSeats() const;

  // Get booked seats
  std::vector<SeatType> getBookedSeats() const;

  std::string getName() const { return name; }

private:
  std::string name;
  std::unique_ptr<Impl> impl;
};

struct Impl {
  struct SharedRoomData {
    mutable std::mutex controlMutex;
    using SeatInfo = std::pair<SeatType, bool>;
    std::vector<SeatInfo> seats;

    explicit SharedRoomData(size_t capacity = DEFAULT_CAPACITY);
    bool bookSeat(SeatType seat);
    std::vector<SeatType> getAvailableSeats() const;
    std::vector<SeatType> getBookedSeats() const;
  };

  explicit Impl(size_t capacity)
      : data{std::make_shared<SharedRoomData>(capacity)} {}

  std::shared_ptr<SharedRoomData> data;
};

} // namespace boosapi
