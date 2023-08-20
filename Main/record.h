#include "Arduino.h"
#include "WString.h"
String doubleToString(double value, int decimalPlaces);
String uint16ToString(uint16_t value);
void write_record(double latitud, double longitud, uint16_t lum);