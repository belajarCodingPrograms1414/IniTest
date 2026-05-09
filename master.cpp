#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

char pilih;
int data;

void setup() {

  Wire.begin();
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  Serial.println("1=Ultrasonic");
  Serial.println("2=TMP36");

  lcd.setCursor(0,0);
  lcd.print("Pilih Sensor");
}

void loop() {

  if (Serial.available()) {

    pilih = Serial.read();

    // kirim perintah ke slave
    Wire.beginTransmission(8);
    Wire.write(pilih);
    Wire.endTransmission();

    delay(100);

    // minta data
    Wire.requestFrom(8,1);

    if (Wire.available()) {

      data = Wire.read();

      lcd.clear();

      if (pilih == '1') {

        Serial.print("Jarak: ");
        Serial.println(data);

        lcd.setCursor(0,0);
        lcd.print("Ultrasonic");

        lcd.setCursor(0,1);
        lcd.print("Jarak:");
        lcd.print(data);
        lcd.print("cm");
      }

      else if (pilih == '2') {

        Serial.print("Suhu: ");
        Serial.println(data);

        lcd.setCursor(0,0);
        lcd.print("TMP36");

        lcd.setCursor(0,1);
        lcd.print("Suhu:");
        lcd.print(data);
        lcd.print("C");
      }

      Serial.println("Pilih lagi 1/2");
    }
  }
}