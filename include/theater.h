#pragma once

#include "movie.h"
#include "room.h"
#include "seat.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace boosapi {

// Theater
// Identified by name
// Has rooms
// Every room shows a movie
// Every room has 20 seats capacity
class Theater {
public:
  Theater(std::string name, size_t rooms_amount);

  std::string getName() const { return name; }
  // Get avialble rooms. Every room is identified by name
  std::vector<std::string> getAvailableRooms() const;

  Room &getRoom(const std::string &name);
  void assignMovie(const std::string &room_name, const MovieItem &movie);

  MovieItem getMovie(const std::string &room_name) const;

private:
  std::string name;
  std::vector<Room> rooms;
  std::unordered_map<std::string, MovieItem> movies;
};

} // namespace boosapi
