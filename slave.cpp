#include <Wire.h>

#define SIG 7

char pilih;
int data;

void setup() {

  Wire.begin(8);

  Wire.onReceive(terimaData);
  Wire.onRequest(kirimData);
}

void loop() {

}

void terimaData(int x) {

  pilih = Wire.read();

  // Ultrasonic
  if (pilih == '1') {

    pinMode(SIG, OUTPUT);

    digitalWrite(SIG, LOW);
    delayMicroseconds(2);

    digitalWrite(SIG, HIGH);
    delayMicroseconds(5);

    digitalWrite(SIG, LOW);

    pinMode(SIG, INPUT);

    long durasi = pulseIn(SIG, HIGH);

    data = durasi * 0.034 / 2;
  }

  // TMP36
  else if (pilih == '2') {

    int nilai = analogRead(A0);

    float volt = nilai * 5.0 / 1023.0;

    data = (volt - 0.5) * 100;
  }
}

void kirimData() {

  Wire.write(data);
}