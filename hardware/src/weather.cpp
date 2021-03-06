#include <HardwareSerial.h>

#include "thermometer.h"
#include "wifi.h"
#include "messages.h"

// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;


void setup()
{
    // initialize the digital pin as an output.
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    Serial.begin(115200);

    Serial1.begin(115200);


    delay(5000);
    Serial.println("starting");
    while(Serial1.available()) {
        Serial.write(Serial1.read());
    }
    Serial.println("Old data flushed. Starting");
    //wifi_reset();

    setup_wifi();
    setup_thermometer();
    digitalWrite(ledPin, HIGH);
}

void loop()
{
    auto temperature = read_thermometer();

    char message[64];
    sensor_message(message, 64, "temperature", temperature * 100);
    send_data(message);

    delay(1000);

    Serial.println("Loop");

    //send_data("yoloswag");
}
