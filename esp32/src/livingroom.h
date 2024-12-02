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
// displayTV (pantalla) pinSDA = 21 pinSCK = 22 
#define lightLivingRoom 19 //Led
#define ONE_WIRE_BUS 13 //Dallas
OneWire wire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

Servo servoLiv;
const byte trigg = 23;  //Sensor proximidad
const byte echo = 25;   //Sensor proximidad
const byte motorLivA = 14;
const byte motorLivB = 15;
const byte enableCeilingLivingRoom = 26; //Motor
int airLivingRoom = 32; //Ventilador
const int servoDoor = 4; //Servo

//variables
int brightnessLiv = 120;  // Brillo inicial del LED (0-255)
bool ledStateLiv = false;
int ventiladorSpeedLiv = 0;      // Velocidad inicial del ventilador
byte motorSpeedLiv = 0;    // Velocidad inicial del motor
bool ventiladorStateLiv = false;
bool motorStateLiv = false;
bool servoStateLiv = false; 
bool tvState = false;
int volumen = 0;

void tvOn() {
  // Ojos
  display.drawCircle(48, 32, 10, WHITE);   // Lente izquierdo
  display.fillCircle(48, 32, 5, WHITE);    // Pupila izquierda
  display.drawCircle(80, 32, 10, WHITE);   // Lente derecho
  display.fillCircle(80, 32, 5, WHITE);    // Pupila derecha

  // Banda de las gafas
  display.drawLine(20, 32, 106, 32, WHITE); // Banda de las gafas

  // Boca usando líneas
  display.drawLine(54, 48, 74, 48, WHITE); // Línea superior de la boca
  display.drawLine(54, 48, 50, 52, WHITE); // Lado izquierdo de la boca
  display.drawLine(74, 48, 78, 52, WHITE); // Lado derecho de la boca

  // Contorno de la cara
  display.drawRoundRect(30, 20, 68, 48, 10, WHITE); // Contorno redondeado

  display.display();
}

void setupLivingroom() {
  Serial.begin(115200);
  
  pinMode(lightLivingRoom, OUTPUT);
  pinMode(airLivingRoom, OUTPUT);
  pinMode(motorLivA, OUTPUT);
  pinMode(motorLivB, OUTPUT);
  pinMode(enableCeilingLivingRoom, OUTPUT);
  pinMode(trigg, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigg, LOW);
  servoLiv.attach(servoDoor);
  servoLiv.write(0);
   
  ledcAttachPin(lightLivingRoom,4);   // Canal PWM led
  ledcSetup(4, 5000, 8); 
  ledcAttachPin(airLivingRoom, 7);   // Canal PWM ventilador
  ledcSetup(7, 5000, 8);         
  ledcAttachPin(enableCeilingLivingRoom, 8); // Canal PWM motor
  ledcSetup(8, 5000, 8); 
  ledcWrite(8, motorSpeedLiv);

  // Configuración del display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();                       
}

// Funciones para controlar el LED

void ledBrightnessLiv(int value) {
  brightnessLiv = constrain(value, 0, 255); // Asegurar que el brillo esté entre 0 y 255
  ledcWrite(4, brightnessLiv);
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
  ledcWrite(7, ventiladorSpeedLiv);             // Canal PWM para el ventilador
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
void motorLiv(bool sentido, byte value){
  if (sentido) { // Avanzar
    digitalWrite(motorLivA, HIGH);
    digitalWrite(motorLivB, LOW);
    ledcWrite(8, value); 
  } else { // Detener
    digitalWrite(motorLivA, LOW);
    digitalWrite(motorLivB, LOW);
    ledcWrite(8, value); 
  }
}

float getTemperatureLiv() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}

void servoDoorLivOn() {
  servoStateLiv = true;
  servoLiv.write(90);
}

void servoDoorLivOff() {
  servoStateLiv = false;
  servoLiv.write(0);
}

void tvOff() {
  display.clearDisplay(); // Limpia la pantalla
  display.display();      // Actualiza la pantalla para reflejar el cambio
}

void pulso() {
  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigg, LOW);
}

int checkBell() {
  pulso();
  long duration;
  int distance;
  static int lastState = 0;

  // Leer el tiempo que tarda el pulso en el pin ECHO
  duration = pulseIn(echo, HIGH);
  // Calcular la distancia en centímetros
  distance = duration / 58;

  // Si la distancia es menor o igual a 15 cm, retorna 1 (alguien está cerca)
  if (distance <= 25) {
      lastState = 1;
  } else {
      lastState = 0;
  }
  return lastState;
}

#endif