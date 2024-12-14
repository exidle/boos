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

} // namespace boosapi
