#ifndef  DHT22_SENSOR_H
#define DHT22_SENSOR_H

#include "mbed.h"

class Dht22Sensor {
public:
    Dht22Sensor(PinName pin, int sample_rate);
    Dht22Sensor(PinName pin);
    int getTemperature();
    int getHumidity();

private:
    void hostSignal(int bitSend);
    void waitForResponse();
    void sampleData();
    void maskData();
    void convertTemperature();
    void convertHumidity();

    Timer _timer;
    DigitalInOut _dht22_pin;
    int _elapsed_time_us;
    unsigned long int _bits_data;
    unsigned long int _bits_data2;
    unsigned int _temperature;
    unsigned int _humidity;
};

#endif