#include "theater.h"

namespace boosapi {

Theater::Theater(std::string name, size_t rooms_amount) : name(name) {
  for (size_t i = 0; i < rooms_amount; ++i) {
    // rooms.push_back(Room("Room " + std::to_string(i + 1)));
    rooms.emplace_back("Room " + std::to_string(i + 1));
  }
}

std::vector<std::string> Theater::getAvailableRooms() const {
  std::vector<std::string> available_rooms(rooms.size());
  std::transform(rooms.begin(), rooms.end(), available_rooms.begin(),
                 [](const Room &r) -> std::string { return r.getName(); });
  return available_rooms;
}

Room &Theater::getRoom(const std::string &name) {
  for (auto &room : rooms) {
    if (room.getName() == name) {
      return room;
    }
  }
  throw std::runtime_error("Room not found");
}

void Theater::assignMovie(const std::string &room_name,
                          const MovieItem &movie) {
  movies[room_name] = movie;
}

MovieItem Theater::getMovie(const std::string &room_name) const {
  return movies.at(room_name);
}

bool Theater::hasMovie(const std::string &room_name) const {
  return movies.find(room_name) != movies.end();
}

} // namespace boosapi
