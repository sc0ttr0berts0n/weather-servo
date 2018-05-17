#include <WiFi.h>
#include <HTTPClient.h>
#include "Credentials.h"
#include <ESP32_Servo.h>

Servo servo;       // initialize the servo object
int servoPin = 18; // use pin 18

// Init Wifi Vars
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWD;

// Init var to hold weather type string
String weatherType;

void setup()
{

    Serial.begin(115200);
    delay(4000);

    servo.attach(servoPin, 500, 2500); // attach the servo
    delay(10);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");
}

void loop()
{

    if ((WiFi.status() == WL_CONNECTED))
    { //Check the current connection status

        HTTPClient http;

        http.begin("https://weather-servo.herokuapp.com/ds?key=" + String(SECRET_KEY)); //Specify the URL
        int httpCode = http.GET();                                                      //Make the request

        if (httpCode > 0)
        { //Check for the returning code

            String payload = http.getString();
            Serial.println(payload);

            // move servo according to payload
            if (payload == "rainy")
            {
                // Do Rainy Stuff
                servo.write(0);
            }
            else if (payload == "cloudy")
            {
                // Do Cloudy Stuff
                servo.write(90);
            }
            else
            {
                // Assume Clear
                servo.write(180);
            }
        }

        else
        {
            Serial.println(httpCode);
            Serial.println("Error on HTTP request");
        }

        http.end(); //Free the resources
    }

    delay(600000); // wait 10 minutes, check in
}
