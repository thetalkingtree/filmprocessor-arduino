#include "Film.h"
#include "math.h"
#include "FomadonDeveloper.h"
#include "FomadonPDeveloper.h"
#include "FomadonLQNDeveloper.h"

FomadonDeveloper::FomadonDeveloper() {
}

FomadonDeveloper::FomadonDeveloper(Film *film) {  // Constructor with parameters
  _film = *film;
}

FomadonDeveloper::FomadonDeveloper(Film *film, float temperature) {  // Constructor with parameters
  _film = *film;
  _temperature = temperature;
}

FomadonDeveloper *FomadonDeveloper::Create(int type) {
  if (type == 1) {
    return new FomadonPDeveloper();
  }

  if (type == 2) {
    return new FomadonLQNDeveloper();
  }

  else
    return NULL;
}

/*
* Interpolate the dev time for a unlisted temperature in the film, or developer technical sheets
*/
void FomadonDeveloper::InterpolateCorrection(float temperature) {
  //TODO: Implememt validation handling
  if ((_temperature < 16) || (_temperature > 26)) {
    // throw ("Temperature out of range. Min 16C Max 26C");
  }
  float retval = -0.0000260417 * pow(temperature, 5) + 0.00260417 * pow(temperature, 4) - 0.103646 * pow(temperature, 3) + 2.05833 * pow(temperature, 2) - 20.5475 * temperature + 84.45;
  float roundNearest = roundf(retval * 100);  // x 100 for two decimal place
  roundNearest = roundNearest / 100;
  devTimeMultiplicator = roundNearest;
}

Film FomadonDeveloper::getFilm() {
  return _film;
}
void FomadonDeveloper::setFilm(Film *film) {
  _film = *film;
}

float FomadonDeveloper::getTemperature() {
  return _temperature;
}
void FomadonDeveloper::setTemperature(float temperature) {
  _temperature = temperature;
}
long FomadonDeveloper::getAgitationInitialSeconds() {
  return agitationInitialSeconds;
}
long FomadonDeveloper::getAgitationSeconds() {
  return agitationSeconds;
}
int FomadonDeveloper::getAgitationIntervalSeconds() {
  return agitationIntervalSeconds;
}
float FomadonDeveloper::getDevTimeMultiplicator() {
  InterpolateCorrection(_temperature);
  return devTimeMultiplicator;
}

void FomadonDeveloper::setTimeCompensationPercentage(int timeCompensationPercentage) {
  FomadonDeveloper::timeCompensationPercentage = timeCompensationPercentage;
}
