#include <Wire.h>

char pilih;
int data;

void setup() {

  Wire.begin();
  Serial.begin(9600);

  Serial.println("=== PILIH SENSOR ===");
  Serial.println("1 = Ultrasonic");
  Serial.println("2 = TMP36");
}

void loop() {

  if (Serial.available()) {

    pilih = Serial.read();

    // kirim perintah ke slave
    Wire.beginTransmission(8);
    Wire.write(pilih);
    Wire.endTransmission();

    delay(100);

    // ambil data dari slave
    Wire.requestFrom(8,1);

    if (Wire.available()) {

      data = Wire.read();

      if (pilih == '1') {

        Serial.print("Jarak: ");
        Serial.print(data);
        Serial.println(" cm");
      }

      else if (pilih == '2') {

        Serial.print("Suhu: ");
        Serial.print(data);
        Serial.println(" C");
      }

      Serial.println("Pilih lagi 1/2");
    }
  }
}