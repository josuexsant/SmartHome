#include <Arduino.h>
#include <ESP32Servo.h>

#ifndef kitchen_h
#define kitchen_h

//Pines
Servo servoKit;
#define lightKitchen 16 //Led
const int servoKitchen = 27; //Servo

//variables
int brightnessKit = 0;  
bool ledStateKit = false;
bool servoStateKit = false; 

void setupKitchen() {
  pinMode(lightKitchen, OUTPUT);
  ledcAttachPin(lightKitchen, 4); // Canal para PWM
  ledcSetup(4, 5000, 8);           // Frecuencia, resolución
  servoKit.attach(servoKitchen);
  servoKit.write(0);                  
}

// Funciones para controlar el LED
void ledBrightnessKit(int value) {
  brightnessKit = constrain(value, 0, 255); // Asegurar que el brillo esté entre 0 y 255
  ledcWrite(4, brightnessKit);
}

void ledOnKit() {
  ledStateKit = true;
  ledBrightnessKit(brightnessKit); // Aplicar el brillo actual
}

void ledOffKit() {
  ledStateKit = false;
  ledBrightnessKit(0); // Apagar el LED
}

void servoGasKit(bool state) {
  servoStateKit = state;
  if (servoStateKit) {
    servoKit.write(90); 
  } else {
    servoKit.write(0);  
  }
}

#endif