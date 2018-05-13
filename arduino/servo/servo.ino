#include <WiFi.h>
#include <HTTPClient.h>
#include "Credentials.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWD;

void setup()
{

    Serial.begin(115200);
    delay(4000);
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

        http.begin("https://api.darksky.net/forecast/2b11c9e517f8526db8af5ba89d7a6e89/37.8267,-122.4233&exclude=currently,minutely,daily,alerts,flags"); //Specify the URL
        int httpCode = http.GET();                                                                                                                       //Make the request

        if (httpCode > 0)
        { //Check for the returning code

            String payload = http.getString();
            Serial.println(httpCode);
            Serial.println(payload);
        }

        else
        {
            Serial.println("Error on HTTP request");
        }

        http.end(); //Free the resources
    }

    delay(1000000000);
}