#include "mbed.h"
#include "Dht22Sensor.h"

Dht22Sensor::Dht22Sensor(PinName pin, int sample_rate) : _dht22_pin(pin), _sampleRate(sample_rate) {
    _bits_data = 0x00000000;
    _bits_data2 = 0x00000000;
    _elapsed_time_us = 0;
    _temperature = 0;
    _humidity = 0;
}

Dht22Sensor::Dht22Sensor(PinName pin) : _dht22_pin(pin){
    _bits_data = 0x00000000;
    _bits_data2 = 0x00000000;
    _elapsed_time_us = 0;
    _temperature = 0;
    _humidity = 0;
    _sampleRate = 1000;
}

void Dht22Sensor::hostSignal(int bitSend){
    _dht22_pin.output();      
    _dht22_pin.write(bitSend);

    if (bitSend == 0) {
        ThisThread::sleep_for(1ms);
        _dht22_pin.write(1);
        wait_us(20);
        _dht22_pin.input();
    }
}

void Dht22Sensor::waitForResponse(){
    while (_dht22_pin.read());
    while (!_dht22_pin.read());
    while (_dht22_pin.read());
}

void Dht22Sensor::sampleData(){

    Dht22Sensor::hostSignal(0);
    Dht22Sensor::waitForResponse();

    for (int i = 0; i < 32; i++) {
            
        while (!_dht22_pin.read());

        _timer.start();
        while (_dht22_pin.read());
        _timer.stop();

        _elapsed_time_us = _timer.elapsed_time().count();

        _bits_data = _bits_data << 1;

        if (_elapsed_time_us > 28) {
            _bits_data += 1;
        }

        _timer.reset();
    }
    Dht22Sensor::hostSignal(1);
}

void Dht22Sensor::convertData(){
    Dht22Sensor::sampleData();

    _bits_data2 = _bits_data & 0xFFFF0000;
    _bits_data = _bits_data & 0x0000FFFF;
    
    if ((_bits_data & 0x8000) == 0x8000) {
        _bits_data *= -1;
    }
    _temperature = _bits_data / 10;

    _bits_data2 = _bits_data2 >> 16;
    _humidity = _bits_data2 / 10;
    
    _bits_data = 0x00000000;

    ThisThread::sleep_for(chrono::milliseconds(_sampleRate));
}

int Dht22Sensor::getTemperature(){
    return _temperature;
}

int Dht22Sensor::getHumidity(){
    return _humidity;
}