#pragma once

#include "movie.h"
#include "theater.h"

namespace boosapi {

class BoosAPI {
public:
  BoosAPI();
  ~BoosAPI() = default;

  std::vector<MovieItem> getAllMovies() const { return movies; }

  std::vector<std::string> getTheaters(const MovieItem &movie) const;

  std::vector<std::string> getRooms(const std::string &theater,
                                    const MovieItem &movie) const;

  std::vector<SeatType> getAvailableSeats(const std::string &theater,
                                          const std::string &room);

  bool bookSeat(const std::string &theater, const std::string &room,
                const SeatType &seat);

private:
  std::vector<Theater> theaters;
  std::vector<MovieItem> movies;
};

} // namespace boosapi
