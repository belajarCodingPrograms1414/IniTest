#include <Wire.h>

#define SIG 7

char perintah;
int data;

void setup() {

  Wire.begin(8);

  Wire.onReceive(terima);
  Wire.onRequest(kirim);
}

void loop() {

}

// =====================
// TERIMA PERINTAH MASTER
// =====================
void terima(int x) {

  perintah = Wire.read();

  // ULTRASONIC
  if (perintah == '1') {

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
  else if (perintah == '2') {

    int nilai = analogRead(A0);

    float volt = nilai * 5.0 / 1023.0;

    data = (volt - 0.5) * 100;
  }
}

// =====================
// KIRIM DATA KE MASTER
// =====================
void kirim() {

  Wire.write(data);
}