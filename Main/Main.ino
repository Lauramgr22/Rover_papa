#include "Arduino.h"
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>  // librería para el LCD por I2C
#include <RTClib.h>             // librería para el RTCLib
#include <TinyGPS++.h>
#include "WString.h"
#include "record.h"
#include "display.h"
#include "brigthness.h"
#include "temperature_humidity.h"
#include "clock.h"

#define GPS_TX_PIN 2
#define GPS_RX_PIN 3

#define DHTTYPE DHT11   // DHT 21 (AM2301)
#define DHTTYPE1 DHT22   // DHT 22  (AM2302), AM2321

const int DHTPin1 = 8;     // what digital pin we're connected to
const int DHTPin2 = 9;     // what digital pin we're connected to

SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); // RX, TX
TinyGPSPlus gps;

double *get_gps(){
   // Objeto para parsear los datos GPS
    while(gpsSerial.available()) {
      Serial.println("***");
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
  Serial.println("GPS no disponible");
  return 0;
}


void setup() {
  gpsSerial.begin(9600);
  Serial.begin(9600); // Iniciar comunicación serie para monitoreo
  Serial.println("0 setup");
  start_lux();
  start_dht();
  start_clock();
  Serial.println("E setup");

}

void loop() {
    //----Llamado de las funciones----
    delay(1000);
    Serial.println(".......");
    double * array = get_gps();
    uint16_t luminosidad = lux();
    /*float * sensor_dht= temp_hum();
    String fecha = day();
    //if( array) { 
      Serial.println("TRUE");     
      start_Display("Guardando datos");
      write_record(5.666,-73.555,luminosidad,sensor_dht[0],sensor_dht[1],sensor_dht[2],sensor_dht[3], fecha);
      delay(1000);
    //} else{
      //start_Display("No se guardaron datos :(");
    //}  
    */ 
}