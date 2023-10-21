#include <Wire.h>

void setup() {
  Wire.begin();                 // join i2c bus as master
}

void loop() {
  Wire.beginTransmission(0x8);    // identify the target device (address 8)
  Wire.write('v');
  Wire.endTransmission();       // send the payload over

  delay(5000);                  // wait a bit before sending it again
}
