#include "HardwareSerial.h"
#include "WString.h"
#include "Arduino.h"
#include <SPI.h>    // incluye libreria interfaz SPI
#include <SD.h>     // incluye libreria para tarjetas SD
#include "display.h"
#include "clock.h"

#define SSpin 10    // Slave Select en pin digital 10

File archivo;     // objeto archivo del tipo File

void writeSD(String line) {
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD
    start_Display("fallo en inicializacion !");
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  
  archivo = SD.open("prueba.txt", FILE_WRITE);  // apertura para lectura/escritura de archivo prueba.txt

  if (archivo) {
    archivo.println(line);  // escritura de una linea de texto en archivo
    archivo.close();        // cierre del archivo
    start_Display("escritura correcta");
    Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie
  } else {
    Serial.println("error en apertura de prueba.txt");  // texto de falla en apertura de archivo
    start_Display("error en apertura de prueba.txt");
  }
}
//----------------------------------------------------------------------------
String doubleToString(double value, int decimalPlaces) {
  char buffer[12];  // Ajusta el tamaño según tus necesidades
  buffer[0] = '\0';

  dtostrf(value, 11, decimalPlaces, buffer);
  
  return String(buffer);
}
//-------------------------------------------------------------------------------
String uint16ToString(uint16_t value) {
  char buffer[6]; // Suficiente para valores hasta 65535
  
  // Utiliza la función snprintf para convertir el valor en una cadena
  snprintf(buffer, sizeof(buffer), "%u", value);
  
  return String(buffer);
}
//------------------------------------------------------------------------------
String floatToString(float number, int decimalPlaces){
  char buffer[20]; // Suficientemente grande para contener el número como cadena
  dtostrf(number, 0, decimalPlaces, buffer); // Convierte el float a una cadena con el número deseado de decimales
  return String(buffer); // Convierte el buffer en un objeto String
}
//--------------------------------------------------------------------------------
void write_record(double latitud, double longitud,uint16_t lum, float temp1, float hum1, float temp2, float hum2, String fecha){
  writeSD(doubleToString(latitud, 8) + "," + doubleToString(longitud, 8)+","+uint16ToString(lum)+","+ floatToString(temp1, 2)+","+ floatToString(hum1, 2)+","+ floatToString(temp2, 2)+","+ floatToString(hum2, 2)+","+fecha);

}