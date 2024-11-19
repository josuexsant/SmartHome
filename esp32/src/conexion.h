#ifndef conexion_h
#define conexion_h

#include <ArduinoJson.h>
#include <Arduino.h>
#include <PubSubClient.h> // Libreria del servidor MQTT
#include <WiFi.h>

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
  String message;
  for (unsigned int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }

  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, message);

  Serial.println("Mensaje recibido");
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
    Serial.println("Intentando conexión MQTT");

    String clientId = "cesar";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      client.subscribe("cesar");
    }
    else
    {
      Serial.println("Fallo la conexión");
      Serial.println(client.state());
      Serial.println("Se intentará de nuevo en 5 segundos");
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
