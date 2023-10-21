#include <Wire.h>

const byte bufferSize = 32;
volatile byte receivedBuffer[bufferSize];
volatile bool dataReceived = false;
volatile byte dataSize = false;

// this is to avoid compiler warning about memcpy and volatile
void * volatileMemcpy (void *dest, const volatile void *src, size_t len) {
  uint8_t *d = (uint8_t *) dest;
  const volatile uint8_t *s = (const volatile uint8_t *) src;
  while (len--) *d++ = *s++;
  return dest;
}

void useData() {
  static byte receivedBufferCopy[bufferSize];
  byte dataSizeCopy;

  // critial section to copy the data before it's used in case a new packet comes in
  noInterrupts();
  dataSizeCopy = dataSize;
  volatileMemcpy(receivedBufferCopy, receivedBuffer, dataSize); // the standard memcpy (https://www.cplusplus.com/reference/cstring/memcpy/) might not be compatible with volatile
  dataReceived = false;
  interrupts();
  // end of critical section, we are working on a clean copy

  // dump the data
  Serial.print(F("New data: "));
  for (byte i = 0; i < dataSizeCopy; i++) Serial.write(receivedBufferCopy[i]);
  Serial.println();
}

void wireCallback(int howMany) {
  dataSize = min(bufferSize, howMany);
  dataReceived = true;
  // empty the buffer and store what fits
  for (int i = 0; i < howMany; i++)
    if (i < bufferSize) receivedBuffer[i] = Wire.read();
}

void setup() {
  Serial.begin(9600);         // start serial for output
  Serial.println(F("\n--- WIRE SLAVE ---"));
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(wireCallback); // register event
}

void loop() {
  if (dataReceived) useData();
}