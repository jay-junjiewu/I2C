#include<Wire.h>

void setup()
{
  Serial.begin(9600);
  Wire.begin(0x8);
}

void loop()
{
  Wire.onRequest(requestEvent);

  Wire.onReceive(receiveEvent);

  delay(100);
}

void receiveEvent()
{
  // Code that runs when master transmits data
}

void requestEvent()
{
  // Code that runs when master requests data
  if(Wire.read() == 0x69)
  {
      Wire.write("nano");
  }
}