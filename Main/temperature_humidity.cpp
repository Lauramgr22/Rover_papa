#include "DHT.h"
#include "display.h"


#define DHTTYPE  DHT11 
#define DHTTYPE1 DHT22  

const int DHTPin1 = 8;     // what digital pin we're connected to
const int DHTPin2 = 9;     // what digital pin we're connected to

DHT dht1(DHTPin1, DHTTYPE);
DHT dht2(DHTPin2, DHTTYPE1);

void start_dht() {
  dht1.begin();
  dht2.begin();
}

float * temp_hum() {
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  Serial.println("==========");
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  Serial.println("==========.");
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

  //if (isnan(h1) || isnan(t1) || isnan(h2) || isnan(t2)) {
    //start_Display("Fallo para leer el sensor DHT");
    //return;
  //}
  static float My_arrayth[] = {t1,h1, t2, h2};
  return My_arrayth;
}