#include <Arduino.h>
#include "bathroom.h"
#include "conexion.h"
#include "bedroom.h"
#include "kitchen.h"
#include "livingroom.h"

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
  
  if (tvState) {
    tvOn();
  } else {
    tvOff();
  }
  
  client.setBufferSize(2048);

}

// Crear el mensaje JSON
String createJsonMessage(float bedroomTemp, float livingRoomTemp, int bellState) {
    String message = "{";
    message += "\"bedroomTemp\":" + String(bedroomTemp) + ",";
    message += "\"livingRoomTemp\":" + String(livingRoomTemp) + ",";
    message += "\"bell\":" + String(bellState);
    message += "}";
    return message;
}

void sendCombinedMessage(PubSubClient& client) {
    float bedroomTemp = getTemperatureBed();
    float livingRoomTemp = getTemperatureLiv();
    int bellState = checkBell();

    String message = createJsonMessage(bedroomTemp, livingRoomTemp, bellState);
    client.publish("yuli", message.c_str());
}


void loop()
{
  static unsigned long lastTemperatureUpdate = 0;
  unsigned long now = millis();
    
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();

  if (now - lastTemperatureUpdate >= 1000) { // Enviar mensaje cada segundo
    sendCombinedMessage(client);
    lastTemperatureUpdate = now;
  }
  
  // Funciones Bathroom
  if (ledStateBat) {
    ledOnBat();
  } else {
    ledOffBat();
  }

  if (servoStateBat) {
    servoWaterBatOn(); 
  } else {
    servoWaterBatOff(); 
  }

  // Funciones Bedroom
  if (ledStateBed) {
    ledOnBed();
  } else {
    ledOffBed();
  }

  if (ventiladorStateBed) {
    ventiladorOnBed();
  } else {
    ventiladorOffBed();
  }

  if (motorStateBed) {
    motorOnBed();
  } else {
    motorOffBed();
  }

  // Funciones Kitchen
  if (ledStateKit) {
    ledOnKit();
  } else {
    ledOffKit();
  }

  if (servoStateKit) {
    servoGasKitOn(); 
  } else {
    servoGasKitOff(); 
  }

  // Funciones Livingroom
  if (ledStateLiv) {
    ledOnLiv();
  } else {
    ledOffLiv();
  }

  if (ventiladorStateLiv) {
    ventiladorOnLiv();
  } else {
    ventiladorOffLiv();
  }

  if (motorStateLiv) {
    motorLiv(true, motorSpeedLiv);
  } else {
    motorLiv(false, 0);
  }

  if (servoStateLiv) {
    servoDoorLivOn(); 
  } else {
    servoDoorLivOff(); 
  }

}