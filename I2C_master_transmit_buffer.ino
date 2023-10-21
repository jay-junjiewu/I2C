#include <Wire.h>

uint8_t payload[] = "0123456789";
const size_t payloadSize = sizeof payload - 1 ; // -1 to not send the trailing null

void setup() {
  Serial.begin(9600);         // start serial for output
  Serial.println(F("\n--- WIRE MASTER ---"));
  Wire.begin();                 // join i2c bus as master
  Serial.println(F("Enter any key to get started"));
  while (Serial.read() == -1); // wait for user input
}

void loop() {
  Wire.beginTransmission(8);    // identify the target device (address 8)

  // build the payload (multiple write possible up to 32 bytes)
  Wire.write(payload, payloadSize);
  Wire.write(payload, payloadSize);
  Wire.write(payload, payloadSize);
  Wire.write(payload, payloadSize);  // this one will get truncated and only "01" will be sent as the wire buffer is 32 bytes deep
  Serial.println();
  Wire.endTransmission();       // send the payload over

  delay(5000);                  // wait a bit before sending it again
}
