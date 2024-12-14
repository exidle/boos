#include "boosapi.h"
#include <crow.h>
#include <string>

int main() {
  boosapi::BoosAPI boosapi;
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")
  ([]() {
    return "Booking API:"
           "\n/api/movies GET;"
           "\n/api/theaters POST param: movie;"
           "\n/api/rooms POST param: theater, param: movie;"
           "\n/api/seats GET param: theater, param: room;"
           "\n/api/book GET param: theater, param: room, param: seat;";
  });

  CROW_ROUTE(app, "/api/movies")
  ([&boosapi]() {
    std::vector<boosapi::MovieItem> movies = boosapi.getAllMovies();
    std::cout << "There are " << movies.size() << " movies" << std::endl;

    crow::json::wvalue response_json;
    auto list = crow::json::wvalue::list();
    for (const boosapi::MovieItem &movie : movies) {
      crow::json::wvalue movie_json;
      movie_json["title"] = movie.title;
      movie_json["year"] = movie.year;
      list.push_back(movie_json);
    }
    response_json["movies"] = std::move(list);

    return crow::response(200, response_json);
  });

  CROW_ROUTE(app, "/api/theaters")
      .methods("POST"_method)([&boosapi](const crow::request &req) {
        auto movie_json = crow::json::load(req.body);
        if (!movie_json) {
          return crow::response(400);
        }

        std::string movie_title = movie_json["title"].s();
        int movie_year = movie_json["year"].i();

        std::cout << "Movie title: " << movie_title << std::endl;
        std::cout << "Movie year: " << movie_year << std::endl;
        std::cout << to_string(boosapi::MovieItem{movie_title, movie_year})
                  << std::endl;

        std::vector<std::string> theaters =
            boosapi.getTheaters(boosapi::MovieItem{movie_title, movie_year});

        std::cout << "There are " << theaters.size() << " theaters"
                  << std::endl;

        crow::json::wvalue response_json;
        auto list = crow::json::wvalue::list();
        for (const std::string &theater : theaters) {
          crow::json::wvalue theater_json;
          theater_json["theater"] = theater;
          list.push_back(theater_json);
        }
        response_json["theaters"] = std::move(list);

        return crow::response(response_json);
      });

  CROW_ROUTE(app, "/api/rooms")
      .methods("POST"_method)([&boosapi](const crow::request &req) {
        auto data_json = crow::json::load(req.body);
        if (!data_json) {
          return crow::response(400);
        }

        const std::string theater_name = data_json["theater"].s();

        auto movie_json = data_json["movie"];
        if (!movie_json) {
          return crow::response(400);
        }

        std::string movie_title = movie_json["title"].s();
        int movie_year = movie_json["year"].i();

        std::cout << "Theater name: " << theater_name << std::endl;
        std::cout << "Movie title: " << movie_title << std::endl;
        std::cout << "Movie year: " << movie_year << std::endl;

        std::vector<std::string> rooms = boosapi.getRooms(
            theater_name, boosapi::MovieItem{movie_title, movie_year});

        crow::json::wvalue response_json;
        auto list = crow::json::wvalue::list();
        for (const std::string &room : rooms) {
          crow::json::wvalue room_json;
          room_json["room"] = room;
          list.push_back(room_json);
        }

        response_json["rooms"] = std::move(list);
        return crow::response(200, response_json);
      });

  CROW_ROUTE(app, "/api/seats")
  ([&boosapi](const crow::request &req) {
    auto const theater_name = req.url_params.get("theater");
    auto const room_name = req.url_params.get("room");
    std::cout << "Theater name: " << theater_name << std::endl;
    std::cout << "Room name: " << room_name << std::endl;
    std::vector<boosapi::SeatType> seats =
        boosapi.getAvailableSeats(theater_name, room_name);

    crow::json::wvalue response_json;
    auto list = crow::json::wvalue::list();
    for (const boosapi::SeatType &seat : seats) {
      crow::json::wvalue seat_json;
      seat_json["seat"] = boosapi::to_string(seat);
      list.push_back(seat_json);
    }

    response_json["seats"] = std::move(list);
    return crow::response(200, response_json);
  });

  CROW_ROUTE(app, "/api/book")
  ([&boosapi](const crow::request &req) {
    auto const theater_name = req.url_params.get("theater");
    auto const room_name = req.url_params.get("room");
    auto const seat = req.url_params.get("seat");

    std::cout << "Theater name: " << theater_name << std::endl;
    std::cout << "Room name: " << room_name << std::endl;
    std::cout << "Seat: " << seat << std::endl;

    try {
      boosapi::SeatType seat_type = boosapi::from_string(seat);
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
