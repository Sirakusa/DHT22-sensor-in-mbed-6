#include "mbed.h"
#include <cstdio>
#include "Dht22Sensor.h"

Dht22Sensor dht(PA_0); // take samples every second
// Dht22Sensor dht(PA_0, 100); take samples every 100 milli seconds

int main()
{
    while (true) {
        dht.convertData();
        printf("temperature = %d °C and relative humidity = %d %%\n",dht.getTemperature(),dht.getHumidity());
    }
}
