#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C

// bibliotecas 
// https://altronics.cl/sensor-temperatura-humedad-dht22
// https://github.com/adafruit/DHT-sensor-library/blob/master/examples/DHT_Unified_Sensor/DHT_Unified_Sensor.ino
// https://github.com/adafruit/Adafruit_Sensor


#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


// creamos el objeto lcd
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

void setup()
{
    lcd.setBacklightPin(3,POSITIVE);  // puerto P3 de PCF8574 como positivo
    lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
    lcd.begin(16, 2);     // 16 columnas por 2 lineas para LCD 1602A
    lcd.clear();      // limpia pantalla

    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    
}

void loop()
{
    // lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
    // lcd.print("Estacion");  
    // lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
    // lcd.print("Meteorologica");   // 

   
    delay(delayMS);
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    
    lcd.setCursor(0, 0); 
    lcd.print("T:");  
    lcd.print(event.temperature);

    dht.humidity().getEvent(&event);
    lcd.print("  H:");  
    lcd.print(event.relative_humidity);

    
}
