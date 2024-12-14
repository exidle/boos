#include "room.h"

namespace boosapi {

Room::Room(std::string name, size_t capacity)
    : name(name), impl{std::make_unique<Impl>(capacity)} {}

Room::~Room() {}

bool Room::bookSeat(SeatType seat) { return impl->data->bookSeat(seat); }

std::vector<SeatType> Room::getAvailableSeats() const {
  return impl->data->getAvailableSeats();
}

std::vector<SeatType> Room::getBookedSeats() const {
  return impl->data->getBookedSeats();
}

Impl::SharedRoomData::SharedRoomData(size_t capacity) {
  //  Every room has 20 seats
  //  divided by 4 rows (A, B, C, D), every row has 5 seats (1, 2, 3, 4, 5)
  char seatLetter = 'A';
  for (auto i = 0; i < capacity; i++) {
    seats.push_back({SeatType{seatLetter, i % 5 + 1}, false});
    if (i % 5 == 0) {
      seatLetter++;
    }
  }
}

bool Impl::SharedRoomData::bookSeat(SeatType seat) {
  std::lock_guard<std::mutex> lock(controlMutex);
  auto it = std::find(seats.begin(), seats.end(), std::make_pair(seat, false));
  if (it != seats.end()) {
    it->second = true;
    return true;
  }
  return false;
}

std::vector<SeatType>
convertSeatInfoToSeatType(std::vector<Impl::SharedRoomData::SeatInfo> &seats) {
  std::vector<SeatType> result;
  std::transform(seats.begin(), seats.end(), std::back_inserter(result),
                 [](const auto &seat) { return seat.first; });
  return result;
}

std::vector<SeatType> Impl::SharedRoomData::getAvailableSeats() const {
  std::lock_guard<std::mutex> lock(controlMutex);
  std::vector<SeatInfo> available_seats;
  std::copy_if(seats.begin(), seats.end(), std::back_inserter(available_seats),
               [](const SeatInfo &seat) { return !seat.second; });
  return convertSeatInfoToSeatType(available_seats);
}

std::vector<SeatType> Impl::SharedRoomData::getBookedSeats() const {
  std::lock_guard<std::mutex> lock(controlMutex);
  std::vector<SeatInfo> available_seats;
  std::copy_if(seats.begin(), seats.end(), std::back_inserter(available_seats),
               [](const SeatInfo &seat) { return seat.second; });
  return convertSeatInfoToSeatType(available_seats);
}
} // namespace boosapi
