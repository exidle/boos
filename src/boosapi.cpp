#include "boosapi.h"

namespace boosapi {

BoosAPI::BoosAPI()
    : movies{MovieItem{"Home Alone 1", 1990},
             MovieItem{"Back to the future", 1997},
             MovieItem{"Total recall", 1991},
             MovieItem{"Fifth element", 1991},
             MovieItem{"Matrix", 1999},
             MovieItem{"Avatar", 2009},
             MovieItem{"Star Wars", 1977},
             MovieItem{"Star Trek", 2009},
             MovieItem{"Terminator", 1984}} {

  constexpr auto ROOMS_AMOUNT = 3;
  constexpr auto THEATERS_AMOUNT = 4;
  for (int i = 0; i < THEATERS_AMOUNT; ++i) {
    theaters.emplace_back("Theater " + std::to_string(i + 1), ROOMS_AMOUNT);
  }

  theaters[0].assignMovie("Room 1", movies[0]);
  theaters[0].assignMovie("Room 2", movies[1]);
  theaters[0].assignMovie("Room 3", movies[2]);

  theaters[1].assignMovie("Room 1", movies[3]);
  theaters[1].assignMovie("Room 2", movies[4]);
  theaters[1].assignMovie("Room 3", movies[5]);

  theaters[2].assignMovie("Room 1", movies[6]);
  theaters[2].assignMovie("Room 2", movies[7]);
  theaters[2].assignMovie("Room 3", movies[8]);

  theaters[3].assignMovie("Room 1", movies[0]);
  theaters[3].assignMovie("Room 2", movies[0]);
  theaters[3].assignMovie("Room 3", movies[0]);
}

std::vector<std::string> BoosAPI::getTheaters(const MovieItem &movie) const {
  std::vector<std::string> found_theaters;
  for (const Theater &theater : theaters) {
    if (std::any_of(theater.getAvailableRooms().begin(),
                    theater.getAvailableRooms().end(),
                    [&movie, &theater](const std::string &room) {
                      return theater.getMovie(room) == movie;
                    })) {
      found_theaters.push_back(theater.getName());
    }
  }
  return found_theaters;
}

std::vector<std::string> BoosAPI::getRooms(const std::string &theater_name,
                                           const MovieItem &movie) const {
  std::vector<std::string> found_rooms;
  auto theater_it = std::find_if(theaters.begin(), theaters.end(),
                                 [&theater_name](const Theater &t) {
                                   return t.getName() == theater_name;
                                 });

  if (theater_it == theaters.end()) {
    return found_rooms;
  }

  for (const std::string &room : theater_it->getAvailableRooms()) {
    if (theater_it->getMovie(room) == movie) {
      found_rooms.push_back(room);
    }
  }
  return found_rooms;
}

std::vector<SeatType>
BoosAPI::getAvailableSeats(const std::string &theater_name,
                           const std::string &room) {
  auto theater_it = std::find_if(theaters.begin(), theaters.end(),
                                 [&theater_name](const Theater &t) {
                                   return t.getName() == theater_name;
                                 });
  if (theater_it == theaters.end()) {
    return std::vector<SeatType>();
  }
  return theater_it->getRoom(room).getAvailableSeats();
}

bool BoosAPI::bookSeat(const std::string &theater_name, const std::string &room,
                       const SeatType &seat) {
  auto theater_it = std::find_if(theaters.begin(), theaters.end(),
                                 [&theater_name](const Theater &t) {
                                   return t.getName() == theater_name;
                                 });
  if (theater_it == theaters.end()) {
    return false;
  }
  return theater_it->getRoom(room).bookSeat(seat);
}

} // namespace boosapi
