#pragma once

#include <string>
namespace boosapi {

struct MovieItem {
  std::string title;
  int year;
};

inline static bool operator==(const MovieItem &lhs, const MovieItem &rhs) {
  return lhs.title == rhs.title && lhs.year == rhs.year;
}

inline static std::string to_string(const MovieItem &movie) {
  return movie.title + " (" + std::to_string(movie.year) + ")";
}

} // namespace boosapi
