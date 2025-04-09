#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// --- Sensor & Pin Definitions ---
#define DHTPIN 4          
#define DHTTYPE DHT22      
DHT dht(DHTPIN, DHTTYPE);

const int mq2Pin = 34;
const int ledPin = 26;
const int buzzerPin = 25;

// --- LCD Setup ---
LiquidCrystal_I2C lcd(0x27, 16, 2);  

// --- WiFi & ThingSpeak ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* thingSpeakServer = "api.thingspeak.com";
String apiKey = "562C98N8KMSDTNNX";


// --- PPM Threshold ---
int MQ2Threshold = 3500;  // You can adjust based on environment


void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  dht.begin();
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  int mqValue = analogRead(mq2Pin);   // Raw ADC value

  float temperature = dht.readTemperature(false);
  float humidity = dht.readHumidity(true);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  lcd.clear();
  if (mqValue > MQ2Threshold) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);
    lcd.setCursor(0, 0);
    lcd.print("  DANGER(SMOKE)");
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    lcd.setCursor(0, 0);
    lcd.print("Air Quality Safe");
  }

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("CH:");
  lcd.print(humidity);
  lcd.print("%");

  Serial.println("---- Sensor Readings ----");
  Serial.println("MQ2 Value  : " + String(mqValue));
  Serial.println("Temperature    : " + String(temperature) + " °C");
  Serial.println("Humidity       : " + String(humidity) + " %");

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String url = String("http://") + thingSpeakServer + "/update?api_key=" + apiKey +
                 "&field1=" + String(mqValue) +
                 "&field2=" + String(temperature) +
                 "&field3=" + String(humidity);

    http.begin(client, url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("Data sent! HTTP GET code: %d\n", httpCode);
    } else {
      Serial.printf("Error in GET request: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(2000); // Delay between updates (ThingSpeak minimum = 15s for free accounts)
}