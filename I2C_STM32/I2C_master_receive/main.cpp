#include "mbed.h"

const int address = 0x8;      // 7 bit I2C address

I2C i2c(PB_9 , PB_8);     // SDA, SCL

// main() runs in its own thread in the OS
int main()
{
    char command_byte = 0x69;
    char data[5];

    DigitalOut led(LED1);   // Set LED1 to output, used for trouble shooting
    while (true) {
        i2c.write((address << 1), &command_byte, 1);  // LSB set to 0 to indicate write (Mbed used 8 bit address)

        ThisThread::sleep_for(1ms);

        i2c.read((address << 1) | 0x1, data, 4);  // LSB set to 1 to indicate read (Mbed used 8 bit address)
        printf("Data Received: ");
        printf("%s\n", data);

        led = !led;

        ThisThread::sleep_for(5s);
    }
}

