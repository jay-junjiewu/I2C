#include<Wire.h>

char buffer[33];

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  Wire.beginTransmission(0x8);
  Wire.write(0x69);                       //command byte
  byte busStatus = Wire.endTransmission();
  
  if(busStatus != 0)
  {
      Serial.print("I2C Bus communication problem...!");
      while(1);    //wait forever
  }
  
  Wire.requestFrom(0x8, 2);   //requesting n-byte data from Slave

  int i = 0;
  while (Wire.available()) {
    buffer[i] = Wire.read();
    i++;
  }
  buffer[i] = '\0';  //null character
  
  Serial.println(buffer);
  
  delay(5000);
}
