#ifndef  DHT22_SENSOR_H
#define DHT22_SENSOR_H

#include "mbed.h"

class Dht22Sensor {
public:
    Dht22Sensor(PinName pin, int sample_rate);
    Dht22Sensor(PinName pin);
    int getTemperature();
    int getHumidity();
    void convertData();

private:
    void hostSignal(int bitSend);
    void waitForResponse();
    void sampleData();

    Timer _timer;
    DigitalInOut _dht22_pin;
    int _elapsed_time_us;
    unsigned long int _bits_data;
    unsigned long int _bits_data2;
    int _temperature;
    int _humidity;
    unsigned int _sampleRate;
};

#endif