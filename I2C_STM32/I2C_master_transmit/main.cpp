#include "mbed.h"

const int address = 0x8;      // 7 bit I2C address

I2C i2c(PB_9 , PB_8);     // SDA, SCL

// main() runs in its own thread in the OS
int main()
{
    char payload[] = "01234";    // Limited to 32 bytes
    const size_t payloadSize = sizeof(payload) - 1; // -1 to not send the null character


    DigitalOut led(LED1);   // Set LED1 to output, used for trouble shooting

    while (true) {
        i2c.write((address << 1), payload, payloadSize);  // LSB set to 0 to indicate write (Mbed used 8 bit address)
        led = !led;
        ThisThread::sleep_for(5s);
    }
}

