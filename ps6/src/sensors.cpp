#include "config.h"
#include "sensors.h"
#include "DHT.h"

DHT dht(DHT_PIN, DHT_TYPE);

void sensors_init(){
    dht.begin();
}


float get_temperature(){
    float temperature = dht.readTemperature();
    Serial.println(temperature);

    return temperature;
}


int get_humidity(){
    int humidity = dht.readHumidity();
    Serial.println(humidity);

    return humidity;
}