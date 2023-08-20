#include "Arduino.h"
#include <SoftwareSerial.h>
#include <Wire.h>               // librería para comunicaciones con el pc
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>  // librería para el LCD por I2C
#include <RTClib.h>             // librería para el RTCLib
#include <TinyGPS++.h>
#include "WString.h"
#include "record.h"
#include "display.h"
#include "brigthness.h"
#include "temperature_humidity.h"


#define GPS_TX_PIN 2
#define GPS_RX_PIN 3

SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); // RX, TX
TinyGPSPlus gps;

double *get_gps(){
   // Objeto para parsear los datos GPS
    while(gpsSerial.available()) {
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
  return 0;
}


void setup() {
  gpsSerial.begin(9600);
  Serial.begin(9600); // Iniciar comunicación serie para monitoreo
  void start_lux();
  void start_dht();
}

void loop() {
    //----Llamado de las funciones----
    double * array = get_gps();
    uint16_t luminosidad= lux();
    float * sensor_dht= temp_hum();
    if( array) {
      Serial.println("TRUE");     
      start_Display("Guardando datos");
      write_record(array[0],array[1],luminosidad,sensor_dht[0],sensor_dht[1],sensor_dht[2],sensor_dht[3]);
      delay(1000);
    } else{
      start_Display("No se guardaron datos");
    }   
}