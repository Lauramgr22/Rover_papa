#include "Arduino.h"
#include "HardwareSerial.h"
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "WString.h"
// Configuración de pines para la comunicación con el módulo GPS


void start_gps() {
  Serial.println("+");
}

double *get_gps(TinyGPSPlus gps, SoftwareSerial gpsSerial){
   // Objeto para parsear los datos GPS
  
    while(gpsSerial.available()) {
      Serial.println(".");
    char c = gpsSerial.read();
    // Alimentar los caracteres al objeto TinyGPS
    if (gps.encode(c)) {
      Serial.println("***");
      if (gps.location.isValid()) {
        // Obtener los valores de latitud y longitud
        double latitude = gps.location.lat();
        double longitude = gps.location.lng();
        static double My_array[] = {latitude,longitude};
        Serial.println("gps tomado");
        return My_array;
      }
    }
  }
  Serial.println("Fallo gps :(");
  return;
}

