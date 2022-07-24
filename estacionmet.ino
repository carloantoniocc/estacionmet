#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// librerias
// https://github.com/adafruit/DHT-sensor-library
// https://github.com/adafruit/Adafruit_Sensor
// https://github.com/fmalpartida/New-LiquidCrystal

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

// Icono de Humededad
byte humchar1[8]={B00000, B00001, B00011, B00011, 
                  B00111, B01111, B01111, B11111,};
byte humchar2[8]={B11111, B11111, B11111, B01111, 
                  B00011, B00000, B00000, B00000,};
byte humchar3[8]={B00000, B10000, B11000, B11000, 
                  B11100, B11110, B11110, B11111,};
byte humchar4[8]={B11111, B11111, B11111, B11110,
                  B11100, B00000, B00000, B00000,};

//Icono de Termometro
byte tempchar1[8]={B00000, B00001, B00010, B00100, //Row 0, Col 2
                  B00100, B00100, B00100, B00111,};
byte tempchar2[8]={B00111, B00111, B00111, B01111, //Row 1, Col 2
                  B11111, B11111, B01111, B00011,};
byte tempchar3[8]={B00000, B10000, B01011, B00100, //ROW 0, Col 3
                  B00111, B00100, B00111, B11100,};
byte tempchar4[8]={B11111, B11100, B11100, B11110, //Row 1, Col 3
                  B11111, B11111, B11110, B11000,};

//Icono de House
byte housechar1[8]={B00000, B00001, B00011, B00011, //Row 0, Col 0
                  B00111, B01111, B01111, B11111,};
byte housechar2[8]={B11111, B11111, B11100, B11100, //Row 1, Col 0
                  B11100, B11100, B11100, B11100,};
byte housechar3[8]={B00000, B10010, B11010, B11010, //ROW 0, Col 1
                  B11110, B11110, B11110, B11111,};
byte housechar4[8]={B11111, B11111, B11111, B10001, //Row 1, Col 1
                    B10001, B10001, B11111, B11111,};



// creamos el objeto lcd
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

void setup()
{
    lcd.setBacklightPin(3,POSITIVE);  // puerto P3 de PCF8574 como positivo
    lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
    lcd.begin(16, 2);     // 16 columnas por 2 lineas para LCD 1602A
    lcd.clear();      // limpia pantalla

    firmware_version();

//    chequeosensor_dht();
    dht.begin();
  
}

void loop()
{
  
    delay(delayMS);
    // Get temperature event and print its value.


    sensors_event_t event;
    
    lcd.clear();
    delay(1000);
    lcd.createChar(1,tempchar1);
    lcd.createChar(2,tempchar2);
    lcd.createChar(3,tempchar3);
    lcd.createChar(4,tempchar4);
    lcd.setCursor(0,0);
    lcd.write(1);
    lcd.setCursor(0,1);
    lcd.write(2);
    lcd.setCursor(1,0);
    lcd.write(3);
    lcd.setCursor(1,1);
    lcd.write(4);
    lcd.setCursor(3,0);
    lcd.print("Temperatura");
    lcd.setCursor(3,1);
    lcd.print(event.temperature);
    lcd.setCursor(9,1);
    lcd.print((char)223);
    lcd.setCursor(10,1);
    lcd.print("C");
    delay(3000);

    dht.temperature().getEvent(&event);
 
    lcd.clear();
    delay(1000);
    lcd.createChar(1,humchar1);
    lcd.createChar(2,humchar2);
    lcd.createChar(3,humchar3);
    lcd.createChar(4,humchar4);
    lcd.setCursor(0,0);
    lcd.write(1);
    lcd.setCursor(0,1);
    lcd.write(2);
    lcd.setCursor(1,0);
    lcd.write(3);
    lcd.setCursor(1,1);
    lcd.write(4);
    lcd.setCursor(3,0);
    lcd.print("Humedad");
    lcd.setCursor(3,1);
    lcd.print(event.relative_humidity);
    delay(3000);

}

void chequeosensor_dht()
{
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);

    lcd.setCursor(0,0);
    lcd.print("SISTEMA DE");
    lcd.setCursor(0,1);
    lcd.print("ARRANQUE");
    delay(3000); 
    lcd.clear(); // Borra pantalla


    lcd.setCursor(0,0);
    lcd.print("Nombre Sensor:");
    lcd.setCursor(0,1);
    lcd.print(sensor.name);
    delay(1000); 
    lcd.clear(); // Borra pantalla
    
    lcd.setCursor(0,0);
    lcd.print("T Maxima :");
    lcd.setCursor(0,1);
    lcd.print(sensor.max_value);
    delay(2000); 
    lcd.clear(); // Borra pantalla

    lcd.setCursor(0,0);
    lcd.print("T Minima :");
    lcd.setCursor(0,1);
    lcd.print(sensor.min_value);
    delay(2000); 
    lcd.clear(); // Borra pantalla

    lcd.setCursor(0,0);
    lcd.print("resolution :");
    lcd.setCursor(0,1);
    lcd.print(sensor.resolution);
    delay(1000); 
    lcd.clear(); // Borra pantalla

    lcd.setCursor(0,0);
    lcd.print("Version :");
    lcd.setCursor(0,1);
    lcd.print(sensor.version);
    delay(1000); 
    lcd.clear(); // Borra pantalla

    lcd.setCursor(0,0);
    lcd.print("sensor_id :");
    lcd.setCursor(0,1);
    lcd.print(sensor.sensor_id);
    delay(1000); 
    lcd.clear(); // Borra pantalla

}

void firmware_version()
{
  
  lcd.clear();
  delay(1000);
  lcd.createChar(1,housechar1);
  lcd.createChar(2,housechar2);
  lcd.createChar(3,housechar3);
  lcd.createChar(4,housechar4);
  lcd.setCursor(0,0);
  lcd.write(1);
  lcd.setCursor(0,1);
  lcd.write(2);
  lcd.setCursor(1,0);
  lcd.write(3);
  lcd.setCursor(1,1);
  lcd.write(4);
  lcd.setCursor(3,0);
  lcd.print("T-LAB TRONIC");
  lcd.setCursor(5,1);
  lcd.print("Ver 1.1");
  delay(5000);
   
}
