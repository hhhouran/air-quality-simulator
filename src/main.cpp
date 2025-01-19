#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// The values below are initializing the connectors from the lcd to the board
// We then instiantiate the LiquidCrystal object with the values
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
float temperature = 0;
float humidity = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht = DHT(A0, DHT11);

void setup()
{
  // Begin method is configuring our rows/columns of our lcd
  humidity = dht.readHumidity(true);
  temperature = dht.readTemperature(true, false);
  lcd.begin(16, 2);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temperature) + "F ");
  lcd.autoscroll();
  delay(2000);
  lcd.print("Humidity: " + String(humidity) + "% ");
}
