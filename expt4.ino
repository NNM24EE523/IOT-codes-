#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();
  float fahrenheit = (temperatureC * 9.0 / 5.0) + 32.0;

  // Check for failed readings
  if (isnan(humidity) || isnan(temperatureC)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    Serial.println("Failed to read from DHT22 sensor!");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(humidity, 1);
    lcd.print("%");

    lcd.setCursor(0, 1);
    if (temperatureC > 32.0) {
      lcd.print("Overheat!");
    } else {
      lcd.print("C:");
      lcd.print(temperatureC, 1);
      lcd.print((char)223); // Degree symbol
      lcd.print(" F:");
      lcd.print(fahrenheit, 1);
    }
  }

  delay(2000); // Wait 2 seconds before next reading
}
