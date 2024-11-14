#include <Arduino.h>
#include "conexion.h"

// Asignación de pines de la ESP32
int lightBedroom = 2; //Led
int ceilingBedroom = 0; //Motor
int sensorBedroom = 12; //Dallas
int airBedroom = 0; //Ventilador
int lightBathroom = 13; //Led
int servoBathroom =0 ; //Servo
int lightKitchen = 14;  //Led
int servoKitchen = 0; //Servo
int lightLivingRoom = 0; //Led
int ceilingLivingRoom = 0; //Motor
int sensorLivingRoom = 12; //Dallas
int airLivingRoom = 0; //Ventilador
int displayTV = 0; //Pantalla
int servoDoor = 0; //Servo
int sensorBell = 0; // Sensor proximidad

// Asignacion memoria para los sensores
int bedRoomTemp = 6;
int livingRoomTemp = 3;
int bell = 2;

void setup()
{
  Serial.begin(115200);
  setup_wifi();

  // Configuración de MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

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

void loop()
{
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  if (now - lastUpdate >= 1000) {
    updateData();
    lastUpdate = now;
  }
  // Reconectar si se desconecta de MQTT
  if (!client.connected())
  {
    reconnect();
  }
  client.loop(); // Procesar mensajes MQTT
}
