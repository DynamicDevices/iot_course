#include <TinyPICO.h>
#include "EspMQTTClient.h"

EspMQTTClient client(
  "guest",
  "",
  "mqtt.cheerlights.com",  // MQTT Broker server ip
  "TestClient"      // Client name that uniquely identify your device
);

// Initialise the TinyPICO library
TinyPICO tp = TinyPICO();

//
// This gets called when the MQTT client makes a connection to the broker
//
void onConnectionEstablished() {

  Serial.println("Connected to broker");

  // Subscribe to topic "cheerlightsRGB"
  
  client.subscribe("cheerlightsRGB", [] (const String &payload)  {

    // We expect a payload of the format "#RRGGBB" where RR is a hexadecimal value for red
    // between 0 and 255, GG for green and BB for blue.
    Serial.println("Received: " + payload);

    // Drop the first "#" and convert our hex string to a 32-bit value
    const char *cPayload = payload.c_str();
    unsigned int colour = strtol(&cPayload[1], NULL, 16);

    // Pass the RGB colour value to the DotStar RGB LED controller code
    tp.DotStar_SetPixelColor( colour );
  });
}

void setup()
{
  // Used for debug output only
  Serial.begin(115200);

  // Uncomment this to see extra debugging messages
  //client.enableDebuggingMessages(true);
}

void loop()
{
  // Do any MQTT handling that needs doing
  client.loop();  
}
