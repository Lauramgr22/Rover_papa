#include "Arduino.h"
#include "WString.h"
String doubleToString(double value, int decimalPlaces);
String uint16ToString(uint16_t value);
String floatToString(float number, int decimalPlaces);
void write_record(double latitud, double longitud, uint16_t lum, float temp1, float hum1, float temp2, float hum2);