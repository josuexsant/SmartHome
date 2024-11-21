#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h> 

#ifndef livingroom_h
#define livingroom_h

// Pines
// displayTV (pantalla) pinSDA = 21 pinSDK = 22 
#define lightLivingRoom 34 //Led
#define ONE_WIRE_BUS 12 //Dallas
OneWire wire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

Servo servoLiv;
const byte trigg = 13;  //Sensor proximidad
const byte echo = 18;   //Sensor proximidad
const byte motorLivA = 14;
const byte motorLivB = 15;
const byte enableCeilingLivingRoom = 26; //Motor
int airLivingRoom = 32; //Ventilador
const int servoDoor = 33; //Servo

//variables
int brightnessLiv = 0;  // Brillo inicial del LED (0-255)
bool ledStateLiv = false;
int ventiladorSpeedLiv = 0;      // Velocidad inicial del ventilador
int motorSpeedLiv = 0;    // Velocidad inicial del motor
bool ventiladorStateLiv = false;
bool motorStateLiv = false;
bool servoStateLiv = false; 

void setupLivingroom() {
  pinMode(lightLivingRoom, OUTPUT);
  pinMode(airLivingRoom, OUTPUT);
  pinMode(motorLivA, OUTPUT);
  pinMode(motorLivB, OUTPUT);
  pinMode(enableCeilingLivingRoom, OUTPUT);
  servoLiv.attach(servoDoor);
  servoLiv.write(0);

  ledcAttachPin(lightLivingRoom, 5); // Canal PWM led
  ledcSetup(5, 5000, 8);   
  ledcAttachPin(airLivingRoom, 6);   // Canal PWM ventilador
  ledcSetup(6, 5000, 8);         
  ledcAttachPin(enableCeilingLivingRoom, 7); // Canal PWM motor
  ledcSetup(7, 5000, 8); 

  // Configuración del display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();                       
}

// Funciones para controlar el LED
void ledBrightnessLiv(int value) {
  brightnessLiv = constrain(value, 0, 255); // Asegurar que el brillo esté entre 0 y 255
  ledcWrite(5, brightnessLiv);
}

void ledOnLiv() {
  ledStateLiv = true;
  ledBrightnessLiv(brightnessLiv); // Aplicar el brillo actual
}

void ledOffLiv() {
  ledStateLiv = false;
  ledBrightnessLiv(0); // Apagar el LED
}

// Funciones para controlar el ventilador
void ventiladorLiv(int value) {
  ventiladorSpeedLiv = constrain(value, 0, 255); // Asegurar que la velocidad esté entre 0 y 255
  ledcWrite(6, ventiladorSpeedLiv);             // Canal PWM para el ventilador
}

void ventiladorOnLiv() {
  ventiladorStateLiv = true;
  ventiladorLiv(ventiladorSpeedLiv); // Aplicar la velocidad actual
}

void ventiladorOffLiv() {
  ventiladorStateLiv = false;
  ventiladorLiv(0); // Apagar el ventilador
}

// Funciones para controlar el motor
void motorLiv(int value) {
  motorSpeedLiv = constrain(value, 0, 255); // Asegurar que la velocidad esté entre 0 y 255
  ledcWrite(7, motorSpeedLiv);              // Canal PWM para el motor
}

void motorOnLiv() {
  motorStateLiv = true;
  motorLiv(motorSpeedLiv); // Aplicar la velocidad actual
}

void motorOffLiv() {
  motorStateLiv = false;
  motorLiv(0); // Apagar el motor
}

void sendTemperatureLiv(PubSubClient& client) {
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);
    String temperatureMsg = "{\"temperature\":" + String(temperature) + "}";
    client.publish("cesar", temperatureMsg.c_str());
}

void servoDoorLiv(bool state) {
  servoStateLiv = state;
  if (servoStateLiv) {
    servoLiv.write(90); 
  } else {
    servoLiv.write(0);  
  }
}

void tvOn() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Pantalla Encendida!");
  display.display();
}

void tvOff() {
  display.clearDisplay(); // Limpia la pantalla
  display.display();      // Actualiza la pantalla para reflejar el cambio
  display.ssd1306_command(SSD1306_DISPLAYOFF); // Apaga la pantalla físicamente
}

void checkBell(PubSubClient& client) {
  long duration;
  int distance;

  // Generar un pulso en el pin TRIG
  digitalWrite(trigg, LOW);
  delayMicroseconds(2);
  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigg, LOW);

  // Leer el tiempo que tarda el pulso en el pin ECHO
  duration = pulseIn(echo, HIGH);

  // Calcular la distancia en centímetros
  distance = duration * 0.034 / 2;

  // Si la distancia es menor o igual a 25 cm, enviar un mensaje
  if (distance <= 25) {
    String message = "{\"alert\":\"Hay alguien afuera de tu casa\"}";
    client.publish("cesar", message.c_str());
  }
}

#endif