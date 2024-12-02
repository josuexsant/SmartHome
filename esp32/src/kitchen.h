#include <Arduino.h>
#include <ESP32Servo.h>

#ifndef kitchen_h
#define kitchen_h

//Pines
Servo servoKit;
#define lightKitchen 18 //Led
const int servoKitchen = 27; //Servo

//variables
int brightnessKit = 0;  
bool ledStateKit = false;
bool servoStateKit = false; 

void setupKitchen() {
  Serial.begin(115200);
  pinMode(lightKitchen, OUTPUT);
  ledcAttachPin(lightKitchen, 3); // Canal para PWM
  ledcSetup(3, 5000, 8);           // Frecuencia, resolución
  servoKit.attach(servoKitchen);
  servoKit.write(0);                  
}

// Funciones para controlar el LED
void ledBrightnessKit(int value) {
  brightnessKit = constrain(value, 0, 255); // Asegurar que el brillo esté entre 0 y 255
  ledcWrite(3, brightnessKit);
}

void ledOnKit() {
  ledStateKit = true;
  ledBrightnessKit(brightnessKit); // Aplicar el brillo actual
}

void ledOffKit() {
  ledStateKit = false;
  ledBrightnessKit(0); // Apagar el LED
}

void servoGasKitOn() {
  servoStateKit = true;
  servoKit.write(90);
}

void servoGasKitOff() {
  servoStateKit = false;
  servoKit.write(0);
}

#endif