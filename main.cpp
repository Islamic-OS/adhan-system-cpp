#include "./adhan/src/calculation_parameters.c"
#include "./adhan/src/data_components.c"
#include "./adhan/src/include/calculation_method.h"
#include "./adhan/src/include/calculation_parameters.h"
#include "./adhan/src/include/coordinates.h"
#include "./adhan/src/include/data_components.h"
#include "./adhan/src/include/high_latitude_rule.h"
#include "./adhan/src/include/prayer_times.h"
#include "./adhan/src/prayer_times.c"
#include <bits/types/time_t.h>
#include <ctime>
#include <iostream>

using namespace std;

#define BD_COORD {23.7231, 90.4086};

int main(void) {
  coordinates_t coordinates = BD_COORD;
  calculation_method method = KARACHI;
  // high_latitude_rule_t highLatitudeRule = MIDDLE_OF_THE_NIGHT;
  calculation_parameters_t calculation_parameters = getParameters(method);
  madhab_t madhab = HANAFI;
  calculation_parameters.madhab = madhab;
  // calculation_parameters.highLatitudeRule = highLatitudeRule;

  printf("Using calculation high lat: %s\n",
         get_high_latitude_rule_name(calculation_parameters.highLatitudeRule));

  printf("Using coordinates: (lat:%f, long:%f)\n", coordinates.latitude,
         coordinates.longitude);
  printf("Using calculation method: %s\n",
         get_calculation_method_name(calculation_parameters.method));
  printf("Using calculation angles: fajr:%d ishaa:%d - %f\n",
         (int)calculation_parameters.fajrAngle,
         calculation_parameters.ishaInterval, calculation_parameters.ishaAngle);
  printf("Using calculation asr: %s\n",
         get_madhab_name(calculation_parameters.madhab));
  printf("Using calculation high lat: %s\n",
         get_high_latitude_rule_name(calculation_parameters.highLatitudeRule));

  char buffer[80];
  printf("Calculating prayer times...\n");

  time_t now = resolve_time_2(2022, 7, 8);

  // string p;
  // time_t now = time(NULL);
  // p = ctime(&now);
  // time_t start_time = add_hours(now, 6);
  //  time_t now;

  // time(&now);
  //  date_components_t dateComponents = from_time_t(start_time);
  date_components_t dateComponents = from_time_t(now);

  // prayer_times_t prayer_times =
  //     new_prayer_times(&coordinates, &dateComponents,
  //     &calculation_parameters);

  // cout << "Date: " << asctime(localtime(&now)) << endl;
  // cout << "Fajr: " << asctime(localtime(&prayer_times.fajr)) << endl;
  // cout << "Sunrise: " << asctime(localtime(&prayer_times.sunrise)) << endl;
  // cout << "Dhuhr: " << asctime(localtime(&prayer_times.dhuhr)) << endl;
  // cout << "Asr: " << asctime(localtime(&prayer_times.asr)) << endl;
  // cout << "Maghrib: " << asctime(localtime(&prayer_times.maghrib)) << endl;
  // cout << "Isha: " << asctime(localtime(&prayer_times.isha)) << endl;

  // printf("Starting from date: %d/%d/%d\n", dateComponents.day,
  //        dateComponents.month, dateComponents.year);

  printf(
      " Date \t\t Fajr \t\t Sunrise \t Dhuhr \t\t Asr \t\t Maghrib \tIshaa\n");

  // for (int i = 1; i < 31; i++) {

  // time_t ref_date = add_yday(start_time, i);
  time_t ref_date = now;

  dateComponents = from_time_t(ref_date);

  prayer_times_t prayer_times = new_prayer_times_with_tz(
      &coordinates, ref_date, &calculation_parameters, 6);

  strftime(buffer, 80, "%x", localtime(&ref_date));
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
  // }

  return 0;
}
