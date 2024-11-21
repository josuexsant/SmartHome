#include <Arduino.h>
#include "bathroom.h"
#include "conexion.h"
#include "bedroom.h"
#include "kitchen.h"
#include "livingroom.h"

/*
int bedRoomTemp = 6;
int livingRoomTemp = 3;
int bell = 2;
*/

void setup()
{
  Serial.begin(115200);
  setup_wifi();

  // Configuración de MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  setupBathroom();
  setupBedroom();
  setupKitchen();
  setupLivingroom();

  client.setBufferSize(2048);
}

/*
void updateData()
{
  // Crear un objeto JSON
  String payload = "{";
  payload += "\"bedroomTemp\":" + String(bedRoomTemp) + ",";
  payload += "\"livingRoomTemp\":" + String(livingRoomTemp) + ",";
  payload += "\"bell\":" + String(bell);
  payload += "}";

  // Publicar el mensaje en el tópico MQTT
  client.publish("cesar", payload.c_str());
}
*/

void loop()
{
  static unsigned long lastTemperatureUpdate = 0;
  unsigned long now = millis();
    
    if (now - lastTemperatureUpdate >= 1000) { // Enviar temperatura cada segundo
        sendTemperatureBed(client);
        lastTemperatureUpdate = now;
    }

    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}