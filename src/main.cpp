#include "boosapi.h"
#include <crow.h>
#include <string>

int main() {
  boosapi::BoosAPI boosapi;
  crow::SimpleApp app; // Create a Crow application

  // Define a route for GET requests to "/"
  CROW_ROUTE(app, "/")([]() { return "Booking API"; });

  // Define a route for GET requests to "/api/movies"
  CROW_ROUTE(app, "/api/movies")
  ([&boosapi]() {
    std::vector<boosapi::MovieItem> movies = boosapi.getAllMovies();

    crow::json::wvalue response_json;
    for (const boosapi::MovieItem &movie : movies) {
      crow::json::wvalue movie_json;
      movie_json["title"] = movie.title;
      movie_json["year"] = movie.year;
      response_json["movies"] = std::move(movie_json);
    }

    return crow::response(200, response_json);
  });

  CROW_ROUTE(app, "/api/theaters/<string>")
  ([&boosapi](const std::string &movie_info) {
    crow::json::rvalue movie_json = crow::json::load(movie_info);
    std::string movie_title = movie_json["title"].s();
    int movie_year = movie_json["year"].i();

    std::vector<std::string> theaters =
        boosapi.getTheaters(boosapi::MovieItem{movie_title, movie_year});

    crow::json::wvalue response_json;
    for (const std::string &theater : theaters) {
      crow::json::wvalue theater_json;
      theater_json["theater"] = theater;
      response_json["theaters"] = std::move(theater_json);
    }

    return crow::response(200, response_json);
  });

  CROW_ROUTE(app, "/api/rooms/<string>/<string>")
  ([&boosapi](const std::string &theater, const std::string &movie_info) {
    crow::json::rvalue movie_json = crow::json::load(movie_info);
    std::string movie_title = movie_json["title"].s();
    int movie_year = movie_json["year"].i();

    crow::json::rvalue theater_json = crow::json::load(theater);
    std::string theater_name = theater_json["theater"].s();

    std::vector<std::string> rooms = boosapi.getRooms(
        theater_name, boosapi::MovieItem{movie_title, movie_year});

    crow::json::wvalue response_json;
    for (const std::string &room : rooms) {
      crow::json::wvalue room_json;
      room_json["room"] = room;
      response_json["rooms"] = std::move(room_json);
    }

    return crow::response(200, response_json);
  });

  CROW_ROUTE(app, "/api/seats/<string>/<string>")
  ([&boosapi](const std::string &theater, const std::string &room) {
    crow::json::rvalue theater_json = crow::json::load(theater);
    std::string theater_name = theater_json["theater"].s();

    crow::json::rvalue room_json = crow::json::load(room);
    std::string room_name = room_json["room"].s();

    std::vector<boosapi::SeatType> seats =
        boosapi.getAvailableSeats(theater_name, room_name);

    crow::json::wvalue response_json;
    for (const boosapi::SeatType &seat : seats) {
      crow::json::wvalue seat_json;
      seat_json["seat"] = boosapi::to_string(seat);
      response_json["seats"] = std::move(seat_json);
    }

    return crow::response(200, response_json);
  });

  CROW_ROUTE(app, "/api/book/<string>/<string>/<string>")
  ([&boosapi](const std::string &theater, const std::string &room,
              const std::string &seat) {
    crow::json::rvalue theater_json = crow::json::load(theater);
    std::string theater_name = theater_json["theater"].s();

    crow::json::rvalue room_json = crow::json::load(room);
    std::string room_name = room_json["room"].s();

    crow::json::rvalue seat_json = crow::json::load(seat);
    try {
      boosapi::SeatType seat_type = boosapi::from_string(seat_json["seat"].s());
      auto booked = boosapi.bookSeat(theater_name, room_name, seat_type);
      if (booked) {
        return crow::response(200, "Seat booked successfully");
      } else {
        return crow::response(400, "Seat already booked");
      }
    } catch (std::exception &e) {
      return crow::response(400, e.what());
    }
  });

  // Start the server on port 18080
  app.port(18080).multithreaded().run();
}
