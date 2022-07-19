#include "./adhan/src/calculation_parameters.c"
#include "./adhan/src/data_components.c"
#include "./adhan/src/include/calculation_method.h"
#include "./adhan/src/include/calculation_parameters.h"
#include "./adhan/src/include/coordinates.h"
#include "./adhan/src/include/data_components.h"
#include "./adhan/src/include/high_latitude_rule.h"
#include "./adhan/src/include/prayer_times.h"
#include "./adhan/src/prayer_times.c"
#include "./build/_deps/tomleleven-src/toml.hpp"
#include <bits/types/time_t.h>
#include <ctime>
#include <iostream>

using namespace std;

/*
Things needed to receive from the user

1. Latitude and Longitude
2. Timezone increment or decrement (eg. 6, -3)
3. Method (Karachi, Gulf, etc.)
4. Madhab (Hanafi, Shafi, etc.)

*/

int main(void) {
  auto data = toml::parse("../testing/adhancfg.toml");

#define COORDS                                                                 \
  {toml::find<float>(data, "LATITUDE"), toml::find<float>(data, "LONGITUDE")};

  coordinates_t coordinates = COORDS;

  calculation_method method;

  string methodFromSrc = toml::find<string>(data, "METHOD");

  if (methodFromSrc == "Karachi") {
    method = KARACHI;
  } else if (methodFromSrc == "MWL") {
    method = MUSLIM_WORLD_LEAGUE;
  } else if (methodFromSrc == "Egyptian") {
    method = EGYPTIAN;
  } else if (methodFromSrc == "Makkah") {
    method = UMM_AL_QURA;
  } else if (methodFromSrc == "Gulf") {
    method = GULF;
  } else if (methodFromSrc == "Moonsighting") {
    method = MOON_SIGHTING_COMMITTEE;
  } else if (methodFromSrc == "ISNA") {
    method = NORTH_AMERICA;
  } else if (methodFromSrc == "Kuwait") {
    method = KUWAIT;
  } else if (methodFromSrc == "Qatar") {
    method = QATAR;
  } else {
    method = OTHER;
  }

  calculation_parameters_t calculation_parameters = getParameters(method);

  madhab_t madhab;
  string madhabFromSrc = toml::find<string>(data, "MADHAB");

  if (madhabFromSrc == "Hanafi") {
    madhab = HANAFI;
  } else {
    madhab = SHAFI;
  }

  calculation_parameters.madhab = madhab;

  char buffer[80];

  // time_t now = resolve_time_2(2022, 7, 11);
  time_t now = time(NULL);
  struct tm *current_time;

  current_time = localtime(&now);

  printf("Day of the month = %d\n", current_time->tm_mday);
  printf("Month of this year = %d\n", (current_time->tm_mon + 1));
  printf("Current year = %d\n", (current_time->tm_year + 1900));

  time_t date =
      resolve_time_2((current_time->tm_year + 1900), (current_time->tm_mon + 1),
                     current_time->tm_mday);
  date_components_t dateComponents = from_time_t(date);

  printf(
      " Date \t\t Fajr \t\t Sunrise \t Dhuhr \t\t Asr \t\t Maghrib\tIshaa\n");

  // time_t ref_date = now;

  // dateComponents = from_time_t(ref_date);

  prayer_times_t prayer_times =
      new_prayer_times_with_tz(&coordinates, date, &calculation_parameters,
                               toml::find<int>(data, "TIMEZONE"));

  strftime(buffer, 80, "%x", localtime(&date));
  printf(" %s\t", buffer);

  strftime(buffer, 80, "%I:%M%p", localtime(&prayer_times.fajr));
  printf(" %s\t", buffer);

  strftime(buffer, 80, "%I:%M%p", localtime(&prayer_times.sunrise));
  printf(" %s\t", buffer);

  strftime(buffer, 80, "%I:%M%p", localtime(&prayer_times.dhuhr));
  printf(" %s\t", buffer);

  strftime(buffer, 80, "%I:%M%p", localtime(&prayer_times.asr));
  printf(" %s\t", buffer);

  strftime(buffer, 80, "%I:%M%p", localtime(&prayer_times.maghrib));
  printf(" %s\t", buffer);

  strftime(buffer, 80, "%I:%M%p", localtime(&prayer_times.isha));
  printf(" %s\n", buffer);

  return 0;
}
