#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "config.h"

const char * requestUrl = "https://192.168.1.4:8000?foo=bar";

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFI with IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    if (http.begin(client, requestUrl)) {
      // start connection and send HTTP header
      Serial.printf("GET %s\n", requestUrl);
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        Serial.println(httpCode);

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.println("Error: Unable to connect");
    }
  }

  delay(10000);
}
