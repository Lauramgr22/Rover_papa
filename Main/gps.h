#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "WString.h"
void start_gps();
double* get_gps(TinyGPSPlus gps, SoftwareSerial gpsSerial);
