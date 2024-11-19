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
  Serial.print("Mensaje recibido bajo el tópico -> ");
  Serial.println(topic);

  Serial.print("Mensaje: ");

  // Convertir el payload a una cadena
  String json;
  for (int i = 0; i < length; i++)
  {
    json += (char)payload[i];
  }
  
  Serial.println(json); // Mostrar el mensaje completo recibido en el monitor serial

  // Parse JSON
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, json);

  if (error)
  {
    Serial.print("Error al parsear JSON: ");
    Serial.println(error.c_str());
    return;
  }

  // Print parsed JSON
  for (JsonObject room : doc.as<JsonArray>())
  {
    Serial.print("Habitación: ");
    Serial.println(room["name"].as<const char *>());

    if (room.containsKey("light"))
    {
      Serial.print("  Luz encendida: ");
      Serial.println(room["light"]["on"].as<bool>());
      Serial.print("  Valor de luz: ");
      Serial.println(room["light"]["value"].as<int>());
    }

    if (room.containsKey("temperature"))
    {
      Serial.print("  Temperatura: ");
      Serial.println(room["temperature"].as<int>());
    }

    if (room.containsKey("air"))
    {
      Serial.print("  Aire encendido: ");
      Serial.println(room["air"]["on"].as<bool>());
      Serial.print("  Valor de aire: ");
      Serial.println(room["air"]["value"].as<int>());
    }

    if (room.containsKey("waterService"))
    {
      Serial.print("  Servicio de agua: ");
      Serial.println(room["waterService"].as<bool>());
    }

    if (room.containsKey("gasService"))
    {
      Serial.print("  Servicio de gas: ");
      Serial.println(room["gasService"].as<bool>());
    }

    if (room.containsKey("tv"))
    {
      Serial.print("  TV encendida: ");
      Serial.println(room["tv"]["on"].as<bool>());
      Serial.print("  Temporizador de TV: ");
      Serial.println(room["tv"]["timer"].as<int>());
    }

    if (room.containsKey("door"))
    {
      Serial.print("  Puerta abierta: ");
      Serial.println(room["door"]["open"].as<bool>());
      Serial.print("  Contraseña de puerta: ");
      Serial.println(room["door"]["password"].as<int>());
    }

    if (room.containsKey("bell"))
    {
      Serial.print("  Timbre encendido: ");
      Serial.println(room["bell"]["on"].as<bool>());
      Serial.print("  Valor de timbre: ");
      Serial.println(room["bell"]["value"].as<int>());
    }

    Serial.println();
  }

  // Enviar mensaje al tópico 'yuli' con los datos recibidos
  client.publish("yuli", json.c_str());
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
