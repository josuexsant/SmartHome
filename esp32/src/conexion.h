#include <ArduinoJson.h>
#include <Arduino.h>
#include <PubSubClient.h> //Libreria del servidor MQTT
#include <WiFi.h>
#include "bathroom.h"
#include "bedroom.h"
#include "kitchen.h"
#include "livingroom.h"

#ifndef conexion_h
#define conexion_h

//const char *ssid = "Totalplay-639A";
//const char *password = "639A4C757nJn8HAk";
const char *ssid = "BUAP_Estudiantes";
const char *password = "f85ac21de4";
const char *mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char *mqtt_user = "";
const char *mqtt_pass = "";

WiFiClient espClient;
PubSubClient client(espClient); // Instancia de la librería MQTT

long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensaje recibido bajo el tópico -> ");
  Serial.println(topic);

  // Convertir payload a string
  String json;
  for (int i = 0; i < length; i++)
  {
    json += (char)payload[i];
  }

  Serial.print("Contenido del mensaje: ");
  Serial.println(json);

  // Parsear JSON como array
  StaticJsonDocument<2048> doc; // Aumenta el tamaño si el JSON es grande
  DeserializationError error = deserializeJson(doc, json);

  if (error)
  {
    Serial.print("Error al parsear JSON: ");
    Serial.println(error.c_str());
    return;
  }

  // Verificar si el documento es un array
  if (!doc.is<JsonArray>())
  {
    Serial.println("El mensaje recibido no es un array JSON.");
    return;
  }

  JsonArray array = doc.as<JsonArray>();

  // Iterar sobre cada objeto en el array
  for (JsonObject obj : array)
  {
    const char *roomName = obj["name"];

    if (strcmp(roomName, "bedroom") == 0)
    {
      Serial.println("....... DORMITORIO .......");

      // Control de la luz
      if (obj.containsKey("light"))
      {
        bool lightOn = obj["light"]["on"];
        int lightValue = obj["light"]["value"].as<int>();
        
        if (lightOn)
        {
          ledBrightnessBed(lightValue); // Ajustar brillo
          ledOnBed();
          Serial.println("Luz encendida.");
        }
        else
        {
          ledOffBed();
          Serial.println("Luz apagada.");
        }
      }

      // Control del ventilador
      if (obj.containsKey("air"))
      {
        bool airOn = obj["air"]["on"];
        int airValue = obj["air"]["value"].as<int>();

        if (airOn)
        {
          ventiladorBed(airValue);
          ventiladorOnBed();
          Serial.println("Aire acondicionado prendido.");
        }
        else
        {
          ventiladorOffBed();
          Serial.println("Aire acondicionado apagado.");
        }
      }

      // Control del motor
      if (obj.containsKey("ceilingFan"))
      {
        bool motorOnValue = obj["ceilingFan"]["on"];
        int motorValue = obj["ceilingFan"]["value"].as<int>();

        if (motorOnValue)
        {
          motorBed(motorValue);
          motorOnBed();
          Serial.println("Ventilador prendido");
        }
        else
        {
          motorOffBed();
          Serial.println("Ventilador apagado.");
        }
      }
    }

    else if (strcmp(roomName, "bathroom") == 0)
    {
      Serial.println("........ BAÑO ............");

      // Control de la luz
      if (obj.containsKey("light"))
      {
        bool lightOn = obj["light"]["on"];
        int lightValue = obj["light"]["value"].as<int>();

        if (lightOn)
        {
          ledBrightnessBat(lightValue); // Ajustar brillo para el baño
          ledOnBat();
          Serial.println("Luz encendida.");
        }
        else
        {
          ledOffBat();
          Serial.println("Luz apagada.");
        }
      }

      // Servicio de agua waterService
      if (obj.containsKey("waterService")){
        bool servoService = obj["waterService"]["on"].as<bool>();

        if (servoService){
          servoWaterBatOn(); // Activar servicio de agua
          Serial.println("Servicio de agua activado.");
        }
        else {
          servoWaterBatOff(); // Desactivar servicio de agua
          Serial.println("Servicio de agua desactivado.");
        }
      }
    }

    else if (strcmp(roomName, "kitchen") == 0)
    {
      Serial.println("........ COCINA ...........");

      // Control de la luz
      if (obj.containsKey("light"))
      {
        bool lightOn = obj["light"]["on"];
        int lightValue = obj["light"]["value"].as<int>();

        if (lightOn)
        {
          ledBrightnessKit(lightValue); // Ajustar brillo para el baño
          ledOnKit();
          Serial.println("Luz encendida.");
        }
        else
        {
          ledOffKit();
          Serial.println("Luz apagada.");
        }
      }

      // Servicio de gas
      if (obj.containsKey("gasService")){
        bool servoServiceGas = obj["gasService"]["on"].as<bool>();

        if (servoServiceGas)
        {
          servoGasKitOn();
          Serial.println("Servicio de gas activado.");
        }
        else
        {
          servoGasKitOff(); 
          Serial.println("Servicio de gas desactivado.");
        }
      }
    }

    else if (strcmp(roomName, "livingRoom") == 0)
    {
      Serial.println("....... SALA ..........");

      // Control de la luz
      if (obj.containsKey("light"))
      {
        bool lightOn = obj["light"]["on"];
        int lightValue = obj["light"]["value"].as<int>();
        
        if (lightOn)
        {
          ledBrightnessLiv(lightValue); // Ajustar brillo
          ledOnLiv();
          Serial.println("Luz encendida.");
        }
        else
        {
          ledOffLiv();
          Serial.println("Luz apagada.");
        }
      }

      // Control del ventilador
      if (obj.containsKey("air"))
      {
        bool airOn = obj["air"]["on"];
        int airValue = obj["air"]["value"].as<int>();

        if (airOn)
        {
          ventiladorLiv(airValue);
          ventiladorOnLiv();
          Serial.println("Aire acondicionado encendido.");
        }
        else
        {
          ventiladorOffLiv();
          Serial.println("Aire acondicionado apagado.");
        }
      }

      // Control del motor
      if (obj.containsKey("ceilingFan"))
      {
        bool motorOnValue = obj["ceilingFan"]["on"];
        int motorValue = obj["ceilingFan"]["value"].as<int>();

        if (motorOnValue)
        {
          motorLiv(motorOnValue, motorValue);
          Serial.println("Ventilador encendido.");
        }
        else
        {
          motorLiv(motorOnValue, 0);
          Serial.println("Ventilador apagado.");
        }
      }

      // Puerta
      if (obj.containsKey("door")){
        bool servoServiceDoor = obj["door"]["open"].as<bool>();
        
        if (servoServiceDoor){
            servoDoorLivOn();
            Serial.println("Puerta abierta.");
        }
        else{
            servoDoorLivOff(); 
            Serial.println("Puerta cerrada.");
          }
      
      }
    
      // Timbre
      if (obj.containsKey("tv")){
      bool tvOnLive = obj["tv"]["on"];
      int value = obj["tv"]["timer"].as<int>();
    
        if (tvOnLive)
        {
          tvOn();
          Serial.println("TV encendida.");
        }
        else
        {
          tvOff();
          Serial.println("TV apagada.");
        }
      }
    }

    else
    {
      Serial.print("Mensaje no dirigido a un área reconocida: ");
      Serial.println(roomName);
    }
  }
}


void setup_wifi()
{
  Serial.println();
  Serial.print("Conectando a -> ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Intentando conexion MQTT");

    String clientId = "yulis";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Conexion exitosa a MQTT");
      client.publish("yuli", "Mensaje");
      client.subscribe("cesar");
    }
    else
    {
      Serial.println("Fallo la conexion");
      Serial.println(client.state());
      Serial.println("Se intentara de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void send(String message)
{
  Serial.println("Mensaje enviado");
  client.publish("yuli", message.c_str());
}

#endif