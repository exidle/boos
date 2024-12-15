# boos
Booking service made in Crow using Conan packet manager boosted with C++ 17.

## Building
To build ensure that conan2 is installed. To install it perform pip install conan.
More details about installation are at [documentation](https://docs.conan.io/2/installation.html).

Ensure that you have a working profile, or run:
conan profile detect --force

For building service execute:
conan install . --build=missing

And then run:
conan create . --build=missing

I did't verify on Windows, perhaps shall work as it is.

## API

Service provides a following REST API:

GET /api/movies
Returns list of all available movies

GET /api/theaters/<string movie>
Returns list of theaters where the given movie is available

GET /api/rooms/<string theater name>/<string movie>
Returns list of rooms in selected theater where give movie is available

GET /api/seats/<string theater name>/<string room name>
Returns available seats in given theater within given room

GET /api/book/<string theater name>/<string room name>/<string seat>
Book in a given theater within given room a given seat.
Returns 200 on success. Returns 400 in case of error.



