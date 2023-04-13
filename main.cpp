#include "mbed.h"
#include <cstdio>

Timer timer;
DigitalInOut dht22(PA_0);
int elapsed_time_us;
unsigned long int bits_Data = 0x00000000;
unsigned long int bits_Data2 = 0x00000000;
unsigned int temperature;
unsigned int humidity;

int main()
{
    while (true) {

        dht22.output();      
        dht22.write(0);
        
        ThisThread::sleep_for(1ms);
        dht22.write(1);
        wait_us(20);
        dht22.input();

        while (dht22.read());
        while (!dht22.read());
        while (dht22.read());

        for (int i = 0; i < 32; i++) {
            
            while (!dht22.read());

            timer.start();
            while (dht22.read());
            timer.stop();

            elapsed_time_us = timer.elapsed_time().count();

            bits_Data = bits_Data << 1;

            if (elapsed_time_us > 28) {
                bits_Data += 1;
            }

            timer.reset();
        }
        
        dht22.output();      
        dht22.write(1);

        bits_Data2 = bits_Data & 0xFFFF0000;
        bits_Data = bits_Data & 0x0000FFFF;
        
        if ((bits_Data & 0x8000) == 0x8000) {
            bits_Data *= -1;
        }
        temperature = bits_Data / 10;

        bits_Data2 = bits_Data2 >> 16;
        humidity = bits_Data2 / 10;
        

        bits_Data = 0x00000000;

        ThisThread::sleep_for(1000ms);
    }
}
